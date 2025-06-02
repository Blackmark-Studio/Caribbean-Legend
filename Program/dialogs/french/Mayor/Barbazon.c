// Жак Барбазон в Ле Франсуа
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc, sTemp;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

//--> -----------------------------------------------блок angry-------------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
//<-- -------------------------------------------блок angry------------------------------------------------------

	switch(Dialog.CurrentNode)
	{
	// ----------------------------------- Диалог первый - первая встреча---------------------------------------
		case "First time":
            dialog.text = NPCStringReactionRepeat("As-tu quelque chose à me dire ? Non ? Alors dégage d'ici !","Je pense avoir été clair, cesse de m'importuner.","Bien que je me sois fait comprendre, tu continues à m'agacer !","D'accord, je commence à en avoir marre de cette grossièreté.","répéter",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Je pars déjà.","D'accord, Jacques...","Désolé, Jacques...","Aïe...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Es-tu fou ? Voulais-tu jouer au boucher ? Tous les pirates sont en colère contre toi, garçon, tu ferais mieux de quitter cet endroit...","Il semble que tu sois devenu fou, garçon. Tu voulais te dégourdir un peu les mains ? Sans vouloir t'offenser, mais tu n'as rien à faire ici. Dégage !");
				link.l1 = RandPhraseSimple("Ecoute, je veux arranger la situation...","Aidez-moi à résoudre ce problème...");
				link.l1.go = "pirate_town";
				break;
			}
			
		//----------------------------------Сага - искушение Барбазона---------------------------------------
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "begin")
			{
				link.l1 = "Je dois te parler, Jacques... En privé.";
				link.l1.go = "Temptation";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "give_silk" && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 60)
			{
				link.l1 = "Je viens de Saint Martin, Jacques...";
				link.l1.go = "Temptation_6";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
			{
				link.l1 = "Et quand vas-tu arrêter d'aboyer et commencer à parler comme un homme, Jacques ? Tu ne t'attendais pas à me voir ?";
				link.l1.go = "terrax";
			}
			
			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
				{
					link.l1 = "Je suis ici pour parler de votre prisonnier.";
					link.l1.go = "CapComission1";
					DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
				}
             	
				if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") // лесник. новая проверка. искл. возможность сразу сдать задание,минуя 15 дней.
				{
					link.l1 = "Bonjour, Jacques, je suis ici à cause de ta mission.";
					link.l1.go = "CapComission3";
				}
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak") && !CheckAttribute(pchar,"GenQuest.CaptainComission.vikupzaplatil")) 
				{ // лесник . второй диалог с проверкой ,если ГГ ещё не принес деньги за выкуп.
					link.l1 = "Je suis ici à propos de votre prisonnier.";
					link.l1.go = "CapComission6";
				}
			}	
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "J'ai entendu dire que vous êtes impliqué dans des affaires liées aux prisonniers...";
				link.l1.go = "Marginpassenger";
			}
		break;
			

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar)+"! Que veux-tu cette fois-ci ?","As-tu oublié de me dire quelque chose ? Je t'écoute.","Combien de temps cela va-t-il durer... Si tu n'as rien à faire, alors ne dérange pas les autres !","Vous m'avez demandé d'être poli. Mais j'exige la même chose de vous !","répéter",10,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("C'est rien. Juste une visite.","Rien...","D'accord...","Tu as raison. Je suis désolé.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";

			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Es-tu fou ? Tu voulais jouer au boucher ? Tous les pirates sont en colère contre toi, garçon, tu ferais mieux de quitter cet endroit...","On dirait que tu es devenu fou, garçon. Tu voulais te dégourdir un peu les mains ? Pas d'offense, mais tu n'as rien à faire ici. Dégage !");
				link.l1 = RandPhraseSimple("Ecoute, je veux arranger la situation...","Aidez-moi à résoudre ce problème...");
				link.l1.go = "pirate_town";
				break;
			}

			//поручение капитана - выкуп
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar,"GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "Je suis ici pour votre prisonnier.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
			}	
			if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway")//  правка лесник,новая проверка ,исключающая тут же сдачу задания
			{
				link.l1 = "Bonjour, Jacques, c'est au sujet de ta mission.";
				link.l1.go = "CapComission3";
			}
		/*	if(CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak")) //лишний диалог лесник
			{
				link.l1 = "Je suis ici à propos de votre prisonnier.";
				link.l1.go = "CapComission6";
			}*/
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				link.l1 = "J'ai entendu dire que tu étais impliqué dans des affaires concernant des prisonniers...";
				link.l1.go = "Marginpassenger";
			}
		break;

