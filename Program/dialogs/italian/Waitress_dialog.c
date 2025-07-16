// диалог официантки
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk1, bOk2;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Tavern\" + NPChar.City + "_Waitress.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	switch(Dialog.CurrentNode)
	{
        case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			//--> Jason Цена чахотки
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") || SandBoxMode)
			{
				bOk1 = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win") || SandBoxMode;
				if (sti(pchar.rank) > 6 && npchar.location == "PortSpein_tavern" && !CheckAttribute(npchar, "quest.Consumption")  && bOk1)
				{
					dialog.text = "Cosa desidera, signore? Mi dispiace, sono solo...'singhiozza'... oh... mi dispiace.";
					link.l1 = "Perché sei così sconvolta, mia signora? Lacrime su un viso così bello? Cosa è successo?";
					link.l1.go = "Consumption";
					break;
				}
			}
			//<-- Цена чахотки
			
			// Addon-2016 Jason, французские миниквесты (”ЊЉ) Џорт Џренс
			if (npchar.location == "PortPax_tavern" && CheckAttribute(pchar, "questTemp.FMQP") && pchar.questTemp.FMQP == "begin")
            {
				DelMapQuestMarkCity("PortPax");
				DelLandQuestMark(npchar);
				PlaySound("Voice\English\Enc_RapersGirl_1.wav");
				dialog.text = "Signore! Signore, aiuto! Assassinio!";
				link.l1 = "Eh? Uccidendo chi? Dove? È uno scherzo, mia cara?";
				link.l1.go = "FMQP";
				break;
			}
			
			//--> Тайна Бетси Прайс
			if (npchar.location == "Villemstad_tavern" && CheckAttribute(pchar, "questTemp.TBP_BetsiPrice") && !CheckAttribute(pchar, "questTemp.TBP_BetsiPrice_Sex"))
			{
				bOk1 = CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && IsOfficer(characterFromId("Mary"));
				bOk2 = CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && IsOfficer(characterFromId("Helena"));
				if (bOk1 || bOk2)
				{
					switch (rand(1))
					{
						case 0:
							dialog.text = ""+pchar.name+"! Così bello rivederti... Grazie per essere passato... ma temo che questo non sia il momento migliore per parlare. Torna quando sarai solo. Allora potremo discutere... di questioni più personali.";
							link.l1 = "Sempre un piacere chiacchierare, ma dovrei andare. Forse ci incontreremo di nuovo.";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = ""+pchar.name+"... Stavo cominciando a pensare che avessi dimenticato la strada per la nostra taverna. Peccato che non sei solo. Speravo che potessimo parlare in privato.";
							link.l1 = "Credo che il destino ci darà ancora la possibilità di parlare in privato.";
							link.l1.go = "exit";
						break;
					}
				}
				else
				{
					switch (rand(1))
					{
						case 0:
							dialog.text = ""+pchar.name+"! Lo sapevo che non mi avresti fatto aspettare troppo. Non voglio perdere un altro minuto. La stanza al piano di sopra è libera... solo per noi. Non dirai di no, vero?";
							link.l1 = "Sai come attirarmi... Beh, non ho motivo di resistere. Ci proviamo?";
							link.l1.go = "TBP_BetsiPriceSex1";
							link.l2 = "Temerei che ho davvero alcune questioni importanti da affrontare oggi. Ma prometto, la prossima volta te lo rifarò.";
							link.l2.go = "exit";
						break;

						case 1:
							dialog.text = ""+pchar.name+"! Stavo cominciando a pensare che ti piacesse farmi aspettare. Non starai lì immobile come una statua, vero? Ci sono modi molto migliori per trascorrere questo tempo.";
							link.l1 = "Nessuno può resistere al tuo fascino... Non ha senso perdere tempo - sto andando al piano di sopra ora.";
							link.l1.go = "TBP_BetsiPriceSex1";
							link.l2 = "Sei davvero una tentatrice, Betsy... Ma purtroppo, devo essere da un'altra parte proprio ora.";
							link.l2.go = "exit";
						break;
					}
				}
				link.l9 = "Voglio farti un paio di domande.";
				link.l9.go = "quests";
				break;
			}
			//<-- Тайна Бетси Прайс
            NextDiag.TempNode = "First time";
			if (CheckAttribute(pchar, "questTemp.different.FackWaitress"))
			{
				if (pchar.questTemp.different == "FackWaitress_toRoom" || pchar.questTemp.different == "FackWaitress_toRoomUp")
				{
					dialog.text = "Ti ho chiesto di salire. Non restare qui e attirare attenzione.";
					link.l1 = "Bene, me ne vado, non voglio metterti nei guai...";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_noMoney" || pchar.questTemp.different == "FackWaitress_fighted")
				{
					dialog.text = "Sono nuovo qui, quindi per favore, non distrarmi dal mio lavoro. Ancora non riesco ad abituarmi...";
					link.l1 = "E dove è la cameriera che lavorava qui prima di te? "+pchar.questTemp.different.FackWaitress.Name+", come ricordo...";
					link.l1.go = "Love_IDN";
				}
				if (pchar.questTemp.different == "FackWaitress_facking")
				{					
					dialog.text = "Torna di nuovo, dolcezza. Potremmo divertirci ancora. Se avessi più tempo libero...";
					link.l1 = "Certo che lo farò, sei stato fantastico!";
					link.l1.go = "exit";
				}
				if (pchar.questTemp.different == "FackWaitress_fackNoMoney")
				{					
					dialog.text = "Non ti conosco, quindi non disturbarmi...";
					link.l1 = "Dove sono i miei soldi?!!";
					link.l1.go = "Love_IDN_1";
				}
				break;
			}
		    switch (Rand(4))
			{
				case 0:
					dialog.text = "Scusa, "+GetSexPhrase("affascinante","bella")+", Sono troppo occupato ora. È un buon momento per la taverna ma non per le chiacchiere!";
					link.l1 = "...";
					link.l1.go = "exit";
				break;

				case 1:
					dialog.text = "Per favore, capitano, non combattete qui! È un duro lavoro pulire questo posto.";
					link.l1 = ""+GetSexPhrase("Ehm... Non stavo nemmeno pensando di farlo.","Sembro forse un ubriacone in cerca di rissa? Sono solo una ragazza, come te, non preoccuparti.")+"";
					link.l1.go = "exit";
				break;

				case 2:
					if (hrand(1) == 0) // Addon-2016 Jason
					{
						dialog.text = ""+GetSexPhrase("Oh, capitano! Vorresti condividere un letto con me oggi? Non mi piace vantarmi ma...","Prendi un posto, capitano. È sempre un piacere incontrare un vero lupo di mare come te.")+"";
						link.l1 = "Peccato che ora abbia fretta. Alla prossima!";
						link.l1.go = "exit";
						bool bOk = (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) || (CheckAttribute(pchar, "questTemp.LSC.Mary_officer")) || npchar.city == GetLadyBethCity(); // 291112
						if (pchar.questTemp.different == "free" && !CheckAttribute(pchar, "questTemp.different.FackWaitress") && PChar.sex != "woman" && pchar.GenQuest.EncGirl != "HorseToTavern" && !bOk)
						{
							link.l2 = "Con grande piacere, tesoro!";
							link.l2.go = "Love_1";
						}
					}
					else
					{
						dialog.text = "Prendi posto, capitano. Assaggia il nostro rum, gioca a carte o dadi. Sentiti come a casa tua! È sempre un piacere incontrare un vero lupo di mare come te.";
						link.l1 = "Grazie, bella.";
						link.l1.go = "exit";
					}
				break;

				case 3:
					dialog.text = "Parla con il padrone se vuoi ordinare qualcosa. Si trova dietro il bancone del bar.";
					link.l1 = "Grazie per un consiglio.";
					link.l1.go = "exit";
				break;

				case 4:
					dialog.text = "Se vuoi riposare e rimetterti in sesto - affitta una stanza. Stare nella sala per tutta la notte non ti aiuterà molto.";
					link.l1 = "Grazie.";
					link.l1.go = "exit";
				break;
			}			
			link.l9 = "Voglio farti alcune domande.";
			link.l9.go = "quests";//(перессылка в файл города)
		break;
		
        case "Love_1":
			dialog.text = "Ascolta allora. Affitta una stanza qui nella taverna. Vai lì e aspettami. Mi intrufolerò lì un po' più tardi...";
			link.l1 = "Ha! Lo farò, tesoro! Ti aspetterò!";
			link.l1.go = "exit";
			pchar.questTemp.different = "FackWaitress_toRoom";
			SetTimerFunction("WaitressFack_null", 0, 0, 1); //освобождаем разрешалку на миниквесты на след. день
			//Шанс, что ограбят, если рендом выпадет на 0. он же делитель сколько она вытащит из кармана
			pchar.questTemp.different.FackWaitress.Kick = hrand(2); 
			pchar.questTemp.different.FackWaitress.Name = GetFullName(npchar); //запомним имя официантки
			pchar.questTemp.different.FackWaitress.City = npchar.city;
			//делаем клона официантки
			sld = GetCharacter(NPC_GenerateCharacter("WairessQuest", npchar.model, "woman", npchar.model.animation, 5, sti(npchar.nation), 3, false, "citizen"));
			sld.name = npchar.name;
			sld.lastname = npchar.lastname;
			sld.dialog.Filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = "Waitress";	
			Pchar.quest.WaitressFack_inRoom.win_condition.l1 = "location";
			Pchar.quest.WaitressFack_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			Pchar.quest.WaitressFack_inRoom.function = "WaitressFack_inRoom";
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
		break;
		
        case "Love_IDN":
			dialog.text = "Lei non lavora più qui, si è ritirata... Mi dispiace, ho un lavoro da fare.";
			link.l1 = "Bene...";
			link.l1.go = "exit";
		break;
		
        case "Love_IDN_1":
			dialog.text = "Ascolta bene, idiota lussurioso. Non so dove sia il tuo denaro! E se continui a mettermi sotto pressione, chiamerò le guardie e ti ritroverai in prigione!";
			link.l1 = "Bene, non sono necessari guardie... Che sciocco...";
			link.l1.go = "Love_IDN_2";
		break;
		
        case "Love_IDN_2":
			dialog.text = "Esattamente, che sciocco. La prossima volta sarai più intelligente e più decente.";
			link.l1 = "Cercherò... (sussurrando) Puttana maledetta...";
			link.l1.go = "exit";
		break;

		case "without_money":
			NextDiag.TempNode = "first time";
			dialog.text = "Mi senti?";
			link.l1 = "Uffa...";
			link.l1.go = "without_money_2";
		break;

		case "without_money_2":
			dialog.text = "Ti senti male? Hai mal di testa?";
			link.l1 = "Maledizione... dove sono?";
			link.l1.go = "without_money_3";
		break;

		case "without_money_3":
			dialog.text = "Non ti ricordi? Ti hanno derubato.";
			link.l1 = "Cosa? Oh... La mia testa... Chi oserebbe?!";
			link.l1.go = "without_money_4";
		break;

		case "without_money_4":
			dialog.text = "Come dovrei saperlo? Sono entrati di corsa, hanno minacciato di uccidere, hanno controllato le tue tasche e se ne sono andati.";
			link.l2 = "Capisco... Merda... Vorrei un po' d'acqua... Grazie.";
			link.l2.go = "exit";
		break;
		
		//--> Jason Цена чахотки
		case "Consumption":
			npchar.quest.Consumption = "true";
			dialog.text = "No, non è niente, signore... grazie per la tua gentilezza ma io ... (piangendo)";
			link.l1 = "Qualcuno ti ha offeso? Calmati, bella, raccontami tutto.";
			link.l1.go = "Consumption_1";
		break;
		
		case "Consumption_1":
			dialog.text = "No, no, signore, non è niente. Perdonami per la mia mancanza di controllo, è solo che... È mio fratello, dicono che sia morto ma non ci credo. Non so cosa credere ma sento nel mio cuore che è in grossi guai. E non ho nessuno tranne Angelo dopo la morte dei nostri genitori... (piange)";
			link.l1 = "Capisco, ma ti chiedo di calmarti, per favore. Cosa è successo a tuo fratello?";
			link.l1.go = "Consumption_2";
		break;
		
		case "Consumption_2":
			dialog.text = "Signore... per favore non fraintendetemi, ma perché un tale capitano dovrebbe preoccuparsi di una semplice e modesta ragazza della taverna? Non ho nemmeno nulla da promettervi per il vostro aiuto...";
			link.l1 = "Effettivamente, hai ragione. L'altruismo non fa per me, quindi sii forte, tutti perdiamo i nostri parenti. C'est la vie come diciamo in Francia...";
			link.l1.go = "exit";
			link.l2 = "Una donna può sempre trovare un modo per ringraziare un uomo.... Ah-ah. Ora, smetti di piangere e raccontami il tuo problema.";
			link.l2.go = "Consumption_3_1";
			link.l3 = "Giovane signorina, non sei informata che la nostra Chiesa ci insegna ad aiutarci a vicenda? Cercherò di aiutarti se ne sono capace, naturalmente.";
			link.l3.go = "Consumption_3_2";
		break;
		
		case "Consumption_3_1":
			if(sti(pchar.reputation.nobility) > 36)
			{
				dialog.text = "È stato un 'suggerimento'? Mi scuso, è stato un errore da parte mia parlare con te! Addio 'caballero'...";
				link.l1 = "Come desideri, tesoro.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Ebbene... Almeno sei onesto nei tuoi desideri. Ti prometto che se trovi Angelo o mi dici cosa gli è realmente accaduto, otterrai ciò che hai chiesto...";
				link.l1 = "Gentile signorina, è un piacere fare affari con te... Ora passiamo direttamente alla storia di tuo fratello.";
				link.l1.go = "Consumption_4";
				npchar.quest.Consumption.sex = "true";
			}
		break;
		
		case "Consumption_3_2":
			dialog.text = "Stai scherzando? Vuoi davvero aiutarmi gratuitamente?";
			link.l1 = "Solo un cattivo uomo non aiuterebbe una ragazza che piange. Non preoccuparti, voglio davvero aiutarti. Che cosa è successo esattamente ad Angelo?";
			link.l1.go = "Consumption_4";
		break;
		
		case "Consumption_4":
			dialog.text = "Molto bene, signore. Mio fratello, lui... oh, non è facile trattenere le lacrime per me, mi dispiace tanto... Eravamo davvero poveri a causa della mia... modestia sul lavoro forse... E Angelo ha iniziato a lavorare con i contrabbandieri locali. Pensava che la sua piccola barca da pesca avrebbe fatto più soldi trasportando qualcosa per evitare la dogana.";
			link.l1 = "Per dirlo in parole più semplici, tuo fratello è diventato un criminale, giusto?";
			link.l1.go = "Consumption_5";
		break;
		
		case "Consumption_5":
			dialog.text = "No, signore, non capisci... lui non è così! L'ha fatto per me! Per impedirmi di guadagnare soldi extra qui... sai cosa intendo. Eravamo indebitati e lui l'ha fatto per il mio onore e la mia anima. E poi... è stato preso. Non era un grosso problema, ho persino preso in prestito più soldi per pagare il suo rilascio... Ma hanno detto che è morto.";
			link.l1 = "Hanno detto? Chi ha detto? E perché non ci credi? È morto in una prigione?";
			link.l1.go = "Consumption_6";
		break;
		
		case "Consumption_6":
			dialog.text = "Sì. Quando ho portato i soldi per pagare il suo rilascio, il comandante mi ha detto che Angelo è morto di consunzione. Pensate solo! Era arrivato lì in buona salute e morì due settimane dopo proprio in quelle stanze. Loro... non mi hanno nemmeno permesso di vedere il corpo. Hanno detto che seppellivano i prigionieri proprio nella baia vicino al forte per evitare un'epidemia.";
			link.l1 = "Un'epidemia? Suona molto vero. Quindi semplicemente non vuoi crederci o hai ragioni più serie?";
			link.l1.go = "Consumption_7";
		break;
		
		case "Consumption_7":
			dialog.text = "No... No! (piange) So che sembra stupido, ma sono sicuro che saprei se fosse morto. Vedi, Angelo è sempre stato forte - un vero marinaio. Ma c'è un'altra cosa\nMio nonno è morto di consunzione quando ero bambino e lui, un vecchio, l'ha combattuta per anni! So come funziona, la consunzione non uccide le persone in giorni, credimi!";
			link.l1 = "Mh... Mi hai fatto dubitare anche a me, qualcosa non va decisamente qui. Non posso prometterti nulla, ma cercherò di scoprire di più.";
			link.l1.go = "Consumption_8";
		break;
		
		case "Consumption_8":
			dialog.text = "Anche una semplice promessa è molto più di quanto speravo! Sei così gentile, signore! Sarò qui ad aspettarti!";
			link.l1 = "Oh, gioventù! Così inconstante nei sentimenti... potresti gentilmente restituirmi la mia mano, bellezza, mi serve ancora ha-ha... Molto bene, allora, andrò a cercare in giro.";
			link.l1.go = "Consumption_9";
		break;
		
		case "Consumption_9":
			DialogExit();
			npchar.dialog.filename = "Quest\LineMiniQuests\Consumption.c";
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Consumption = "begin";
			AddQuestRecord("Consumption", "1");
		break;
		//<-- Цена чахотки
		
		// Addon-2016 Jason, французские миниквесты (”ЊЉ) Џорт Џренс
		case "FMQP":
			dialog.text = "No, no scherzi! Al piano di sopra! Due teppisti stanno uccidendo un nobile gentiluomo! Aiutalo, capitano, sei l'unico uomo armato qui!";
			link.l1 = "Corri fuori, chiama le guardie! Sto salendo al piano di sopra!";
			link.l1.go = "FMQP_1";
			link.l2 = "Mia cara, devi avermi scambiato per una guardia. Chiama una pattuglia in caso di omicidio.";
			link.l2.go = "FMQP_exit";
		break;
		
		case "FMQP_exit":
			dialog.text = "A-ah, guardie! Aiutatemi!";
			link.l1 = "...";
			link.l1.go = "FMQP_exit_1";
		break;
		
		case "FMQP_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
			LocatorReloadEnterDisable("Portpax_town", "reload4_back", true);
			SetFunctionTimerCondition("FMQP_Remove", 0, 0, 1, false);
		break;
		
		case "FMQP_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			pchar.quest.FMQP_room.win_condition.l1 = "locator";
			pchar.quest.FMQP_room.win_condition.l1.location = "Portpax_tavern";
			pchar.quest.FMQP_room.win_condition.l1.locator_group = "reload";
			pchar.quest.FMQP_room.win_condition.l1.locator = "reload2_back";
			pchar.quest.FMQP_room.function = "FMQP_InRoom";
		break;
	}
}
