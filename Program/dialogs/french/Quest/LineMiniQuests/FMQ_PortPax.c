// Addon-2016 Jason, французские миниквесты (ФМК) Порт-о-Пренс
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Un bug évident. Informez-en les développeurs.";
			link.l1 = "Oh, je le ferai.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "officer":
			PlaySound("Voice\English\z_arest_02.wav");
			dialog.text = "Que diable se passe-t-il ici, messieurs ? J'ai entendu des combats.";
			link.l1 = "Bonjour officier, j'ai entendu une femme crier et...";
			link.l1.go = "officer_1";
		break;
		
		case "officer_1":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "officer_2":
			dialog.text = "";
			link.l1 = ""+GetFullName(pchar)+". Capitaine "+GetFullName(pchar)+".";
			link.l1.go = "officer_3";
		break;
		
		case "officer_3":
			dialog.text = "Vous êtes libre de partir pour l'instant, capitaine. Je vois ce qui s'est passé ici, nous vous convoquerons si nous avons des questions.";
			link.l1 = "Très bien...";
			link.l1.go = "officer_4";
		break;
		
		case "officer_4":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			sld.Dialog.currentnode = "noble_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "officer_5":
			PlaySound("Voice\English\z_arest_02.wav");
			dialog.text = "Que diable se passe-t-il ici, messieurs ? J'ai entendu des combats.";
			link.l1 = "Merci, officier, j'ai entendu une femme crier à l'aide et j'ai vu ce gentilhomme attaqué par deux vauriens. J'ai essayé de sauver le pauvre homme mais, hélas, j'étais trop tard. Les salauds l'ont tué !";
			link.l1.go = "officer_6";
		break;
		
		case "officer_6":
			dialog.text = "Que le Diable m'emporte... C'est un Espagnol ! Que ferait-il ici ? Hm. Et qui êtes-vous alors, monsieur ?";
			link.l1 = ""+GetFullName(pchar)+". Capitaine "+GetFullName(pchar)+".";
			link.l1.go = "officer_7";
		break;
		
		case "officer_7":
			dialog.text = "Capitaine, vous êtes libre de partir pour l'instant. Vos paroles correspondent à celles du témoin. Nous vous appellerons si besoin est.";
			link.l1 = "Très bien...";
			link.l1.go = "officer_8";
		break;
		
		case "officer_8":
			DialogExit();
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
		break;
		
		case "noble":
			dialog.text = "Permettez-moi de tout vous expliquer, señor ! Je m'appelle Don Domingo Ortiz Albalate de Saint-Domingue. Je suis venu à Port-au-Prince sur l'invitation d'une jeune señorita et j'ai fait une halte dans cette taverne en attendant le rendez-vous prévu. Alors que je m'occupais de mes affaires, j'ai été attaqué par ces deux maudits voleurs. Je serais en train de dîner avec les anges en ce moment si ce n'était pas pour ce Bon Samaritain qui est passé par là.";
			link.l1 = "Don Domingo Ortiz Albalate? Vous êtes espagnol?";
			link.l1.go = "noble_1";
		break;
		
		case "noble_1":
			dialog.text = "Aussi espagnol que le roi Felipe lui-même, ha ! Je voudrais également souligner que mes papiers sont en buen orden. Je suis noble d'Espagne, pas un pirata sucia !";
			link.l1 = "Don Domingo, nos plus sincères excuses pour cet incident malheureux ! Veuillez nous accompagner pour quelques questions et une bouteille de vin à la garnison. Nous nous occuperons de tout. Quant à vous...";
			link.l1.go = "noble_2";
		break;
		
		case "noble_2":
			DialogExit();
			sld = CharacterFromID("FMQP_off");
			sld.Dialog.currentnode = "officer_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "noble_3":
			PlaySound("Voice\English\LE\Domingo\Domingo_01.wav");
			dialog.text = "Señor Capitan ! Señor Capitan ! Je jure par Santiago et la Bienheureuse Vierge que vous êtes un homme noble, et un véritable fils de Castille récompense toujours une telle noblesse ! J'aimerais vous voir récompensé plus tard lorsque j'aurai terminé mes affaires ici. S'il vous plaît, honorez-moi par une visite à ma modeste demeure à Saint-Domingue ! C'est près des portes de la ville. Je préparerai un festin pour vous, mon buen caballero Carlos ! Souvenez-vous de mon nom, c'est Don Domingo Ortiz Albalate !";
			link.l1 = "...";
			link.l1.go = "noble_4";
		break;
		
		case "noble_4":
			DialogExit();
			AddMapQuestMarkCity("santodomingo", true);
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "FMQP_AfterFightInTown");
		break;
		
		case "noble_5":
			dialog.text = "Capitaine "+GetFullName(pchar)+"?! Oh Madre de Dios ! Quel désastre ! C'est un massacre ! Que s'est-il passé ici, buen amigo ? Qui sont ces hommes ?";
			link.l1 = "Heureux de vous voir, Don Domingo. Ce sont... Je suis venu ici pour vous rendre visite. Vous voyez ce gars là-bas? C'est Ugo, votre serviteur et il...";
			link.l1.go = "noble_6";
		break;
		
		case "noble_6":
			dialog.text = "Ugo ?! Oh, non, vous avez été dupé, capitaine !";
			link.l1 = "Je vois, cela semble m'arriver souvent. Trois vauriens ont fait irruption chez vous, ont assassiné votre fidèle homme Ugo - j'ai trouvé son cadavre déjà à l'étage - puis vous ont tendu une embuscade. Mon arrivée n'était pas prévue dans leur plan. Ils n'ont pas survécu à notre rencontre.";
			link.l1.go = "noble_7";
		break;
		
		case "noble_7":
			dialog.text = "Sainte Marie, priez pour nous! Vous maniez votre épée comme les maîtres d'escrime de Tolède! C'est bien que vous soyez de mon côté! Oh, mon pauvre Ugo! Il m'a élevé depuis que j'étais enfant et maintenant... être assassiné par ces maudits canailles!";
			link.l1 = "Don Domingo, il semble que vous n'êtes pas encore hors de danger. Votre homme Ugo savait quelque chose, lisez cette note. Je l'ai trouvée sur une table.";
			link.l1.go = "noble_8";
		break;
		
		case "noble_8":
			ChangeItemDescribe("letter_parol", "itmdescr_letter_parol");
			RemoveItems(pchar, "letter_parol", 1);
			dialog.text = "Donne-le-moi... (lisant) Cela ne peut pas être... oh, non ! C'est incroyable ! Tio Luis... Mais...";
			link.l1 = "Un indice sur qui a fait ça ?";
			link.l1.go = "noble_9";
		break;
		
		case "noble_9":
			dialog.text = "Seulement des soupçons... d'affreux soupçons mi amigo ! Comment le frère de ma mère pourrait-il faire une telle chose ?";
			link.l1 = "Pourriez-vous m'en dire plus ? Je suis désolé, Don Domingo, mais d'après mon expérience, les proches sont souvent les pires ennemis qu'un homme puisse avoir...";
			link.l1.go = "noble_10";
		break;
		
		case "noble_10":
			dialog.text = "Si, tu as raison, Carlos ! Je te dirai tout ! Tu m'as déjà sauvé deux fois et il semble que tu sois le seul homme en qui je puisse avoir confiance en ce moment ! Mais quittons cet endroit horrible, il me rend malade. Je dois informer l'alcalde de ce bazar, ils prendront soin du pauvre Ugo. Que dirais-tu de boire un peu de vin dans la taberna locale pour calmer nos nerfs ?";
			link.l1 = "Vos nerfs en ont certainement plus besoin que les miens, montrez le chemin, señor !";
			link.l1.go = "noble_11";
		break;
		
		case "noble_11":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Santodomingo_tavern", "sit", "sit_base2", "FMQP_InSantoDomingoTavern");
		break;
		
		case "noble_12":
			LAi_SetSitType(pchar);
			dialog.text = "Alors, mon ami, permets-moi de te raconter une... version abrégée de l'histoire de ma famille. Ma mère, Dona Isabella Ortiz, épousa mon père, le Marquis Ricardo Albalate, et prit son nom de famille selon la coutume. Son frère, Luis Ortiz, était commandant de garnison dans les colonies, mais après le mariage de ma mère, il fut nommé par mon père comme gestionnaire d'une plantation de sucre non loin de Portobello. C'était une immense et riche plantation, très rentable en vérité. Après la mort tragique de mes parents en mer il y a quelques années, j'ai hérité de tout en tant que leur fils unique, y compris la plantation. Mon oncle a conservé son poste et j'étais assez satisfait du loyer qu'il me payait. Il était toujours à l'heure avec ses paiements.";
			link.l1 = "Alors tu penses que ton oncle...";
			link.l1.go = "noble_13";
		break;
		
		case "noble_13":
			dialog.text = "Oui. Pour l'instant, il n'est rien d'autre qu'un locataire. Je suis le propriétaire de la plantation, pas lui. Mais! Si quelque chose m'arrive - elle deviendra sa propriété.";
			link.l1 = "Tu sais, Domingo, j'ai connu des hommes qui auraient tué tous leurs parents de sang-froid pour une récompense bien moins juteuse que celle-là.";
			link.l1.go = "noble_14";
		break;
		
		case "noble_14":
			dialog.text = "Tu devrais choisir de meilleures fréquentations, Carlos. Mon cher Ugo a mentionné les papiers de mon oncle dans sa dernière lettre... C'est un indice direct. Oh, je ne veux pas y croire ! Mais... ma cousine, Margarita Ortiz, qui vit en Espagne, a été fiancée il n'y a pas longtemps. Cela pourrait-il en être la cause, mon bon capitaine ?";
			link.l1 = "Ton oncle adoré pourrait soudainement avoir besoin d'un peu d'argent...";
			link.l1.go = "noble_15";
		break;
		
		case "noble_15":
			dialog.text = "De l'argent ?! Mais bien sûr... mais n'oublie pas le titre de marquis ! Cela ferait de mon cousin un parti convenable pour son futur mari ! Jesu Christo ! Que j'étais stupide !";
			link.l1 = "Ce titre de noblesse a plus de valeur que la plantation de sucre.";
			link.l1.go = "noble_16";
		break;
		
		case "noble_16":
			dialog.text = "Attends mon ami ! Je viens de me rappeler que ce n'était pas la première tentative sur ma vie ! J'ai eu une rencontre avec un mendiant dans la rue il y a quelques semaines ! Le canaille ivre m'a offensé d'une manière que je ne pouvais ignorer. Il s'est avéré être un sacré bon escrimeur, il a dégainé son épée et a même réussi à me blesser avec une rapière avant que je ne le tue.";
			link.l1 = "Et comment diable t'es-tu retrouvé dans une taverne à Port-au-Prince ? Tu as mentionné une jeune señorita ?";
			link.l1.go = "noble_17";
		break;
		
		case "noble_17":
			dialog.text = "(rougissant) Monsieur...Oui capitaine, il y avait une jeune et jolie señorita sur les lieux... maintenant je vois qu'elle n'était que l'appât pour le piège. Salauds, les salauds sont partout, on ne peut faire confiance à personne ! Pauvre Ugo... il est mort maintenant.";
			link.l1 = "Tu devrais faire quelque chose à ce propos, Domingo. Que dirais-tu de fuir en Espagne ?";
			link.l1.go = "noble_18";
		break;
		
		case "noble_18":
			dialog.text = "En Espagne ? Et laisser ma plantation à ce vaurien ? Capitaine, je suis le Marquis Domingo Ortiz Albalate !";
			link.l1 = "Mais...";
			link.l1.go = "noble_19";
		break;
		
		case "noble_19":
			dialog.text = "Mon ami Carlos, puis-je vous demander de l'aide ? Avec Ugo mort, je n'ai plus personne à mes côtés en qui je puisse avoir confiance. Vous m'avez déjà sauvé deux fois ! Deux fois ! Je vous dois une fière chandelle, je vous suis redevable à jamais et pourtant j'ose vous demander une autre faveur. Je jure par la Sainte Mère, je vous récompenserai comme il se doit !";
			link.l1 = "Très bien, tu es un bon homme pour un Espagnol. Que puis-je faire pour toi, Domingo ?";
			link.l1.go = "noble_20";
		break;
		
		case "noble_20":
			dialog.text = "Allons à ma plantation à Portabello ! Je sais que mon oncle est à Cartagena en ce moment. Ugo a mentionné des papiers, alors vérifions les livres et documents de Don Luis Ortiz ! Nous pourrions trouver quelque chose qui nous aidera à dévoiler sa vile conspiration au grand jour. C'est assez loin jusqu'à Portobello, mais je vous paierai intégralement pour le voyage !";
			link.l1 = "Il serait absurde de vous rejeter à ce stade, Don Domingo. Je suis trop engagé pour me retirer maintenant.";
			link.l1.go = "noble_21";
		break;
		
		case "noble_21":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = "Gracias a Dios, je savais que tu m'aiderais, amigo ! Tiens, prends ces vingt mille pesos en paiement pour le voyage à Portobello. Quand levons-nous l'ancre ? Nous devons nous dépêcher avant que mon oncle ne revienne de Carthagène !";
			link.l1 = "Ne perdons pas de temps alors.";
			if (CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 20) link.l1.go = "noble_22";
			else link.l1.go = "noble_22x";
		break;
		
		case "noble_22x":
			GiveNationLicence(HOLLAND, 20);
			dialog.text = "Voici une licence de la Compagnie des Indes occidentales néerlandaises. Elle expire dans vingt jours, mettons simplement votre nom dessus. C'est fait. Cela devrait nous aider à éviter tout problème avec la Costa Garda.";
			link.l1 = "Excellent!";
			link.l1.go = "noble_22";
		break;
		
		case "noble_22":
			dialog.text = "Suis-je maintenant autorisé à monter à bord de ton navire, mon ami ?";
			link.l1 = "Considérez-vous comme un invité d'honneur. Dès que nous aurons le bon vent - nous mettons les voiles.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_OnBoard");
			AddMapQuestMarkCity("portobello", true);
		break;
		
		case "noble_23":
			dialog.text = "Alors Capitaine Carlos, nous y voilà. Maintenant, nous devrions trouver la maison de mon oncle et vérifier ce qu'il y a à l'intérieur.";
			link.l1 = "Don Domingo, devrions-nous nous attendre à des problèmes avec la garde ?";
			link.l1.go = "noble_24";
		break;
		
		case "noble_24":
			dialog.text = "Non. Cependant... hm. Il est possible que Luis les ait montés contre moi. De toute façon, la discrétion est toujours la meilleure partie du courage. Trouvons la maison dont nous avons besoin.";
			link.l1 = "Ne le sais-tu pas déjà ? C'est ta plantation.";
			link.l1.go = "noble_25";
		break;
		
		case "noble_25":
			dialog.text = "Hm.. Pour être tout à fait honnête, la dernière fois que j'étais ici, je n'avais que huit ans. Pourtant, j'ai l'intention de corriger cela dès que possible !";
			link.l1 = "Je vois. Alors commençons à chercher. La maison de votre oncle doit être la plus grande ici.";
			link.l1.go = "noble_26";
		break;
		
		case "noble_26":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			AddQuestRecord("FMQ_Portpax", "7");
		break;
		
		case "noble_27":
			dialog.text = "Qu'as-tu là, mon ami ?";
			link.l1 = "Regardez, Don Domingo. On dirait des registres comptables. Cela pourrait être intéressant.";
			link.l1.go = "noble_28";
		break;
		
		case "noble_28":
			ChangeItemDescribe("Almanac", "itmdescr_Almanac");
			RemoveItems(pchar, "Almanac", 1);
			dialog.text = "(lisant) Hum... Ouais. Regarde ça... Ay caramba ! Cent mille pesos ! Et encore cent cinquante mille ! Et ici... (tournant les pages) Oncle Luis !";
			link.l1 = "Quelque chose d'intéressant ?";
			link.l1.go = "noble_29";
		break;
		
		case "noble_29":
			dialog.text = "Quelque chose d'intéressant ! Mon oncle précieux avait un revenu cinq fois supérieur à ce qu'il me disait ! Voleur ! Escroc !";
			link.l1 = "Je ne peux pas dire que je suis surpris. On ne peut pas faire entièrement confiance à quelqu'un sans vérifier l'état réel des affaires de temps en temps. C'est juste du bon sens.";
			link.l1.go = "noble_30";
		break;
		
		case "noble_30":
			dialog.text = "Le bon sens pour les hommes du commun, peut-être. Mon éducation m'a aveuglé à de telles tromperies chez des gentilshommes que je croyais honorables ! Tu as raison comme toujours, Carlos ! Mon propre oncle me vole ! Merdouille ! C'est ma faute mais je vais arranger ça. Cette plantation m'appartient et mon oncle a été démis de ses fonctions dès aujourd'hui ! Il n'est plus rien ! Je le ferai passer par la quille !";
			link.l1 = "Don Domingo... Ne pensez-vous pas que votre oncle pourrait désapprouver une telle décision ?";
			link.l1.go = "noble_31";
		break;
		
		case "noble_31":
			dialog.text = "Je m'en fiche qu'il soit d'accord ou non ! Je suis le marquis Domingo Ortiz Albalate et Luis Ortiz n'est qu'un locataire, et un ancien locataire en plus ! Et il...";
			link.l1 = "Calmez-vous, señor. Vous êtes un visage inconnu ici et je suis un Français naviguant sous licence hollandaise avec un... passé tumultueux avec les patrouilles anti-piraterie espagnoles. Quant à votre oncle, il possède pratiquement cette ville. Pensez aux gardes et au gouverneur local. Pensez-vous qu'ils choisiront votre camp ?";
			link.l1.go = "noble_32";
		break;
		
		case "noble_32":
			dialog.text = "Tu frappes le point avec une rapière... Peut-être... Non. Les soldats espagnols n'oseront jamais lever la main sur un noble ! Mon oncle peut me défier s'il l'ose !";
			link.l1 = "Pourtant, je suggère d'emprunter un autre chemin. Que diriez-vous de la cour de justice ?";
			link.l1.go = "noble_33";
		break;
		
		case "noble_33":
			dialog.text = "Ha ! Tu as raison, Carlos. Allons parler aux autorités compétentes. Mon oncle a fait une erreur en notant les détails exacts dans ses notes sur ses affaires avec les contrebandiers. Il a acheté des esclaves à bas prix. Ces livres nous rendront un grand service, je doute que le salaud puisse me nuire de quelque manière que ce soit en étant assis dans les cachots. Allons-y mon ami ! À Portobello !";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PrepareUncle");
		break;
		
		case "noble_34":
			//PlaySound("Voice\English\LE\Domingo\Domingo_04.wav");
			dialog.text = "C'est rien d'autre qu'un mensonge sale et insolent ! Comment ose-t-il salir le bon nom de mes parents avec sa langue indigne ! Maudit soit-il, je vais lui faire payer pour ça ! Tire ton épée, assassin !";
			link.l1 = "";
			link.l1.go = "noble_35";
		break;
		
		case "noble_35":
			DialogExit();
			sld = CharacterFromID("FMQP_Uncle");
			sld.Dialog.currentnode = "uncle_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noble_36":
			PlaySound("Voice\English\LE\Domingo\Domingo_05.wav");
			dialog.text = "Tonton Luis est à sa place légitime réservée à son âme - en enfer... Carlos, tu m'as été envoyé par mon ange gardien ! Je suis heureux que tu n'aies pas cru aux paroles de ce vaurien. Pour être honnête, je craignais que tu ne me laisses ici seul à combattre ce canalla\nOui señor, je ne suis pas parfait moi-même mais ça... ce mensonge éhonté sur moi engageant des pirates pour tuer mes propres parents ! M'accuser de ça... ça ! Bah ! Un destin bien mérité.";
			link.l1 = "Content que nous ayons réussi, Don Domingo. Et maintenant ? J'espère que nous n'avons pas enfreint la loi espagnole.";
			link.l1.go = "noble_37";
		break;
		
		case "noble_37":
			dialog.text = "Avec la loi ? Ha-ha ! Non Carlos, je vais montrer ce livre de comptes impeccable avec toutes les opérations de contrebande de mon oncle dedans. N'oublie pas les nombreuses tentatives sur ma vie, nous avons un grand nombre de témoins après sa dernière tentative à l'instant. Ne t'en fais pas, mi buen amigo. C'est ma ville, il est temps de leur montrer à tous !";
			link.l1 = "Veuillez avancer prudemment, señor. Laissez-les penser mieux de vous qu'ils ne le faisaient de votre défunt oncle.";
			link.l1.go = "noble_38";
		break;
		
		case "noble_38":
			dialog.text = "C'est le plan, capitaine. Mais je ne montrerai aucune pitié à quiconque ose me défier. Permettez-moi de vous exprimer ma sincère gratitude, Carlos ! Allez à la taverne, reposez-vous, prenez une ou deux coupes. Je serais ravi de vous rejoindre, mais vous aviez raison. Il est temps de devenir plus sage et de prendre moi-même le contrôle de la plantation. Venez me voir ici demain, capitaine !";
			link.l1 = "Très bien, Don Domingo. À demain.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PlantatonPause");
		break;
		
		case "noble_39":
			DelLandQuestMark(npchar);
			PlaySound("VOICE\English\LE\Domingo\Domingo_05.wav");
			dialog.text = "Ah, te voilà mon bon ami !";
			link.l1 = "Comment allez-vous, don Domingo ? Comment va votre plantation ?";
			link.l1.go = "noble_40";
		break;
		
		case "noble_40":
			dialog.text = "La plantation est excellente, je ne peux pas en dire autant de l'argent - il s'avère que mon cher oncle avait transféré tout l'argent à la banque de Carthagène. Il faudra beaucoup de temps aux avocats pour récupérer mon or. Mais ça va, je peux m'en occuper. Ne sois pas triste, capitaine, je tiendrai mes promesses de te récompenser pour ta noblesse, ton honnêteté et ton amitié !";
			link.l1 = "Jamais pensé à une récompense quand je combattais à vos côtés, señor...";
			link.l1.go = "noble_41";
		break;
		
		case "noble_41":
			dialog.text = "Je sais cela, capitaine, et cela en dit long sur votre caractere ! Tout bon acte doit etre recompense. Ainsi, bien que je n'aie pas d'argent pour le moment, je donnerai l'ordre de charger votre navire avec les marchandises de ma plantation. Je veux dire du cafe, un bon lot. Vous pourrez le vendre avec un grand profit, j'en suis sur.";
			link.l1 = "Oh ! C'est agréable..";
			link.l1.go = "noble_42";
		break;
		
		case "noble_42":
			dialog.text = "De plus, j'ai quelques objets de petite valeur pour moi, mais de grande valeur pour tout marin tel que vous. Une belle longue-vue et trois amulettes. Veuillez accepter ceci, c'est tout à vous maintenant.";
			link.l1 = "Gratitude!";
			link.l1.go = "noble_43";
		break;
		
		case "noble_43":
			Log_Info("You have received a good spyglass");
			Log_Info("You have received three amulets");
			PlaySound("interface\important_item.wav");
			dialog.text = "Enfin, je te fais don de mon rapière en guise de ma gratitude incommensurable envers toi. Elle m'a bien servi, qu'elle te serve encore mieux. Regarde-la et souviens-toi de ton bon ami espagnol - marquis Domingo Albalate !";
			link.l1 = "Merci beaucoup, señor ! Je ne m'attendais pas...";
			link.l1.go = "noble_44";
		break;
		
		case "noble_44":
			Log_Info("You have received the Smallsword");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "Et maintenant, hélas, je dois faire mes adieux. Je devrais aller à Portobello pour voir le gouverneur et ensuite à Carthagène... Pour résumer, mon existence insouciante est terminée, il est temps de vivre comme un homme adulte.";
			link.l1 = "Eh bien, vous êtes bien plus malin maintenant...";
			link.l1.go = "noble_45";
		break;
		
		case "noble_45":
			dialog.text = "C'est vrai. Ce fut un plaisir, mon ami ! Viens me voir un de ces jours. Bon vent en mer !";
			link.l1 = "Bonne chance dans tes affaires de plantation, don Domingo !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_ReceiveReward");
		break;
		
		case "noble_46":
			PlaySound("Voice\English\YoungMan02.wav");
			dialog.text = "Eh, nous sommes en retard, senor ! Quel dommage, mon bon vieil oncle a déjà fait un sacré ménage parmi ses papiers. On dirait qu'on lui a parlé de Santo-Domingo et il a pris des mesures de précaution... Mais je ne vais pas laisser ça comme ça ! Je devrais voir le gouverneur de Portobello pour entamer une procédure légale contre mon oncle. J'en ai assez qu'il gère ma fortune.";
			link.l1 = "Bonne decision.";
			link.l1.go = "noble_47";
		break;
		
		case "noble_47":
			dialog.text = "Je veux vous remercier, capitaine ! Ce fut un plaisir ! Je vous offre mon rapière en gage de ma gratitude envers vous. Elle m'a bien servi, qu'elle vous serve encore mieux. Regardez-la et souvenez-vous de votre bon ami espagnol - le marquis Domingo Albalate !";
			link.l1 = "Merci beaucoup, senor ! Je ne m'attendais pas...";
			link.l1.go = "noble_48";
		break;
		
		case "noble_48":
			Log_Info("You have received the Smallsword");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			GiveItem2Character(pchar, GetGeneratedItem("blade_16")); // belamour legendary edition используем GetGeneratedItem иначе пачка одинаковых клинков из первой части массива
			dialog.text = "Hélas, je dois maintenant faire mes adieux. Je devrais aller à Portobello. Mon existence insouciante est terminée, il est temps de vivre comme un homme adulte. Bon vent en mer !";
			link.l1 = "Bonne chance avec votre oncle, don Domingo ! Je suis sûr que vous triompherez !";
			link.l1.go = "noble_49";
		break;
		
		case "noble_49":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("PortoBello_Plantation", "reload2_back", false);
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 40.0);
			pchar.questTemp.FMQP = "fail";
			AddQuestRecord("FMQ_Portpax", "13");
			CloseQuestHeader("FMQ_Portpax");
			sld = &Locations[FindLocation("PortoBello_Plantation")];
			sld.soldiers = true;
		break;
		
		case "uncle":
			PlaySound("Voice\English\OliverTrast02.wav");
			dialog.text = "On dirait que je suis arrivé à temps. Mon neveu insouciant et son ange gardien Capitan "+GetFullName(pchar)+"Ne sois pas si surpris, Français, je sais qui tu es.";
			link.l1 = "Luis Ortiz ?";
			link.l1.go = "uncle_1";
		break;
		
		case "uncle_1":
			dialog.text = "Vous avez raison, capitaine, mais vous avez tout le reste faux. Vous ne devriez pas fourrer votre nez dans les affaires familiales des autres hommes. Vous n'avez même aucune idée de qui vous protégez. Mon neveu dissolu Domingo est un débauché sans valeur, le visiteur numéro un de chaque taverne et bordel qui couche ou du moins essaie de coucher avec chaque fille à l'horizon. Je lui paie son loyer chaque mois et il le gaspille en quelques jours, réclamant toujours plus et plus. Encore et encore. Son comportement constant et indigne a rendu sa mère et ma sœur folles.\nJ'ai entendu des rumeurs selon lesquelles ce vilain garçon a même engagé et dirigé des corsaires anglais vers un certain navire du Marquis Ricardo Albalate qu'ils ont coulé avec cet homme digne et ma chère sœur. Domingo voulait tellement l'argent de notre famille qu'il serait prêt à tuer pour l'obtenir... Malheureusement, je n'ai pas réussi à trouver suffisamment de preuves pour envoyer ce scélérat à la potence.";
			link.l1 = "";
			link.l1.go = "uncle_2";
		break;
		
		case "uncle_2":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			sld.Dialog.currentnode = "noble_34";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "uncle_3":
			dialog.text = "Typique. Cris, cliquetis d'épées et de coupes, plein de bruit et de fureur, ne signifiant rien. Combien vous a-t-il payé, capitaine, pour votre protection ?";
			link.l1 = "Autant que je comprenne, après avoir échoué à déterrer des preuves contre votre neveu, vous avez commencé à envoyer des assassins à sa poursuite. On dirait qu'un simple procès aurait suffi.";
			link.l1.go = "uncle_4";
		break;
		
		case "uncle_4":
			dialog.text = "Tu parles des mensonges. Domingo ici a fait une quantité illimitée d'ennemis. Il a laissé une traînée d'amants éconduits et de maris trompés sur son passage. Je me demande comment il a même réussi à survivre aussi longtemps ! Demande-lui, combien de mariages a-t-il ruinés ? Combien de fiancés insultés a-t-il blessés ou tués ?";
			link.l1 = "Son serviteur Ugo...";
			link.l1.go = "uncle_5";
		break;
		
		case "uncle_5":
			dialog.text = "Ah Ugo ! Le pire fripon de tous ! Ugo aimait son maître vaurien. Tous les crimes de son maître n'étaient pour lui que des enfantillages. Souviens-toi, Français, les affaires de famille sont réservées à la famille. Ceux qui fouinent et se mêlent se retrouveront dans de beaux draps.";
			link.l1 = "Maintenant tu me menaces.";
			link.l1.go = "uncle_6";
		break;
		
		case "uncle_6":
			int icpy = GetOfficersQuantity(pchar);
			iTotalTemp = 10000+10000*icpy;
			dialog.text = "Pas une menace, capitaine, une promesse. Écoute, garçon, tu as fait un long chemin, mais comme je te considère comme une victime délirante et non comme un ennemi, écoute mon offre simple et généreuse : pars. Je ne veux pas verser de sang ici. Nous n'avons pas besoin de ton aide pour résoudre nos affaires de famille. Je suis même prêt à compenser les ennuis que tu as subis à cause de mon idiot de neveu - "+FindRussianMoneyString(iTotalTemp)+"pièces de huit. Prends-le et laisse-nous entiers. Rejette mon offre et nous te renverrons à ton navire en fines tranches.";
			link.l1 = "'La famille d'abord' est ce que je dis toujours. Cela ne me concerne pas, alors donne l'argent et 'vaya con Dios.'";
			link.l1.go = "uncle_7";
			link.l2 = "Ton histoire pue plus que l'engrais de ta plantation. Don Domingo n'est peut-être pas un saint, mais vous, señor, êtes un diable !";
			link.l2.go = "uncle_8";
		break;
		
		case "uncle_7":
			AddMoneyToCharacter(pchar, iTotalTemp);
			dialog.text = "Je savais que vous étiez un homme raisonnable. Prenez votre argent et adios capitaine. Essayez de ne pas fouiller dans le linge sale des autres à l'avenir - ils ne l'apprécient jamais.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_UncleExit");
		break;
		
		case "uncle_8":
			dialog.text = "Un diable ? Eh bien, je prendrai plaisir à t'envoyer en enfer !";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQP_UncleFight");
		break;
		
		case "ugo":
			pchar.quest.FMQP_SantoDomingoOver.over = "yes";
			PlaySound("Voice\English\Serve_senior.wav");
			dialog.text = TimeGreeting()+"señor. Comment puis-je vous être utile ?";
			link.l1 = "Salutations. Pardonnez-moi, mais est-ce la résidence de Senor Domingo Albalate ?";
			link.l1.go = "ugo_1";
		break;
		
		case "ugo_1":
			dialog.text = "Si, c'est la maison d'Albalate. Elle est modeste mais confortable. Mon nom est Ugo, je sers le jeune maître. Êtes-vous ici pour lui ?";
			link.l1 = "Si, senor. Don Domingo m'a invité chez lui il n'y a pas longtemps. Il était très persuasif. Puis-je le voir ?";
			link.l1.go = "ugo_2";
		break;
		
		case "ugo_2":
			dialog.text = "Hélas, mon bon caballero, Don Domingo n'est pas chez lui en ce moment. Personnellement, j'aimerais bien savoir moi-même où se trouve ce garnement... eh, je vous prie de m'excuser, jeune señor. Puis-je vous demander ce que vous avez besoin de lui ?";
			link.l1 = "Eh bien... J'ai aidé Don Domingo par hasard. Il a été attaqué par deux vauriens dans une taverne de Port-au-Prince. J'ai aidé votre maître à se défendre contre ces... comment les a-t-il appelés... maldita canalla. Don Domingo m'a invité à lui rendre visite ici après qu'il ait terminé son enquête. Je pensais que tout devrait être réglé maintenant, donc je m'attendais à le voir chez lui.";
			link.l1.go = "ugo_3";
		break;
		
		case "ugo_3":
			dialog.text = "Madre de Dios ! Quelles histoires épouvantables vous racontez ici ! Je dois voir le commandant immédiatement - pour le prévenir des dangers auxquels Don Domingo fait face en ce moment ! Señor, vous devez partir et je dois me dépêcher !";
			link.l1 = "Calme-toi, Ugo. Ton jeune maître est en sécurité. Il a mentionné que ses papiers sont en règle, ils étaient censés le libérer déjà, c'est pourquoi je suis ici. Je crois que nous devrions le voir bientôt.";
			link.l1.go = "ugo_4";
		break;
		
		case "ugo_4":
			dialog.text = "Oh! Comment avez-vous pu ? Mon jeune maître, ce garçon naïf - et entre les mains de ces mangeurs de grenouilles français ? Sans parler des ladrones menaçant sa vie ? Non, je dois voir le commandant ! Monsieur, je vous en prie, allez-y !";
			link.l1 = "Très bien, très bien, ne sois pas si insistant. Je m'en vais.";
			link.l1.go = "ugo_exit";
			link.l2 = "Señor, pourquoi êtes-vous si nerveux ? Je vous ai déjà dit qu'il n'y a aucun danger pour votre maître. Laissez-moi rester ici et attendre l'arrivée du Señor Domingo, je suis très fatigué de mon long voyage et j'apprécierais votre hospitalité. J'aimerais un peu d'eau fraîche et un bain chaud pour rincer la brise salée de ma gorge. Ensuite, vous pouvez aller à la garnison locale et faire ce que vous voulez.";
			link.l2.go = "ugo_5";
		break;
		
		case "ugo_exit":
			DialogExit();
			LocatorReloadEnterDisable("Santodomingo_town", "houseSp4", true);
			DoQuestReloadToLocation("SantoDomingo_town", "reload", "houseSp4", "FMQP_SDMFail");
		break;
		
		case "ugo_5":
			dialog.text = "Seigneur, quittez cette maison sur-le-champ !";
			link.l1 = "Ugo, je doute fort qu'un serviteur soit autorisé à parler à un gentilhomme de cette manière. Je doute aussi que Don Domingo approuverait un tel traitement envers un homme qui lui a sauvé la vie !";
			link.l1.go = "ugo_6";
		break;
		
		case "ugo_6":
			dialog.text = "Ah vraiment ? (criant en haut) Les gars, descendez, on a un problème !";
			link.l1 = "Qu'est-ce que c'est que ce bordel ?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_SantoDomingoFight");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
