// диалоги прочих НПС по квесту LSC
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
			dialog.text = "Vuoi qualcosa?";
			link.l1 = "No, non è nulla.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//-----------------------------------бандосы Акулы в трюме с припасами--------------------------------------
		case "PantryGuard":
			dialog.text = "Ooh, ooh, guardate un po' qui, ragazzi! Chi ci è venuto a trovare! Un ladro che fruga nei forzieri altrui! Vieni qua! E tu, compare, non provare nemmeno a fare il fesso o a tirar fuori la lama – da questa distanza non sbaglio un colpo... Chad sarà proprio lieto di vederti!";
			link.l1 = "Ma io... Sono appena arrivato!";
			link.l1.go = "PantryGuard_1";
		break;
		
		case "PantryGuard_1":
			dialog.text = "Hai ragione, ah-ah! Ti sei cacciato in un bel casino, compare... E non c’è via di scampo. Ora, consegna le tue armi e seguimi! La gabbia sulla 'Tartaro' ti aspetta da una vita, furfante!";
			link.l1 = "...";
			link.l1.go = "PantryGuard_2";
		break;
		
		case "PantryGuard_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			SetLaunchFrameFormParam("Few hours later...", "", 0, 3);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 7, 10); //крутим время
			RecalculateJumpTable();
			DoQuestFunctionDelay("LSC_GotoPrison", 3.0);
		break;
		
		case "CommonGuard":
			dialog.text = "Non provare a rubare nulla qui. Terrò d’occhio ogni tua mossa.";
			link.l1 = "Siate i benvenuti.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CommonGuard";
		break;
		
		case "ChadGuard":
			dialog.text = "Vai e fai ciò che Chad t’ha ordinato. Non fiatare troppo!";
			link.l1 = "Sì, sto arrivando...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ChadGuard";
		break;
		
		case "ChadGuard_Attack":
			dialog.text = "Ehi! Che diavolo stai facendo laggiù? Maledetto! Ora sei finito!";
			link.l1 = "...";
			link.l1.go = "ChadGuard_Attack_1";
		break;
		
		case "ChadGuard_Attack_1":
			DialogExit();
			sld = characterFromId("Chimiset");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "afraid", "", -1);
			for(i = 1; i <= 3; i++)
			{				
				sld = CharacterFromID("ChadGuard_"+i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = characterFromId("Capper");
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "Tartarusprison", "goto", "goto8");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_ChadGuard_Die");
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Notsearchbody = true; // запрет обыска трупов
		break;
		
		// ----------------------------------Марчелло Циклоп--------------------------------
		// если ждали в каюте
		case "Cabin":
			dialog.text = "Ehi, che diavolo ci fai qui, maledizione? Dov’è Barbier?";
			link.l1 = "Il nostro amico Adolfo è... malato. Non poteva venire all’incontro, così mi ha chiesto di sedermi un po’ nella sua cabina e aspettarti.";
			link.l1.go = "Cabin_1";
		break;
		
		case "Cabin_A":
			dialog.text = "Ehi, che diavolo ci fai qui, maledizione?";
			link.l1 = "Il nostro amico Adolfo è... malato. Non ha potuto venire all’incontro, così mi ha chiesto di sostituirlo. Per così dire.";
			link.l1.go = "Cabin_1";
		break;
		
		case "Cabin_1":
			dialog.text = "Sembra strano... stamane stava bene e ora si trova in cattiva salute.";
			link.l1 = "Eh, sai com'è la vita. Una febbre improvvisa e via...";
			link.l1.go = "Cabin_2";
		break;
		
		case "Cabin_2":
			dialog.text = "Oh, la tua faccia non mi piace per niente. Stai mentendo. Barbier non affiderebbe mai questo incontro a qualcun altro. Parla, mascalzone, chi sei e che fine gli hai fatto fare?";
			link.l1 = "Sai, nemmeno tu sei uno spettacolo per gli occhi. Ti ho già detto che Barbier è malato. Sei duro d’orecchio o devo ripetermi? Doveva darti la chiave e...";
			link.l1.go = "Cabin_3";
		break;
		
		case "Cabin_3":
			DialogExit();
			sld = characterFromId("Mary");
			LAi_SetActorType(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// на Церес Смити - спасаем Мэри
		case "mary":
			dialog.text = "Maledizione! Mi hai trovato alla fine...";
			link.l1 = "Sì, feccia! Non le metterai mai le mani addosso! Preparati a crepare!";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "LSC_KillCyclop_CS");
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		// посланник от Акулы по варианту N
		case "SharkCureer":
			dialog.text = "Sei tu "+GetFullName(pchar)+"?";
			link.l1 = "Sì, sono proprio io. Che succede?";
			link.l1.go = "SharkCureer_1";
		break;
		
		case "SharkCureer_1":
			dialog.text = "Lo Squalo mi manda. Vuole che tu lo raggiunga al più presto. Dice che ha qualcosa d’importante per te.";
			link.l1 = "Che fretta hai?.. Va bene, vado subito sulla 'San Agustin'.";
			link.l1.go = "SharkCureer_2";
		break;
		
		case "SharkCureer_2":
			// сюда можно поставить таймер на гибель Акулы, если не придёт до конца суток
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance_20"; // ноду Акуле
		break;
		
		// посланник от Акулы по варианту M
		case "SharkCureer_3":
			dialog.text = "Sei tu "+GetFullName(pchar)+"?";
			link.l1 = "Sì, sono io. Che c’è, forestiero?";
			link.l1.go = "SharkCureer_4";
		break;
		
		case "SharkCureer_4":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
			{
				dialog.text = "Uh, sono stanco di cercarti... Lo Squalo e Layton Dexter vogliono vederti subito. È una faccenda di gran peso, quindi muoviti.";
				link.l1 = "Ah sì? Va bene, vado subito alla 'San Agustin'.";
				link.l1.go = "SharkCureer_6";
			}
			else
			{
				dialog.text = "Uh, sono stanco di cercarti... L'Ammiraglio Layton Dexter vuole vederti subito. È una faccenda di gran peso, dunque muoviti, filibustiere.";
				link.l1 = "Ammiraglio?";
				link.l1.go = "SharkCureer_5";
			}
		break;
		
		case "SharkCureer_5":
			dialog.text = "Sì. Essendo il secondo al comando, è diventato il nostro ammiraglio dopo la morte dello Squalo.";
			link.l1 = "Capisco. Va bene, vado subito alla 'San Agustin'.";
			link.l1.go = "SharkCureer_6";
		break;
		
		case "SharkCureer_6":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		break;
		
		// тюремщик вместо Каппера
		case "Prisonboss":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "Ah, eccoti... Ti riconosco, sei l’ultimo che ha scambiato due parole con Chimiset. L’hai mandato al creatore?";
				link.l1 = "Taglia corto con le frottole! Sai benissimo che non sono stato io. E sono convinto che tu sappia chi è l’assassino.";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "Ah, che noia starsene qui tutto il giorno! Se solo portassi un po’ di rum e delle carte, compare, potremmo anche giocarcela a dadi...";
				link.l1 = "Scusami, compare, non ho tempo per queste chiacchiere. Forse più tardi.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Prisonboss";
		break;
		
		case "meeting":
			dialog.text = "Ho qualche sospetto, sì, ma di fatti non ne ho. Nessuno ha visto la morte del moro. Si spettegola dappertutto sull’isola che sia stata colpa nostra, della gente dello Squalo, e che qualche novellino abbia fatto il lavoro su ordine dell’ammiraglio. Capisci ora? Quindi non andare dai Rivados, soprattutto adesso. Sono troppo furibondi.";
			link.l1 = "Va bene. Ho capito.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prisonboss";
		break;
		
		case "Prisonboss_M":
			dialog.text = "Ah, che noia stare qui tutto il giorno! Se solo portassi un po’ di rum e delle carte, compare, potremmo farci una bella partita a carte...";
			link.l1 = "Scusa, compare, non ho tempo per queste ciance. Magari più tardi.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Prisonboss_M";
		break;
		
		// заместитель Акселя в магазине
		case "AxelHelper":
			dialog.text = "Cosa vuoi, compare?";
			link.l1 = "Hm. E che affari t’hanno portato qui? Dov’è Axel?";
			link.l1.go = "AxelHelper_1";
		break;
		
		case "AxelHelper_1":
			dialog.text = "Axel è occupato. Sta avendo un incontro con Donald Greenspen e rimarrà con lui fino a stasera. Quindi se vuoi comprare qualcosa – torna domattina. E io tengo d’occhio la bottega, perciò non pensare nemmeno di rubare…";
			link.l1 = "Capisco. E perché proprio oggi si mette a fare questo? Va bene, tornerò qui domattina.";
			link.l1.go = "exit";
			NextDiag.TempNode = "AxelHelper_2";
		break;
		
		case "AxelHelper_2":
			dialog.text = NPCStringReactionRepeat("Ti ho già raccontato tutto. Torna qui domani.","Non scocciarmi, compare. Sparisci!","Non farmi arrabbiare, brutto bastardo!","Vattene!!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("D'accordo.","Ho capito, ho capito.","Zitto...","Come?!",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;
		
		// мать Белого Мальчика - Агнес Кристиансен
		case "agnes":
			dialog.text = "Cosa vuoi, messere?";
			link.l1 = "Hm... Mi scusi, signora. Perdonate la mia sfrontatezza e la mia scortesia, ma vorrei domandarvi una cosa: conoscete forse un uomo chiamato Ole Christiansen?";
			link.l1.go = "agnes_1";
		break;
		
		case "agnes_1":
			dialog.text = "Ripeti ancora quello che hai detto... Ole Christiansen? Ole?!";
			link.l1 = "Sì. Lo chiamano anche il Ragazzo Bianco per via del colore particolare dei suoi capelli. Lo conosci?";
			link.l1.go = "agnes_2";
		break;
		
		case "agnes_2":
			dialog.text = "Lo conosco?! È mio figlio, e manca da dieci anni! Lo sai dov’è, messere? Dimmi subito dove si trova, che ne è stato di lui?!";
			link.l1 = "Calmati, signora, non agitarti così. Sta bene. È sulla mia nave. Tutto quel che gli serve è sbarcare e venire qui.";
			link.l1.go = "agnes_3";
		break;
		
		case "agnes_3":
			dialog.text = "Oh... Pare che il Signore abbia finalmente ascoltato le mie preghiere! Non immagini quanto mi sono dannato quando è sparito! Ed è tutta, tutta colpa mia! Dove lo hai trovato? Non è un ragazzo qualunque... beh, tu sai di cosa parlo.";
			link.l1 = "Sì, lo conosco. Già, è davvero uno fuori dal comune. E non è cambiato per niente. Pare ancora un ragazzino, quel diavolo. L’ho trovato su un’isola. Ci siamo imbattuti per caso. Mi chiese una perlina bianca... maledizione!... Voleva una perla.";
			link.l1.go = "agnes_4";
		break;
		
		case "agnes_4":
			dialog.text = "Una perla? Oh, Dio! Le perle sono la ragione per cui mio figlio è sparito! È tutta colpa di quella maledetta collana!";
			link.l1 = "È vero che Ole... è scappato di casa per aver strappato la tua collana di perle?... Calmati, signora, non piangere!";
			link.l1.go = "agnes_5";
		break;
		
		case "agnes_5":
			dialog.text = "Sì, è vero. Ole mi ha strappato la collana al molo e tutte le perle sono cadute in acqua. L'ho maledetto come una furia e mio defunto marito... lo ha punito. Ole è sparito il giorno dopo. Non puoi immaginare quanto mi sono dannata per questo!";
			link.l1 = "Ole raccoglie perle da anni. Le chiama le perline bianche. Le ha raccolte tutte per te e mi ha chiesto di portarlo da te. Non sapevo altro, tranne che cercare la casa col tetto rosso. Ma alla fine sono riuscito a trovarti.";
			link.l1.go = "agnes_6";
		break;
		
		case "agnes_6":
			dialog.text = "Raccogliendo perle?! Oh, Dio! Che colpa terribile ho davanti al mio povero ragazzo! Io... e lui che raccoglieva perle! Oh!";
			link.l1 = "Suppongo sia meglio che chiami vostro figlio, padrona. Era così impaziente di vedervi. Diceva che sareste stata felice di vedere le perle. Ma credo che la vostra gioia non sarà per quelle...";
			link.l1.go = "agnes_7";
		break;
		
		case "agnes_7":
			dialog.text = "Mynheer... saresti così gentile. Portami il mio Ole. Voglio stringerlo tra le braccia e chiedergli perdono...";
			link.l1 = "Certo, padrona. Lo porteranno qui subito.";
			link.l1.go = "agnes_8";
		break;
		
		case "agnes_8":
			DialogExit();
			SetLaunchFrameFormParam("One hour later", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
			DoQuestFunctionDelay("LSC_OleGoHome", 5.0);
		break;
		
		case "agnes_9":
			dialog.text = "";
			link.l1 = "Ebbene, signora, ecco vostro figlio – Ole Christiansen. Lo riconoscete?";
			link.l1.go = "agnes_10";
		break;
		
		case "agnes_10": // перекидываем pchar
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, characterFromID("Agnes"));
			ChangeShowIntarface();
			SetMainCharacterIndex(GetCharacterIndex("Agnes"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Ole");
			sld.dialog.currentnode = "home";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "agnes_11":
			dialog.text = "Mynheer... Mi scusi, non le ho chiesto il nome... "+pchar.name+"?";
			link.l1 = ""+GetFullName(pchar)+", padrona. Capitano "+GetFullName(pchar)+".";
			link.l1.go = "agnes_12";
		break;
		
		case "agnes_12":
			dialog.text = "Capitano, non puoi immaginare quanto io sia riconoscente per mio figlio! L’hai aiutato e l’hai portato qui. Mi hai ridato la vita! Farò di tutto per il mio ragazzo, riverserò su di lui tutto l’amore che gli è mancato in tutti questi anni.";
			link.l1 = "Sono felice per te, signora. E anche per Ole. È un bravo ragazzo, mi ha dato una mano quando le cose si sono fatte dure. Ha un cuore gentile, quel ragazzo. Conosco un uomo che Ole ha strappato dalle fauci della morte.";
			link.l1.go = "agnes_13";
		break;
		
		case "agnes_13":
			dialog.text = "Mynheer, insisto che domani dovete venire qui, o quando il tempo vi sarà propizio. Vi devo ringraziare per mio figlio. Ora però sono un po’... insomma, capite.";
			link.l1 = "Lo faccio, mia signora.";
			link.l1.go = "agnes_14";
		break;
		
		case "agnes_14":
			dialog.text = "Torna qui domani. Ti ricompenserò come si deve per tutto il bene che hai fatto a mio figlio e a me.";
			link.l1 = "Va bene. Verrò senz’altro a trovarti!";
			link.l1.go = "agnes_15";
		break;
		
		case "agnes_15":
			DialogExit();
			bDisableCharacterMenu = false;//лоченые интерфейсы
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetOwnerType(npchar);
			LocatorReloadEnterDisable("Marigo_town", "houseSp2", true);
			NextDiag.CurrentNode = "agnes_16";
			pchar.quest.LSC_Ole_return.win_condition.l1 = "Timer";
			pchar.quest.LSC_Ole_return.win_condition.l1.date.hour  = 8.0;
			pchar.quest.LSC_Ole_return.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_Ole_return.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_Ole_return.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_Ole_return.function = "LSC_OleAgnesRegard";
			// удаляем Оле из пассажиров
			sld = characterFromId("Ole");
			RemovePassenger(Pchar, sld);
			DeleteAttribute(pchar, "GenQuest.Ole");
			DoQuestReloadToLocation("Marigo_town", "reload", "houseSp2", "");
		break;
		
		case "agnes_16":
			dialog.text = "Ah, eccovi qua, signor mio "+GetFullName(pchar)+"! Su, accomodati...";
			link.l1 = "Grazie! Come sta il vecchio?";
			link.l1.go = "agnes_17";
		break;
		
		case "agnes_17":
			dialog.text = "Oh, non puoi immaginare cosa hai fatto! Sei stato un balsamo per il cuore di una madre afflitta... Ti sono debitrice, pregherò per te in eterno.";
			link.l1 = "Mi fai arrossire, madonna...";
			link.l1.go = "agnes_18";
		break;
		
		case "agnes_18":
			dialog.text = "Ho sempre saputo che l’umiltà è ciò che rende nobile un vero gentiluomo... Ho preparato dei doni per ciò che hai fatto. Sì, sì! E neanche pensare di rifiutare! Prendi... Per prima cosa, ecco uno scrigno pieno di dobloni. Poi, accetta questo amuleto incantato, lo chiamano Scarabeo.\nMio marito lo possedeva, e sono certa che sarebbe lieto di sapere che il suo tesoro finirà nelle mani di un capitano così onorabile, che mi ha riportato il figlio. Mio marito era un falegname e diceva che lo Scarabeo gli dava velocità nelle mani.\nSpero che questo anello ti sia utile. Meriti di portarlo, senza dubbio! E infine, prendi i miei attrezzi da sarta. È un bel set. Potrai confezionare un bel mucchio di cose buone con questi.";
			link.l1 = "Oh! Questi sono davvero doni preziosi per qualsiasi capitano! Grazie, signora.";
			link.l1.go = "agnes_19";
		break;
		
		case "agnes_19":
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a chest with doubloons");
			Log_Info("You have received the 'Scarab' amulet");
			Log_Info("You have received a sartorial set");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "talisman7");
			GiveItem2Character(pchar, "tailor_tool");
			dialog.text = "E voglio che tu sappia che le porte della mia dimora sono sempre aperte per te, in ogni momento. Qui troverai sempre cibo, una bottiglia di vino pregiato e tutto ciò che desideri.";
			link.l1 = "Grazie per le vostre gentili parole, madonna. Sarà un piacere rivedervi quando tornerò in questa città.";
			link.l1.go = "agnes_20";
		break;
		
		case "agnes_20":
			dialog.text = "Non mancare di venire!";
			link.l1 = "E ora devo andare. Addio e buona fortuna!";
			link.l1.go = "agnes_21";
		break;
		
		case "agnes_21":
			DialogExit();
			NextDiag.CurrentNode = "agnes_22";
			AddCharacterExpToSkill(pchar, "Fortune", 350);
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterComplexReputation(pchar, "authority", 4);
		break;
		
		case "agnes_22":
			dialog.text = "Ah, capitano "+GetFullName(pchar)+"! Che gioia vederti! Vieni, siediti, ti verso da bere...";
			link.l1 = "Grazie! Volevo solo salutarti e sapere come te la cavi. Mi fa piacere che tu e Ole stiate bene.";
			link.l1.go = "exit";
			NextDiag.TempNode = "agnes_22";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Che stai facendo lì, eh? Ladro!","Guarda un po’! Appena mi sono perso nei miei pensieri, tu hai deciso di curiosare nel mio forziere!","Hai deciso di rovistare tra i miei forzieri? Non te la caverai così facilmente!");
			link.l1 = "Maledizione!";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "Cosa?! Hai pensato di frugare nei miei forzieri? Non la passerai liscia, mascalzone!";
			link.l1 = "Ragazzina sciocca!";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
