<?php

/**
 * @file
 * Declares our migrations.
 */

/**
 * Implements hook_migrate_api().
 */
function migrate_news_migrate_api() {
    $api = array(
        'api' => 2,
        'groups' => array(
            'news' => array(
                'title' => t('News Migrations'),
            ),
        ),
        'migrations' => array(
            'NewsArticle' => array(
                'class_name' => 'MigrateNewsArticleXMLMigration',
                'group_name' => 'news',
            ),
            'NewsTermCategoryMigration' => array(
                'class_name' => 'NewsTermCategoryMigration',
                'group_name' => 'news',
            ),
            'NewsTermSourceMigration' => array(
                'class_name' => 'NewsTermSourceMigration',
                'group_name' => 'news',
            ),
        ),
    );
    return $api;
}
