/*******************************************************************************
 * Copyright (c) 2022 CEA
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0.
 *
 * SPDX-License-Identifier: EPL-2.0
 * Contributors: see AUTHORS file
 *******************************************************************************/
package fr.cea.nablab.sirius.web.app.configuration;

import fr.cea.nablab.sirius.web.app.services.GraphQLWiringFactory;

import java.io.IOException;
import java.util.List;

import org.eclipse.sirius.components.graphql.api.IDataFetcherWithFieldCoordinates;
import org.eclipse.sirius.components.graphql.utils.types.UploadScalarType;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.core.io.Resource;
import org.springframework.core.io.support.ResourcePatternResolver;

import graphql.GraphQL;
import graphql.execution.AsyncExecutionStrategy;
import graphql.execution.AsyncSerialExecutionStrategy;
import graphql.execution.DataFetcherExceptionHandler;
import graphql.execution.ExecutionStrategy;
import graphql.schema.GraphQLCodeRegistry;
import graphql.schema.GraphQLSchema;
import graphql.schema.idl.RuntimeWiring;
import graphql.schema.idl.SchemaGenerator;
import graphql.schema.idl.SchemaParser;
import graphql.schema.idl.SchemaPrinter;
import graphql.schema.idl.SchemaPrinter.Options;
import graphql.schema.idl.TypeDefinitionRegistry;

/**
 * @author arichard
 */
@Configuration
public class GraphQLConfiguration {

    private final Logger logger = LoggerFactory.getLogger(GraphQLConfiguration.class);

    /**
     * Creates the GraphQL configuration used to execute GraphQL queries.
     *
     * @param codeRegistry
     *            The GraphQL code registry
     *
     * @return The GraphQL configuration
     */
    @Bean
    public GraphQL graphQL(GraphQLSchema graphQLSchema) {
        var options = Options.defaultOptions();
        String schema = new SchemaPrinter(options).print(graphQLSchema);

        this.logger.trace(schema);

        DataFetcherExceptionHandler exceptionHandler = new GraphQLDataFetcherExceptionHandler();
        ExecutionStrategy queryExecutionStrategy = new AsyncExecutionStrategy(exceptionHandler);
        // @see https://www.graphql-java.com/documentation/v11/execution/ The graphql specification says that mutations
        // MUST be executed serially and in the order in which the query fields occur.
        ExecutionStrategy mutationExecutionStrategy = new AsyncSerialExecutionStrategy(exceptionHandler);
        // @formatter:off
        return GraphQL.newGraphQL(graphQLSchema)
                .queryExecutionStrategy(queryExecutionStrategy)
                .mutationExecutionStrategy(mutationExecutionStrategy)
                .build();
        // @formatter:on
    }

    @Bean
    public GraphQLSchema graphQLSchema(ResourcePatternResolver resourcePatternResolver, GraphQLWiringFactory graphQLWiringFactory,
            List<IDataFetcherWithFieldCoordinates<?>> dataFetchersWithCoordinates) {
        GraphQLCodeRegistry.Builder builder = GraphQLCodeRegistry.newCodeRegistry();
        dataFetchersWithCoordinates.forEach(dataFetcherWithCoordinates -> {
            dataFetcherWithCoordinates.getFieldCoordinates().forEach(fieldCoordinates -> builder.dataFetcher(fieldCoordinates, dataFetcherWithCoordinates));
        });
        var graphQLCodeRegistry = builder.build();

        try {
            TypeDefinitionRegistry typeRegistry = new TypeDefinitionRegistry();

            SchemaParser schemaParser = new SchemaParser();
            SchemaGenerator schemaGenerator = new SchemaGenerator();

            Resource[] resources = resourcePatternResolver.getResources("classpath*:/schema/**/*.graphqls"); //$NON-NLS-1$
            this.logger.info("{} GraphQL schemas found", resources.length); //$NON-NLS-1$
            for (Resource resource : resources) {
                if (this.logger.isInfoEnabled()) {
                    this.logger.info("Processing the GraphQL schema: {}", resource.getURL()); //$NON-NLS-1$
                }
                TypeDefinitionRegistry childTypeDefinitionRegistry = schemaParser.parse(resource.getInputStream());
                typeRegistry.merge(childTypeDefinitionRegistry);
            }

            // @formatter:off
            var runtimeWiring = RuntimeWiring.newRuntimeWiring()
                    .codeRegistry(graphQLCodeRegistry)
                    .wiringFactory(graphQLWiringFactory)
                    .scalar(UploadScalarType.INSTANCE)
                    .build();
            // @formatter:on

            GraphQLSchema graphQLSchema = schemaGenerator.makeExecutableSchema(typeRegistry, runtimeWiring);
            return graphQLSchema;
        } catch (IOException exception) {
            this.logger.warn(exception.getMessage(), exception);
        }
        return null;
    }
}
