CREATE TABLE `rooms_newbie` (
  `id` int(11) NOT NULL,
  `model` varchar(150) NOT NULL,
  `decoration` varchar(150) NOT NULL,
  `items` longtext NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

ALTER TABLE `rooms_newbie`
  ADD UNIQUE KEY `id` (`id`);

  
ALTER TABLE `rooms_newbie`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT;