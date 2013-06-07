delete from command where name = "blink";
insert into command (name, security, help) values ("blink",2,"Teleport you a few meters ahead (5 by default).\n\nSyntax: .blink [#distance]");