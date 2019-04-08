<?php

/**
 * @file
 *  migration news. 
 *
 */

/**

 * Abstract intermediate class holding common settings.
 */
class MigrateNewsArticleXMLMigration extends XMLMigration {

    public function __construct($arguments) {
        parent::__construct($arguments);
        $this->description = t('XML feed for news of NDTV Top-stories');

        $items_url = 'http://feeds.feedburner.com/ndtvnews-top-stories.xml';

        $item_xpath = '/rss/channel/item';
        $item_ID_xpath = 'guid';

        $fields = array(
            'title' => t('title'),
            'description' => t('Description of producer'),
            'link' => t('link'),
            'category' => t('category'),
            'source' => t('source'),
            'pubDate' => t('pubDate'),
            'updatedAt' => t('updatedAt'),
        );

        $items_class = new MigrateItemsXML($items_url, $item_xpath, $item_ID_xpath);
        $this->source = new MigrateSourceMultiItems($items_class, $fields);

        $this->destination = new MigrateDestinationNode('article');

        $this->map = new MigrateSQLMap($this->machineName, array(
            'guid' => array(
                'type' => 'varchar',
                'length' => 40,
                'not null' => TRUE,
            ),
                ), MigrateDestinationNode::getKeySchema()
        );

        // Mapped fields
        $this->addFieldMapping('title', 'title')
                ->xpath('title')
                ->description(t('Mapping news title in source to node title'));

        // Mapped fields
        $this->addFieldMapping('body', 'description')
                ->xpath('description')
                ->description(t('Mapping news description in source to node body'));

        $this->addFieldMapping('field_news_link', 'link')
                ->xpath('link')
                ->description(t('Mapping news link in source to node body'));

        $this->addFieldMapping('migrate_news_category', 'category')
                ->xpath('category')
                ->description(t('Mapping news category in source to node body'));

        $this->addFieldMapping('migrate_news_source', 'source')
                ->xpath('source')
                ->description(t('Mapping news source in source to node body'));

        $this->addFieldMapping('created', 'pubDate')
                ->xpath('pubDate')
                ->description(t('Mapping lastBuildDate in source to node created date'));

        $this->addFieldMapping('changed', 'updatedAt')
                ->xpath('updatedAt')
                ->description(t('Mapping lastBuildDate in source to node created date'));

        $destination_fields = $this->destination->fields();
        if (isset($destination_fields['path'])) {
            $this->addFieldMapping('path')
                    ->issueGroup(t('DNM'));
            if (isset($destination_fields['pathauto'])) {
                $this->addFieldMapping('pathauto')
                        ->issueGroup(t('DNM'));
            }
        }
    }

}

class NewsTermCategoryMigration extends Migration {

    public function __construct($arguments) {
        parent::__construct($arguments);

        $this->description = t('Migrate styles from the source database to taxonomy terms');

        $items_url = 'http://feeds.feedburner.com/ndtvnews-top-stories.xml';


        $item_xpath = '/rss/channel/item';
        $item_ID_xpath = 'category';

        $fields = array(
            'category' => t('category'),
        );

        $items_class = new MigrateItemsXML($items_url, $item_xpath, $item_ID_xpath);
        $this->source = new MigrateSourceMultiItems($items_class, $fields);


        $this->destination = new MigrateDestinationTerm('migrate_news_category');

        $this->map = new MigrateSQLMap($this->machineName, array(
            'category' => array(
                'type' => 'varchar',
                'length' => 40,
                'not null' => TRUE,
            ),
                ), MigrateDestinationTerm::getKeySchema()
        );


        $this->addFieldMapping('name', 'category');
        $destination_fields = $this->destination->fields();
    }

}

class NewsTermSourceMigration extends Migration {

    public function __construct($arguments) {
        parent::__construct($arguments);

        $this->description = t('Migrate styles from the source database to taxonomy terms');

        $items_url = 'http://feeds.feedburner.com/ndtvnews-top-stories.xml';

        $item_xpath = '/rss/channel/item';
        $item_ID_xpath = 'source';

        $fields = array(
            'source' => t('source'),
        );

        $items_class = new MigrateItemsXML($items_url, $item_xpath, $item_ID_xpath);
        $this->source = new MigrateSourceMultiItems($items_class, $fields);


        $this->destination = new MigrateDestinationTerm('migrate_news_source');

        $this->map = new MigrateSQLMap($this->machineName, array(
            'source' => array(
                'type' => 'varchar',
                'length' => 40,
                'not null' => TRUE,
            ),
                ), MigrateDestinationTerm::getKeySchema()
        );

        $this->addFieldMapping('name', 'source');

        $destination_fields = $this->destination->fields();
    }

}
