// Джессика Роуз - нежить и супербосс
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	float locx, locy, locz;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Tu veux quelque chose ?";
			link.l1 = "Non, ce n'est rien.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// бой на рифе
		case "reef":
			PlaySound("Voice\English\saga\Jessica Rose-06.wav");
			dialog.text = "Toi ! Tu l'as amenée ici ! Elle est de sa chair et de son sang ! Elle est de sa chair et de son sang ! La fille de la putain est venue sur la tombe de sa mère ! Elle mourra ! Et tu ne pourras pas l'empêcher ! Ne te mets pas en travers de Jessica ! Que la vengeance soit mienne !";
			link.l1 = "...";
			link.l1.go = "reef_1";
		break;
		
		case "reef_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "stage_1":
			PlaySound("Voice\English\saga\Jessica Rose-07.wav");
			dialog.text = "Ha ! Vous ne pouvez pas me blesser !\n L'air, l'eau, la terre, le feu - je vous ordonne de m'assister !\n Que les morts se lèvent, que le feu brûle, que l'eau garde le pont et que le vent vous prenne sur ses ailes et vous jette à terre !\n Amusez-vous bien !!!";
			link.l1 = "May I help you?";
			link.l1.go = "stage_1_exit";
		break;
		
		case "stage_1_exit":
			DialogExit();
			LAi_SetActorType(pchar);
			CreateLocationParticles("blast_inv", "quest", "top", 1.6, 0, 0, "");
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "goto", LAi_FindFarFreeLocator("goto", locx, locy, locz));
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaFirstKick_2", 3.5);
			SetCameraShake(4.0, 12.0, 0.1, 0.1, 0.05, true, false, -1);
		break;
		
		case "stage_2":
			PlaySound("Voice\English\saga\Jessica Rose-08.wav");
			dialog.text = "Ha ! Tu ne peux pas me blesser !\nQue plus de morts se lèvent et attaquent, que le feu brûle la pierre, que le vent t'emporte et te jette à terre et que la terre absorbe tes forces !\nAmuse-toi bien !!!";
			link.l1 = "...";
			link.l1.go = "stage_2_exit";
		break;
		
		case "stage_2_exit":
			DialogExit();
			LAi_SetActorType(pchar);
			CreateLocationParticles("blast_inv", "quest", "rock", 1.6, 0, 0, "");
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.BladePenalty = 30;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaSecondKick_2", 3.5);
			SetCameraShake(4.0, 12.0, 0.1, 0.1, 0.05, true, false, -1);
		break;
		
		case "stage_3":
			PlaySound("Voice\English\saga\Jessica Rose-07.wav");
			dialog.text = "Ha ! Tu ne peux pas me blesser !\nQue le poison couvre mon épée à lame flamboyante, que le vent t'emporte dans ses étreintes, que l'eau boive ta vivacité !\nMeurs ! Ha-ha-ha !";
			link.l1 = "... ";
			link.l1.go = "stage_3_exit";
		break;
		
		case "stage_3_exit":
			DialogExit();
			npchar.viper = true;
			TakeNItems(npchar, "potion2", 3);
			LAi_SetActorType(pchar);
			PlaySound("Sea Battles_01\Bomb_Explosion_03.wav");
			PlaySound("People Fight\Death_NPC_08.wav");
			pchar.GenQuest.EnergyPenalty = 2;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(pchar, "shore67", "quest", "bridge2");
			LAi_ActorTurnToLocator(pchar, "quest", "bridge1");
			LAi_ActorAnimation(Pchar, "Ground_sitting", "", 3.5);
			DoQuestCheckDelay("Saga_JessikaThirdKick_2", 3.5);
			SetCameraShake(4.0, 12.0, 0.1, 0.1, 0.05, true, false, -1);
		break;
		
		case "stage_4":
			PlayStereoOGG("music_shore");
			sld = characterFromId("Svenson");
			dialog.text = "Assez... Je suis fatigué. Je suis vaincu... Ayez pitié du sort de la pauvre Jessica !";
			link.l1 = "Bien sûr... Je vais épargner à ta pauvre âme le poids de ce cadavre !";
			link.l1.go = "exit_battle";
			if (CheckAttribute(sld, "quest.jessika_peace")) // выслушал историю Джессики
			{
				link.l2 = "Je connais ton histoire, Jessica. Et je suis désolé que ta vie ait été si triste et se soit terminée de cette façon. Tu veux me parler, n'est-ce pas ? Eh bien, je vais essayer d'oublier que tu as récemment tenté de me tuer et je vais t'écouter, même si ce ne sera pas facile pour moi...";
				link.l2.go = "exit_talk";
			}
		break;
		
		case "exit_battle":
			DialogExit();
			SetMusic("music_teleport");
			DeleteAttribute(npchar, "viper");
			LAi_SetImmortal(npchar, false);
			npchar.chr_ai.hp = stf(npchar.chr_ai.hp)+100;
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Saga_JessikaDie");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.Saga.JessSeekTreatment = 0;
			LAi_LocationDisableOfficersGen(pchar.location, false);//офицеров пускать
		break;
		
		case "exit_talk":
			dialog.text = "Merci... Tu sais déjà pour Béatrice Sharp et Lawrence... mon Lawrence. Je l'ai tuée sans hésiter, mais je n'ai pas pu le tuer. Je ne pouvais pas le faire, mais lui, il pouvait. Jessica est morte...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Reef");
			NextDiag.TempNode = "exit_talk_0";
		break;
		
		case "exit_talk_0":
			dialog.text = "... mais le vœu de sang, lié par un terrible serment, est encore non accompli. La puissance de ce vœu provient de la magie indienne. Elle a ressuscité le cadavre de sa tombe.\nLa haine a transformé mon âme en désert. Tous ceux qui sont venus sur ce récif ont été massacrés par ma main et leurs cadavres sont devenus mes marionnettes. Je ne peux demander de l'aide à personne d'autre que celui qui m'a vaincu...";
			link.l1 = "Et que puis-je faire pour vous? La seule chose que je puisse faire, c'est de vous épargner la souffrance...";
			link.l1.go = "exit_talk_1";
		break;
		
		case "exit_talk_1":
			PlaySound("Voice\English\saga\Jessica Rose-03.wav");
			dialog.text = "Aidez-moi... Emmenez-moi à lui.";
			link.l1 = "À Lawrence Beltrope ? Et comment suis-je censé faire cela ? Mon équipage s'enfuira dès qu'ils te verront ou ils te brûleront sans remords. D'ailleurs, tu es toujours capable de massacrer mes hommes et de les 'contrôler'...";
			link.l1.go = "exit_talk_2";
		break;
		
		case "exit_talk_2":
			dialog.text = "Ils ne me verront pas. Mais toi, tu me verras. Tu as dû déjà comprendre que je possède des pouvoirs inaccessibles aux vivants. Mais je ne peux monter à bord de ton navire sans ta permission. Emmène-moi à lui.\nJe ne resterai pas longtemps avec vous. Et je ne ferai pas de mal à ton équipage. Dépose-moi à la baie de Portland en Jamaïque à minuit, la nuit suivante nous nous reverrons et tu recevras ce que tu cherchais ici.";
			link.l1 = "Comment savez-vous pourquoi je suis ici ?";
			link.l1.go = "exit_talk_3";
		break;
		
		case "exit_talk_3":
			PlaySound("Voice\English\saga\Jessica Rose-01.wav");
			dialog.text = "Je sais beaucoup de choses. Plus que les vivants. Je l'ai vue... Tu as besoin d'un document pour elle et tu l'obtiendras. Tu obtiendras encore plus, je te donnerai quelque chose en plus. Emmène-moi à lui...";
			link.l1 = "Hm. Je n'aime pas tes intentions sanguinaires envers Helen. N'ose même pas la toucher. Après tout, elle n'est pas responsable des actions de sa mère.";
			link.l1.go = "exit_talk_4";
		break;
		
		case "exit_talk_4":
			dialog.text = "Tu m'as vaincu. Je ne lui ferai aucun mal... Je le promets.";
			link.l1 = "Ce n'est pas encore fini. Vas-tu me libérer de tes innombrables malédictions? J'admets que l'idée de vivre avec elles pour toujours ne me plaît guère...";
			link.l1.go = "exit_talk_5";
		break;
		
		case "exit_talk_5":
			dialog.text = "Ce n'est pas si simple... Quand nous nous retrouverons à Portland Cove après que je... je te dirai comment te soigner.";
			link.l1 = "Apres vous quoi?.. Qu'entendez-vous par là?";
			link.l1.go = "exit_talk_6";
		break;
		
		case "exit_talk_6":
			dialog.text = "Après ma rencontre avec lui.";
			link.l1 = "Oh, il ne sera pas content. Je peux imaginer. Bien, résumons : premièrement, tu promets que personne ne te verra, deuxièmement, tu ne feras aucun mal à mon équipage, troisièmement, tu n'auras même pas une pensée pour Hélène, quatrièmement, tu me donneras ce que je cherche, et cinquièmement, tu me guériras de tes malédictions. Ai-je raison ?";
			link.l1.go = "exit_talk_7";
		break;
		
		case "exit_talk_7":
			dialog.text = "Presque. Je ne vais pas te guérir, mais je te dirai comment faire. Tu devras le faire toi-même.";
			link.l1 = "D'accord. Marché conclu alors. Je vous permets de monter à bord de mon navire.";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Reef2");
			NextDiag.TempNode = "exit_talk_8";
		break;
		
		case "exit_talk_8":
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			dialog.text = "";
			link.l1 = "Hé ! Où es-tu ? Disparu juste comme ça...";
			link.l1.go = "exit_talk_9";
		break;
		
		case "exit_talk_9":
			DialogExit();
			LAi_group_Delete("EnemyFight");
			pchar.quest.Saga_JessFire.over = "yes"; 
			pchar.quest.Saga_JessFire1.over = "yes"; 
			pchar.quest.Saga_JessFire2.over = "yes";
			ref chr = &Locations[FindLocation(pchar.location)];
			DeleteAttribute(chr, "hell_fire_1");
			DeleteAttribute(chr, "hell_fire_2");
			DeleteAttribute(chr, "hell_fire_3");
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			AddQuestRecord("Shadows", "9");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.Saga.JessOnShip = "true"; // атрибут на отрицательные последствия
			pchar.quest.Saga_Jessika_Travel.win_condition.l1 = "Hour";
			pchar.quest.Saga_Jessika_Travel.win_condition.l1.start.hour = 0.00;
			pchar.quest.Saga_Jessika_Travel.win_condition.l1.finish.hour = 2.00;
			pchar.quest.Saga_Jessika_Travel.win_condition.l2 = "location";
			pchar.quest.Saga_Jessika_Travel.win_condition.l2.location = "shore36";
			pchar.quest.Saga_Jessika_Travel.function = "Saga_JessikaOnJamaica";
			NextDiag.CurrentNode = "shore";
			npchar.greeting = "jessika_2";
			LAi_LocationDisableOfficersGen(pchar.location, false);//офицеров пускать
			LAi_LocationDisableOfficersGen("shore36", true);//офицеров не пускать в бухту Портленд
		break;
		
		case "shore":
			dialog.text = "Tu as tenu ta promesse - nous sommes en Jamaïque. Viens ici demain soir et je tiendrai la mienne. Adieu.";
			link.l1 = "Adieu...";
			link.l1.go = "shore_1";
		break;
		
		case "shore_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Saga.JessOnShip");
			DeleteAttribute(npchar, "SaveItemsForDead");
			DeleteAttribute(npchar, "DontClearDead");
			LAi_SetActorType(npchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			AddQuestRecord("Shadows", "10");
			SetFunctionTimerCondition("Saga_JessikaShoreWait", 0, 0, 1, false);
			NextDiag.CurrentNode = "shore_2";
			npchar.greeting = "jessika_3";
		break;
		
		case "shore_2":
			dialog.text = "C'est fini, "+pchar.name+"...";
			link.l1 = "Que veux-tu dire ?";
			link.l1.go = "shore_3";
		break;
		
		case "shore_3":
			dialog.text = "C'est fini... Tiens, prends-le, c'est ce que tu cherchais. C'est la lettre de ma rivale, elle a été enterrée avec elle. Elle est bien conservée. Je lui ai pardonné et il n'y a plus de haine dans mon âme.";
			link.l1 = "As-tu... rencontré avec lui? Avec Lawrence?";
			link.l1.go = "shore_4";
		break;
		
		case "shore_4":
			GiveItem2Character(pchar, "letter_beatriss"); // дать письмо
			AddQuestRecordInfo("Letter_beatriss", "1");
			dialog.text = "Oui. La dernière chose qu'il a ressentie dans sa vie était l'horreur. Je ne le plains pas.";
			link.l1 = "Puisse Dieu pardonner son âme pécheresse... Il semble que je ne le rencontrerai jamais.";
			link.l1.go = "shore_5";
		break;
		
		case "shore_5":
			dialog.text = "Tu n'as rien perdu de valeur. C'était un homme très mauvais. Maintenant, nous devrions nous dire adieu, il ne me reste plus rien à faire ici. Mon serment a été accompli et la magie a perdu son pouvoir. Je t'ai promis un cadeau. Tiens. Voici mon Flamberge. Je n'en ai plus besoin. Cette lame est unique, tu n'en trouveras pas de meilleure dans le monde entier.";
			link.l1 = "Merci...";
			link.l1.go = "shore_6";
		break;
		
		case "shore_6":
			RemoveAllCharacterItems(npchar, true);
			GiveItem2Character(pchar, "blade_25");
			PlaySound("interface\important_item.wav");
			dialog.text = "Maintenant, à propos de toi. Va à Bridgetown, à l'église locale, pour lever mes malédictions. Tu y trouveras un prêtre. Il me connaissait personnellement. Parle-lui et il te dira quoi faire. Prépare vingt bougies, tu en auras besoin.";
			link.l1 = "Es-tu sûr qu'il me guérira ?";
			link.l1.go = "shore_7";
		break;
		
		case "shore_7":
			dialog.text = "Vous le ferez vous-même. Dieu vous guidera. Soyez sûr. Tout ira bien.";
			link.l1 = "Très bien, je vais naviguer vers la Barbade immédiatement. Et maintenant ?";
			link.l1.go = "shore_8";
		break;
		
		case "shore_8":
			PlaySound("Voice\English\saga\Jessica Rose-04.wav");
			dialog.text = "Et maintenant je souhaite une dernière chose. Enterre mon corps ici dans cette baie près de la mer. Je le veux. Peut-être qu'un jour tu visiteras la tombe de la pauvre Jessica. Adieu, "+pchar.name+", et priez pour moi...";
			link.l1 = "Jess?..";
			link.l1.go = "shore_9";
		break;
		
		case "shore_9":
			DialogExit();
			LAi_KillCharacter(npchar);
			bQuestDisableMapEnter = false;
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("shore36", false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddQuestRecord("Shadows", "11");
			pchar.questTemp.Saga.JessTreatment = "true";
			// вытираем Белтропа
			sld = characterFromId("Beltrop");
			sld.lifeday = 0;
			pchar.questTemp.Saga.Beltrop_die = "true"; // Белтроп убит
			sld = ItemsFromID("letter_jess");
			sld.price = 1; // страницу можно выкладывать 270912 
		break;
		
		case "soul":
			dialog.text = "Me reconnaissez-vous, Capitaine ?";
			link.l1 = "Est-ce... est-ce toi ? Mais comment ?";
			link.l1.go = "soul_1";
		break;
		
		case "soul_1":
			dialog.text = "Oui, "+pchar.name+", c'est moi, c'est Jessica ! Du moins, quand je ressemblais à ça il y a vingt ans.";
			link.l1 = "Alors... suis-je mort? Mais quand? Comment?";
			link.l1.go = "soul_2";
		break;
		
		case "soul_2":
			dialog.text = "Tu n'es pas mort, "+pchar.name+". Tu es dans l'église de Bridgetown maintenant. Tu es juste... en train de dormir.";
			link.l1 = "Est-ce juste un rêve ? Les choses semblent trop réelles...";
			link.l1.go = "soul_3";
		break;
		
		case "soul_3":
			dialog.text = "Ça arrive parfois, "+pchar.name+". Dieu vous a entendu. Vos prières non seulement vous ont guéri, mais ont aussi purifié mon âme. Merci beaucoup, "+pchar.name+" ! Et je veux te demander de me pardonner pour ce qui s'est passé au récif. C'est... enfin, pardonne-moi. Je ne pouvais pas partir sans te demander pardon.";
			link.l1 = "Je te pardonne, Jessica. Suis-je vraiment vivant ?";
			link.l1.go = "soul_4";
		break;
		
		case "soul_4":
			dialog.text = "Tu es... Ne t'inquiète pas. Bientôt tu te réveilleras. Je voulais juste te dire adieu.";
			link.l1 = "Tu es si... belle !";
			link.l1.go = "soul_5";
		break;
		
		case "soul_5":
			dialog.text = "Aimes-tu moi ? Oui, il fut un temps où les meilleurs prétendants des Petites Antilles me courtisaient et chaque troisième pirate de l'Isla Tesoro était prêt à se battre en duel pour moi.";
			link.l1 = "Mais tu n'as toujours eu besoin que d'un seul... Eh, talisman roux ! Dis-moi juste, pourquoi as-tu fini comme ça ?";
			link.l1.go = "soul_6";
		break;
		
		case "soul_6":
			dialog.text = "À cause de ma colère. À cause de ma haine. À cause de l'incapacité à comprendre, pardonner et oublier. J'aurais pu commencer une nouvelle vie, mais j'ai préféré me consacrer à une vengeance stupide et inutile. Vous m'avez libéré. Merci, "+pchar.name+"...";
			link.l1 = "Je suis vraiment désolé pour ta vie...";
			link.l1.go = "soul_7";
		break;
		
		// здесь проверяем Мэри
		case "soul_7":
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{ // Мэри-офицер
				dialog.text = "N'arrête pas... Tu as encore ton talisman de gingembre...";
				link.l1 = "Mon quoi ?";
				link.l1.go = "mary_1";
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && CheckAttribute(pchar, "questTemp.LSC.marywait"))
			{ // Мэри осталась на острове
				dialog.text = "N'arrête pas... Tu as encore ton talisman de gingembre...";
				link.l1 = "Mon quoi?";
				link.l1.go = "mary_3";
				break;
			}
			dialog.text = "Ne... Considérez mon expérience triste et ne répétez pas mes erreurs. Et ne laissez pas non plus les personnes que vous aimez les faire.";
			link.l1 = "Je prendrai cela en considération et je ne ferai sûrement pas les mêmes erreurs...";
			link.l1.go = "soul_8";
		break;
		
		case "mary_1":
			dialog.text = "Réfléchis un peu. Elle est sur ton navire.";
			link.l1 = "Mary?!";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "Oui. Elle est la meilleure que tu auras jamais dans ta vie. Souviens-toi de cela. Son amour est pur, sa dévotion est infinie. Elle est courageuse, jeune, mais désespérée et inexpérimentée. Elle ne comprend pas grand-chose. Prends soin d'elle, protège-la et ne laisse personne se mettre entre vous deux. Elle est ton talisman...";
			link.l1 = "Je... Je ne la quitterai jamais et je la protègerai de tout danger.";
			link.l1.go = "soul_8";
		break;
		
		case "mary_3":
			dialog.text = "Elle est sur l'île étrange faite de navires morts... Elle n'y est pas seule, mais elle est solitaire. Chaque matin, elle commence par une pensée pour toi, chaque jour elle prie pour toi, chaque nuit une lumière brille dans sa cabine et son oreiller est mouillé à cause de ses larmes...";
			link.l1 = "Marie...";
			link.l1.go = "mary_4";
		break;
		
		case "mary_4":
			dialog.text = "Il y a une fille entre vous deux. La fille de la femme qui s'est jadis interposée entre moi et Lawrence. Le destin de ton talisman est entre tes mains. Ils ne peuvent pas coexister ensemble tout comme Beatrice et moi ne le pouvions pas.";
			link.l1 = "Comment le sais-tu ?";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "L'autre côté... Il montre beaucoup... C'est ton choix, mais souviens-toi : Mary est la meilleure que tu auras jamais dans ta vie. Son amour est pur, sa dévotion est infinie. Elle est courageuse, jeune, mais désespérée et inexpérimentée. Elle ne comprend pas grand-chose. Elle a besoin de ta protection, de tes soins et de ton amour. Elle est ton talisman.";
			link.l1 = "Je vais y réfléchir. Je vais sûrement le faire...";
			link.l1.go = "soul_8";
		break;
		
		case "soul_8":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_friend")) sTemp = "";
			else sTemp = "And about the daughter of Beatrice, know that your noble actions on her behalf will be left unvalued. Soon you will see that for yourself. Be careful with her. Well...\n";
			dialog.text = ""+sTemp+"Je dois partir. Il est temps de dire adieu... Pour de bon cette fois. N'oublie pas Jessica et essaie de visiter sa tombe de temps en temps... Toi seul sais où elle se trouve.";
			link.l1 = "Bien sûr, Jess. Je le visiterai et je prierai pour toi.";
			link.l1.go = "soul_9";
		break;
		
		case "soul_9":
			dialog.text = "Merci. Au revoir, "+pchar.name+"Adieu !";
			link.l1 = "Adieu, Jessica...";
			link.l1.go = "soul_10";
		break;
		
		case "soul_10":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_JessikaSoul_4", -1);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