//--> -----------------------------------Сага - Искушение Барбазона---------------------------------------------
		case "Temptation":
			dialog.text = "Sais-tu que m'importuner est risqué ? Très bien, je t'écoute.";
			link.l1 = "J'ai une dette. Une grosse. Le temps de payer approche et je n'ai pas un sou. Des gens bien ont chuchoté que tu as un talent pour élaborer des plans et que tu sais toujours où décrocher le gros lot...";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_1":
			dialog.text = "Ecoute, garçon ! Je suis Jacques le Bienveillant seulement pour ceux qui me sont loyaux. Pour les autres, je suis Barbazon et parfois Lucifer lui-même. Comment pourrais-je savoir que je peux te faire confiance ?";
			link.l1 = "Essaie-moi. Je te jure que tu ne le regretteras pas !";
			link.l1.go = "Temptation_2";
		break;
		
		case "Temptation_2":
			dialog.text = "Hm... Je suppose que tu sais ce que Jacques le Gentilhomme fait aux gens qui le trompent, n'est-ce pas ? Quoi qu'il en soit, je ne te confondrai pas avec des détails terribles. J'ai une petite mission. Si tu réussis, alors tous tes problèmes financiers sont réglés.";
			link.l1 = "Ne doute pas de moi, j'ai été dans beaucoup de combats et...";
			link.l1.go = "Temptation_3";
		break;
		
		case "Temptation_3":
			dialog.text = "Tais-toi et écoute-moi ! Il y a quelques semaines, une patrouille hollandaise a capturé l'un de mes employés non loin de Saint-Martin. Il me livrait de la soie hollandaise. C'est très rare, les Hollandais n'apportent ici que de petits lots pour les besoins de la marine de la Compagnie.\nDonc, j'ai réussi à obtenir six balles de soie et Simon Morel était censé me les apporter sur sa brigantine 'Chien Salé', mais il a croisé une patrouille hollandaise par accident. Ou pas par accident. C'est ce que m'a dit le navigateur de Morel, il m'a dit qu'il était le seul à avoir survécu au combat.\nIl m'a aussi donné le journal de bord de Morel qui confirme l'histoire. Selon le journal, Morel avait jeté la soie lors d'une tentative de fuite. C'est étrange, non ? La soie est légère. Ils auraient dû jeter leurs canons, ils n'avaient de toute façon aucune chance contre la patrouille.";
			link.l1 = "Il y a vraiment quelque chose qui cloche ici.";
			link.l1.go = "Temptation_4";
		break;
		
		case "Temptation_4":
			dialog.text = "Tout est possible. Beaucoup d'hommes courageux travaillent pour moi et bien moins intelligents. Sans vouloir t'offenser, heh. Tu dois vérifier l'endroit où Morel s'est débarrassé de la cargaison. C'est à 21 degrés 10' Nord et 61 degrés 30' Ouest selon le journal de bord du capitaine.\nLes Hollandais enroulent la soie autour de tiges de liège, donc les ballots doivent encore flotter à la surface. Il doit y avoir six ballots. Mets les voiles immédiatement, le temps presse.";
			link.l1 = "Je suis en route !";
			link.l1.go = "Temptation_5";
		break;
		
		case "Temptation_5":
			DialogExit();
			SetFunctionTimerCondition("Saga_BarbTemptationOver", 0, 0, 10, false); // таймер
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			pchar.quest.BarbTemptation.win_condition.l1 = "location";
			pchar.quest.BarbTemptation.win_condition.l1.location = "SentMartin";
			pchar.quest.BarbTemptation.function = "Saga_BarbTemptationBarkas";
			pchar.questTemp.Saga.BarbTemptation = "silk";
			AddQuestRecord("BarbTemptation", "2");
		break;
		
		case "Temptation_6":
			dialog.text = "Super ! As-tu trouvé ma soie ?";
			link.l1 = "Oui, six d'entre eux comme tu l'as dit.";
			link.l1.go = "temptation_wrong";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 90)
			{
				link.l2 = "Oui. Mais ils étaient plus nombreux que tu ne l'avais dit, neuf, pas six. Je les ai tous amenés ici, à toi de comprendre comment cela a pu arriver.";
				link.l2.go = "temptation_right";
			}
		break;
		
		case "temptation_wrong":
			dialog.text = "Mauvaise réponse. Il aurait dû y avoir neuf balles. Et si tu en as trouvé six, alors tu as dû trouver le reste. Donc, soit tu es un rat, soit juste un idiot paresseux. Tu me dois trois balles de soie et trois de plus comme... 'compensation morale' pour avoir essayé de m'arnaquer.";
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 120)
			{
				link.l1 = "Quel petit malin ! Je m'en souviendrai. Voilà ta soie et oublions ma faute.";
				link.l1.go = "temptation_wrong_1";
			}
			link.l2 = "On m'a dit qu'il y avait six ballots, pas un de plus. Je t'ai donné tout ce que j'ai trouvé et je me fous de ce que tu penses. Je n'ai plus de soie.";
			link.l2.go = "temptation_wrong_2";
		break;
		
		case "temptation_wrong_1":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 120);
			dialog.text = "Bien. J'espère que cela ne se reproduira pas, car je veux te confier une tâche importante. Combien d'argent veux-tu gagner ?";
			link.l1 = "L'argent est toujours bienvenu, pour l'instant cinquante mille pesos feraient l'affaire.";
			link.l1.go = "junior";
		break;
		
		case "temptation_wrong_2":
			dialog.text = "Oh, c'est comme ça que tu parles maintenant ! Tu ne t'en tireras pas comme ça. Je t'ai prévenu - n'essaie pas de m'arnaquer, bon sang ! Gardes ! Il y a un foutu rat dans la résidence !";
			link.l1 = "Merde !";
			link.l1.go = "temptation_wrong_fight";
		break;
		
		case "temptation_wrong_fight":
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetWarriorType(npchar);
			ChangeCharacterAddressGroup(npchar, "LeFransua_townhall", "goto", "goto1");
			LAi_SetImmortal(npchar, true);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i = 1; i <= 3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("BarbGuard_"+i, "citiz_4"+(i+6), "man", "man", 80, PIRATE, 1, true, "quest"));
				FantomMakeCoolFighter(sld, 80, 100, 100, "blade_21", "pistol4", "bullet", 3000);
				ChangeCharacterAddressGroup(sld, "LeFransua_townhall", "reload", "reload1");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "temptation_right":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 80);
			dialog.text = "Bon travail. Je te testais pour voir si tu étais avide et tu as réussi mon épreuve. Il devait y avoir neuf ballots. L'un d'eux est à toi. Maintenant, nous pouvons parler sérieusement. Combien d'argent te faut-il ?";
			link.l1 = "L'argent est toujours bienvenu, pour l'instant cinquante mille pesos feraient l'affaire.";
			link.l1.go = "junior";
		break;
		
		case "junior":
			dialog.text = "Tu as une occasion de gagner encore plus. Un homme sérieux m'a demandé de trouver un gaillard sûr comme toi pour une mission délicate et dangereuse. Cet homme est très riche et il te récompensera généreusement si tu ne le déçois pas.";
			link.l1 = "Je suis prêt.";
			link.l1.go = "junior_1";
		break;
		
		case "junior_1":
			dialog.text = "Très bien. Écoute maintenant. Tu dois trouver son agent nommé 'Canaille'. Il est le capitaine du polacre 'Marlin', c'est tout ce que je sais de lui. Tu le trouveras à Kapsterville. Le mot de passe est 'la chasse a commencé'. Il te dira quoi faire. Tu ne me dois rien. Je veux juste t'aider. Si tu as de la chance, alors nous nous reverrons.";
			link.l1 = "Merci pour ton aide. Je suis en route !";
			link.l1.go = "junior_2";
		break;
		
		case "junior_2":
			DialogExit();
			AddQuestRecord("BarbTemptation", "7");
			Saga_SetJuniorInCharles(); // ставим Валета
			pchar.questTemp.Saga.BarbTemptation = "valet";
		break;
		
		case "terrax":
			dialog.text = "Quoi ?! Je vais t'arracher...";
			link.l1 = "Tu ne le feras pas, Barbazon. Montrons nos cartes ! Je travaille pour Jan Svenson. J'ai découvert ta conspiration avec Jackman. Je sais tout, ce que tu prévoyais et quel rôle tu avais aussi. Jackman et son frère sont morts, le premier a tué Blaze Sharp et cela a déterminé son sort, le second n'était pas assez bavard, je le crains...";
			link.l1.go = "terrax_1";
		break;
		
		case "terrax_1":
			dialog.text = "Merde ! Tyrex ne me pardonnera jamais pour ça, mais je suis toujours..";
			link.l1 = "Ne fais rien de stupide, Jacques. Je savais que cette conversation ne serait pas facile, alors je me suis préparé. Regarde par la fenêtre... ta cabane est entourée par mes mousquetaires. Mes hommes sont partout dans ton village et il y a un groupe de frappe juste à l'extérieur des portes. Tu veux commencer un massacre ? C'est facile ! ";
			link.l1.go = "terrax_2";
		break;
		
		case "terrax_2":
			dialog.text = "Nom de Dieu ! Que veux-tu ?";
			link.l1 = "Tu ne me croiras pas, Barbazon, mais tout ce que je veux, c'est... la paix ! Je veux la paix. C'est pourquoi je ne dirai rien à Tyrex de ta part dans cette conspiration contre lui. Mais seulement si tu fais ce que je veux...";
			link.l1.go = "terrax_3";
		break;
		
		case "terrax_3":
			dialog.text = "Que veux-tu de moi ? De l'argent ? Combien ?";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				link.l1 = "Oh, non, laissez cela à vos sbires sans cervelle. J'ai besoin de quelque chose de différent. J'ai besoin de votre vote pour Steven Dodson.";
			}
			else
			{
				link.l1 = "Oh, non, laisse ça à tes agents sans cervelle. J'ai besoin de quelque chose de différent. J'ai besoin de ton vote pour Marcus Tyrex.";
			}
			link.l1.go = "terrax_4";
		break;
		
		case "terrax_4":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "And Steven Dodson is on our side.";
			else sTemp = "";
			dialog.text = "Vraiment ? Laisse-moi réfléchir... et que dirais-tu si je dis non ?";
			link.l1 = "Alors tu resteras seul. Absolument seul. Svenson, Tyrex et Hawk se dresseront contre toi."+sTemp+"Je ne leur montrerai que la lettre du coquin, le frère de Jackman, et ma parole sera aussi digne de confiance. Maintenant, combien de temps penses-tu pouvoir rester assis confortablement après ça ?";
			link.l1.go = "terrax_5";
		break;
		
		case "terrax_5":
			dialog.text = "Faucon ? Il est vivant ?!";
			link.l1 = "Il l'est. Je l'ai sauvé du piège tendu par Jackman. Ainsi, le plus proche ami de Jacob sera son ennemi de sang. Et je les rejoindrai, souviens-toi de cela, Barbazon.";
			link.l1.go = "terrax_6";
		break;
		
		case "terrax_6":
			dialog.text = "Jackman n'est pas mon ami ! Que le diable t'emporte ! Tu m'as coincé !";
			link.l1 = "Balivernes. Donne ta voix pour l'homme dont je t'ai parlé et rien ne changera pour toi. Je t'ai déjà dit, Jacques, je veux la paix. Je pourrais faire en sorte que tous les barons te détestent, mais je ne le ferai pas... pas encore.";
			link.l1.go = "terrax_7";
		break;
		
		case "terrax_7":
			GiveItem2Character(pchar, "splinter_jb"); // дать осколок
			dialog.text = "D'accord. Entendu. Tu as ma parole. Tiens, prends mon éclat de pierre, tu en as besoin, n'est-ce pas?";
			link.l1 = "Exactement. Je suis content que nous soyons tombés d'accord, Jacques. Et prends la lettre du 'Coquin' comme un doux souvenir. Ou mieux encore, brûle-la, tu ne veux pas qu'elle soit trouvée. Oh, et une dernière chose...";
			link.l1.go = "terrax_8";
		break;
		
		case "terrax_8":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "Une dernière chose ?! Que veux-tu encore de moi ?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon"))
			{
				link.l1 = "Permets-moi de te rappeler quelque chose. Il n'y a pas si longtemps, tu as envoyé ton chien Ignacio Marco pour m'assassiner. C'est moi qui l'ai tué. C'est moi qui ai enterré ton plan de piller un galion d'or espagnol. C'est moi qui ai envoyé tes amis dans l'embuscade espagnole près de Saint-Martin. Mon nom est Charlie Prince ! Nous en avons fini maintenant, Jacques, et sois plus poli avec moi la prochaine fois que nous nous verrons. Crois-moi, 'garçon', nous nous reverrons, et plus d'une fois je suppose.";
				link.l1.go = "terrax_8_1";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon") && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
				{
					link.l1 = "Laisse-moi te rappeler quelque chose. Il n'y a pas si longtemps, tu as envoyé ton chien Ignacio Marco pour m'assassiner. C'est moi qui l'ai tué. C'est moi qui ai enterré ton plan de piller un galion d'or espagnol. Mon nom est Charlie Prince ! Nous en avons fini maintenant, Jacques, et sois plus poli avec moi la prochaine fois que nous nous verrons. Crois-moi, 'garçon', nous nous reverrons, et plus d'une fois, je suppose. N'oublie pas, j'ai tous les barons pirates de mon côté. Adieu, Barbazon...";
					link.l1.go = "terrax_9";
				}
				else
				{
					link.l1 = "Sois plus poli avec moi la prochaine fois que nous nous verrons. Crois-moi, 'garçon', nous nous reverrons, et plus d'une fois je suppose. N'oublie pas, j'ai tous les barons pirates de mon côté. Adieu, Barbazon...";
					link.l1.go = "terrax_9";
				}
			}
		break;
		
		case "terrax_8_1":
			dialog.text = "";
			link.l1 = "N'oublie pas, j'ai chaque baron pirate à mes côtés. Adieu, Barbazon...";
			link.l1.go = "terrax_9";
		break;
		
		case "terrax_9":
			DialogExit();
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "26");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Saga_SGM_"+i);
				LAi_SetCitizenType(sld);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.lifeday = 0;
			}
			ChangeCharacterComplexReputation(pchar, "fame", 1);
			bDisableFastReload = false;
			LAi_LocationFightDisable(&Locations[FindLocation("LeFransua_town")], false);
		break;

