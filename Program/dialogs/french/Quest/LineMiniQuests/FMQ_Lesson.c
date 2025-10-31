// Addon-2016 Jason, французские миниквесты (ФМК) Последний урок
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
			dialog.text = "Un bug évident. Parlez-en aux développeurs.";
			link.l1 = "Ah, je le ferai.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "greguar":
			PlaySound("Voice\English\LE\Greguar\Greguar_04.wav");
			pchar.quest.FMQL_delete_guide.over = "yes";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
			if (CheckAttribute(pchar, "questTemp.HWIC") || pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "Oh, "+GetFullName(pchar)+"! Tu as l'air différent mon ami et tu as du succès! Ils commencent à parler de toi, tu sais? Tu apprends vite, monseigneur, je suis vraiment fier de toi. Je te souhaite plus de fortunes et de chance à l'avenir! Heureux de te revoir!";
				link.l1 = "Monsieur Gregoire Valinnie, quelle rencontre ! Je vous dois beaucoup pour mes humbles réussites. Enchanté de vous rencontrer aussi ! Bonne chance !";
				link.l1.go = "greguar_exit_1";
			}
			else
			{
				dialog.text = "Oh, "+GetFullName(pchar)+"! Vous avez l'air différent mon ami et vous avez du succès ! Ils commencent à parler de vous, savez-vous ? Vous apprenez vite, monsieur, je dois dire que vous m'avez rendu fier.";
				link.l1 = "Monsieur Gregoire Valinnie, quelle rencontre ! Je vous dois beaucoup pour mes humbles accomplissements. Enchanté de vous rencontrer ! Laissez-moi deviner, vous avez une proposition d'affaire pour moi ?";
				link.l1.go = "greguar_1";
			}
		break;
		
		case "greguar_1":
			dialog.text = "Oui ! Je le fais. Je serai bref, le temps, c'est de l'argent. Alors, une escadre de la couronne néerlandaise naviguant du Brésil à Curaçao avec une cargaison de biens de valeur stratégique a été embusquée par les Anglais entre Trinidad et le continent. Un flûte de la Compagnie a réussi à fuir et à s'amarrer sur la côte de Boca de la Serpienta. Ils ont sauvé une partie de la cargaison mais pas pour longtemps - ils ont été attaqués par une tribu indienne locale\nSelon mes informations, ils ont exterminé tous les Néerlandais sur cette côte et ont emporté la cargaison dans leur village. Les Indiens ont aussi saisi les armes à feu néerlandaises mais ont subi de lourdes pertes. C'est notre chance ! Les Britanniques et les Néerlandais se battent encore dans cette région et ils sont trop occupés pour se soucier de la flûte perdue. Pour l'instant... Vous avez un navire et un équipage. Nous pouvons y naviguer, débarquer et achever les Indiens. La cargaison est extrêmement précieuse et il y en a beaucoup là-bas\nJ'ai déjà envoyé une petite expédition pour faire du repérage - c'était tout ce que je pouvais me permettre, des problèmes d'argent vous vous souvenez ? J'ai un acheteur de confiance, vous pouvez compter sur mon épée et mes mercenaires. Partage à cinquante-cinquante, nous avons une semaine pour y arriver. Alors mon ami, êtes-vous partant ?";
			link.l1 = "Excusez-moi, monsieur, mais je vais passer. Je viens de terminer un voyage difficile, nous n'avons pas assez de temps pour faire des réparations et recruter. Même dans cet endroit oublié de Dieu, un homme ne peut pas tout avoir.";
			link.l1.go = "greguar_exit";
			link.l2 = "Ça ressemble à une affaire dangereuse avec un parfum de profit décent et d'aventures. Bien sûr que je suis partant ! Ne perdons pas de temps !";
			link.l2.go = "greguar_2";
		break;
		
		case "greguar_exit":
			dialog.text = "Dommage. C'est donc à vous de décider. Bon vent, monsieur, je m'y rendrai quand même. Un homme doit essayer, n'est-ce pas ?";
			link.l1 = "Bon vent, monsieur Valinnie!";
			link.l1.go = "greguar_exit_1";
		break;
		
		case "greguar_exit_1":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload5_back", "none", "", "", "", 20.0);
		break;
		
		case "greguar_2":
			dialog.text = "Bon choix, mon ami ! Tu pourrais utiliser un peu d'argent en plus, n'est-ce pas ? Comment va ton frère, d'ailleurs ?";
			link.l1 = "Je peux toujours utiliser de l'argent en plus. Michel ? Mon frère est en bonne santé et il s'ennuie. Je l'envie parfois... Il est temps de mettre les voiles !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_Begin");
		break;
		
		case "greguar_3":
			PlaySound("Voice\English\QuestMan02.wav");
			dialog.text = "Facile comme bonjour ! C'étaient les novices qui ont survécu à l'escarmouche avec les Hollandais. Nous devrions nous enfoncer plus loin dans les terres, mon expédition doit s'y trouver !";
			link.l1 = "Ça semblait trop facile... mais il est trop tôt pour célébrer, monsieur Valinnie. Regardez par là...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_SecondCoastBattle");
		break;
		
		case "greguar_4":
			PlaySound("Voice\English\LE\Greguar\Greguar_05.wav");
			dialog.text = "Malediction sur ces peaux-rouges ! Ils ont failli nous avoir ! Maintenant, je suis sûr qu'il ne reste que des femmes et des enfants dans le village. En avant !";
			link.l1 = "Je ne suis pas si sûr que tu aies mentionné des mousquets, je ne les ai pas vus... Ah peu importe. Allons-y !";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_GoToJungle");
		break;
		
		case "greguar_5":
			PlaySound("Voice\English\LE\Greguar\Greguar_06.wav");
			dialog.text = "Que veux-tu dire ? Les Hollandais et nous avons dû tous les tuer !";
			link.l1 = "";
			link.l1.go = "greguar_6";
		break;
		
		case "greguar_6":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Prosper_fmql")) sld = CharacterFromID("FMQL_Prosper");
			else sld = CharacterFromID("FMQL_mercen");
			sld.dialog.currentnode = "prosper_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "greguar_7":
			dialog.text = "Fuir ? Es-tu fou ? Nous y sommes presque ! As-tu peur d'une bande de sauvages peints ?";
			link.l1 = "";
			link.l1.go = "greguar_8";
		break;
		
		case "greguar_8":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Prosper_fmql")) sld = CharacterFromID("FMQL_Prosper");
			else sld = CharacterFromID("FMQL_mercen");
			sld.dialog.currentnode = "prosper_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "greguar_9":
			dialog.text = "Les plus basses des bassesses, capitaine. Je retourne en Europe. Je suis déçu ! De vous, de ces lâches et de cette foutue région !";
			link.l1 = "... ";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_10":
			DialogExit();
			DoQuestReloadToLocation("shore18", "goto", "goto8", "FMQL_JungleExit");
		break;
		
		case "greguar_11":
			dialog.text = "Pff ! Nous l'avons fait !";
			link.l1 = "Mais à quel prix ! Regarde ! Presque tous les membres de notre escouade sont morts. Nous devrions battre en retraite, Gregoire, il n'y a aucune garantie qu'il n'y ait pas plus de guerriers qui nous attendent. De plus, nous n'avons tout simplement pas assez de monde pour transporter le butin.";
			link.l1.go = "greguar_12";
		break;
		
		case "greguar_12":
			dialog.text = "Sacrebleu ! C'est triste, mais tu as raison, "+pchar.name+": même si les sauvages sont tous morts, nous ne pourrons pas emporter la cargaison avant que les Hollandais ou les Anglais ne débarquent ici. Nous devons partir maintenant ! Au diable cette maudite côte !";
			link.l1 = "... ";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_13":
			dialog.text = "Fuh ! Nous l'avons fait ! Bien joué, "+pchar.name+" ! Maintenant, allons dans l'antre des sauvages pour notre prix ! Rien ne peut nous arrêter maintenant !";
			link.l1 = "Nous devrions nous dépêcher pendant que les Britanniques et les Hollandais sont encore occupés entre eux. Allons-y !";
			link.l1.go = "greguar_14";
		break;
		
		case "greguar_14":
			DialogExit();
			DoQuestCheckDelay("FMQL_RunToGrabbing", 1.0);
		break;
		
		case "greguar_15":
			dialog.text = "Nous avons bien réussi, "+pchar.name+" Maintenant, tout ce dont nous avons besoin, c'est de vendre la cargaison sans éveiller de soupçons. J'ai un acheteur fiable, il nous attendra à la baie de Lamentin à minuit. Ne prends pas d'officiers et évite l'endroit avant la rencontre, le client est un type très nerveux.";
			link.l1 = "Les affaires sont les affaires. La cargaison doit être vendue et cela doit être fait en toute sécurité, sinon ma dette envers Poincy augmentera encore plus. Très bien, j'y serai avant minuit.";
			link.l1.go = "greguar_16";
		break;
		
		case "greguar_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.quest.FMQL_goods_timer.win_condition.l1 = "Timer";
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.hour  = 0.0;
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQL_goods_timer.function = "FMQL_MeetingOnLamanten";
			AddQuestRecord("FMQ_Lesson", "7");
			LAi_LocationDisableOfficersGen("Shore38", true); // may-16
			LAi_LocationFightDisable(&Locations[FindLocation("Shore38")], true);
			locations[FindLocation("Shore38")].DisableEncounters = true;
			Pchar.GenQuest.Hunter2Pause = true;
		break;
		
		case "greguar_17":
			PlaySound("Voice\English\Master_01.wav");
			pchar.quest.FMQL_goods_over.over = "yes";// лесник снято прерывание на встречу.
			dialog.text = "C'est fait. La cargaison est debarquee, le client est ici. Parlons affaires.";
			link.l1 = "... ";
			link.l1.go = "greguar_18";
		break;
		
		case "greguar_18":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("FMQL_contra_"+i);
				if (i == 2) 
				{
					LAi_CharacterEnableDialog(sld);
					AddLandQuestMark(sld, "questmarkmain");
				}
			}
		break;
		
		case "greguar_19":
			dialog.text = "Surprise, sales bâtards !";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_LookOnGuards");
		break;
		
		case "greguar_20":
			PlaySound("Voice\English\OliverTrast01.wav");
			dialog.text = "Ah, Johnny, quel type ! Super ! Tu as quelque chose à dire, "+pchar.name+"?";
			link.l1 = "Non. En fait, oui ! Putain, mais qu'est-ce que c'est que ça ?!";
			link.l1.go = "greguar_21";
		break;
		
		case "greguar_21":
			dialog.text = "Ne taquine pas le mort, monseigneur. Où sont tes manières ?.. L'argent est ici, la cargaison est gérée par moi et mes amis. Je ne les ai pas envoyés à la côte, cela aurait été du gâchis. Surtout envoyer Johnny là-bas. Vois ce peau-rouge avec une coulevrine dans les mains ? Tu sais, Johnny n'a jamais vraiment aimé sa propre tribu.";
			link.l1 = "Je vois... Et maintenant ? Vas-tu me tuer aussi ?";
			link.l1.go = "greguar_22";
		break;
		
		case "greguar_22":
			dialog.text = "Eh bien, je devrais. Mais je suis sentimental. Pars et prends un quart de l'argent. La cargaison et le reste de l'argent resteront ici avec moi. Ne tente pas de jouer les héros, ce ne sont pas les jungles du continent. Tu n'as aucune chance.";
			link.l1 = "Et où sont ta noblesse et tes manières, Gregoire? Je ne m'attendais pas à cela de ta part. Je m'en vais, mais je n'oublierai pas cela.";
			link.l1.go = "greguar_23";
			link.l2 = "Je ne joue pas le héros, je ne l'ai jamais fait. Je vais simplement vous tuer tous ! D'abord ces dames, puis le singe avec le lance-grenades et ensuite toi !";
			link.l2.go = "greguar_25";
		break;
		
		case "greguar_23":
			dialog.text = "Il n'y a ni nobles, ni voyous sur cette plage, monsieur. Il n'y a que cinq hommes, un gros canon et une victime. Cela se passe ici tout le temps, mais vous avez fait le seul bon choix. Bien joué. Savez-vous qu'à votre place, il pourrait y avoir deux autres personnes, debout ici, en ce moment même ? Ils sont presque comme vous. Mais vous êtes ici et eux non, et je pense qu'ils périront à cause de cela.";
			link.l1 = "Je ne suis pas...";
			link.l1.go = "greguar_24";
		break;
		
		case "greguar_24":
			dialog.text = "Un jour, vous le ferez. Ils n'ont pas reçu leur dernière leçon. Vous l'avez fait. Vous êtes le bienvenu. Adieu, monsieur. Bienvenue aux Caraïbes !";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_PeaceFinal");
		break;
		
		case "greguar_25":
			dialog.text = "Ahh... Tu n'es pas l'élève le plus brillant que j'aie eu. Très bien... à chacun son goût!";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_BattleOnBeach");
		break;
		
		case "mercen":
			PlaySound("Voice\English\pirat_guard_4.wav");
			dialog.text = "Parfait timing ! Nous avons à peine fui la horde des Caribes, ils se dirigeaient vers votre direction et, à en juger par votre apparence, vous les avez déjà rencontrés. Leur village est tout proche mais nos ennuis ne font que commencer.";
			link.l1 = "";
			link.l1.go = "prosper_2";
		break;
		
		case "prosper":
			dialog.text = ""+GetFullName(pchar)+"! Tu es là ! Et pourquoi cela ne m'étonne-t-il pas ! Timing parfait, mon ami. Nous avons à peine échappé à la horde des Caraïbes, ils se dirigeaient vers toi et, à en juger par ton apparence, tu les as déjà rencontrés.";
			link.l1 = "Prosperer ! Et je suis surpris ! Encore en train de faire des trous dans les Indiens ? J'espère que Selina va bien ?";
			link.l1.go = "prosper_1";
		break;
		
		case "prosper_1":
			dialog.text = "C'était insensé de ma part de rejoindre cette expédition, je me demande si ma fille me reverra un jour. Selina ? Eh bien, elle est assise à la maison et rêve de toi ! Les jeunes de la Martinique ont perdu tout espoir à présent... Tu sais, je ne regrette plus d'avoir acheté ce mousquet. Une arme solide. Fiable. Aussi une raison supplémentaire de participer à une autre entreprise suicidaire, bien que ce soit maintenant un peu moins suicidaire depuis que tu es arrivé. Leur village est tout près mais nos problèmes ne font que commencer.";
			link.l1 = "";
			link.l1.go = "prosper_2";
		break;
		
		case "prosper_2":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_3":
			dialog.text = "Pas tous. Notre éclaireur a été abattu mais a tout de même réussi à atteindre leur repaire. Un chef lui-même vient ici avec ses gardes. Et ils ont des mousquets hollandais. Ils ont l'avantage du nombre et ils sont furieux comme l'enfer. Le chef est le meilleur guerrier de leur tribu, ses hommes sont des diables en chair. Nous devons décider rapidement, ici et maintenant. Soit nous leur donnons bataille, soit nous fuyons. Je préfère la dernière option, pour être honnête...";
			link.l1 = "";
			link.l1.go = "prosper_4";
		break;
		
		case "prosper_4":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_5":
			dialog.text = "Tu ne les as pas vus, mon bonhomme ! Ces 'sauvages' ont des mousquets et ils savent diablement bien s'en servir. Quelqu'un leur a donné des leçons, ça ne fait aucun doute ! Alors ne me traite plus de lâche !";
			link.l1 = "Calmons-nous et décidons de ce que nous allons faire. Il y a encore du temps.";
			link.l1.go = "prosper_6";
		break;
		
		case "prosper_6":
			int n = 0;
			for (i=1; i<=5; i++)
			{
				if (GetCharacterIndex("FMQL_sailor_"+i) != -1) n++;
			}
			dialog.text = "Je t'écoute, "+pchar.name+".";
			if (n > 2 && GetSummonSkillFromName(pchar, SKILL_SNEAK) > 30)
			{
				Notification_Skill(true, 31, SKILL_SNEAK);
				link.l1 = "Nous allons leur donner du fil à retordre, les gars ! Il y a des marchandises et de l'argent juste derrière cette colline ! Nous sommes ici pour ça et nous ne partons pas. Pas question qu'une bande de peaux-rouges, même avec des mousquets, puisse nous arrêter ! Enterrons ces salauds et finissons le travail ! Nous avons assez d'hommes, il y a une chance de les prendre en embuscade. Quatre hommes les accueilleront avec du feu sur les flancs et le reste d'entre nous prendra position ici. Réduisez leur nombre et achevez-les !";
				link.l1.go = "prosper_8";
			}
			else
			{
				if (GetCharacterSkill(pchar, SKILL_SNEAK) < 31) Notification_Skill(false, 31, SKILL_SNEAK);
				if (n < 3) notification("Not enough people", "X");
				if (n > 0)
				{
					link.l1 = "Nous allons leur livrer bataille, les gars ! Il y a des marchandises et de l'argent juste derrière cette colline ! Nous sommes ici pour cela et nous ne partons pas. Il n'est pas question qu'une bande de peaux-rouges, même avec des mousquets, puisse nous arrêter ! Enterrons ces salauds et terminons le travail !";
					link.l1.go = "prosper_7";
				}
				else
				{
					link.l1 = "Nous avons toutes les chances contre nous de toutes les manières possibles. N'oublie pas les Néerlandais juste derrière nous.";
					link.l1.go = "prosper_9";
				}
			}
		break;
		
		case "prosper_9":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_7":
			DialogExit();
			pchar.questTemp.FMQL = "battle";
			AddDialogExitQuestFunction("FMQL_PrepareAttack");
		break;
		
		case "prosper_8":
			DialogExit();
			pchar.questTemp.FMQL = "sneak";
			AddDialogExitQuestFunction("FMQL_PrepareSneakAttack");
		break;
		
		case "prosper_9x":
			dialog.text = "Nous sommes vivants et nous sommes chez nous ! Je le jure, j'ai eu ma dose d'aventures... pour les prochains mois, ha-ha ! Je devrais aller voir ma fille, s'il vous plaît, venez nous rendre visite, "+pchar.name+"Et s'il vous plaît, soyez prudent.";
			link.l1 = "Pas de promesses, Prosper. Bon vent !";
			link.l1.go = "prosper_10";
		break;
		
		case "prosper_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
		break;
		
		case "prosper_11":
			pchar.quest.FMQL_prosper_dead.over = "yes";
			LAi_RemoveCheckMinHP(npchar);
			PlaySound("Voice\English\pirat_guard_4.wav");
			dialog.text = "Je vous avais prévenu, capitaine, de faire attention ! J'avais des soupçons sur ce salaud.";
			link.l1 = "Prosperer ! Merci ! Mais comment ?";
			link.l1.go = "prosper_12";
		break;
		
		case "prosper_12":
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.FMQL.PirateDead")) sTemp = "Poor lad, even though he was a pirate.";
			dialog.text = "Johnny est devenu trop bavard. Le peau-rouge sur le sable. Il est venu à un bordel et a tenté de séduire une fille. Ils ont refusé de le servir, Johnny s'est mis en colère, a commencé à crier qu'il allait bientôt être riche, une fois qu'il et ses copains auront tué un capitaine dans la jungle. J'ai vu ce qui allait arriver et j'ai couru vers votre officier qui a aussi réussi à se faire une réputation dans la ville."+sTemp+" Je te dois beaucoup, "+pchar.name+", donc il n'est pas nécessaire de me remercier trop chaleureusement.";
			link.l1 = "Et pourtant, merci beaucoup, Prosper ! C'était dur ici... trop dur. Veux-tu rejoindre mon équipage ? J'ai besoin d'un officier comme toi. Il est difficile de trouver des hommes loyaux de nos jours, surtout des tireurs d'élite.";
			link.l1.go = "prosper_13";
		break;
		
		case "prosper_13":
			dialog.text = "Non, mon ami. J'ai des obligations envers ma fille. Elle m'a fait jurer de laisser mes aventures derrière moi. C'était ma dernière. Nom d'un chien, quel dommage, mais j'aime ma fille plus que tout au monde. Adieu, "+pchar.name+". Et.. Selina parle de vous tout le temps. Peut-être pourriez-vous nous rendre visite un jour?";
			link.l1 = "Qui sait, peut-être que je le ferai... Adieu, Prosper! Je souhaite que ta fille trouve un bon mari... (à soi-même) Leçon apprise, monsieur Gregoire, leçon apprise... à chacun son dû, disait-il... Je m'en souviendrai.";
			link.l1.go = "prosper_14";
		break;
		
		case "prosper_14":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
			AddQuestRecord("FMQ_Lesson", "15");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
		break;
		
		case "contra":
			DelLandQuestMark(npchar);
			dialog.text = "Qui diable es-tu ?";
			link.l1 = "Nous avons la cargaison. Intéressé ?";
			link.l1.go = "contra_1";
		break;
		
		case "contra_1":
			dialog.text = "Ha. Très intéressé. Surtout mon client. Quel est le butin ?";
			link.l1 = ""+FindRussianQtyString(sti(pchar.questTemp.FMQL.Sanl))+"de bois de fer, "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Silk))+" de navire de soie, "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Rope))+" de corde et "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Oil))+" de résine.";
			link.l1.go = "contra_2";
		break;
		
		case "contra_2":// Addon 2016-1 Jason пиратская линейка
			iTotalTemp = 2200*sti(pchar.questTemp.FMQL.Sanl)+1600*sti(pchar.questTemp.FMQL.Silk)+1000*sti(pchar.questTemp.FMQL.Rope)+900*sti(pchar.questTemp.FMQL.Oil);
			dialog.text = "Très bien. 2200 pesos pour chaque pièce de bois de fer, 900 pesos pour la résine, 1600 pesos pour la soie de navire et 1000 pesos pour les cordages. Qu'avons-nous ici... Eh bien-bien. "+iTotalTemp+" pesos. Marché conclu ?";
			link.l1 = "Marché conclu !";
			link.l1.go = "contra_3";
		break;
		
		case "contra_3":
			LAi_Fade("", "");
			FMQL_CreateGuidesWarriors();
			dialog.text = "Splendide ! Apportez-en plus. Les Hollandais ne cessent d'être généreux avec les peaux-rouges... Et qui sont ces invités ? Qu'est-ce que c'est que ce bordel ?!";
			link.l1 = "";
			link.l1.go = "contra_4";
		break;
		
		case "contra_4":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_19";
			AddMoneyToCharacter(sld, iTotalTemp);
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FMQL_beach":
			pchar.quest.FMQL_pirate_dead.over = "yes";
			LAi_RemoveCheckMinHP(npchar);
			dialog.text = "Oui, capitaine. J'avais trop bu pour une raison.";
			link.l1 = "Toi ? Comment ?!";
			link.l1.go = "FMQL_beach_1";
		break;
		
		case "FMQL_beach_1":
			dialog.text = "Je suis désolé, capitaine. J'ai dû boire une ou deux tasses après ce bazar avec les Indiens. Il y avait une fille, j'ai pris une chambre pour cent pesos et elle... elle...";
			link.l1 = "Quoi ? Vous dévalisé ?";
			link.l1.go = "FMQL_beach_2";
		break;
		
		case "FMQL_beach_2":
			sld = CharacterFromID("FMQL_Prosper");
			dialog.text = "Non ! Elle est tombée amoureuse ! Nom de Dieu, j'aurais dû m'enfuir de là ! Mais alors ton ami se pointe, me hurlant dessus à propos de cette racaille, ton ancien compagnon, qui veut te rouler et te tuer.";
			if (LAi_GetCharacterHP(sld) > 0)
			{
				link.l1 = "Bien joué, Prosper...";
				link.l1.go = "FMQL_beach_3";
			}
			else
			{
				link.l1 = "Prosper... Je suis tellement désolé. Je m'occuperai de ta fille. Leçon apprise, monsieur Gregoire... Qu'avez-vous dit ? À chacun son dû ? Je devrais m'en souvenir.";
				link.l1.go = "FMQL_beach_3";
			}
		break;
		
		case "FMQL_beach_3":
			dialog.text = "Allons-nous y aller, capitaine ?";
			link.l1 = "Ouais. Merci pour votre service. Éloigne-toi d'une chope et nous te sauverons de cette beauté. Allons-y.";
			if (CheckAttribute(pchar, "questTemp.FMQL.ProsperDead")) link.l1.go = "FMQL_beach_5";
			else link.l1.go = "FMQL_beach_4";
		break;
		
		case "FMQL_beach_4": // Проспер жив
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload_sea", "none", "", "", "FMQL_PirateNormal", 10.0);
			sld = CharacterFromID("FMQL_Prosper");
			sld.Dialog.currentnode = "prosper_11";
			sld.MusketerDistance = 20;
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0); 
		break;
		
		case "FMQL_beach_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "FMQL_PirateNormal", 10.0);
			if (sti(pchar.money) >= 20000) DoQuestFunctionDelay("FMQL_MoneyForSelina", 0.5);
			else
			{
				pchar.quest.FMQL_money_20k.win_condition.l1 = "Money";
				pchar.quest.FMQL_money_20k.win_condition.l1.value = 20000;
				pchar.quest.FMQL_money_20k.win_condition.l1.operation = ">=";
				pchar.quest.FMQL_money_20k.function = "FMQL_MoneyForSelina";
			}
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
			AddQuestRecord("FMQ_Lesson", "10");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
