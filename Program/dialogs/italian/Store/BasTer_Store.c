// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Avanti, cosa vuoi?","Proprio di questo stavamo parlando. Devi aver dimenticato...","Questa è la terza volta oggi che parli di qualche domanda...","Ascolta, questo è un negozio. Le persone comprano roba qui. Non disturbarmi!","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sai, "+NPChar.name+", forse la prossima volta.","Giusto, ho dimenticato per qualche motivo...","Sì, è davvero la terza volta...","Mm, non vorrei...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			//Jason --> ----------------------------------мини-квест Бесчестный конкурент------------------------------------
			if (CheckAttribute(pchar, "questTemp.Shadowtrader"))
			{
				if(pchar.questTemp.Shadowtrader == "begin" && GetNpcQuestPastDayParam(npchar, "Shadowtrader_date") < 5 && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Grazie, capitano, per aver esaudito la mia richiesta. Ora, quando "+pchar.questTemp.Shadowtrader.Guardername+" è qui, posso almeno sentirmi un po' più rilassato.";
					link.l1 = "Hmm... Non vorrei sembrare invadente, ma mi sembra che tu abbia dei problemi. Puoi dirmi di cosa si tratta - forse, potrei aiutarti?"; 
					link.l1.go = "Shadowtrader_fort";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.Trouble") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Allora? Hai consegnato la mia lettera?";
					link.l1 = "Lo ho. Il comandante ha risposto a voce che le prove nella tua lettera sono insufficienti per far sì che la guardia cittadina prenda qualsiasi misura."; 
					link.l1.go = "Shadowtrader_trouble";
					pchar.quest.ShadowtraderTimeFort_Over.over = "yes";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store" && CheckAttribute(pchar, "questTemp.Shadowtrader.EndFort"))
				{
					dialog.text = "Ho già sentito la notizia - stanotte le guardie hanno scoperto un mercato nero di contrabbandieri e li hanno arrestati tutti. Era sotto il controllo di un raro pezzo di feccia, ora è a posto, non potrà fare del male a nessun altro per un po'\nIl comandante mi ha parlato del tuo ruolo in tutto questo, hai la mia gratitudine! Hai mantenuto la tua parola! Ecco, prendi i soldi - 15.000 pesos. Mi hai salvato. Ora non c'è nulla che minaccia la mia attività!";
					link.l1 = "Prego. È stato facile."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Escape") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Allora, ci sono buone notizie, "+pchar.name+"?";
					link.l1 = "Ho trovato il tuo rivale. Non sarà più un fastidio per te - sono riuscito a convincerlo... a lasciare quest'isola. Il suo 'negozio' era in una casa vicino alle porte della città. Spetta a te decidere cosa fare con il carico che è stato abbandonato. Puoi consegnarlo alle autorità o cercare di raccoglierlo per te stesso."; 
					link.l1.go = "Shadowtrader_Escape_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Free") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Ho già sentito la notizia - stanotte le guardie hanno scoperto un covo di contrabbandieri sotto una delle case. Due furfanti trovati morti. Ottimo lavoro, "+pchar.name+", Ti ammiro! Ecco, prendi la ricompensa - 15 000 pesos. Mi hai appena salvato! Ora farò commercio sul serio!\nSoddisfa la mia curiosità - il loro capo... è anche tra i due morti?";
					link.l1 = "No. Ma non mostrerà mai più il suo volto nella tua città. Credo che dovrebbe essere a diverse dozzine di miglia di distanza da quest'isola, mentre stiamo parlando."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Kill") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "Ho già sentito la notizia - questa notte le guardie hanno scoperto un negozio segreto di contrabbandieri in una delle case. Tre furfanti sono stati trovati morti. Ottimo lavoro, "+pchar.name+", Ti ammiro! Prendi, ecco la tua ricompensa - 15.000 pesos. Mi hai appena salvato! Ora posso commerciare sul serio!\nSoddisfa la mia curiosità - il loro capo... era tra i due morti?";
					link.l1 = "Sì. Ti sei liberato del tuo rivale per sempre. Non ti darà mai più fastidio."; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
			}
			//<-- мини-квест Бесчестный конкурент
		break;
		
		// --> мини-квест Бесчестный конкурент
		case "Shadowtrader_begin":
			pchar.questTemp.Shadowtrader = "true";
			pchar.questTemp.Shadowtrader_block = true;
			pchar.questTemp.Shadowtrader.Guardername = GenerateRandomName_Generator(sti(npchar.nation), "man");
			dialog.text = "Potresti per favore andare alla taverna, trovare un uomo di nome "+pchar.questTemp.Shadowtrader.Guardername+" e digli di venire qui il più presto possibile? Non posso lasciare il negozio e quel testa di legno sta nella taverna, imbottendosi di rum, e sicuramente non penserà nemmeno di venire qui, nonostante sia di turno.";
			link.l1 = "Sono sempre felice di aiutare, amico - tanto più perché stavo proprio pensando di andare alla taverna.";
			link.l1.go = "Shadowtrader_begin_1";
			link.l2 = "Ti stai prendendo gioco di me? Sembro il tuo fattorino? La taverna è a due passi da qui - puoi andarci tu stesso.";
			link.l2.go = "exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
		break;
		
		case "Shadowtrader_begin_1":
			dialog.text = "Grazie! Per favore, ditegli di venire qui subito. Oh mio Dio, perché deve essere così fastidioso...";
			link.l1 = "Non preoccuparti. Lo manderò da te.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.City = npchar.City;
			pchar.questTemp.Shadowtrader.nation = sti(npchar.nation);
			//создаем охранника
			sld = GetCharacter(NPC_GenerateCharacter("ShadowGuarder" , "officer_7", "man", "man", 10, sti(npchar.nation), 5, true, "quest"));
			FantomMakeCoolFighter(sld, 20, 50, 50, "topor_2", "pistol3", "bullet", 50);
			sld.name = pchar.questTemp.Shadowtrader.Guardername;
			sld.lastname = "";
			sld.dialog.FileName = "Quest\LineMiniQuests\ShadowTrader.c";
			sld.dialog.currentnode = "ShadowGuarder";
			sld.greeting = "pirat_common";
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator(pchar.questTemp.Shadowtrader.City + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "sit", "sit_front1");
			SaveCurrentNpcQuestDateParam(npchar, "Shadowtrader_date");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Shadowtrader_fort":
			dialog.text = "Oh, capitano, avrei davvero bisogno del tuo aiuto. Potresti per favore consegnare questa lettera al comandante il prima possibile? Ti pagherei 300 monete per quel piccolo affare - come ho già detto, non posso lasciare il mio negozio.";
			link.l1 = "Nessun problema. Dammi quella lettera.";
			link.l1.go = "Shadowtrader_fort_1";
			link.l2 = "No, buon uomo, non ho più tempo per quelle stronzate.";
			link.l2.go = "Shadowtrader_fort_end";
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_fort_1":
			dialog.text = "Eccoti. Per favore, consegnalo a lui oggi e portami la sua risposta.";
			link.l1 = "Non preoccuparti, lo farò io.";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1"); // 240912
			pchar.questTemp.Shadowtrader.Tradername = GetFullName(npchar);
			SetFunctionTimerCondition("ShadowtraderTimeFort_Over", 0, 0, 1, false);
			pchar.questTemp.Shadowtrader = "current"
			pchar.questTemp.Shadowtrader.Fort = "true";
			AddQuestRecord("Shadowtrader", "1");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
		break;
		
		case "Shadowtrader_fort_end":
			dialog.text = "Ebbene, a quanto pare dovrò chiedere a qualcun altro. Mi dispiace di averti disturbato, capitano.";
			link.l1 = "Nessun problema. Arrivederci!";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader = "true";
			DeleteAttribute(pchar, "questTemp.Shadowtrader_block");
		break;
		
		case "Shadowtrader_trouble":
			dialog.text = "Ecco cosa ha detto? Che prove vuole da me, allora?! Il mio cadavere? Beh, presto ci sarà uno, se continua così!..";
			link.l1 = "Ehi, ehi, "+npchar.name+", calmati, o avrai un colpo. Ecco, bevi un po' d'acqua... Ora dimmi, cosa succede - forse potrei essere in grado di aiutarti?";
			link.l1.go = "Shadowtrader_trouble_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Trouble");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_trouble_1":
			dialog.text = "Oh, capitano! Per favore, prendi i tuoi 300 pesos - quasi me ne ero dimenticato... Certo, ti dirò, ma non sono sicuro di come tu possa aiutarmi. Il mio affare è quasi rovinato - tutto a causa di quei maledetti contrabbandieri e quel bastardo sconosciuto che li guida.";
			link.l1 = "Contrabbandieri?";
			link.l1.go = "Shadowtrader_trouble_2";
			AddMoneyToCharacter(pchar, 300);
		break;
		
		case "Shadowtrader_trouble_2":
			dialog.text = "Ecco! Quei furfanti hanno chiaramente deciso di cacciarmi dalla città! Fino ad allora tutto era come al solito - rivendevano oggetti proibiti, e quando le pattuglie li prendevano, si nascondevano o li corrompevano. Ma di recente hanno aperto da qualche parte in una bottega di un vicolo e hanno iniziato a vendere le merci più popolari a prezzi incredibilmente bassi!\nNon posso permettermi quel lusso - infatti devo pagare le tasse - mi sono progressivamente impoverito e i marinai quasi non vogliono più le mie merci - tutte le merci le comprano da questi canaglie.";
			link.l1 = "Ma avresti dovuto rivolgerti alle autorità! Dopotutto, è il loro lavoro - fermare tale illegalità.";
			link.l1.go = "Shadowtrader_trouble_3";
		break;
		
		case "Shadowtrader_trouble_3":
			dialog.text = "Hai visto l'ultimo risultato d'appello con i tuoi occhi. Il governatore è troppo impegnato e il comandante non crede che i contrabbandieri abbiano organizzato negozi dietro le quinte, o finge di non crederci - e, suppongo, è questo il caso \nNaturalmente, perché dovrebbero farlo? E io dico: Sono sicuro che qualche furfante malandrino che vuole distruggere ed espellermi dalla città ha architettato tutto, e poi si occuperà tranquillamente del mio affare per pulire le loro piccole mani sporche.";
			link.l1 = "Ehm... la tua opinione non è infondata. È nella natura dei commercianti - fare un gatto e topo con qualcuno... Oh, mi dispiace, naturalmente non mi riferivo a te. ";
			link.l1.go = "Shadowtrader_trouble_4";
		break;
		
		case "Shadowtrader_trouble_4":
			dialog.text = "Oh, niente... E recentemente è venuto da me qualche scavezzacollo e ha detto sfacciatamente che se avessi continuato a fare rumore, avrebbero bruciato il mio negozio\nCosì ho assunto una guardia del corpo. "+pchar.questTemp.Shadowtrader.Guardername+" non viene a buon mercato, ma è un professionista e sotto la sua protezione posso sentirmi un po' più calmo.";
			link.l1 = "Capisco... Una storia spiacevole, davvero. A quanto pare, avevi ragione - non c'è nulla che io possa fare per te. Ma ancora, sono certo che le cose si sistemeranno da sole - tali loschi stabilimenti di solito non durano a lungo. Beh, buona fortuna!";
			link.l1.go = "Shadowtrader_end";
			link.l2 = "Capisco. Beh, forse potrei ancora essere in grado di aiutarti...";
			link.l2.go = "Shadowtrader_trouble_5";
		break;
		
		case "Shadowtrader_trouble_5":
			dialog.text = "Mi stai offrendo comunque il tuo aiuto? Ma cosa hai intenzione di fare?";
			link.l1 = "Cercherò di trovare quel tuo 'collega' e... persuaderlo a smettere di infastidirti. Sai, ho certe abilità nel persuadere le persone.";
			link.l1.go = "Shadowtrader_trouble_6";
		break;
		
		case "Shadowtrader_trouble_6":
			dialog.text = "Sei serio? Che il Signore benedica la tua giusta causa! Se mi libererai da quella sporcizia, sarò in debito con te.";
			link.l1 = "Bene, consideralo un affare. Inizierò a cercare, allora.";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.seeksmugglers = "true";
			AddLandQuestMark(characterFromId("BasTer_Smuggler"), "questmarkmain");
			AddQuestRecord("Shadowtrader", "2");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			AddQuestUserData("Shadowtrader", "sSex1", GetSexPhrase("ся","ась"));
		break;
		
		case "Shadowtrader_end":
			pchar.questTemp.Shadowtrader = "true";
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_block");
			DialogExit();
		break;
		
		case "Shadowtrader_Escape_complete":
			dialog.text = "È vero? Posso ora fare affari senza alcuna paura? Oh, grazie mille! Ecco la tua ricompensa - 15000 pesos. Per quanto riguarda la merce nella loro casa, penso che sia meglio consegnarla al comandante. Grazie ancora!";
			link.l1 = "Prego. Non è stato troppo difficile. Ti ho detto che sono bravo a persuadere.";
			link.l1.go = "Shadowtrader_complete";
		break;
		
		case "Shadowtrader_complete":
			dialog.text = "Vieni a trovarmi di nuovo, capitano - Sarò sempre felice di vederti.";
			link.l1 = "Certo! E ora mi permetta di prendere congedo - ho cose da fare! Arrivederci e buona fortuna nel tuo commercio, "+npchar.name+"!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.End");
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.Shadowtrader = "complete";
			AddQuestRecord("Shadowtrader", "11");
			AddQuestUserData("Shadowtrader", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_block");
			DeleteAttribute(pchar, "questTemp.Shadowtrader.EndFort");
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
		break;
		//<-- мини-квест Бесчестный конкурент
	}
	UnloadSegment(NPChar.FileDialog2);
}
