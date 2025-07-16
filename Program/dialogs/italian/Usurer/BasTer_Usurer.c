// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quali domande hai?","Come posso aiutarti?"),"Hai provato a farmi quella domanda poco tempo fa...","Sì, lascia che indovini... Ancora una volta stiamo girando in tondo?","Ascolta, io gestisco le finanze qui, non rispondo alle domande...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea...","Non ho nulla di cui parlare al momento."),"Umph, dove se n'è andata la mia memoria...","Hai indovinato, mi dispiace...","Capisco...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "continue")
            {
                link.l1 = "Sono il capitano "+GetFullName(pchar)+". Il tuo uomo mi ha detto che volevi vedermi. Sono tutto orecchie.";
                link.l1.go = "FMQG";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "sucsess")
            {
                link.l1 = "Di nuovo io, monsieur "+GetFullName(pchar)+". Ho portato Bertrand Pinette. È nella mia stiva.";
                link.l1.go = "FMQG_14";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "letter")
            {
                link.l1 = "Sono di nuovo io, monsignore "+GetFullName(pchar)+". Parliamo un po'.";
                link.l1.go = "FMQG_17";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "killers")
            {
                link.l1 = "Sono di nuovo io, monsieur "+GetFullName(pchar)+". Parliamo un po'.";
                link.l1.go = "FMQG_17";
            }
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter"))
            {
                link.l1 = "Sono io di nuovo, monsieur "+GetFullName(pchar)+". Immagino che non ti aspettassi di rivedermi.";
                link.l1.go = "FMQG_23";
            }
		break;
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "A-ah, capitano "+GetFullName(pchar)+"! Sono così felice di vederti! Ti stavo aspettando da un bel po'... Bene. Ho una domanda da farti. Un po' di tempo fa, un uomo di nome Bertrand Pinette si è avvicinato a te nel porto per salire sulla tua nave. Un signore benestante con una parrucca di lusso. Ti suona familiare?";
			link.l1 = "Sì, lo fa. Si è veramente avvicinato a me con questo preciso scopo.";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			DelLandQuestMark(npchar);
			Log_Info("You have received a heavy purse");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "purse3");
			dialog.text = "Voleva assumere te e la tua nave? Capitano, mi faresti un grande favore raccontandomi tutti i dettagli di questo caso. Ne varrà la pena. Tieni, prendi questa borsa piena di monete. È tua, ora per favore raccontami di Bertrand Pinette.";
			link.l1 = "Molto bene. Monsieur Pinette ha assunto la mia nave per portare lui e due suoi amici dalla Guadalupa alla Spagna Maine. Più precisamente, alla Baia dei Mosquitos di Portobello. Ho fatto il lavoro, hanno lasciato la mia nave e sono entrati direttamente nella giungla.";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			dialog.text = "Capisco. E il signor Pinette ha menzionato la sua destinazione finale? E i suoi compagni?";
			link.l1 = "Secondo le sue parole, stavano andando a Panama. I suoi amici erano abbastanza intriganti: due ufficiali, uno spagnolo e uno francese. Ancora non riesco a capire cosa li unisse, ma non mi pagavano per fare domande.";
			link.l1.go = "FMQG_3";
		break;
		
		case "FMQG_3":
			dialog.text = "Un ufficiale spagnolo? E un ufficiale francese? Oh! Non è niente male! Bravo, monsieur Pinette! Che furbo! Ha trovato il modo di guadagnare anche qui! Panama, hai detto?";
			link.l1 = "Sì, e ti ho detto tutto quello che sapevo. Posso andarmene?";
			link.l1.go = "FMQG_4";
		break;
		
		case "FMQG_4":
			dialog.text = "Aspetta, capitano. Ho una proposta di affari per te. Non ti dispiacerebbe guadagnare qualche moneta? Ma, prima, lascia che ti dica qualcosa sui tuoi passeggeri.";
			link.l1 = "Bene, ascoltiamo.";
			link.l1.go = "FMQG_5";
		break;
		
		case "FMQG_5":
			dialog.text = "Signor Bertrand Pinette è apparso nella nostra colonia due anni fa e ha subito iniziato a fare affari con i capitani. L'affare è, beh, anche un affare oscuro... Gli consegnavano merci di grande scarsità in questo luogo, beni di valore, contrabbando, a volte anche schiavi... Stava costantemente prendendo prestiti per le sue operazioni illegali nel mio ufficio, ma ha sempre ripagato con tutti gli interessi\nPrima di lasciare l'isola con il vostro buon aiuto, aveva preso un grosso prestito, molto più grande del solito. Lui era... era un cliente fidato con una storia di credito impeccabile, ecco perché gli avevo fornito un prestito. Grande errore. Signor Pinette è fuggito e ovviamente non ha intenzione di restituire le mie monete.";
			link.l1 = "Quanto ammonta la somma, se posso chiedere?";
			link.l1.go = "FMQG_6";
		break;
		
		case "FMQG_6":
			dialog.text = "È grande. Circa centocinquantamila pesos in dobloni. Dieci casse, ognuna con centocinquanta dobloni. E senza menzionare tutti gli interessi.";
			link.l1 = "Mh... Ti ha pagato per due anni, ti ha fatto abituarti, ha contratto un prestito sostanzioso e poi è diventato un fuorilegge. Astuto.";
			link.l1.go = "FMQG_7";
		break;
		
		case "FMQG_7":
			dialog.text = "Esattamente, capitano. Ecco perché vorrei assumerti per un lavoro: trova quel mascalzone e portalo qui. Io, il governatore e il comandante troveremo un modo per farlo estinguere il suo debito. Hai visto quell'uomo, era tuo passeggero, significa che hai più possibilità di trovare il signor Pinette di chiunque altro. Certo, assumerò anche dei cacciatori di taglie professionisti per quel suo misero culo, ma ho la sensazione che il tuo aiuto risulterà più efficace.";
			link.l1 = "E che ne è della ricompensa?";
			link.l1.go = "FMQG_8";
		break;
		
		case "FMQG_8":
			dialog.text = "Per svolgere il lavoro, ti darò un baule pieno di dobloni, centocinquanta monete.";
			link.l1 = "Direi che sarebbe una ricompensa piuttosto patetica per rintracciare e rapire un'anima viva nella città spagnola.";
			link.l1.go = "FMQG_9";
		break;
		
		case "FMQG_9":
			dialog.text = "Capitano, presumo che il signor Pinette ti abbia pagato bene con i miei soldi visto che valuti la mia proposta così poco. Ti assicuro che ne vale la pena. Naturalmente, hai tutto il diritto di rifiutare... ma ho qualcosa da dirti e sicuramente ti farà cambiare idea.";
			link.l1 = "E cosa sarebbe?";
			link.l1.go = "FMQG_10";
		break;
		
		case "FMQG_10":
			dialog.text = "Alcuni giorni prima della fuga di Pinette da Guadeloupe, un prigioniero era scappato dal carcere di Basse-Terre. Il suo nome è don Carlos de Milyar, un nobile spagnolo e un ufficiale. È riuscito a fuggire grazie al tradimento di un ufficiale francese, un tenente dei Marines... Capisci cosa voglio dire?";
			link.l1 = "Hm... E come mi riguarda? Stavo facendo un trasporto di passeggeri, nient'altro.";
			link.l1.go = "FMQG_11";
		break;
		
		case "FMQG_11":
			dialog.text = "Certo, lo eri! Personalmente, non ho alcun dubbio che tu non abbia nulla a che fare con l'organizzazione della fuga di don de Milyar. Ma non è così che il nostro governatore e il nostro comandante potrebbero pensarci. Un'accusa di complicità se sei fortunato e se non lo sei... davvero non voglio continuare. Vedi da solo, hai preso a bordo un ufficiale spagnolo in fuga, molto probabilmente in qualche insenatura nascosta... ho ragione, capitano?";
			link.l1 = "Capisco. Mi stai ricattando. Ho commesso un errore venendo qui...";
			link.l1.go = "FMQG_12";
		break;
		
		case "FMQG_12":
			dialog.text = "Cosa ne dici, capitano?! Non ti sto ricattando! Tutto quello che chiedo è di aiutarmi in cambio di una buona ricompensa. Saresti così gentile da trovare il signor Pinette e portarlo a Basse-Terre? Aspetterò il tuo ritorno. Credo che due mesi siano sufficienti per navigare fino a Panama e tornare.";
			link.l1 = "Non mi lasci scelta. Anche se dubito che tale approccio commerciale servirà a farci diventare amici. Addio, signore.";
			link.l1.go = "FMQG_13";
		break;
		
		case "FMQG_13":
			DialogExit();
			LocatorReloadEnterDisable("Baster_town", "reload1_back", false);
			LocatorReloadEnterDisable("Baster_town", "reload2_back", false);
			LocatorReloadEnterDisable("Baster_town", "gate_back", false);//открыть выходы из города
			pchar.questTemp.FMQG = "headhunter_panama";
			ReOpenQuestHeader("FMQ_Guadeloupe");
			AddQuestRecord("FMQ_Guadeloupe", "7");
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("FMQG_UsurerTimeOut", 0, 0, 122, false);
			}
			else SetFunctionTimerCondition("FMQG_UsurerTimeOut", 0, 0, 61, false);
			AddMapQuestMarkCity("panama", false);
			AddLandQuestMark(characterFromId("Panama_tavernkeeper"), "questmarkmain");
			
			// Sinistra - Старт квеста "Мерзкий Божок"
			PChar.quest.ChickenGod_StartLoc.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ChickenGod_StartLoc.win_condition.l1.location = PChar.location;
			PChar.quest.ChickenGod_StartLoc.function = "ChickenGod_BrothelCheck";
		break;
		
		case "FMQG_14":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "Ottime notizie, capitano! Manderò subito i miei uomini a prendere questo bastardo dalla tua nave. Questo uccellino non mi sfuggerà questa volta... Te lo sei meritato il tuo premio, prendi questo baule. Per favore, non arrabbiarti con me, ecco un amuleto per te. È un dono.";
			link.l1 = "Grazie. Presumo che il tuo silenzio sia anche parte della mia ricompensa?";
			link.l1.go = "FMQG_15";
		break;
		
		case "FMQG_15":
			Log_Info("You have received a chest full of doubloons");
			Log_Info("You have received a 'Fisherman' amulet");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "chest");
			GiveItem2Character(pchar, "obereg_7");
			dialog.text = "Silenzio? Su cosa? Sarei lieto di vederti tra i miei clienti. Sai cosa dicono del silenzio e dell'oro?";
			link.l1 = "Vale molto più dell'oro a volte, signore. Lezione appresa. Addio!";
			link.l1.go = "FMQG_16";
		break;
		
		case "FMQG_16":
			DialogExit();
			pchar.quest.FMQG_UsurerTimeOut.over = "yes";
			ref sld = characterFromId("FMQG_pass_1");
			RemovePassenger(pchar, sld);
			sld.lifeday = 0;
			pchar.questTemp.FMQG = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Guadeloupe", "23");
			CloseQuestHeader("FMQ_Guadeloupe");
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;
		
		case "FMQG_17":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("baster");
			dialog.text = "Sto ascoltando. Immagino che Bertrand Pinette sia sulla tua nave?";
			link.l1 = "No. Anche se ho qualcosa di molto meglio per te. Leggi questo.";
			link.l1.go = "FMQG_18";
		break;
		
		case "FMQG_18":
			RemoveItems(pchar, "letter_baker", 1);
			dialog.text = "Cos'è questo?";
			link.l1 = "Continua a leggere, signore. Continueremo più tardi.";
			link.l1.go = "FMQG_19";
		break;
		
		case "FMQG_19":
			LAi_Fade("", "");
			dialog.text = "(leggendo) Ehm ... Cos'è questa assurdità di un paziente febbrile?";
			link.l1 = "Sei serio? Va bene, porterò queste 'sciocchezze' al governatore. Credo che mostrerà un grande interesse nell'apprendere la verità sulla scomparsa della 'Courage' e del suo carico di diamanti... Perché sei diventato così pallido?";
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter")) link.l1.go = "FMQG_24";
			else link.l1.go = "FMQG_20";
		break;
		
		case "FMQG_20":
			dialog.text = "Allora, hai trovato Pinette dopo tutto...";
			link.l1 = "Sì. Allora ti propongo un affare. Dimenticati di Carlos de Milyar, Jean Deno e altri bravi signori, fai questo e io dimenticherò questa lettera.";
			link.l1.go = "FMQG_21";
		break;
		
		case "FMQG_21":
			dialog.text = "Molto bene, capitano... Accetto le vostre condizioni.";
			link.l1 = "Magnifico. Spero che non siate arrabbiati con me, abbiamo finito ora, penso. Addio.";
			link.l1.go = "FMQG_22";
		break;
		
		case "FMQG_22":
			DialogExit();
			pchar.quest.FMQG_UsurerTimeOut.over = "yes";
			pchar.questTemp.FMQG = "cave";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
			pchar.quest.FMQG_cave.win_condition.l1 = "location";
			pchar.quest.FMQG_cave.win_condition.l1.location = "Guadeloupe_Cave";
			pchar.quest.FMQG_cave.function = "FMQG_InCave";
			// заполним сундук
			pchar.GenQuestBox.Guadeloupe_Cave = true;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse1 = 5;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse2 = 2;
			pchar.GenQuestBox.Guadeloupe_Cave.box3.items.purse3 = 1;
			SetFunctionTimerCondition("FMQG_ClearBox", 0, 0, 3, false);
			if (CheckAttribute(pchar, "questTemp.FMQG.Letter"))
			{
				SetFunctionTimerCondition("FMQG_RemoveHunterScore", 0, 0, 1, false);
				AddQuestRecord("FMQ_Guadeloupe", "29");
				DeleteAttribute(pchar, "questTemp.FMQG.Letter");
			}
			else AddQuestRecord("FMQ_Guadeloupe", "25");
		break;
		
		case "FMQG_23":
			dialog.text = "Ha... Hai ragione, capitano.";
			link.l1 = "Ho qualcosa per te. Prendi questo e leggi.";
			link.l1.go = "FMQG_18";
		break;
		
		case "FMQG_24":
			dialog.text = "Allora, hai trovato Pinette dopo tutto...";
			link.l1 = "Sì. Quindi ti propongo un affare. Ripristina il mio buon nome nelle colonie francesi e dimenticherò questa lettera.";
			link.l1.go = "FMQG_25";
		break;
		
		case "FMQG_25":
			dialog.text = "Ma...";
			link.l1 = "Non me ne frega niente di come lo farai. Se la caccia alla mia testa non finisce domani, il governatore saprà tutto.";
			link.l1.go = "FMQG_21";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