//-----------------------------------Поручение капитана - Выкуп-------------------------------------------------
		case "CapComission1":
			dialog.text = "Ha-ha. Penses-tu que je n'ai qu'un seul prisonnier ici? Nomme-le.";
			link.l1 = pchar.GenQuest.CaptainComission.SlaveName+"Est-il ici ?";
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.toMayor");
		break;

		case "CapComission2":
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = "Il l'était. Je l'ai vendu à ce propriétaire de plantation de la Barbade - le colonel Bishop, quand il était ici il y a une semaine.";
				link.l1 = "Merde...";
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = "Ah, enfin. Je pensais le vendre à ce propriétaire de plantation de la Barbade, il sera ici dans une semaine ou deux... As-tu une rançon ?";
				link.l1 = "Écoute, il y a un petit problème... En fait, je n'ai pas autant d'argent. Mais je suis prêt à travailler.";
				link.l1.go = "CapComission2_2";
				if(makeint(pchar.money) > 150000)
				{
					link.l2 = "C'est bien que tu ne l'aies pas vendu. Voici tes pièces - 150.000 pesos. Où puis-je le trouver ?";
					link.l2.go = "CapComission2_3";
				}	
			}
		break;
		
		case "CapComission2_1":
			dialog.text = "Tu étais trop lent... Et pourquoi te soucies-tu de lui ? Je n'ai négocié qu'avec ses proches.";
			link.l1 = "Ils m'ont demandé de venir ici.";
			link.l1.go = "CapComission2_11";
		break;
		
		case "CapComission2_11":
			dialog.text = "Eh bien, tu es en retard. Je ne peux rien faire.";
			link.l1 = "Ecoute, pour combien l'as-tu vendu, si ce n'est pas un secret ?"; 
			link.l1.go = "CapComission2_12";
		break;
		
		case "CapComission2_12":
			dialog.text = "Eh, ce n'est pas ça. Mais je ne te le dirai pas... Tu vas rire si je le fais. Ha-ha-ha-ha ! Adieu.";
			link.l1 = "À   plus tard.";
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");//правка лесник.  в СЖ запись ниже не работает																																				  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			CaptainComission_GenerateManager();
		break;
		
		case "CapComission2_2":
			if(rand(3) == 1)
			{

				dialog.text = "Eh bien, "+pchar.name+", tu sais, ça ne marche pas comme ça. Reviens avec l'argent et tu auras ton faiblard, ha-ha.";
				link.l1 = "D'accord. À bientôt.";
				link.l1.go = "CapComission2_4";
			}
			else
			{
				dialog.text = "Eh bien, eh bien.. J'ai une affaire à régler... Je ne sais même pas par où commencer. J'ai besoin de couler un pirate qui a franchi la ligne.";
				link.l1 = "Ne peut-il pas simplement être tué dans la jungle ?";
				link.l1.go = "CapComission2_2_1";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = "Ce n'est pas comme ça que les affaires fonctionnent, tu sais... Je n'ai pas besoin de sa mort, je dois apprendre à certaines personnes à éviter de prendre ma part du butin. Mais s'il finit par nourrir les requins, ça ne me dérangera pas.";
			link.l1 = "Pourquoi n'envoies-tu pas tes propres hommes à sa poursuite ?";
			link.l1.go = "CapComission2_2_2";
		break;
		
		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Dat"); // belamour gen
			dialog.text = "Hm... Eh bien, "+GetName(NAMETYPE_ORIG,pchar.GenQuest.CaptainComission.UnknownPirateName,NAME_NOM)+"a convaincu quelques pirates que leur part du butin est gardée dans notre cachette non loin de "+XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore+"Gén")+". Leurs deux navires '"+pchar.GenQuest.CaptainComission.ShipName1+"' et '"+pchar.GenQuest.CaptainComission.ShipName2+"levé les ancres il n'y a pas longtemps et a navigué vers "+sLoc+"Maintenant tu comprends pourquoi je ne peux pas faire confiance à mes hommes pour ce boulot ?";
			link.l1 = "Je le fais. Combien de temps j'ai?";
			link.l1.go = "CapComission2_2_3";
		break;
		
		case "CapComission2_2_3":
			dialog.text = "12 à 15 jours pas plus, c'est important pour moi s'ils n'atteignent pas la cachette, sinon ce serait absurde de les couler avec une cargaison précieuse. Dans ce cas, il vaudrait mieux qu'ils l'apportent ici...";
			link.l1 = "D'accord, je suis partant. Je vais essayer de les attraper.";
			link.l1.go = "CapComission2_2_4";
		break;
		
		case "CapComission2_2_4":
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");//правка
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в СЖ не работает имя . лесник
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
            pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
            pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips"; 
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			
			DialogExit();
		break;
		
		case "CapComission2_3":
			dialog.text = "Ne t'inquiète pas. Mes hommes le livreront à ton navire. Et pourquoi te soucies-tu de lui ?";
			link.l1 = "Je ne le fais pas. Ses proches m'ont demandé de le livrer.";
			link.l1.go = "CapComission2_31";
		break;
		
		case "CapComission2_31":
			dialog.text = "Ah, c'est bien. Je me sentais presque désolé de donner un prix si bas pour ton homme. Ha-ha-ha-ha ! Adieu.";
			link.l1 = "À plus.";
			link.l1.go = "CapComission2_32";
		break;
		
		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.vikupzaplatil = true; // новая проверка ,если шарль заплатил выкуп за пленника. лесник																																								
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission2_4":
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", "Jacques Barbazon");		// лесник																												  
				//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); в СЖ не работает
			}	
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;		
			DialogExit();
		break;
		
		case "CapComission3":
			dialog.text = "Alors, , "+GetFullName(pchar)+", as-tu coulé mes potes ? Ha-ha-ha...";
			if(pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = "Non. Je n'ai pas réussi à les attraper. Et je ne les ai pas rencontrés au retour.";
				link.l1.go = "CapComission4";
			}
			if(pchar.GenQuest.CaptainComission.PirateShips == "died")	
			{
				link.l1 = "Je l'ai fait. Je les ai envoyés nourrir les requins.";
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
		break;
		
		case "CapComission4":
			dialog.text = "Satané ! Que tu les aies rencontrés ou non, ça ne compte plus maintenant ! Et quelle sera ta prochaine suggestion ?";
			link.l1 = "Peut-être avez-vous un travail plus facile pour moi ?";
			link.l1.go = "CapComission4_1";
			link.l2 = "Écoute, "+NPChar.name+", fais baisser le prix pour le prisonnier...";
			link.l2.go = "CapComission4_2";
		break;
		
		case "CapComission4_1":
			dialog.text = "Non.";
			link.l1 = "Adieu alors...";
			link.l1.go = "CapComission4_3";
		break;
		
		case "CapComission4_2":
			dialog.text = "Faire baisser le prix ?! Je viens de perdre ma cachette à cause de ton incompétence ! Et maintenant je peux augmenter le prix ! Tu peux le prendre pour 200 000 pesos si tu veux, ou tu peux foutre le camp d'ici.";
			link.l1 = "C'est trop cher... Adieu...";
			link.l1.go = "CapComission4_4";
			if(sti(pchar.money) >= 200000)
			{
				link.l2 = "Merde, prends tes pièces.";
				link.l2.go = "CapComission4_5";
			}	
		break;
		
		case "CapComission4_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // лесник																			  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));// в СЖ не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;
		
		case "CapComission4_4":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // правка	// лесник																	  
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); в сж не работает
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
		break;
		
		case "CapComission4_5":
			dialog.text = "Tu peux prendre ce faible...";
			link.l1 = "Adieu.";
			link.l1.go = "CapComission4_6";
		break;
		
		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", "Barbazon"); // правки имени в сж лесник
			//AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));//в СЖ не работает // belamour gen : это хорошо, но закомментить нужно было)))
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();	
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
		case "CapComission5":
			dialog.text = "Ho-ho ! Bien joué ! Prends ton faible et bonne chance.";
			link.l1 = "Merci. Adieu.";
			link.l1.go = "CapComission5_1";
		break;
		
		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PirateShips");
			DialogExit();		
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");	
		break;
		
	   	/*case "CapComission6":    // ЕСЛИ В ПЕРВЫЙ РАЗ ОТКАЗАЛ В ЗАДАНИИ ,ТО ПУСТЬ БАБКИ ИЩЕТ
		     ИНАЧЕ ПОВТОРНАЯ ДАЧА ЗАДАНИЯ ПРЕВРАЩАЕТ КВЕСТ В КАШУ.. лесник
			dialog.text = "Tu as apporté la rançon"+GetSexPhrase("","la")+"? Car je ne plaisantais pas en disant que je le vendrais aux planteurs.";			
			link.l1 = "Ecoute, "+NPChar.name+", euh, vois-tu... En fait, je n'ai pas cet argent. Mais je suis prêt"+GetSexPhrase("","a")+"travailler.";
			link.l1.go = "CapComission2_2";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "C’est bien que tu ne l'aies pas vendu. Voici tes pièces - 150000 pesos. Où puis-je le trouver ?"link.l2.go ="CapComission2_3";
			}			
		break;*/
		  case "CapComission6":                        // лесник . пусть шарль бабло ищет,или забить на пленника.
			dialog.text = "As-tu apporté l'argent? Je ne plaisantais pas en parlant de vendre cet homme à la plantation.";			
			link.l1 = "Je n'ai pas l'argent, "+NPChar.name+", mais j'y travaille.";
			link.l1.go = "exit";
			if(makeint(pchar.money) > 150000)
			{
				link.l2 = "C'est bien que tu ne l'aies pas vendu. Voici tes pièces - 150.000 pesos. Où puis-je le trouver ?"link.l2.go ="CapComission2_3";
			}			
		break;
																																					 																																													  																																															
