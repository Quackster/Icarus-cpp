ALTER TABLE `users` ADD `has_logged_in` TINYINT(1) NOT NULL DEFAULT '0' AFTER `credits`;