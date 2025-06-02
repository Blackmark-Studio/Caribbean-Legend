// Addon-2016 Jason, французские миниквесты (ФМК) Гваделупа
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
			dialog.text = "Un evidente malfunzionamento. Segnala la cosa agli sviluppatori.";
			link.l1 = "Oh, ci puoi scommettere.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// квестодатель
		case "citizen":
			DelMapQuestMarkCity("Baster");
			LAi_SetImmortal(npchar, false);
			LAi_RemoveLoginTime(npchar);
			dialog.text = "Saluti, capitano! Ho una proposta d’affari che troverai assai interessante.";
			link.l1 = "Avanti, monsieur.";
			link.l1.go = "citizen_1";
			DelLandQuestMark(npchar);
		break;
		
		case "citizen_1":
			dialog.text = "Voglio ingaggiare la tua nave per un trasporto dalla Guadalupa fino alla Terraferma spagnola.";
			link.l1 = "Vuoi imbarcarti lì come passeggero?";
			link.l1.go = "citizen_2";
			link.l2 = "Il Mar dei Caraibi spagnolo? Passo. Non siamo certo amici degli spagnoli. Ti consiglio di cercare un altro babbeo.";
			link.l2.go = "citizen_no";
		break;
		
		case "citizen_no":
			dialog.text = "Come volete, capitano, anche se questa traversata non è poi così rischiosa. Addio.";
			link.l1 = "Addio.";
			link.l1.go = "citizen_exit";
		break;
		
		case "citizen_no_1":
			dialog.text = "Come desiderate, capitano. Addio!";
			link.l1 = "Addio.";
			link.l1.go = "citizen_exit";
		break;
		
		case "citizen_exit":
			DialogExit();
			chrDisableReloadToLocation = false;
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
		break;
		
		case "citizen_2":
			dialog.text = "Non proprio così, monsieur. Un passeggero è un uomo che dipende dal volere del capitano. Io desidero ingaggiare voi, la vostra ciurma e la vostra nave, per portare me stesso e due miei compari fino a Panama.";
			link.l1 = "A Panama? Come, diavolo? Vuoi circumnavigare tutto il maledetto continente?";
			link.l1.go = "citizen_3";
		break;
		
		case "citizen_3":
			dialog.text = "Ah-ah-ah! Bella trovata, capitano. Certo che no. Dovrai solo portarci alla Baia delle Zanzare, che non è lontana da Portobello. Da lì ce la faremo da soli fino a Panama, non è la nostra prima scorribanda nella giungla.";
			link.l1 = "E che mi dici del pagamento?";
			link.l1.go = "citizen_4";
		break;
		
		case "citizen_4":
			dialog.text = "Due scrigni colmi di dobloni. Trecento pezzi d’oro. Uno lo avrai subito, appena saremo a bordo. Il secondo sarà tuo non appena giungeremo a destinazione.";
			link.l1 = "Una ricompensa così generosa per un lavoretto tanto semplice. Dov'è la fregatura, buon uomo?";
			link.l1.go = "citizen_5";
		break;
		
		case "citizen_5":
			dialog.text = "Capitano, il tempo è oro, io e i miei compari non ne abbiamo. Dobbiamo mollare gli ormeggi stanotte e arrivare là entro dieci giorni. Sarà la nostra seconda corsa. Allora, ci stai?";
			link.l1 = "Affare fatto!";
			link.l1.go = "citizen_6";
			link.l2 = "Mi dispiace, monsieur, ma la vostra proposta mi puzza troppo. Andate a cercarvi un altro gonzo.";
			link.l2.go = "citizen_no_1";
		break;
		
		case "citizen_6":
			dialog.text = "Splendido. I miei compari sono nella giungla al momento, farò sapere loro del nostro patto. Ci troverai stanotte sulla spiaggia di Capster alle dieci in punto. Non far tardi, Capitano!";
			link.l1 = "D’accordo. Capster Beach, stanotte, alle dieci in punto.";
			link.l1.go = "citizen_7";
		break;
		
		case "citizen_7":
			dialog.text = "Un momento, capitano, non ci siamo nemmeno presentati. Il mio nome è Bertrand Pinette. E voi siete...";
			link.l1 = ""+GetFullName(pchar)+". Capitano "+GetFullName(pchar)+"Ci vediamo, monsieur Pinette.";
			link.l1.go = "citizen_8";
		break;
		
		case "citizen_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "OpenTheDoors", 20.0);
			npchar.location = "None";
			AddQuestRecord("FMQ_Guadeloupe", "1");
			pchar.quest.FMQG_Capster.win_condition.l1 = "Hour";
			pchar.quest.FMQG_Capster.win_condition.l1.start.hour = 22.00;
			pchar.quest.FMQG_Capster.win_condition.l1.finish.hour = 23.99;
			pchar.quest.FMQG_Capster.win_condition.l2 = "Ship_location";
			pchar.quest.FMQG_Capster.win_condition.l2.location = "Shore29";
			pchar.quest.FMQG_Capster.win_condition.l3 = "location";
			pchar.quest.FMQG_Capster.win_condition.l3.location = "Shore29";
			pchar.quest.FMQG_Capster.function = "FMQG_CapsterBeach";
			SetFunctionTimerCondition("FMQG_StartLate", 0, 0, 1, false);
			pchar.questTemp.FMQG = "begin";
			pchar.GenQuest.SmugglersBlock = "baster_tavern";
		break;
		
		case "citizen_9":
			DelLandQuestMark(npchar);
			dialog.text = "Capitano "+GetFullName(pchar)+", eccoti. Siamo pronti a salpare?";
			link.l1 = "Sì. Benvenuto a bordo.";
			link.l1.go = "citizen_10";
		break;
		
		case "citizen_10":
			dialog.text = "Benissimo. Prendi il tuo anticipo – uno scrigno pieno di dobloni. E ricorda: hai solo dieci giorni per portarci a destinazione. Non un giorno di più!";
			link.l1 = "Ricordo i patti. Tranquilli, ci arriviamo in tempo. Prendete posto.";
			link.l1.go = "citizen_11";
		break;
		
		case "citizen_11":
			DialogExit();
			GiveItem2Character(pchar, "chest");
			log_info("You have received a chest full of doubloons");
			PlaySound("interface\important_item.wav");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "officers", "sea_1", "none", "", "", "FMQG_OnBoard", 20.0);
			for (i=2; i<=3; i++)
			{
				sld = characterFromId("FMQG_pass_"+i);
				LAi_ActorRunToLocation(sld, "officers", "sea_"+i, "none", "", "", "", 10.0);
			}
			pchar.quest.FMQG_SailStart.win_condition.l1 = "location";
			pchar.quest.FMQG_SailStart.win_condition.l1.location = "Guadeloupe";
			pchar.quest.FMQG_SailStart.function = "FMQG_SailingStart";
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("FMQG_SailingLate", 0, 0, 20, false);
				SetFunctionTimerCondition("FMQG_MutiniActivate", 0, 0, 40, false);
			}
			else
			{
				SetFunctionTimerCondition("FMQG_SailingLate", 0, 0, 10, false);
				SetFunctionTimerCondition("FMQG_MutiniActivate", 0, 0, 20, false);
			}
			pchar.questTemp.FMQG = "sail";
			DeleteAttribute(pchar, "GenQuest.SmugglersBlock");
		break;
		
		case "citizen_12":
			dialog.text = "Dunque, Capitano, avete portato a termine la vostra parte dell’accordo. Ora tocca a me. Prendete questo forziere insieme alla nostra più sincera gratitudine.";
			link.l1 = "È stato un piacere fare affari con voi, monsieur.";
			link.l1.go = "citizen_13";
		break;
		
		case "citizen_13":
			GiveItem2Character(pchar, "chest");
			log_info("You have received a chest full of doubloons");
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Sailing", 200);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			dialog.text = "Anche a te. Addio, capitano "+GetFullName(pchar)+".";
			link.l1 = "Addio!";
			link.l1.go = "citizen_14";
		break;
		
		case "citizen_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 20.0);
			for (i=2; i<=3; i++)
			{
				sld = characterFromId("FMQG_pass_"+i);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
				sld.lifeday = 0;
			}
			AddQuestRecord("FMQ_Guadeloupe", "6");
			CloseQuestHeader("FMQ_Guadeloupe");
			pchar.questTemp.FMQG = "pause";
			pchar.quest.FMQG_Continue.win_condition.l1 = "Ship_location";
			pchar.quest.FMQG_Continue.win_condition.l1.location = "Baster_town";
			pchar.quest.FMQG_Continue.win_condition.l2 = "location";
			pchar.quest.FMQG_Continue.win_condition.l2.location = "Baster_town";
			pchar.quest.FMQG_Continue.function = "FMQG_BasterContinue";
			/* pchar.quest.FMQG_Block1.win_condition.l1 = "Rank";
			pchar.quest.FMQG_Block1.win_condition.l1.value = 13;
			pchar.quest.FMQG_Block1.win_condition.l1.operation = ">=";
			pchar.quest.FMQG_Block1.function = "FMQG_Block"; */
			//SetFunctionTimerCondition("FMQG_Block", 0, 0, 90, false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);	// лесник - открыть оружие снова.
			AddMapQuestMarkCity("baster", false);
		break;
		
		case "citizen_12a":
			dialog.text = "Dunque, Capitano, eccoci qui. Hai rispettato solo metà dell’accordo, quindi farò lo stesso. Tieniti l’anticipo come paga intera. Spero che non ti dispiaccia, dopotutto la colpa è tua.";
			link.l1 = "Non posso dire che mi piaccia questa faccenda, ma ammetto che hai ragione. Ora separiamoci qui.";
			link.l1.go = "citizen_13a";
		break;
		
		case "citizen_13a":
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Sneak", 50);//скрытность
			dialog.text = "Comunque sia, grazie per il servizio, capitano "+GetFullName(pchar)+". Addio!";
			link.l1 = "Addio.";
			link.l1.go = "citizen_14";
		break;
		
		case "citizen_15":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("bridgetown");
			dialog.text = "Oh! Che incontro! "+TimeGreeting()+", "+GetFullName(pchar)+"! Ma come?";
			link.l1 = TimeGreeting()+", monsieur Pinette. Non è stato facile trovarti.";
			link.l1.go = "citizen_16";
		break;
		
		case "citizen_16":
			sld = characterFromId("Baster_usurer");
			dialog.text = "E qual è la ragione, capitano?";
			link.l1 = "Mio buon signore, vi è un uomo di nome "+GetFullName(sld)+" e desidera ardentemente vederti. Immagino tu sappia il perché.";
			link.l1.go = "citizen_17";
		break;
		
		case "citizen_17":
			sld = characterFromId("Baster_usurer");
			dialog.text = "Ma certo che lo so, mio caro Capitano, ma dovete sapere che nemmeno io ho gran voglia di vedere monsieur "+GetFullName(sld)+"   proprio per niente. Sei forse il suo segugio? Non ci arrivo mica.";
			link.l1 = "Ahimè, ma così stanno le cose ora e non ne vado fiero. Ho fatto una sciocchezza e ora, monsieur "+GetFullName(sld)+", maledetto lui, mi ha messo di fronte a una scelta. O il tuo glorioso ritorno a Guadalupa, oppure la mia pellaccia come complice nella tua piccola impresa di liberare don Carlos de Milyar. E questo mi rovinerà, lo sai bene.";
			link.l1.go = "citizen_18";
		break;
		
		case "citizen_18":
			sld = characterFromId("Baster_usurer");
			dialog.text = "Ah, quel bastardo! È davvero una canaglia ricattare la gente così... Allora, Capitano, che decidi? Prenderai una decisione o ti farai ricattare da uno così?";
			link.l1 = "E tu che ne pensi? Credo proprio che tu venga con me a Basse-Terre.";
			link.l1.go = "citizen_19";
			link.l2 = "Ho forse scelta, qui?";
			link.l2.go = "citizen_25";
		break;
		
		case "citizen_19":
			dialog.text = "Oh, devo proprio deluderti, Capitano. Non ho alcuna intenzione di salire a bordo della tua splendida nave. Qui con la forza non otterrai nulla, il posto è pieno di guardie e io griderò aiuto al minimo segno di violenza. Certo, potresti provare a pugnalarmi, ma il nostro bravo amico non vedrebbe mai un soldo da un cadavere freddo. Quindi, la cosa più saggia per te ora è lasciarmi in pace. Ti permetterò di andar via senza un graffio.";
			link.l1 = "Credi davvero che me ne andrò così dopo tutto quello che è successo? Mi hai trascinato in questo guaio, maledetto, ora paga il fio!";
			link.l1.go = "citizen_20";
			link.l2 = "Hai ragione, suppongo. Mi piacerebbe piantarti la lama tra le costole, ma non avrebbe senso. Non ti illudere che sia finita qui. Ora me ne vado a Basse-Terre, dove informerò il nostro caro amico di dove ti trovi. Poi manderà i suoi uomini mascherati alle tue calcagna.";
			link.l2.go = "citizen_21";
		break;
		
		case "citizen_20":
			dialog.text = "A-ah! Soldati! Aiuto!!!";
			link.l1 = "...";
			link.l1.go = "citizen_fight";
		break;
		
		case "citizen_21":
			dialog.text = "Ma certo. Di' al tuo padrone che tenga a bada i suoi mascalzoni mascherati – ultimamente sto diventando piuttosto famoso. Addio, Capitano.";
			link.l1 = "...";
			link.l1.go = "citizen_22";
		break;
		
		case "citizen_22":
			DialogExit();
			LAi_SetActorType(npchar);
			AddQuestRecord("FMQ_Guadeloupe", "19");
			pchar.quest.FMQG_Mayak.win_condition.l1 = "location";
			pchar.quest.FMQG_Mayak.win_condition.l1.location = "Mayak2";
			pchar.quest.FMQG_Mayak.function = "FMQG_Lighthouse";
		break;
		
		case "citizen_23":
			DelLandQuestMark(npchar);
			dialog.text = "Fermati! Mi arrendo! Mi arrendo!";
			link.l1 = "Ben detto! Ora getta l'arma e marcia verso la nave!";
			link.l1.go = "citizen_24";
		break;
		
		case "citizen_24":
			DialogExit();
			chrDisableReloadToLocation = false;
			RemoveAllCharacterItems(npchar, true);
			DoQuestReloadToLocation("Mayak2", "goto", "goto1", "FMQG_OnLighthouse");
		break;
		
		case "citizen_25":
			dialog.text = "C’è sempre una scelta, capitano. Da quel che capisco, non mi daresti la caccia se non fosse per quelle minacce del banchiere, vero?";
			link.l1 = "Proprio così.";
			link.l1.go = "citizen_26";
		break;
		
		case "citizen_26":
			dialog.text = "Bene. Allora ti preparo un modo sicuro per tappare quella bocca. Scriviamo una lettera che porterai al tuo principale. Digli che se mai dovesse parlare, il governatore di Guadalupa verrà a sapere dell’uomo che ha ordito e finanziato la sparizione della Courage, una lancia corriera incaricata di trasportare un grosso carico di diamanti.";
			link.l1 = "Hm. Credo di cominciare a capire, monsieur Pinette.";
			link.l1.go = "citizen_27";
		break;
		
		case "citizen_27":
			dialog.text = "Contento che tu abbia quella testa, Capitano. De Lion inchioderà di persona la zucca di quel furfante alle porte della città se scopre la verità sulla sparizione del Courage. Nella lettera che sto per scrivere troverai le prove che placheranno il ricattatore. Dammi un attimo che prendo la penna.";
			link.l1 = "D'accordo...";
			link.l1.go = "citizen_28";
		break;
		
		case "citizen_28":
			LAi_Fade("", "");
			GiveItem2Character(pchar, "letter_baker");
			ChangeItemDescribe("letter_baker", "itmdescr_letter_pinett");
			dialog.text = "(scrivendo) Tieni, prendi questo. In questo pacco ci sono due lettere simili. Consegnane una al banchiere, che se la goda pure. L’altra tienila per te, e nascondila bene.";
			link.l1 = "  Questa informazione è affidabile?";
			link.l1.go = "citizen_29";
		break;
		
		case "citizen_29":
			sld = characterFromId("Baster_usurer");
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Baster", false);
			dialog.text = "Te lo giuro sul mio onore, mi hai aiutato e ora tocca a me ricambiare. Stai tranquillo, il ricattatore ti lascerà in pace appena leggerà questo testamento. Ah, già... Un'ultima cosa, capitano. Visto che abbiamo risolto tutto senza spargimenti di sangue... ho una scorta nascosta e ti dirò dove trovarla, se mi prometti di non impicciarti più nei miei affari d'ora in avanti. Tanto a Guadalupa non mi faranno mai più mettere piede.";
			link.l1 = "Se la lettera farà il suo dovere, allora su questo puoi contarci, te lo giuro.";
			link.l1.go = "citizen_30";
		break;
		
		case "citizen_30":
			dialog.text = "Affare fatto, allora. Cerca tra le rocce dentro la grotta di Guadalupa. Che ti serva da umile ricompensa per le tue fatiche. Che il vento ti sia favorevole, capitano.";
			link.l1 = "Altrettanto a voi, monsieur Pinette.";
			link.l1.go = "citizen_31";
		break;
		
		case "citizen_31":
			DialogExit();
			pchar.questTemp.FMQG = "letter";
			AddQuestRecord("FMQ_Guadeloupe", "24");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 1;
		break;
		
		case "citizen_fight":
			chrDisableReloadToLocation = true;
			LAi_group_Delete("EnemyFight");
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			AddDialogExitQuest("MainHeroFightModeOn");
			DoQuestFunctionDelay("FMQG_PlantationGuards", 3.0);
			pchar.questTemp.FMQG = "fail";
			AddQuestRecord("FMQ_Guadeloupe", "18");
			CloseQuestHeader("FMQ_Guadeloupe");
		break;
		
		// вестовой к ростовщику
		case "cureer":
			DelMapQuestMarkCity("baster");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			npchar.lifeday = 0;
			dialog.text = "Salute, monsieur! Siete il capitano "+GetFullName(pchar)+", giusto?";
			link.l1 = "Esatto. Che posso fare per voi?";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			sld = characterFromId("BasTer_usurer");
			dialog.text = "Monsieur "+GetFullName(pchar)+", il proprietario della banca di Basse-Terre ti chiede di fargli visita il prima possibile. Mi ha ordinato di controllare ogni giorno l’ufficio del porto per non rischiare di mancare il tuo arrivo.";
			link.l1 = "Interessante, e perché mai avrebbe tutta questa smania di vedermi?";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			dialog.text = "Monsieur "+GetFullName(sld)+" ti racconterà di persona il motivo. Spero che tu non rifiuterai il suo invito.";
			link.l1 = "Hm.. Va bene. Questi banchieri sono gente potente e non perdono mai tempo coi pesci piccoli. Andrò a trovare quell'uomo il prima possibile.";
			link.l1.go = "cureer_3";
		break;
		
		case "cureer_3":
			dialog.text = "Grazie, Capitano. Addio!";
			link.l1 = "Addio.";
			link.l1.go = "cureer_4";
		break;
		
		case "cureer_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Baster_town", "reload1_back", true);
			LocatorReloadEnterDisable("Baster_town", "reload2_back", true);
			LocatorReloadEnterDisable("Baster_town", "gate_back", true);//закрыть выходы из города
			pchar.questTemp.FMQG = "continue";
			pchar.quest.FMQG_Block.over = "yes";
			pchar.quest.FMQG_Block1.over = "yes";
			AddLandQuestMark(characterFromId("Baster_usurer"), "questmarkmain");
		break;
		
		// Жан Дено
		case "Juan":
			dialog.text = "Argh! Feccia! Non può essere un incontro casuale...";
			link.l1 = "Proprio così, Jean... perdona, volevo dire Juan. Ti ho rintracciato. Ora potresti accomodarti nella mia stiva? Sfogati un po', poi parleremo.";
			link.l1.go = "Juan_1";			
		break;
		
		case "Juan_1":
			DialogExit();
			Lai_SetPlayerType(pchar);
			DeleteAttribute(npchar, "DontRansackCaptain");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 3.0);
			pchar.questTemp.FMQG.Prisoner = GetFullName(npchar);
			pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
			AddQuestRecord("FMQ_Guadeloupe", "14");
			pchar.questTemp.FMQG = "juan_capture";
			DoQuestCheckDelay("LAi_ReloadBoarding", 3.5);
		break;
		
		case "Juan_2":
			dialog.text = "";
			link.l1 = "Ho mantenuto la mia parte dell’accordo. Ora tocca a te. Spara pure, ma tieni bene a mente cosa succede a chi mente.";
			link.l1.go = "Juan_3";
		break;
		
		case "Juan_3":
			dialog.text = "Troverai Bertrand Pinette a Barbados, precisamente nella piantagione principale. Aveva intenzione di continuare i suoi traffici laggiù. Il sorvegliante della piantagione è un suo compare.";
			link.l1 = "Che genere d’operazioni?";
			link.l1.go = "Juan_4";
		break;
		
		case "Juan_4":
			dialog.text = "Proprio come faceva a Guadalupa. Traffici mezzi leciti, contrabbando, schiavi. Credo che punti al commercio degli schiavi e allo zucchero, altrimenti perché si sarebbe trasferito in piantagione?";
			link.l1 = "Capisco. Ha forse dei protettori tra le autorità inglesi?";
			link.l1.go = "Juan_5";
		break;
		
		case "Juan_5":
			dialog.text = "Suppongo di sì. Un tipo curioso, quello. Ha sempre amici dappertutto.";
			link.l1 = "Altro?";
			link.l1.go = "Juan_6";
		break;
		
		case "Juan_6":
			dialog.text = "Come cosa? Furbo e scaltro, sa sempre tutto, ha sempre un asso nella manica. Non ho avuto molto tempo per saperne di più su di lui.";
			link.l1 = "Va bene. D’accordo, devo salpare verso Bridgetown. Sei libero, don Juan. Ma non ti azzardare a dare l’allarme a Pinette. Se non lo trovo laggiù, sarà di nuovo il tuo culo a rischiare.";
			link.l1.go = "Juan_7";
		break;
		
		case "Juan_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			pchar.questTemp.FMQG = "headhunter_pinett";
			AddQuestRecord("FMQ_Guadeloupe", "17");
			// Пинетта - в Бриджтаун
			sld = characterFromId("FMQG_pass_1");
			ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation_F2", "goto", "goto1");
			sld.Dialog.currentnode = "citizen_15";
			LAi_SetStayType(sld);
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("bridgetown", false);
		break;
		
		case "killer":
			dialog.text = "Mi spiace, compare. Niente di personale. Sai troppe cose, ecco il tuo guaio.";
			link.l1 = "...";
			link.l1.go = "killer_1";
		break;
		
		case "killer_1":
			DialogExit();
			AddLandQuestMark(characterFromId("Baster_usurer"), "questmarkmain");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // правки релиза								  
			LAi_group_Delete("EnemyFight");
			int n = 2;
			if (MOD_SKILL_ENEMY_RATE > 6) n = 3;
			for (i=1; i<=n; i++)
			{
				sld = characterFromId("FMQG_killer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FMQG_KillersDestroy");
			LAi_SetFightMode(pchar, true);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