//--------------------------------------------Похититель------------------------------------------------------
		case "Marginpassenger":
			dialog.text = "Et pourquoi t'occupe de ce que je fais? Tu ferais mieux de filer...";
			link.l1 = "Tshh, calme-toi. J'ai des affaires avec toi. C'est à propos de ton prisonnier.";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "Ah, très bien. Qui veux-tu rançonner ?";
			link.l1 = "Attends. Je ne suis pas là pour racheter, je suis là pour te proposer d'acheter un prisonnier. Et bien, tu auras l'occasion de recevoir une rançon pour lui.";
			link.l1.go = "Marginpassenger_2";
		break;
		
		case "Marginpassenger_2":
			dialog.text = "Hm. Et pourquoi as-tu besoin de mes services ? Pourquoi ne veux-tu pas récupérer l'argent directement pour toi ?";
			link.l1 = "Ça me semble assez risqué. Je pourrais avoir des ennuis avec les autorités.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "Ha-h... bien alors. Jetons un oeil. Qui est ton prisonnier ?";
			link.l1 = "C'est "+pchar.GenQuest.Marginpassenger.Text+" "+XI_ConvertString("Colonie"+pchar.GenQuest.Marginpassenger.City+"Gen")+".";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "Je vois... ce serait un bon marché si tu ne mens pas. Je suppose que je peux te payer pour cet homme "+iTemp+" pesos ou te donner des informations intéressantes à la place. C'est ton choix.";
			link.l1 = "Je ferais mieux de prendre des pesos. J'en ai assez de cette affaire...";
			link.l1.go = "Marginpassenger_money";
			link.l2 = "Ha ! Dis-m'en plus. Je suis sûr que tu vas me dire quelque chose d'intéressant.";
			link.l2.go = "Marginpassenger_offer";
		break;
		
		case "Marginpassenger_money":
			dialog.text = "L'argent alors. Prends-les. Maintenant, ce n'est plus ton problème. Livre l'objet de la vente ici.";
			link.l1 = "Il doit déjà être près des portes de la ville. Merci ! Tu m'as vraiment aidé.";
			link.l1.go = "Marginpassenger_money_1";
		break;
		
		case "Marginpassenger_money_1":
			iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon)*2*stf(pchar.GenQuest.Marginpassenger.Chance))*100;
			dialog.text = "De rien, apporte-m'en plus... À la prochaine!";
			link.l1 = "Bonne chance...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iTemp);
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", iTemp);
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;
		
		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GOOD_EBONY + rand(makeint(GOOD_MAHOGANY - GOOD_EBONY));
			pchar.GenQuest.Marginpassenger.GoodsQty = 200+rand(10)*10;
			switch (hrand(1))
			{
				case 0: //бухта на южном мейне
					SelectSouthshore();
					while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
					dialog.text = "C'est bon de faire affaire avec un homme intelligent. Écoute maintenant : dans quelques jours à "+XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Ce")+" une expédition espagnole arrivera du continent, chargée de marchandises précieuses. Ils attendront un navire censé prendre la cargaison. Si tu y arrives dans une semaine, tu auras une chance de prendre la cargaison pour toi-même.\nSi j'étais toi, je serais déjà en train de me diriger vers mon navire. Et amène le prisonnier ici.";
					link.l1 = "Merci ! Les marchandises seront une belle compensation pour mes ennuis. Et mon passager doit déjà être près des portes de la ville. Il sera amené à vous.";
					link.l1.go = "Marginpassenger_offer_1";
				break;
				
				case 1: //просто кораблик
					SelectSouthcity();
					pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
					dialog.text = "C'est bon de faire affaire avec un homme intelligent. Maintenant écoute : dans environ une semaine, une brigantine espagnole '"+pchar.GenQuest.Marginpassenger.ShipName1+" chargé de marchandises précieuses naviguera de "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen")+" à "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Gén")+". Si tu te dépêches, tu l'attraperas facilement.\nTu es encore là ? Si j'étais toi, je serais déjà en route vers mon navire. Et amène le prisonnier ici.";
					link.l1 = "Merci ! Les marchandises seront une belle compensation pour mes soucis. Et mon passager doit déjà être près des portes de la ville. Il vous sera amené.";
					link.l1.go = "Marginpassenger_offer_2";
				break;
			}
			sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;
		
		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));//лесник - окончание в СЖ // belamour gen
			AddQuestUserData("Marginpassenger", "sName", "Jacques the Kindman"));
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;
		
		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sName", "Jacques the Kindman"));
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity+"Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Southcity1+"Acc")); // лесник - окончание в СЖ
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5+rand(2), false);
		break;
		
