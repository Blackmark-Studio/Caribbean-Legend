// гид
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Desideri qualcosa?";
			link.l1 = "No, niente.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "guide_0":
			SetAchievement("Test_Ach");
			PlaySound("Voice\English\LE\Greguar\Greguar_01.wav");
			dialog.text = "Piacere darle il benvenuto nelle colonie, signore! Mi permetta di presentarmi: "+GetFullName(pchar)+". Viene dall'Europa? È la prima volta qui?";
			link.l1 = "Buongiorno, monsieur. Il mio nome è "+GetFullName(pchar)+". Sì, sono appena sceso dalla nave.";
			link.l1.go = "guide_1";
		break;
		
		case "guide_1":
			DelLandQuestMark(npchar);
			dialog.text = "Vedendo un nobile gentiluomo, ho ritenuto mio dovere offrire aiuto. Qui, nel Nuovo Mondo, ci sono le proprie regole — e non conoscerle può costare caro. La gente di rango come noi dovrebbe aiutarsi a vicenda. Non credereste quanta feccia si è radunata qui, pronta a tradire il prossimo per una manciata di monete.\n"+
			"Posso mostrarle la città e metterla brevemente al corrente?";
			link.l1 = "Molto nobile da parte sua, monsieur! Accetto volentieri la sua proposta.";
			link.l1.go = "guide_2";
			link.l2 = "Grazie per la premura, signore, le sono veramente riconoscente, ma penso che senza difficoltà me la caverò da solo.";
			link.l2.go = "guide_exit";
		break;
		
		case "guide_exit":
			dialog.text = "Come desidera, monsieur. In ogni caso, sono stato felice di conoscerla. La gente nobile è così rara in questa landa selvaggia. Tutto il bene e buona fortuna!";
			link.l1 = "E anche a lei, "+GetFullName(npchar)+"!";
			link.l1.go = "guide_exit_1";			
		break;
		
		case "guide_exit_1":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DoQuestCheckDelay("NgtF3", 1.0);
			QuestPointerToLoc("FortFrance_town", "reload", "reload3_back");
		break;
		
		case "guide_2":
			dialog.text = "Magnifico! La vita ai Caraibi è semplice, e ogni insediamento è costruito secondo le stesse regole. Se si abitua a Saint-Pierre, si abituerà a qualsiasi altra città.";
			link.l1 = "";
			link.l1.go = "guide_tavern";			
		break;
		
		case "guide_tavern":
			dialog.text = "Taverna — il cuore del porto. Qui troverà alloggio, rum, pettegolezzi e potrà assumere marinai e ufficiali. E anche — giocare a carte, trovare lavoro o usare i servizi di contrabbandieri e mercanti di mappe del tesoro.";
			link.l1 = "";
			link.l1.go = "guide_market";
			locCameraFromToPos(-2.08, 5.32, 68.88, true, -15.00, 0.90, 55.00);
		break;
		
		case "guide_market":
			dialog.text = "Mercato. Le merci per uso personale si possono sempre comprare al mercato. Dall'armaiolo — armi, armature e munizioni, dall'erborista — pozioni curative. Le zingare e i monaci commerciano amuleti, e il rigattiere vende ogni sorta di cianfrusaglie utili a chi non disdegna di arrangiarsi con le proprie mani.";
			link.l1 = "";
			link.l1.go = "guide_brothel";
			locCameraFromToPos(-13.58, 4.11, 69.06, true, -45.00, -6.00, 52.00);
		break;
		
		case "guide_brothel":
			dialog.text = "Bordello. Non c'è medicina migliore per il corpo dei piaceri amorosi tra le braccia di una donna esperta. Se la salute vacilla — fate un salto qui, svagatevi, ricevete una dose di carezze e vi sentirete un'altra persona.";
			link.l1 = "";
			link.l1.go = "guide_bank";
			locCameraFromToPos(-2.75, 7.07, 61.10, true, 60.00, -6.60, 42.65);
		break;
		
		case "guide_bank":
			dialog.text = "Banca. Casa dell'usuraio. Si può prendere in prestito o investire denaro, cambiare pesos in dobloni. E inoltre — è il posto migliore per vendere gioielli.";
			link.l1 = "";
			link.l1.go = "guide_prison";
			locCameraFromToPos(3.07, 7.64, 51.99, true, 45.00, -8.30, 4.50);
		break;
		
		case "guide_prison":
			dialog.text = "Prigione. I veri criminali qui sono pochi — principalmente ogni sorta di feccia. Se volete trovare lavoro tra i rifiuti della società — parlate con il comandante. Per una piccola tangente può farvi passare alle celle.";
			link.l1 = "";
			link.l1.go = "guide_townhall";
			locCameraFromToPos(-50.52, 5.79, 38.60, true, -47.65, 3.95, 33.52);
		break;
		
		case "guide_townhall":
			dialog.text = "Palazzo. Il palazzo della persona più importante della colonia — il governatore. Gli uomini d'affari e i capitani vengono qui per lavori seri. Essere in buoni rapporti con il governatore è una grande cosa, perché da lui dipende in gran parte come tutta la sua nazione vi tratterà.";
			link.l1 = "";
			link.l1.go = "guide_12";
			locCameraFromToPos(3.14, 7.39, 37.55, true, 1.06, 8.45, 14.14);
		break;
		
		case "guide_12":
			dialog.text = "Ha fretta di andare da qualche parte e la sto distraendo?";
			link.l1 = "Beh... immagino di sì. Monsieur, sono venuto qui per trovare mio fratello. Dicono che sia da qualche parte a Saint-Pierre. È un uomo importante e sicuramente conosciuto dal governatore...";
			link.l1.go = "guide_13";
			SetCameraDialogMode(npchar);
		break;
		
		case "guide_13":
			dialog.text = "Ah, capisco. Il nostro governatore si chiama Jacques Dyel du Parquet. Sono sicuro che vi riceverà senza indugio.";
			link.l1 = "Chi altro potrei chiedere di mio fratello? Forse non dovrei disturbare Sua Eccellenza subito?";
			link.l1.go = "guide_14";
		break;
		
		case "guide_14":
			dialog.text = "Se vostro fratello è davvero conosciuto in Martinica — chiedete ai passanti. Forse qualcuno saprà indicarvi. A proposito, come si chiama?";
			link.l1 = "Michelle de Monper.";
			link.l1.go = "guide_15";
		break;
		
		case "guide_15":
			dialog.text = "Ho sentito questo nome, ma, ahimè, non ho avuto l'onore di essere presentato personalmente. Provate a chiedere in città — o andate direttamente dal governatore. Buona fortuna, monsieur. Sicuramente ci rivedremo e chiacchiereremo!";
			link.l1 = "Grazie, "+GetFullName(npchar)+"!";
			link.l1.go = "guide_16";
		break;
		
		case "guide_16":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			LAi_group_MoveCharacter(npchar, "FRANCE_CITIZENS"); // пока идем заниматься Мишелем
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestCheckDelay("NgtF3", 1.0);
			QuestPointerToLoc("FortFrance_town", "reload", "reload3_back");
		break;
		
		case "guide_21":
			dialog.text = "Oh, siete di nuovo voi, amico mio! Vedo che vi hanno ammesso nel sancta sanctorum di Saint-Pierre — la fortezza dei Cavalieri di Malta. Da quanto si vede, siete un pesce grosso. Avete trovato vostro fratello?";
			link.l1 = "Beh sì, l'ho trovato...";
			link.l1.go = "guide_22";
		break;
		
		case "guide_22":
			dialog.text = "Scusate l'insistenza, monsieur, ma mi è sembrato di non sentire gioia nella vostra voce...";
			link.l1 = "È vero, signore. Speravo di andarmene da qui e tornare in Francia con la prossima nave, ma il destino sembra aver deciso di prendersi gioco di me: rimango qui a lungo... no, dannazione — per un tempo indefinito! E, immaginate, per giunta devo diventare un marinaio, bah!";
			link.l1.go = "guide_23";
		break;
		
		case "guide_23":
			dialog.text = "Per qualche motivo non sono sorpreso. Ho già sentito parlare della vostra avventura sul pinaccia 'Ulysse'. Non scoraggiatevi — essere proprietario della propria nave e capitano è molto onorevole. Avete intenzione di comprare una nave, vero?";
			link.l1 = "Sì, dannazione, è esattamente questo che devo fare... Resta solo da trovare un cantiere navale e in qualche modo raccogliere denaro. Ma non so né dove sia il cantiere, né come pilotare una nave, né dove prendere i soldi — niente!";
			link.l1.go = "guide_24";
		break;
		
		case "guide_24":
			dialog.text = "Con i soldi, ahimè, non posso aiutare — sono io stesso al verde in questo momento. Ma per il resto — sono al vostro servizio. Siete pronto a continuare il tour?";
			link.l1 = "Sì, forse, poiché non per niente si dice: la conoscenza è potere.";
			link.l1.go = "guide_25";
			link.l2 = "Grazie di cuore, monsieur, ma da qui in poi me la caverò da solo.";
			link.l2.go = "guide_exit_11";
		break;
		
		case "guide_exit_11":
			dialog.text = "Cieszyłem się z naszej znajomości. A co do pieniędzy na statek — porozmawiaj z wpływowymi ludźmi w mieście. Na przykład z kupcem w sklepie.\n"+
			"Powodzenia, "+pchar.name+" — bądź odważny, a wszystko ci się uda.";
			link.l1 = "";
			link.l1.go = "guide_exit_12";			
		break;
		
		case "guide_exit_12":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "guide_25":
			dialog.text = "Allora seguitemi! Iniziamo con le basi — le navi.";
			link.l1 = "";
			link.l1.go = "guide_shipyard";
		break;
		
		case "guide_shipyard":
			dialog.text = "Cantiere navale. Qui si comprano e si riparano le navi. La scelta non è grande — principalmente piccole imbarcazioni, ma a volte si trovano navi serie. Qui si possono anche comprare cannoni e decorare le vele.";
			link.l1 = "";
			link.l1.go = "guide_port";
			locCameraFromToPos(-23.25, 7.74, 77.79, true, -27.85, 5.36, 73.65);
		break;
		
		case "guide_port":
			dialog.text = "Molo — la porta verso il mare. Non appena avrete una nave — qui vi aspetterà una scialuppa. Per ora consiglio di assumere un navigatore, un tesoriere e un cannoniere — con loro vi sentirete più sicuri in mare.";
			link.l1 = "";
			link.l1.go = "guide_portoffice";
			locCameraFromToPos(-8.55, 4.06, 91.31, true, 40.00, -8.00, 0.00);
		break;
		
		case "guide_portoffice":
			dialog.text = "Zarząd portu. Tu można zostawić statek na postoju i znaleźć uczciwą pracę dla kapitana: fracht, eskorta, dostarczanie poczty. Im więcej zleceń wykonasz, tym lepsze stawki.";
			link.l1 = "";
			link.l1.go = "guide_store";
			locCameraFromToPos(48.38, 9.48, 43.95, true, 43.69, 5.47, 48.13);
		break;
		
		case "guide_store":
			dialog.text = "Sklep. Kapitanowie zaglądają tu po prowiant, rum, lekarstwa, proch i amunicję. Jeśli czegoś brakuje — szukaj przemytników w tawernie. Ale bez dobrego kwatermistrza handel to strata czasu i pieniędzy.";
			link.l1 = "";
			link.l1.go = "guide_gate";
			locCameraFromToPos(-21.10, 6.60, 45.21, true, -30.00, 3.70, 45.00);
		break;
		
		case "guide_gate":
			dialog.text = "Brama. Jeśli molo to brama na morze, to tutaj jest wejście na dzikie tereny. Niebezpieczne, ale konieczne, gdy trzeba dotrzeć do fortu, znaleźć skarb lub przejść do innej osady.";
			link.l1 = "";
			link.l1.go = "guide_45";
			locCameraFromToPos(50.58, 5.74, 23.21, true, 100.00, 0.00, 20.00);
			//AddQuestRecordInfo("Guide_OnLand", "1");
		break;
		
		case "guide_45":
			dialog.text = "Nie każda kolonia wita obcych. Jeśli nie chcesz czekać do nocy, podnieś inną flagę na morzu, a potem polegaj na skradaniu się lub kup licencję handlową.";
			link.l1 = "";
			link.l1.go = "guide_46";
		break;
		
		case "guide_46":
			dialog.text = "Jest pan świetnym słuchaczem, mój przyjacielu. Może trochę rozrywki? Proponuję treningowy pojedynek za bramą.";
			link.l1 = "Oczywiście! To się świetnie składa.";
			link.l1.go = "guide_47";
			link.l2 = "Dziękuję z całego serca, monsieur, ale dalej poradzę sobie sam.";
			link.l2.go = "guide_exit_11";
		break;
		
		case "guide_47": // телепортируем за городские ворота
			DialogExit();
			LAi_SetActorType(npchar);
			DoQuestReloadToLocation("FortFrance_ExitTown", "goto", "goto19", "Guide_ExitTown");
		break;
		
		case "guide_49":
			dialog.text = "Mój przyjacielu, zakładam, że nie jest pan nowicjuszem w szermierce?";
			link.l1 = "Ha! Jeden abordaż już przeżyłem i nawet...";
			link.l1.go = "guide_50";
			if (FindCharacterItemByGroupWithout_knife_03(pchar, BLADE_ITEM_TYPE) == "")
			{
				GiveItem2Character(pchar, "blade_05");
				EquipCharacterByItem(Pchar, "blade_05");
			}
		break;
		
		case "guide_50":
			dialog.text = "Doskonale. Zaczynamy?";
			link.l1 = "Zatańczmy!";
			link.l1.go = "guide_56";
			npchar.quest.guide_win = 0;
		break;
		
		case "guide_56": // махач
			LAi_SetPlayerType(pchar);
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_Delete("EnemyFight");
			if (MOD_SKILL_ENEMY_RATE <= 6)	// На первых трёх сложностях Валинье будет ослаблен
			{
				LAi_SetHP(npchar, LAi_GetCharacterMaxHP(npchar) * 0.7, LAi_GetCharacterMaxHP(npchar) * 0.7);
				npchar.rank = 1;
				SetSelfSkill(npchar, 1, 1, 1, 1, 1);
			}
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			// ставим проверяльщики
			LAi_SetCheckMinHP(pchar, 1, true, "Guide_HeroFail");
			LAi_SetCheckMinHP(npchar, 1, true, "Guide_HeroWin");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			//DoQuestCheckDelay("GuideFight_tutorial", 1.0);
		break;
		
		case "guide_57": // побил гида с первого раза
			dialog.text = "You... you are a man who knows how to hold his sword. Well done, Monsieur. You need more practice, but you have the potential to become a true swordmaster.";
			link.l1 = "Merci beaucoup. What now?";
			link.l1.go = "guide_62"; // нода на выход
			if (MOD_SKILL_ENEMY_RATE >= 6)
			{
				link.l2 = "More practice you say? Are you serious? I'm tired of this patronizing tone ever since I set foot in this miserable place!";				//Пасхалка Корсары 2 для сложности СФ и выше
				link.l2.go = "guide_64";
			}
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 80);
		break;
		
		case "guide_58": // побил гида со второго или третьего раза
			dialog.text = "Much better! See, all you need is to concentrate. You need more practice, one day you will become a decent fencer.";
			link.l1 = "Merci beaucoup. What now?";
			link.l1.go = "guide_62"; // нода на выход
			AddComplexSelfExpToScill(20, 20, 20, 20);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
		break;
		
		case "guide_59": // побили первый раз
			dialog.text = "I won, Monsieur. Move faster, parry my stabs, jump back. A rematch?";
			link.l1 = "Oui! No mercy, Monsieur!";
			link.l1.go = "guide_56";
			link.l2 = "No, I had enough. Let's finish the lesson. What now?";
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_60": // побили второй раз
			dialog.text = "I won again, "+pchar.name+"! Don't lose your initiative. Catch my hits, feint them. If you see that I am going to hit hard - jump away or parry, don't just guard. Again!";
			link.l1 = "Come, Monsieur, I shall thrash you this time!";
			link.l1.go = "guide_56";
			link.l2 = "No, I've had enough. Let's finish the lesson. What now?";
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_61": // побили третий раз
			dialog.text = "You have a lot to learn, "+pchar.name+". Don't worry, you still got a lot of time to master your fencing. But be careful, don't take any chances until you know how to hold a weapon.";
			link.l1 = "I will consider it, Monsieur, but I have to say that you were just too lucky! This blasted heat... the only reason why I didn't beat the hell out of you. Merde, let's end our fencing lesson. What now?";
			link.l1.go = "guide_62"; // нода на выход
		break;
		
		case "guide_62":
			dialog.text = "Now it's time to say farewell, Monsieur. It was a pleasure. I hope that my presentation and training did you some good and will prove useful in the future. Perhaps, we shall meet again one day.\nAnd about the money you need - talk to important people of our city. Visit all the places that I have shown you today and speak to their owners. Ask around. Take a walk to the jungle and to the fort. Find a job or... well, I am not a priest or a judge, check people's houses and see what trinkets you can find in their unlocked chests. Just do it when their backs are turned or the guards will catch you.\nGood luck, "+pchar.name+", I have a strong feeling that you have the spark of true greatness inside you. Do your best to kindle it into a roaring fire!";
			link.l1 = "Merci, Monsieur. The pleasure was mine. Godspeed!";
			link.l1.go = "guide_63";
		break;
		
		case "guide_63":
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			DoQuestReloadToLocation("FortFrance_Town", "quest", "quest2", "");
		break;
		
		case "guide_64": // решили убить Валинье
			dialog.text = "Hold your tongue, Monsieur! I won't tolerate such insolence any further. However, I understand your reaction to a new environment, therefore I forgive your outburst this time. But mind your words from now on. Farewell, Monsieur de Maure.";
			link.l1 = "No offense, Monsieur Valinnie. If we were in the Louvre at this moment, you'd watch your tone! It's time to teach a province a final lesson. Defend yourself!";
			link.l1.go = "guide_65";
		break;
		
		case "guide_65":
			DialogExit();
			
			npchar.rank = 25;
			int iHp = MOD_SKILL_ENEMY_RATE*10+300;
			LAi_SetHP(npchar, iHp, iHp);
			SetSelfSkill(npchar, 80, 80, 80, 80, 50);
			SetShipSkill(npchar, 50, 80, 35, 30, 50, 20, 30, 20, 80);
			SetSPECIAL(npchar, 9, 5, 8, 6, 5, 10, 8);
			SetCharacterPerk(npchar, "Energaiser");
			SetCharacterPerk(npchar, "BasicDefense");
			SetCharacterPerk(npchar, "AdvancedDefense");
			SetCharacterPerk(npchar, "CriticalHit");
			SetCharacterPerk(npchar, "Tireless");
			SetCharacterPerk(npchar, "HardHitter");
			SetCharacterPerk(npchar, "Sliding");
			SetCharacterPerk(npchar, "BladeDancer");
			SetCharacterPerk(npchar, "SwordplayProfessional");
			SetCharacterPerk(npchar, "Gunman");
			SetCharacterPerk(npchar, "GunProfessional");
			GiveItem2Character(npchar, "blade_30");
			EquipCharacterbyItem(npchar, "blade_30");
			GiveItem2Character(npchar, "cirass7");
			GiveItem2Character(npchar, "obereg_7");
			GiveItem2Character(npchar, "talisman11");
			AddMoneyToCharacter(npchar, 10000);
			AddItems(npchar, "gold_dublon", 25);
			AddItems(npchar, "bullet", 5);
			AddItems(npchar, "grapeshot", 5);
			AddItems(npchar, "GunPowder", 10);
			TakeItemFromCharacter(npchar, "blade_12");
			npchar.cirassId = Items_FindItemIdx("cirass4");
			LAi_SetCurHPMax(npchar);
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_Delete("EnemyFight");
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Guide_HeroKill");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string FindCharacterItemByGroupWithout_knife_03(ref chref, string groupID)
{
	ref refItm;
    string resultItemId;

	resultItemId  = "";
	for(i=TOTAL_ITEMS-1; i>=0; i--)
	{
		refItm = &Items[i];
		if( !CheckAttribute(refItm,"groupID") ) continue;
		if(refItm.groupID!=groupID) continue;
		if( !CheckAttribute(chref,"items."+refItm.id) ) continue;
		if(refItm.id == "knife_03") continue;
		if (groupID == BLADE_ITEM_TYPE)
		{
			resultItemId  = refItm.id;
		}
	}
	
	if (resultItemId != "")
	{
        return resultItemId;
	}

	return "";
}