//---------------------------------------попытка залезть в сундуки --------------------------------------------
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Vol !!! C'est inacceptable ! Prépare-toi, "+GetSexPhrase("garçon","fille")+"...","Hé, qu'est-ce que tu fous là ?! Tu pensais pouvoir me voler ? T'es foutu... ","Attends, mais qu'est-ce que c'est que ça ? Lâche-moi tout de suite ! Il s'avère que tu es un voleur ! Fin de la route, salaud...");
			link.l1 = LinkRandPhrase("Merde !","Carramba!!","Merde !!");
			link.l1.go = "PL_Q3_fight";
		break;
					
// ----------------------------------------------блок нод angry--------------------------------------------------
		case "AngryRepeat_1":
            dialog.text = "Sors d'ici !";
			link.l1 = "Oups...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Ne me dérange pas avec tes bavardages bon marché. La prochaine fois, tu n'aimeras pas le résultat...";
        			link.l1 = "Je l'ai.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("C'est fini, pas de discussion.","Je ne veux plus te parler, alors tu ferais mieux de ne pas me déranger.");
			link.l1 = RandPhraseSimple("Comme tu veux...","Hm, d'accord alors...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "J'espère que tu montreras plus de respect et cesseras d'être grossier ?";
        			link.l1 = "Tu peux en être sûr, Jacques, je le ferai.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("LeFransua_town","reload","reload6");
		break;
		
		case "pirate_town":
            dialog.text = "Resoudre le probleme ? Comprends-tu ce que tu as fait ? Quoi qu'il en soit, apporte-moi un million de pesos et je persuaderai les gars d'oublier tes 'exploits'. Si l'idee ne te plait pas, alors tu peux aller au diable.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "D'accord, je suis prêt à payer.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Compris. Je m'en vais.";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Bien! Considérez-vous à nouveau propre. Mais j'espère que vous ne ferez plus de telles choses dégoûtantes.";
			link.l1 = "Je ne le ferai pas. Bien trop cher pour moi. Adieu...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
}

void SelectSouthshore()
{
	switch (rand(6))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
		case 0: 
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana"; 
		break;
		
		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago"; 
		break;
		
		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo"; 
		break;
	}
}
