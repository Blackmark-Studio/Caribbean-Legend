// Лукас Роденбург - вице-директор ГВИК
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl"))
			{
				dialog.text = "Parla, ragazzo, ma fa' in fretta. Ho il diavolo alle calcagna.";
				link.l1 = "Ho sentito dire che state reclutando capitani.";
				link.l1.go = "Holl_start";	
			break;
			}
			dialog.text = "Hai qualche faccenda per me?";
			link.l1 = "No, mi dispiace. Me ne vado.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Second_time":
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.questTemp.HWIC.Holl == "BaltazarEsc")
			{
				dialog.text = "Dovevi già essere a metà strada per Sint Maarten, kapitein.";
				link.l1 = "Mi preparo a salpare, mynheer.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "BaltazarCom")
			{
				dialog.text = "Ah, capitano, eccovi! Non vi avevo scorto arrivare, ho appena finito di leggere la lettera di Ridderbrock. Avete lasciato un’impressione notevole. Vi chiama il ‘guardiano dei mercanti e flagello dei pirati. Un dono del Cielo alla Compagnia!’ Che ne dite, voi, di simili parole?";
				link.l1 = "Preferirei restare solo un capitano qualunque. Un capitano qualunque, ma ricco.";
				link.l1.go = "SantiagoTrip";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripBegin")
			{
				dialog.text = "Perché sei ancora qui e non già in rotta per Cuba?!";
				link.l1 = "Sì, sì, sto arrivando, mynheer.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripFinal")
			{
				sld = characterFromId("Santiago_usurer");
				dialog.text = "Ah, capitano! Devo confessare che cominciavo a inquietarmi. Com’è andata?";
				link.l1 = "Non è stato senza impicci, ma te ne parlerò più tardi. Prima gli affari. Signore "+GetFullName(sld)+" mi ha ordinato di riferirti quanto segue: 'quest'uomo deve crepare'. Allora Geraldi considererà la faccenda chiusa. Ha aggiunto che questa scelta è volontà della loro stirpe.";
				link.l1.go = "SantiagoTrip_8";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripComplete")
			{
				dialog.text = "Felice di vederti, kapitein! Son lieto che tu sia venuto a trovarmi.";
				link.l1 = "Buon giorno, signor mio. Immagino che abbiate un altro incarico della Compagnia per me?";
				link.l1.go = "JacobBerg";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "JacobTakeShip")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED)
				{
					dialog.text = "Ti ho ordinato di ormeggiare la tua nave. Sei forse troppo stupido o ignorante per eseguire ordini semplici?";
					link.l1 = "Nessuna delle due, signore. Sono solo di passaggio.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Dunque, hai ormeggiato la tua nave. Ora ti presterò il mio sciabecco. Sei pronto a partire subito per questa missione? La mia nave è ben armata e pronta a mollare gli ormeggi, non resta che salpare, perbacco.";
					link.l1 = "Sì, certamente. Sono pronto, signor Rodenburg.";
					link.l1.go = "JacobBerg_6";
					DelLandQuestMark(npchar);
				}
			break;
			}
			if (pchar.questTemp.HWIC.Holl == "JacobLongway")
			{
				dialog.text = "Che ci fai ancora qui? Va’ subito da Longway.";
				link.l1 = "Scusate, sono già in viaggio.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MirageTake")//а вот теперь начинается дурдом с перебором кораблей
			{
				int iMir = 0;
				int iMef = 0;
				for(i = 0; i < COMPANION_MAX; i++)
				{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE) iMir = 1;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG) iMef = 1;
				}
				}//установили признак наличия кораблей в эскадре.
				RemoveItems(PChar, "JacobJournal", 1);//удалим журнал ван Берга
				pchar.quest.MirageConvoyOver.over = "yes"; //снять таймер
				if (iMir == 1 && iMef == 0)//потеряли Мейфенг
				{
					dialog.text = "Kapitein... Sono già al corrente del vostro viaggio.";
					link.l1 = "Ah, davvero? Allora dovresti già sapere che...";
					link.l1.go = "Jacob_lostMef";
					DelLandQuestMark(npchar);
					break;
				}
				if (iMir == 0 && iMef == 1)//потеряли Мираж
				{
					dialog.text = "Kapitein... Sono già al corrente del vostro viaggio.";
					link.l1 = "Ah sì? Allora dovrai ben sapere che...";
					link.l1.go = "Jacob_lostMir";
					DelLandQuestMark(npchar);
					break;
				}
				if (iMir == 0 && iMef == 0)//а это вообще плохо
				{
					dialog.text = "Kapitein... Sono già al corrente del tuo viaggio.";
					link.l1 = "Ah davvero? Allora dovresti già sapere che...";
					link.l1.go = "Jacob_failFull";
					DelLandQuestMark(npchar);
					break;
				}
					dialog.text = "Eccoti qua, Kapitein... So già tutto sul tuo viaggio.";
					link.l1 = "Ah, davvero? Allora dovresti sapere che...";
			link.l1.go = "Jacob_complete";
			DelLandQuestMark(npchar);
			break;
			}
			if (pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Vai ad Antigua. Subito.";
				link.l1 = "Scusami, sto già andando.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "FleetwoodSink" || pchar.questTemp.HWIC.Holl == "FleetwoodCapture")
			{//опять начинаем проверять корабли
				iMir = 0;
				for(i = 0; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE) iMir = 1;
					}
				}//установили признак наличия Миража в эскадре.
				pchar.quest.ToAntiguaOver.over = "yes"; //снять таймер
				if (iMir == 0)//потеряли Мираж
				{
					dialog.text = "Mi hanno avvisato del vostro arrivo, kapitein. So anche che avete perso la mia Mirage in combattimento.";
					link.l1 = "Siete ben informato, signor Rodenburg. Nonostante tutti i miei sforzi, non siamo riusciti a salvarla.";
					link.l1.go = "Fleetwood_fail";
					DelLandQuestMark(npchar);
				}
				else
				{
					dialog.text = "Mi hanno avvisato del vostro arrivo, kapitein. Vedo che la Mirage è attraccata sana e salva. Bene così.";
					link.l1 = "Ho solo seguito i vostri ordini, mynheer. Mi avete comandato di far fuori Fleetwood e adesso è all'altro mondo. Mi avete detto di riportare la Mirage al porto locale ed eccola qua.";
					link.l1.go = "Fleetwood_complete";
					DelLandQuestMark(npchar);
				}
				pchar.quest.Meifeng_fail.over = "yes";
				Group_DeleteGroup("Meifeng_Empty");
				sld = characterFromId("MeifengCap");
				sld.lifeday = 0;//зачистим Мейфенг без китайца
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "Abby_prepare")
			{
				dialog.text = "Ah, eccoti. Bene vederti. Ho un altro incarico per te, proprio come promesso.";
				link.l1 = "Ascolto, signor mio.";
				link.l1.go = "Abby";
				DelLandQuestMark(npchar);
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.HWIC.Holl.LucasMoney") && pchar.questTemp.HWIC.Holl == "AbbyAgreeMarried")
			{
				dialog.text = "Ah, sono lieto di vederti, figliolo. Hai tardato e cominciavo a preoccuparmi. Sei riuscito a cavar fuori qualcosa da Abigail?";
				link.l1 = "Non solo ho risolto anche gli altri tuoi impicci. Ho trovato l'isola e il tesoro perduto di Shneur. Salomone è felice e Abigail accetterà la tua proposta. Congratulazioni, signor mio!";
				link.l1.go = "Abby_2";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "NotFindAbbyIsland")
			{
				dialog.text = "Ah, son lieto di vederti, amico mio. Sei riuscito a cavare qualcosa da Abigail?";
				link.l1 = "Sì. Ho parlato con Abigail e suo padre. C'è un grattacapo, signore: suo padre ha perso tutta la fortuna. Abigail si sente indegna di te, teme le malelingue e i bisbigli se una fanciulla senza dote sposasse un gentiluomo come te. Spero che tu capisca.";
				link.l1.go = "Abby_6";
				DelLandQuestMark(npchar);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LucasMoney") && pchar.questTemp.HWIC.Holl == "AbbyAgreeMarried")
			{
				dialog.text = "Ah, amico mio! Spero che tu abbia portato notizie gradite?";
				link.l1 = "Il tuo piano ha funzionato. Abigail accetterà. Congratulazioni, signor mio.";
				link.l1.go = "Abby_8";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MerdokStart")
			{
				dialog.text = "Ti stavo aspettando. Ragazzo mio, ti sei cacciato in un brutto guaio.";
				link.l1 = "Cosa vuoi dire?";
				link.l1.go = "Merdok";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MerdokDie")
			{
				dialog.text = "I miei uomini al molo mi hanno avvisato del tuo arrivo. Johan van Merden è morto?";
				link.l1 = "Sì. Lui e il suo compare sono spariti. È stata una bella scaramuccia, ma l’ho portata a termine.";
				link.l1.go = "Merdok_4";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Non abbiamo più nulla da dirci, kapitein.";
			link.l1 = "Capito, me ne vado.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "Che c’è? Il tempo è oro.";
		link.l1 = "Scusate, me ne vado.";
		link.l1.go = "exit";
		break;
		
//------------------------------------------------1 задание--------------------------------------------
		case "Holl_start":
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Bridgetown_tavernkeeper"));
			DelLandQuestMark(characterFromId("Knippel"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			dialog.text = "Forse. Chi sei tu? Parla in fretta, il tempo è denaro.";
			link.l1 = "Sono il capitano "+pchar.name+", la mia nave e  possono tornarti utili.";
			link.l1.go = "Holl_start_0";			
		break;
		
		case "Holl_start_0":
			dialog.text = "Hm, una lega sconosciuta da saggiar nel crogiolo.";
			link.l1 = "Ecco perché son qui, signor mio.";
			link.l1.go = "Holl_start_1";			
		break;
		
		case "Holl_start_1":
			pchar.questTemp.HWIC.Holl.PirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "Benissimo, vedremo di che pasta sei fatto. D’accordo Kapetein, qualunque sia il tuo nome, conosci Balthazar Ridderbrock? No? Che fortuna. Avari, brontoloni e teste calde come lui sono merce rara.\nMa a quanto pare tutte queste splendide qualità non gli bastavano, così è stato abbastanza sveglio, il bastardo, da offendere un filibustiere di nome "+GetName(NAMETYPE_ORIG,pchar.questTemp.HWIC.Holl.PirateName,NAME_NOM)+"   nella taverna locale e ha chiamato la guardia appena la parte offesa ha sfiorato l’elsa della spada...";
			link.l1 = "...e han fatto penzolar quel pirata alla prima cima libera?";
			link.l1.go = "Holl_start_2";			
		break;
		
		case "Holl_start_2":
			dialog.text = "Non è così semplice. "+GetName(NAMETYPE_ORIG,pchar.questTemp.HWIC.Holl.PirateName,NAME_NOM)+" non è un pirata qualunque, ma un corsaro olandese, un veterano delle ultime due guerre contro gli inglesi. I contribuenti locali gli vogliono un gran bene. Non posso dire lo stesso di Ridderbrock.";
			link.l1 = "Dunque il nostro corsaro respira ancora?";
			link.l1.go = "Holl_start_3";			
		break;
		
		case "Holl_start_3":
			dialog.text = "Sì, ma è davvero furibondo. Ecco perché Ridderbrock se la fa sotto dalla paura.";
			link.l1 = "Suppongo che la mia buona sorte stia per finire. Quando incontrerò il signor Ridderbrock?";
			link.l1.go = "Holl_start_4";			
		break;
		
		case "Holl_start_4":
			dialog.text = "Imminentemente. La brava gente di Philipsburg attende con ansia una spedizione di zucchero, quella che il nostro comune conoscente Ridderbrock ha promesso di recapitare. Non ritengo quell’uomo degno neppure della suola dei suoi stivali, ma ahimè, lavora per noi. Dunque, va’ subito all’ufficio del porto. Trova lì Ridderbrock e digli che gli ho ordinato di mollare gli ormeggi all’istante.\nLo seguirai nell’ombra e... lo scorterai a Philipsburg sano e salvo. Non voglio "+GetName(NAMETYPE_ORIG,pchar.questTemp.HWIC.Holl.PirateName,NAME_NOM)+"   mandare la reputazione della Compagnia a fondo nei Caraibi insieme al suo carico.";
			link.l1 = "Ugh, una scorta. E il compenso per questo... incarico da quattro soldi?";
			link.l1.go = "Holl_start_5";			
		break;
		
		case "Holl_start_5":
			dialog.text = "Capitano, prima finisci il lavoro. Balthazar ti pagherà appena avrà raggiunto la sua destinazione. A Philipsburg! Non in pasto ai pesci! Poi torna a riferire, una volta fatto. Se te la cavi, potrai contare sul mio appoggio – e su quello della Compagnia. Ora puoi andare.";
			link.l1 = "Arrivederci, signor mio.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Create_Baltazar");
			pchar.questTemp.HWIC.Holl = "BaltazarEsc";
			NextDiag.TempNode = "Second_time";
			pchar.quest.HWIC_ReturnOfficer.over = "yes";//чтобы офицер не доставал
			pchar.questTemp.HWIC.CanTake.Holl = "true";//признак, что голландка уже бралась
		break;
		
//----------------------------------------------задание 1а--------------------------------------------	
		case "SantiagoTrip":
			dialog.text = "Sì, Ridderbrock è un cane avaro, persino per un olandese. Ma chi se ne frega, non m’importa più nulla di lui. Parliamo piuttosto di te, Kapitein Come-Diavolo-Ti-Chiami. Mi piace il tuo modo di fare, quindi ti propongo un altro lavoretto. Stavolta pago io di tasca mia.";
			link.l1 = "Ascolto, signor mio.";
			link.l1.go = "SantiagoTrip_1";			
			AddSimpleRumourCity("Ah, so you are the brave kapitein who escorted that scoundrel Ridderbrock? We heard all about about it... He paid you only five thousand pesos! He's been boasting about it nonstop at the tavern in Philipsburg drunk as a swine. If I were you captain, I drag him out into the street and thrash him.", "Villemstad", 20, 3, "");//слух по 1 заданию
		break;
		
		case "SantiagoTrip_1":
			dialog.text = "Mi serve un uomo per una faccenda di gran peso. Te la sei cavata con la questione Ridderbrock, perciò la Compagnia ritiene ch’io possa affidarti quest’incarico.";
			link.l1 = "Suppongo di dover sentirmi onorato. Che succede?";
			link.l1.go = "SantiagoTrip_2";
		break;
		
		case "SantiagoTrip_2":
			sld = characterFromId("Santiago_usurer");
			dialog.text = "Non posso darti dettagli precisi, ma sappi che non è un affare mio: riguarda la Compagnia. Un’occasione per ingraziarti il nostro favore, che ti assicuro è assai redditizio.\nSalpa per Santiago a Cuba e consegna questo pacco a Don "+GetFullName(sld)+" Ha un posto importante nella banca di Geraldi ed è anche il mio... il nostro socio d’affari. Devi consegnargli quest’oro che ti darò subito. Mi fido della tua onestà, kapitein. O, almeno, del tuo istinto di sopravvivenza. La Compagnia trova sempre chi cerca di fregarla.";
			link.l1 = "Dubiti di me, signor mio?";
			link.l1.go = "SantiagoTrip_3";
		break;
		
		case "SantiagoTrip_3":
			if (pchar.BaseNation == ENGLAND || pchar.BaseNation == FRANCE) sTemp = " I am also giving you this short-term Company trade license in order to spare you from any diplomatic entanglements with the Spanish. This will allow you to dock at Spanish colonies for some time.";
			else sTemp = "";
			dialog.text = "In questo momento, non metto in dubbio la tua parola. Fidati, non mi sognerei nemmeno di discutere di questa faccenda con te, se avessi dei dubbi. Sappi che abbiamo perso un sacco di tempo per sistemare questo affare: hai solo quindici giorni per consegnare."+sTemp+"\nIl mio messaggio e il pacco devono arrivare in tempo. È vitale, ragazzo. Sbrigati, ma fa’ attenzione, questa non sarà una passeggiata.";
			link.l1 = "Altro ancora? Perché mi metti in guardia, signor Rodenburg?";
			link.l1.go = "SantiagoTrip_4";
		break;
		
		case "SantiagoTrip_4":
			if (pchar.BaseNation == ENGLAND || pchar.BaseNation == FRANCE) GiveNationLicence(HOLLAND, 20);
			dialog.text = "Diciamo solo che ho i miei sospetti. Non preoccuparti, se te la caverai veloce come l’ultima volta, potresti diventare un uomo di fiducia per gli affari più delicati della Compagnia.";
			link.l1 = "Tutto quello che devo fare è consegnare questa lettera e il denaro al banchiere di Santiago entro quindici giorni? Non sembra poi così difficile, almeno in apparenza.";
			link.l1.go = "SantiagoTrip_5";
		break;
		
		case "SantiagoTrip_5":
			dialog.text = "Non così in fretta, ragazzo... Mi pare che tu non abbia davvero colto la gravità della faccenda. Se porti a termine questo lavoretto, mi renderai molto riconoscente. Ma se fallisci, finirai per farmi imbestialire. E allora ti piscerò addosso, chiaro, kapitein? "+GetFullName(pchar)+"?";
			link.l1 = "Messaggio ricevuto. Hai la mia parola. Farò del mio meglio per mantenerti di buon umore.";
			link.l1.go = "SantiagoTrip_6";
		break;
		
		case "SantiagoTrip_6":
			dialog.text = "Benissimo. Ora prendi la lettera, questi forzieri e rammenta patto e condizioni. E un’ultima cosa: stattene lontano dai guai a Santiago.";
			link.l1 = "Molto bene.";
			link.l1.go = "SantiagoTrip_7";
		break;
		
		case "SantiagoTrip_7":
			DialogExit();
			GiveItem2Character(pchar, "NPC_Letter");
			ChangeItemDescribe("NPC_Letter", "itmdescr_NPC_Letter4");
			TakeNItems(pchar, "chest", 5); 
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("SantiagoTripOver", 0, 0, 32, false);
			}
			else SetFunctionTimerCondition("SantiagoTripOver", 0, 0, 16, false); //таймер
			AddQuestRecord("Holl_Gambit", "1-43");
			pchar.questTemp.HWIC.Holl = "SantiagoTripBegin";
			AddMapQuestMarkCity("Santiago", true);
			AddLandQuestMark(characterFromId("Santiago_usurer"), "questmarkmain");
		break;
		
		case "SantiagoTrip_8":
			dialog.text = "«Deve morire»... così, senza tanti complimenti. Non me l’aspettavo proprio. Mh. Hai svolto il tuo compito egregiamente, kapitein. Ora raccontami tutto, voglio il resoconto.";
			link.l1 = "Niente di che... una passeggiata da marinaretto.";
			link.l1.go = "SantiagoTrip_9";
			link.l2 = "Sono stato stordito e rapito da un uomo a Santiago. Era fin troppo curioso riguardo ai tuoi affari con Geraldi. Sono riuscito a scappare, ma prima ho dovuto mandarlo all’altro mondo. L’unico indizio che mi ha lasciato è il nome di un certo Gaston. Non ho la minima idea di cosa significhi tutto ciò.";
			link.l2.go = "SantiagoTrip_10";
			link.l3 = "Sono stato stordito e rapito da un tizio a Santiago. Sembrava ficcare il naso nei tuoi affari con Geraldi. Sono riuscito a scappare, ma prima ho dovuto spedirlo all'altro mondo. Non sono riuscito a cavargli nulla prima di mandarlo al diavolo.";
			link.l3.go = "SantiagoTrip_11";
		break;
		
		case "SantiagoTrip_9":
			dialog.text = "La riconoscenza della Compagnia non si limita alle belle parole. Prendi la tua ricompensa, te la sei guadagnata.";
			link.l1 = "Lavorare per la Compagnia rende davvero bene.";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_10":
			dialog.text = "Cosa! Rapimento... Ma aspetta... Gaston! Capisco... Credo. Ahimè, figliolo, sei rimasto invischiato in una brutta faccenda. Navighiamo in acque sconosciute, vedremo come va a finire. Mi fa piacere che tu l’abbia scampata.\nParliamo di cose più liete – prendi questa ricompensa, te la sei guadagnata.";
			link.l1 = "Lavorare per la Compagnia rende un bel gruzzolo";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_11":
			dialog.text = "Fandonie! Rapirti... ho però qualche sospetto. Se continuerai a lavorare per me, scoprirai di più. Hai avuto fortuna, e mi rallegra che tu sia vivo.\nParliamo ora di cose più piacevoli: accetta questa ricompensa, te la sei guadagnata.";
			link.l1 = "Lavorare per la Compagnia rende assai bene";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_12":
			AddMoneyToCharacter(pchar, 25000);
			dialog.text = "Esattamente, ragazzo mio! Potresti diventare un agente ben pagato della Compagnia, se continueremo a collaborare. Ora va', riposati dal tuo viaggio. Hai soddisfatto le mie aspettative. Ti sarei davvero riconoscente se tornassi tra una settimana, abbiamo ancora un mare di lavoro da sbrigare.";
			link.l1 = "Potete contar su di me, signor Rodenburg.";
			link.l1.go = "SantiagoTrip_13";
		break;
		
		case "SantiagoTrip_13":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "true";
			AddQuestRecord("Holl_Gambit", "1-46");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 80);
			AddSimpleRumourCity("My brother at the Company says that Mynheer Rodenburg is quite pleased by your performance, kapitein. Don't lose your chance, Lucas rarely shows such favor.", "Villemstad", 10, 3, "");
			SetTimerFunction("GollandGambit_2_ZadanieStart", 0, 0, 7);
		break;
		
//-----------------------------------------------2 задание--------------------------------------------
		case "JacobBerg":
			dialog.text = "Sei sveglio, capitano. Proprio così. Bene, parliamo dei particolari della missione che ci aspetta...";
			link.l1 = "Sono tutt’orecchi.";
			link.l1.go = "JacobBerg_1";			
		break;
		
		case "JacobBerg_1":
			dialog.text = "Ho una missione di massima importanza per te, ragazzo, e pretendo che tu segua alla lettera ogni mia istruzione. Come ben sai, i rapporti tra le Province Unite e l’Inghilterra sono... tutt’altro che amichevoli. Gli inglesi si son messi in testa di dover comandare il mondo intero. Peccato che non tutti siano d’accordo con queste fandonie. Ovunque cerchino di far affari, puoi star sicuro che la Compagnia Olandese delle Indie Occidentali ci sia arrivata prima di loro.\nNoi olandesi abbiamo la flotta mercantile più vasta del globo, e le nostre squadre armate difendono gli interessi della Repubblica qui e altrove. Gli inglesi ci rodono d’invidia per la nostra potenza commerciale e fanno di tutto per mettere i bastoni tra le ruote alla Compagnia. Ora, c’è un certo capitano di marina inglese, tale Richard Fleetwood. Pur essendo ufficiale della Commonwealth, si comporta da pirata. Attacca e depreda qualunque vascello osi batter bandiera olandese nei Caraibi. Dice che è una contromossa contro la ‘nave fantasma’ che affonda i mercantili inglesi. Sostiene che questa ‘nave fantasma’ sia un corsaro con una lettera di corsa olandese.\nHai sentito parlare di questa ‘nave fantasma’, kapitein?";
			link.l1 = "Queste fandonie le senti in ogni taverna. Basta offrire un po' di rum a un vecchio nostromo e ti racconterà qualsiasi storia desideri...";
			link.l1.go = "JacobBerg_2";
		break;
		
		case "JacobBerg_2":
			dialog.text = "Questa faccenda non è un delirio da ubriacone. Ho indagato sulle imprese di questa ‘nave fantasma’. Ho scoperto che si tratta di un normale bastimento, di legno e tela, con uomini in carne ed ossa a bordo, una ketch chiamata ‘Mirage’. Al comando c’è un certo Jacob van Berg, che la spaccia per la leggendaria ‘Olandese Volante’.";
			link.l1 = "Van Berg? Un cognome olandese. Un vero 'Olandese Volante', eh?";
			link.l1.go = "JacobBerg_3";
		break;
		
		case "JacobBerg_3":
			dialog.text = "Esatto. Jacob van Berg è un olandese, viene da Leiden. Ma la Repubblica l'ha già condannato alla forca molto tempo fa. È un ricercato, un bucaniere che pensa solo al proprio tornaconto. Richard Fleetwood gli dà la caccia. E useremo questo contro quel presuntuoso inglese.\nPreferirei non far fuori Fleetwood subito, anche se se lo merita da una vita. La morte sarebbe troppo poco per lui. Voglio non solo togliergli la vita, ma anche infangare il suo nome e il suo onore. È questo che desidero. E così anche gli altri porci inglesi impareranno la lezione.\nParliamo di dettagli.";
			link.l1 = "Mynheer, questa faccenda comincia a puzzare di qualcosa di personale...";
			link.l1.go = "JacobBerg_4";
		break;
		
		case "JacobBerg_4":
			dialog.text = "Non ti riguarda affatto. Tu esegui gli ordini, poi ti pagherò. Grazie al mio informatore, ho scoperto dove si nasconde Jacob van Berg con la sua 'Mirage'. Opera da una città sul litorale meridionale della Spagna. Vai da lui, scopri dove ha ormeggiato la sua nave fantasma.\nPoi ammazzalo, trova la sua 'Mirage', prendila come bottino e riportala qui. Devi catturare la 'Mirage', non ti venga in mente di affondarla.";
			link.l1 = "Sembra abbastanza semplice. Dove dovrei cercare van Berg?";
			link.l1.go = "JacobBerg_5";
		break;
		
		case "JacobBerg_5":
			dialog.text = "Tutti i dettagli ti saranno forniti dal mio uomo. Si chiama Longway, un cinese. Ti affido la mia nave personale per questa missione, lo xebec 'Meifeng'. Longway ne è il capitano, ma seguirà i tuoi ordini. \nVai all’ufficio portuale locale e ormeggia tutte le tue navi lì. Torna da me quando avrai finito.";
			link.l1 = "Va bene, andrò a trovare il capitano del porto. Non ti farò attendere troppo a lungo.";
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Holl = "JacobTakeShip";
			AddLandQuestMark(characterFromId("Villemstad_portman"), "questmarkmain");
		break;
		
		case "JacobBerg_6":
			dialog.text = "Longway ti aspetta fuori. Ti mostrerà la tua nuova nave e ti passerà qualche dritta sulla posizione di van Berg. In bocca al lupo, kapitein, e non farmi fare la figura dello scemo. Ricorda che devi riportarmi la 'Meifeng', quindi cerca di non mandarla a fondo mentre prendi la 'Mirage'.";
			link.l1 = "In arrivo!";
			link.l1.go = "JacobBerg_7";	
		break;
		
		case "JacobBerg_7":
			DialogExit();
			pchar.quest.Create_Longway.win_condition.l1 = "location";
			pchar.quest.Create_Longway.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Create_Longway.function = "Create_Longway";
			pchar.questTemp.HWIC.Holl = "JacobLongway";
			AddQuestRecord("Holl_Gambit", "1-7");
			pchar.questTemp.HWIC.TakeQuestShip = "true";//все ПУ недоступны для стоянки до поры, также корабль нельзя продать
			pchar.questTemp.HWIC.HollEquip = "true";//форма солдат
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
		break;
		
		//дурдом продолжается
		case "Jacob_lostMir":
			dialog.text = "Incapace imbecille. Hai fallito la tua missione di catturare la nave pirata. Tutti i miei piani sono andati in malora. Ti tolgo 'Meifeng'. Sparisci, non abbiamo più bisogno di te.";
			link.l1 = "Mi dispiace. Addio, signor Rodenburg.";
			link.l1.go = "Jacob_RemoveShip";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MAYFANG;
		break;
		
		case "Jacob_lostMef":
			dialog.text = "Sei un idiota senza cervello. Hai perso la 'Meifeng'. Questo è inammissibile... Mi prendo la 'Mirage' e trattengo il tuo compenso per ripagare la mia perdita. Fuori dai piedi, non abbiamo più bisogno di te.";
			link.l1 = "Mi dispiace. Addio, signor Rodenburg.";
			link.l1.go = "Jacob_RemoveShip";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MIRAGE;
		break;
		
		case "Jacob_failFull":
			dialog.text = "Dio mio, sei davvero un caso raro. Un incapace e pure uno scimunito. Hai fallito nel catturare la Mirage e hai perso pure la Meifeng. Fuori dai piedi dal mio ufficio, dannato imbecille!";
			link.l1 = "Me ne vado.";
			link.l1.go = "exit";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Longway");
			AddDialogExitQuestFunction("LandEnc_OfficerFired");//Лонгвэя из офицеров
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Detector = "holl_fail";
		break;
		
		case "Jacob_complete":
			dialog.text = "Ben fatto. La voce del tuo successo è già giunta alle mie orecchie. Van Berg è morto e hai catturato la sua nave. Il tuo compenso è di 50.000 pesos, prendili.\nRiprendo la 'Meifeng' da te. Ora è tempo che tu prenda il comando della 'Mirage', avrà un ruolo cruciale nella prossima fase. Sei pronto?";
			link.l1 = "Sì, signor Rodenburg.";
			link.l1.go = "Fleetwood";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MAYFANG;
			AddDialogExitQuestFunction("Jacob_RemoveShip");	
			AddSimpleRumourCity("They say that you are on special assignment for Mynheer Rodenburg himself. Something about sending those English to the bottom of the sea. It seems that you are a man on the rise, kapitein.", "Villemstad", 15, 3, "");
		break;
		
		case "Jacob_RemoveShip":
			DialogExit();
			AddDialogExitQuestFunction("Jacob_RemoveShip");	
			sld = characterFromId("Longway");
			sld.lifeday = 0;
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Detector = "holl_fail";
			AddSimpleRumourCity("They say that you have failed Mynheer Rodenburg himself. Good luck, you'll need it.", "Villemstad", 20, 3, "");
		break;
		
//----------------------------------------------3 задание-------------------------------------------------
		
		case "Fleetwood":
			AddMoneyToCharacter(pchar, 50000);
			dialog.text = "Adesso ci occupiamo di Fleetwood. Lo attirerai fuori usando il 'vascello fantasma' Mirage, che lui insegue con tanto ardore. Prepara un trabocchetto vicino a Dominica, il Mirage farà da esca.\nPer prima cosa, fai sapere a Fleetwood che il Mirage è stato avvistato non lontano da Dominica. Il nostro valoroso inglese mollerà tutto e si precipiterà subito a Dominica a caccia della sua preda. Non parlare con Fleetwood direttamente, o non ne uscirai vivo. Trova la farmacia a St. John's. L'apotecario John Murdock è un vecchio compare mio.\nDigli che agisci per mio ordine e lui ti aiuterà a trovare orecchie locali pronte a riempirsi di succose fandonie sul 'vascello fantasma' che assalta i mercanti inglesi intorno a Dominica.";
			link.l1 = "Posso farlo. L'obiettivo è tendere un agguato a Fleetwood a Dominica, dico bene?";
			link.l1.go = "Fleetwood_1";
		break;
		
		case "Fleetwood_1":
			dialog.text = "Esatto. Longway e 'Meifeng' ti aspetteranno vicino a Dominica. Voi due potrete facilmente acciuffare quel cane inglese. Salite a bordo della sua nave e frugate nella sua cabina. Voglio il suo diario di bordo. Ti pagherò extra per quello.\nMa la tua priorità è far fuori quel bastardo di Fleetwood, quindi se abbordarlo non è fattibile - mandalo a fondo. Soprattutto, devi preservare la 'Mirage' a qualunque costo. La sua parte nel prossimo atto del piano è cruciale.";
			link.l1 = "Capisco.";
			link.l1.go = "Fleetwood_2";
		break;
		
		case "Fleetwood_2":
			dialog.text = "Un consiglio, kapitein. Non gettare l’ancora a St. John’s. Sbarca in una delle baie dell’isola e raggiungi la città passando per la giungla, altrimenti John non vorrà parlare con te. Se attiri troppo l’attenzione, farà finta di non conoscerti. Stai attento anche in mare – la 'Mirage' è temuta nelle colonie inglesi, quindi evita le loro navi da guerra e i porti se non vuoi che una muta di lupi di mare ti dia la caccia. Questo è tutto. Che Dio ti accompagni.";
			link.l1 = "Aye aye.";
			link.l1.go = "Fleetwood_3";
		break;
		
		case "Fleetwood_3":
			DialogExit();	
			pchar.questTemp.HWIC.Holl = "toAntigua";
			AddQuestRecord("Holl_Gambit", "1-15");
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			SetFunctionTimerCondition("ToAntiguaOver", 0, 0, 60, false); //таймер 2 месяца
			AddMapQuestMarkShore("Shore1", false);
			AddMapQuestMarkShore("Shore2", false);
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Fleetwood_complete":
			if (pchar.questTemp.HWIC.Holl == "FleetwoodSink")//Флитвуд утоп с журналом
			{
				dialog.text = "Sei tornato, kapitein... Hai il diario di bordo di Richard Fleetwood?";
				link.l1 = "Purtroppo no. Non ho fatto in tempo a salire a bordo della sua nave prima che la facesse affondare.";
				link.l1.go = "Fleetwood_complete_1";
				break;
			}
			if (!CheckCharacterItem(pchar, "FleetwoodJournal"))
			{
				dialog.text = "Sei tornato, capitano... Hai il diario di bordo di Richard Fleetwood?";
				link.l1 = "Purtroppo no. Sono riuscito ad abbordare la Valkyrie e a far fuori quell’uomo in duello, ma il suo diario non l’ho trovato. Uno dei suoi mascalzoni ha dato fuoco alla santabarbara e ci sono rimasti soltanto pochi istanti per filarcela con la pelle intatta.";
				link.l1.go = "Fleetwood_complete_1";
				break;
			}
			dialog.text = "Sei tornato, kapitein... Hai il giornale di bordo di Richard Fleetwood?";
			link.l1 = "L'ho fatto. Eccolo qui. Sono riuscito a salire a bordo della Valkyrie, anche se per un pelo. Quel bastardo ha dato fuoco alla santabarbara della sua nave e l'ha fatta saltare in aria. Siamo scappati per un soffio dalla morte.";
			link.l1.go = "Fleetwood_complete_2";
		break;
		
		case "Fleetwood_complete_1":
			AddMoneyToCharacter(pchar, 100000);
			dialog.text = "Che gran peccato, avrebbe risposto a molte delle nostre domande. Ma ormai non ha più importanza. Hai fatto fuori quel cane inglese insolente, e questo è ciò che conta davvero. Ecco la tua ricompensa: 100.000 pesos. Prendo la 'Mirage' da te, restituiremo questa nave all’Inghilterra.";
			link.l1 = "Che diavolo?! È una splendida nave, volevo tenermela!";
			link.l1.go = "Fleetwood_complete_3";
		break;
		
		case "Fleetwood_complete_2":
			AddMoneyToCharacter(pchar, 150000);
			RemoveItems(PChar, "FleetwoodJournal", 1);
			dialog.text = "Eccellente! Sei davvero un uomo capace. Se tutti i nostri capitani fossero come te, la Repubblica Olandese sarebbe al primo posto fra le grandi potenze marittime della storia. Ecco la tua ricompensa: 100.000 pesos, più altri 50.000 per il giornale di bordo. Prendo la 'Mirage' da te, restituiremo questa nave all'Inghilterra.";
			link.l1 = "Diavolo! È una splendida nave, volevo tenermela!";
			link.l1.go = "Fleetwood_complete_3";
		break;
		
		case "Fleetwood_complete_3":
			dialog.text = "Figliolo, sei un soldato eccellente, ma fidati della mia esperienza nelle faccende politiche. Ricorda cosa ti dissi di Fleetwood? Intendo inchiodare il suo nome e la sua reputazione a una macina e gettarla negli abissi. Quei nobili arroganti di Port Royal dovranno ingoiare e strozzarsi.\nTrasformeremo Richard Fleetwood nel capitano della 'nave fantasma' Mirage, un lupo travestito che mette l’una contro l’altra Inghilterra e Olanda, saccheggiando, depredando e massacrando cittadini innocenti di entrambe le nazioni per arricchirsi! Una vera infamia! Ho già pronti testimoni e prove, ma sarà la 'Mirage' la punta di diamante di questa mia messinscena perfetta.";
			link.l1 = "E allora che mi venga un colpo. Vuoi sacrificare la mia splendida nave per il tuo dannato piano!?";
			link.l1.go = "Fleetwood_complete_4";
			AddDialogExitQuestFunction("Lucas_ExangeShip");
		break;
		
		case "Fleetwood_complete_4":
			dialog.text = "Attento a come parli, ragazzo, questa è guerra. A volte bisogna sacrificare non solo uomini, ma anche navi e ricche colonie per raggiungere i nostri fini politici. Ogni guerra ha le sue perdite... A proposito di perdite, ho brutte notizie per te.\nMentre eri via, Willemstad è stata assalita da corsari inglesi. Il forte li ha scacciati, sì, ma non prima che entrassero nel porto con navi incendiarie.\nLa tua nave era all’ancora e ha preso fuoco fino allo scafo. È andata, persa per sempre.";
			link.l1 = "Mynheer, mi state prendendo per il culo in questo momento. Maledizione all’inferno! E ora che diavolo faccio?!";
			link.l1.go = "Fleetwood_complete_5";			
		break;
		
		case "Fleetwood_complete_5":
			dialog.text = "Non ti crucciare così, kapitein, ho anche buone nuove. Per lenire il tuo sdegno, ti cedo il mio Vento Bello, lo xebec 'Meifeng'. Sei libero di usare la nave come meglio credi, entro i limiti della ragione. Inoltre, incontrami domani alla residenza del governatore: sei stato nominato per un’onorificenza di stato, con il ringraziamento della Repubblica Olandese e della Compagnia delle Indie Occidentali. Non lasciare la città finché non l’avrai ricevuta, kapitein.";
			link.l1 = "Questo sì che addolcisce un po’ la mia sventura. È un onore. A proposito, signor mio, dove diavolo è finito Longway?";
			link.l1.go = "Fleetwood_complete_6";
		break;
		
		case "Fleetwood_complete_6":
			dialog.text = "Longway è sparito di colpo appena gli ho ordinato di fare rotta su Dominica. Ho il sospetto che qualche cane inglese gli abbia teso un agguato... oppure no. Sto indagando.";
			link.l1 = "Capisco. Il suo aiuto a Dominica sarebbe stato prezioso. Fleetwood e la sua 'Valkerie' erano una coppia temibile. Spero che Longway sia ancora vivo... Tot zeins, mynheer!";
			link.l1.go = "Fleetwood_complete_7";
			pchar.questTemp.HWIC.Holl = "Award";
			AddQuestRecord("Holl_Gambit", "1-24");
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", true);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", true);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", true);
		break;
		
		case "Fleetwood_complete_7":
			DialogExit();
			pchar.quest.Award_FromLucas.win_condition.l1 = "Timer";
			pchar.quest.Award_FromLucas.win_condition.l1.date.hour  = 8.00;
			pchar.quest.Award_FromLucas.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Award_FromLucas.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Award_FromLucas.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Award_FromLucas.win_condition.l2 = "location";
			pchar.quest.Award_FromLucas.win_condition.l2.location = "Villemstad_townhall";
			pchar.quest.Award_FromLucas.function = "AwardFromFromLucas";
			AddSimpleRumour("Tell me captain, was that damned English dog Fleetwood was really responsible for plundering English 'and' Dutch merchants? Really? Such an artful dodger! It is good that you have eliminated this bastard. You are a real hero, captain!", HOLLAND, 10, 3);
		break;
		
		case "Fleetwood_fail":
			dialog.text = "Non sei solo un pagliaccio qualunque, sei tutto il circo messo insieme. Eravamo a un passo dal gran finale e tu hai rovinato tutto... Ti darò 30.000 pesos per togliere di mezzo Fleetwood. Non ho più incarichi per te e il nostro accordo è finito. Fuori dai piedi.";
			link.l1 = "Come desideri.";
			link.l1.go = "Fleetwood_fail_1";			
		break;
		
		case "Fleetwood_fail_1":
			AddMoneyToCharacter(pchar, 30000);
			dialog.text = "Ho brutte notizie per te.\nMentre eri via, Willemstad è stata assalita da corsari inglesi. Il forte è riuscito a respingerli, ma non prima che entrassero nel porto con navi incendiarie.\nLa tua nave era all’ancora ed è stata bruciata fino alla linea di galleggiamento. È andata persa completamente.";
			link.l1 = "Immagino che dovrò andare a farmi fottere da solo, allora! Grazie di niente!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Holl = "end";
			pchar.questTemp.HWIC.Detector = "holl_fail";
			AddSimpleRumour("Tell me, captain, is it true that you have sunk this damned English dog Fleetwood? Really? It is good that you have eliminated this bastard. You did well, captain!", HOLLAND, 15, 3);
		break;
		
		case "LucasAward":
			dialog.text = "Capitano "+GetFullName(pchar)+"! Per aver eliminato Richard Fleetwood, pericoloso criminale di stato, per aver smascherato il tradimento inglese contro la Repubblica, per il coraggio e l’audacia dimostrati, ti vengono assegnati mille dobloni d’oro a nome della Repubblica Olandese!\nRiceverai inoltre questo prezioso strumento di navigazione – sogno di ogni lupo di mare al servizio di sua maestà.";
			link.l1 = "Sono lieto di servire la Repubblica!";
			link.l1.go = "LucasAward_1";			
		break;
		
		case "LucasAward_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetActorType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
			sld.dialog.currentnode = "Bek_7";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			GiveItem2Character(pchar, "bussol");
		break;
		
		case "LucasAward_2":
			dialog.text = "Ancora congratulazioni, amico mio. E mi raccomando, vienimi a trovare tra una settimana. Abbiamo bisogno di te per una faccenda davvero delicata.";
			link.l1 = "Inteso, signor Rodenburg. Verrò a trovarvi tra una settimana.";
			link.l1.go = "LucasAward_3";			
		break;
		
		case "LucasAward_3"://наведем порядок
			LAi_SetActorType(pchar);
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-25");
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_ActorGoToLocator(sld, "goto", "goto6", "BekSitDown", -1);
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("LucasGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
			sld = characterFromId("Lucas");
			LAi_ActorGoToLocator(sld, "reload", "reload1", "LucasReturnInCabinet", -1);
			bDisableFastReload = true;
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			SetTimerFunction("GollandGambit_4_ZadanieStart", 0, 0, 7);
			AddSimpleRumourCity("They say that you were given a state award by Matias Beck himself! The Republic should be proud to have people like you, kapetein!", "Villemstad", 20, 4, "");
		break;
		
//--------------------------------------------------4 задание----------------------------------------------
		
		case "Abby":
			dialog.text = "Lascia che ti racconti una storia. Ti aiuterà a capire quanto sia delicato il tuo prossimo incarico. Qualche mese fa, una fluyt battente bandiera inglese diretta a Willemstad fu attaccata dal defunto Jacob van Berg. Prese la nave e la fece affondare non lontano da un’isola che non appare su nessuna delle nostre carte. Soltanto due passeggeri si salvarono: un ebreo chiamato Solomon Shneur e sua figlia Abigail. Tutti gli altri morirono, compreso il resto della loro famiglia. I nostri due ebrei raggiunsero l’isola aggrappati a dei relitti\nSolomon riuscì persino a trascinare con sé uno scrigno pieno dell’oro di famiglia. Molto parsimonioso da parte sua. Un altro personaggio della nostra storia, Richard Fleetwood, navigava nelle vicinanze e udì i rumori della battaglia. Arrivò troppo tardi per catturare van Berg, e la 'Mirage' fuggì. Fleetwood decise di controllare l’isola in cerca di superstiti\nSalvò Solomon e Abigail da morte certa su quell’isola deserta. Sfortunatamente per il vecchio ebreo, Solomon non aveva occhio da marinaio. Scambiò la 'Valkerie' di Richard per la 'Mirage' di Jacob e – terrorizzato, credendo che il pirata fosse tornato per finirli – nascose il suo oro da qualche parte sull’isola. Così lui e sua figlia arrivarono qui senza un soldo, lasciati da Fleetwood alla Laguna Blanca, vicino a Willemstad, la loro destinazione originale.\nSolomon mi ha raccontato questa storia. La Repubblica Olandese sostiene la libera pratica della religione. Come parte di questa politica, la Compagnia sostiene la comunità ebraica qui. Mi sono assicurato che avessero un tetto sulla testa, cibo e vestiti. Ho visitato spesso la loro casa. Abigail è una... giovane donna straordinaria. Sincera e fiduciosa\nNon ti mentirò, capitano, la desidero e intendo farla mia moglie. Lei mi ama a sua volta, ma qualcosa si è messo tra noi.";
			link.l1 = "Suo padre non è troppo entusiasta di avere un genero cristiano, eh?";
			link.l1.go = "Abby_0";			
		break;
		
		case "Abby_0":
			dialog.text = "Ah! Il vecchio Salomone sarebbe al settimo cielo se sposassi Abigail, genero non circonciso o meno. In verità, lui la spinge ad accettare la mia proposta. No, no, questa è una faccenda che va oltre ebrei e cristiani. Ti chiedo, figliolo, di aiutarmi a risolvere questo guaio. Parla con Abigail e scopri che cosa la turba. Sei uno straniero, magari a te confiderà cose che a noi, per via della sua graziosa modestia, non direbbe mai. La casa di Shneur sta sulla destra rispetto all’ufficio della Compagnia, se ci dai le spalle. So che sai incantare con le parole. Ma ricordati una cosa: Richard Fleetwood era il vero capitano della 'nave fantasma'... Tienilo a mente quando parlerai con Abigail.";
			link.l1 = "Ah! Ma certo che lo ricordo, signor Rodenburg. Non è forse cosa nota a tutti, dopotutto? Allora non perdo tempo, vado subito a far visita alla vostra amata.";
			link.l1.go = "Abby_1";			
		break;
		
		case "Abby_1":
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbyInHouse";
			AddQuestRecord("Holl_Gambit", "1-26");
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "Abby_2":
			dialog.text = "Hai davvero trovato l'isola dove Salomone ha nascosto il suo oro? Ma questa sì che è una notizia squisita! Cominciavo a pensare che non ci fosse impresa che tu non possa compiere... Hai scovato altro nel nascondiglio?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.ScullnotReturn"))
			{
				link.l1 = "No, nient'altro. Solo denaro.";
				link.l1.go = "Abby_3";
			}
			else
			{
				link.l1 = "C'era un oggetto curioso – un teschio di giada. L'ho consegnato a Solomon, che m'ha detto fosse un cimelio di famiglia. Ha pure aggiunto che avevi intenzione di comprarglielo...";
				link.l1.go = "Abby_4";
			}
		break;
		
		case "Abby_3":
			pchar.questTemp.HWIC.Holl.LucasItem = "obereg_11";
			dialog.text = "Hm. Va bene allora. Però è davvero strano. Bah... Ti sono debitore, signore, e non lo dimenticherò mai. Ho preparato una ricompensa per te – 50.000 pesos e questo amuleto. Ora sono tuoi.";
			link.l1 = "Grazie, signor Rodenburg!";
			link.l1.go = "Abby_5";
		break;
		
		case "Abby_4":
			pchar.questTemp.HWIC.Holl.LucasItem = "totem_04";
			dialog.text = "Eccellente! Sì, acquisterò questo artefatto da Salomone, non gli serve e ho già un compratore con la borsa gonfia che lo aspetta. Ho preparato una ricompensa per te – cinquantamila pesos e quest’amuleto. Ora sono tuoi.";
			link.l1 = "Grazie, signor Rodenburg!";
			link.l1.go = "Abby_5";
		break;
		
		case "Abby_5":
			dialog.text = "Non ho alcun incarico degno d’un kapitein come te al momento. Ma non sparire da Curaçao troppo a lungo, avrò presto di nuovo bisogno dei tuoi servigi.";
			link.l1 = "Ho capito, signor mio. Addio!";
			link.l1.go = "exit";
			GiveItem2Character(pchar, pchar.questTemp.HWIC.Holl.LucasItem);
			AddMoneyToCharacter(pchar, 50000);
			pchar.quest.Merdok_prepare.win_condition.l1 = "Timer";
			pchar.quest.Merdok_prepare.win_condition.l1.date.hour = sti(GetTime());
			pchar.quest.Merdok_prepare.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			pchar.quest.Merdok_prepare.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.Merdok_prepare.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			pchar.quest.Merdok_prepare.win_condition.l2 = "location";
			pchar.quest.Merdok_prepare.win_condition.l2.location = "Villemstad_town";
			pchar.quest.Merdok_prepare.function = "GiveTaskMerdok";
			pchar.questTemp.HWIC.Holl = "Merdok_wait";
			AddQuestRecord("Holl_Gambit", "1-34");
			DelMapQuestMarkCity("Villemstad");
			SetTimerFunction("GollandGambit_5_ZadanieStart", 0, 0, 10);
			AddSimpleRumourCity("Have you heard the latest news? Mynheer Rodenburg is going to marry Abigail Shneur, the beautiful daughter of the old crazy Jew Solomon. What can I say, she is a lucky girl. God willing, she'll be baptized a true Christian before the wedding!", "Villemstad", 20, 3, "");
		break;
		
		case "Abby_6":
			dialog.text = "Ah, tutto qui? Assurdo... proprio da femminucce. Ascoltami, figliolo, questa faccenda si risolve in un attimo. So bene quant’oro c’era nel tesoro di Salomone: duecentomila pesos. Per la mia felicità e quella di Abigail, sono disposto a tirar fuori questa somma. Te la do, tu sparisci da Curaçao per una settimana o due. Poi torni da Salomone e gli consegni il denaro, fingendo d’aver trovato il tesoro. Il lupo sazio e la pecora salva. Su, prendi questi quattrini.";
			link.l1 = "Un piano chiaro e senza fronzoli. Diamoci sotto.";
			link.l1.go = "Abby_7";
		break;
		
		case "Abby_7":
			dialog.text = "Salpa verso il mare aperto e torna da me tra dieci giorni. Va’ a farti valere. Cerca la Manga Rosa, fabbrica qualche provvista, o trova qualcosa da combinare.";
			link.l1 = "Come volete, signor Rodenburg.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 200000);
			pchar.questTemp.HWIC.Holl = "GiveLucasMoney";
			SaveCurrentQuestDateParam("questTemp.HWIC.Holl.LucasMoney");
			pchar.questTemp.HWIC.Holl.LucasMoney = "true";
			AddQuestRecord("Holl_Gambit", "1-35");
		break;
		
		case "Abby_8":
			pchar.questTemp.HWIC.Holl.LucasItem = "obereg_11";
			dialog.text = "Splendido! Ancora una volta, hai portato a termine il compito in modo impeccabile. Ti sono debitore, signor mio, e non lo dimenticherò mai. Ho preparato per te una ricompensa: 50.000 pesos e questo amuleto. Ora sono tuoi.";
			link.l1 = "Grazie, signor Rodenburg!";
			link.l1.go = "Abby_5";
		break;
		
//-------------------------------------------5 задание-------------------------------------------------
		case "Merdok":
			dialog.text = "Sì, proprio così. Amico mio, a volte è difficile capire chi sia davvero amico e chi sia nemico. Spesso ti sfugge il momento in cui il tuo più fidato compare si trasforma nel tuo peggior rivale. Il nostro conoscente comune di St John's, John Murdock – chiamato anche Johan van Merden – era agente della Compagnia, ma ora si è venduto ai dannati inglesi.\nLa sua nuova missione è far fuori una delle stelle più brillanti della Compagnia... cioè te.";
			link.l1 = "Sono lusingato. Menomale che me l’hai detto, altrimenti non ci avrei mai pensato.";
			link.l1.go = "Merdok_1";
		break;
		
		case "Merdok_1":
			dialog.text = "Precisamente, kapitein. Quello è una volpe astuta. Trova quel bastardo e ficcagli una pallottola prima che colpisca. Salpa per Antigua e cerca un ingresso segreto alla sua bottega d’erbe. Davanti alla chiesa c’è una botola che porta a un passaggio nascosto. Usala.";
			link.l1 = "Me ne occupo io.";
			link.l1.go = "Merdok_2";
		break;
		
		case "Merdok_2":
			dialog.text = "Un'ultima cosa, kapitein. Quando Johan sarà morto, fruga sul suo cadavere, in casa e nello scantinato. Tiene un archivio – un registro bello grasso in cui annotava note compromettenti mentre serviva la Compagnia. Se i nostri nemici lo trovano, siamo tutti dannati.\nRecupera quell'archivio maledetto e portamelo, ti pagherò un buon extra. Ora vai. Che Dio ti accompagni, Kapitein "+pchar.name+", e cerca di tornare intero. La Repubblica ha bisogno di te!";
			link.l1 = "Vi prometto, signor mio, che tornerò intero. È senza dubbio nel mio stesso interesse!";
			link.l1.go = "Merdok_3";
		break;
		
		case "Merdok_3":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "KillMerdok";
			AddQuestRecord("Holl_Gambit", "1-42");
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			bDisableFastReload = false;
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);//откроем проход в подземелье из дома
			LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false);//откроем проход в дом из подземелья
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//аптеку закроем
			pchar.quest.Merdok_inCave.win_condition.l1 = "location";
			pchar.quest.Merdok_inCave.win_condition.l1.location = "SentJons_TownCave";
			pchar.quest.Merdok_inCave.function = "MerdokInUndergroundCave";
			LAi_LocationDisableOfficersGen("SentJons_TownCave", true);//офицеров в шахту не пускать
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("SentJons", false);
		break;
		
		case "Merdok_4":
			dialog.text = "Eccellente, capitano! Mi rallegra davvero, lo dico sul serio. Hai trovato il suo archivio?";
			if (CheckCharacterItem(pchar, "MerdokArchive"))//архив
			{
				link.l1 = "Sì, eccolo. Sul cadavere del farmacista o nei suoi bauli non c’era nessun altro documento.";
				link.l1.go = "Merdok_book";
			}
			link.l2 = "No.  Ho cercato ovunque, ma non ho trovato un accidente.";
			link.l2.go = "Merdok_5";
			DeleteAttribute("SentJons_TownCave", "box2");//если не нашли шифр - уже и не найдем
		break;
		
		case "Merdok_5":
			dialog.text = "È un vero peccato, ma poco male. Son sicuro che Johan non ebbe il tempo di passare la cosa agli inglesi, altrimenti saremmo già appesi al pennone come prosciutti... Probabilmente l’ha nascosta in qualche covo segreto... che vi marcisca per l’eternità! Ti faccio i miei complimenti, kapitein, per la riuscita della nostra impresa!";
			link.l1 = "Gratitudine!";
			link.l1.go = "Merdok_6";
			
			SetTimerCondition("PZ_LigaInJungle", 0, 0, 7, false);	// проверку не прошёл, значит нападёт Лига через неделю, после чего начнётся таймер на 30 дней 1 этапа
		break;
		
		case "Merdok_book":
			dialog.text = "Sontuoso! Ora è al sicuro, dove deve stare. Hai dimostrato ancora una volta d’essere il migliore... Dammi il libro... Per l’archivio c’è una ricompensa – questo moschetto di pregio. Mi ha servito con onore, ora appartiene a te!";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.PZ_RodenburgUkradenaStranitsa"))
			{
				link.l1.go = "Merdok_book_2";
			}
			else
			{
				link.l1.go = "Merdok_book_6";
			}
			RemoveItems(PChar, "MerdokArchive", 1);
		break;
		
		case "Merdok_book_2":
			dialog.text = "Che razza di gioco fai, Capitano? Mancano diverse pagine — pagine che per me valgono più dell’oro. Credevi che non me ne sarei accorto, così da usarmi contro di me? Oppure speravi di strappare un bottino più ricco? Mi spiace deluderti su entrambi i fronti.";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l1 = "(Affidabile) Chiedo venia. Il mio unico errore è stato non aver consultato io stesso gli archivi in anticipo.";
				link.l1.go = "VD_Merdok_book_3";
				SetTimerCondition("PZ_Etap1_Start", 0, 0, 30, false);	// 1 этап стартует через 30 дней
			}
			else
			{
				notification("Perk check failed", "Trustworthy");
				link.l1 = "Davvero strapperei le pagine e poi consegnerei l’archivio con aria indifferente?";
				link.l1.go = "Merdok_book_3";
				SetTimerCondition("PZ_LigaInJungle", 0, 0, 7, false);	// проверку не прошёл, значит нападёт Лига через неделю, после чего начнётся таймер на 30 дней 1 этапа
			}
			LAi_Fade("", "");
		break;
		
		case "Merdok_book_3":
			dialog.text = "L’avidità, la stupidità e l’insolenza spingono talvolta la gente a follie indicibili, Capitano.";
			link.l1 = "Nessuno di quei tre mi ha spinto, te lo assicuro.";
			link.l1.go = "Merdok_book_4";
		break;
		
		case "Merdok_book_4":
			dialog.text = "Quindi mi stai dicendo che van Merden ha strappato quelle pagine e le ha nascoste da qualche altra parte?";
			link.l1 = "Esatto. Potrei tornare a cercarli—rovesciare l’intera farmacia, o persino tutto St. John's—se lo ritenete necessario.";
			link.l1.go = "Merdok_book_5";
		break;
		
		case "Merdok_book_5":
			dialog.text = "Non serve, signore. Tutto ciò che conta sta già qui, e senza le pagine mancanti il resto non mi minaccia affatto.";
			link.l1 = "";
			link.l1.go = "Merdok_book_6";
		break;
		
		case "VD_Merdok_book_3":
			dialog.text = "Dunque, si tratta più di negligenza o disinteresse che di disonestà o di qualche intrigo? Pensi che fosse già così quando l’hai trovato?";
			link.l1 = "Molto probabilmente, signor Rodenburg. Forse van Merden ha strappato quelle pagine in anticipo. ";
			link.l1.go = "VD_Merdok_book_4";
		break;
		
		case "VD_Merdok_book_4":
			dialog.text = "Forse è meglio così. Senza quelle pagine, il resto dell’archivio non mi fa paura – soprattutto se finisce in mani inesperte.";
			link.l1 = "";
			if (IsCharacterPerkOn(pchar, "Trustworthy")) link.l1.go = "Merdok_book_6";
			else link.l1 = "Merdok_6";
		break;
		
		case "Merdok_book_6":
			dialog.text = "C'è una ricompensa per l'archivio: questo moschetto pregiato. Mi ha servito con onore e ora appartiene a te!";
			link.l1 = "Grazie!";
			link.l1.go = "Merdok_6";
			GiveItem2Character(PChar, "mushket2");
		break;
		
		case "Merdok_6":
			dialog.text = "Abbiamo fatto un bel colpo, tu ed io, kapitein. Non esagero dicendo che senza di te nulla di tutto ciò sarebbe accaduto. Se continuerai a servire la Repubblica, ti attendono vette di carriera straordinarie, forse addirittura la nobiltà.";
			link.l1 = "Immagino sia un addio, signor Rodenburg.";
			link.l1.go = "Merdok_7";
		break;
		
		case "Merdok_7":
			dialog.text = "È l’addio, "+pchar.name+"Ho compiuto tutto ciò che desideravo qui, dunque fra una settimana farò vela verso Amsterdam. La mia novella sposa Abigail e mio suocero Solomon verranno con me. Peter Stuyvesant ha già trovato un nuovo vice-direttore per la Compagnia, quindi rivolgiti a lui se avrai bisogno di qualcosa.\nPer i tuoi servigi ti dono la Meifeng. Ora è tua, kapitein, te la sei meritata.";
			link.l1 = "Grazie, Signor Rodenburg. Ormai mi sono affezionato alla Meifeng e già la penso come fosse mia.";
			link.l1.go = "Merdok_8";
		break;
		
		case "Merdok_8":
			dialog.text = "E ora devo chiederti di lasciarmi, figliolo. Ho un mare di faccende prima di mollare gli ormeggi... Vienimi a trovare ad Amsterdam un giorno! Berremo insieme e ricorderemo i bei tempi andati...";
			link.l1 = "Eh già, buon uomo. Che la vostra nuova vita sia piena di fortuna e bottino! Addio!";
			link.l1.go = "Merdok_9";
			// belamour legendary edition -->
			link.l2 = "Ah, signor mio. Spero che la vostra nuova vita sia colma di gioia e fortuna! \n(con i denti stretti) ... Che il diavolo vi porti, arrogante bastardo. Aspetta solo di assaporare le delizie d’esser marito di una “modesta” bisbetica ebrea.";
			link.l2.go = "Merdok_9a";
		break;
		
		case "Merdok_9a":
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			DialogExit();
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			AddQuestRecord("Holl_Gambit", "1-41");
			CloseQuestHeader("Holl_Gambit");
			sld = characterFromId("Abigile");//уберем Аби
			sld.lifeday = 0;
			sld = characterFromId("Solomon");//уберем Соломона
			sld.lifeday = 0;
			pchar.quest.Lucas_quit.win_condition.l1 = "Timer";
			pchar.quest.Lucas_quit.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Lucas_quit.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Lucas_quit.function = "LucasQuit";//прерывание на Лукаса
			pchar.questTemp.HWIC.Detector = "holl_win";
			CheckPortugalHWIC();
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddSimpleRumourCity("Mynheer Rodenburg has sailed to Amsterdam with his young wife and father-in-law. Are you the new vice-director?", "Villemstad", 30, 3, "");
			AddSimpleRumour("They say, kapitein, that you are well regarded by the governor-general. Mynheer Rodenburg supposedly appointed you as his successor in the Company, is that so?", HOLLAND, 30, 3);
		break;
		
		case "Merdok_9":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			DialogExit();
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			AddQuestRecord("Holl_Gambit", "1-41");
			CloseQuestHeader("Holl_Gambit");
			sld = characterFromId("Abigile");//уберем Аби
			sld.lifeday = 0;
			sld = characterFromId("Solomon");//уберем Соломона
			sld.lifeday = 0;
			pchar.quest.Lucas_quit.win_condition.l1 = "Timer";
			pchar.quest.Lucas_quit.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Lucas_quit.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Lucas_quit.function = "LucasQuit";//прерывание на Лукаса
			pchar.questTemp.HWIC.Detector = "holl_win";
			CheckPortugalHWIC();
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddSimpleRumourCity("Mynheer Rodenburg has sailed to Amsterdam with his young wife and father-in-law. Are you the new vice-director?", "Villemstad", 30, 3, "");
			AddSimpleRumour("They say, kapitein, that you are well regarded by the governor-general. Mynheer Rodenburg supposedly appointed you as his successor in the Company, is that so?", HOLLAND, 30, 3);
		break;
		
//----------------------------------------------за Англию------------------------------------------------------
		case "Lucas_abordage":
			dialog.text = "Dio nei Cieli! Cane di Fleetwood! Oggi potrai uscirne vincitore, ma Lucas Rodenburg venderà cara la propria pelle.";
			link.l1 = "Non credo proprio. Mi consegnerai la tua pellaccia gratis, taccagno olandese.";
			link.l1.go = "Lucas_abordage_1";
		break;
		
		case "Lucas_abordage_1":
			PlaySound("Voice\English\hambit\Lucas Rodenburg-04.wav");
			dialog.text = "Dalle profondità dell’inferno ti cagherò in bocca! Ho appena dato fuoco alla stiva e presto le fiamme lambiranno la santabarbara! Le nostre navi sono incatenate a distanza d’abbraccio, quindi non c’è scampo! Brucerai o finirai in pasto agli squali!";
			link.l1 = "Maledizione! Ritirata, ragazzi, dobbiamo battercela!";
			link.l1.go = "Lucas_abordage_2";
			// belamour legendary edition -->
			link.l2 = "Non me ne andrò finché la tua anima non lascerà il tuo corpo. Sta’ fermo, farà male.";
			link.l2.go = "Lucas_abordage_2a";
		break;
		
		case "Lucas_abordage_2a":
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom1"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
		case "Lucas_abordage_2":
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom1"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
//----------------------------------------------против всех--------------------------------------------------
		case "LucasPrisoner":
			dialog.text = "Che ci fai qui, maledetto? Sei venuto a prenderti gioco di me? Forse finalmente mi dirai che parte reciti in questa farsa. Sei stato tu a prendere la brigantino, vero? Era questo il tuo piano fin dall’inizio?";
			link.l1 = "Sono qui per porgerti i saluti, Lucas Rodenburg. I migliori saluti da John Merdock, che tu hai tradito. Eri il mio incarico e l’ho portato a termine. Addio, per ora.";
			link.l1.go = "LucasPrisoner_1";
		break;
		
		case "LucasPrisoner_1":
			PlaySound("Voice\English\hambit\Lucas Rodenburg-04.wav");
			dialog.text = "Johan? Ahah! Dunque era lui il burattinaio di tutta questa faccenda! Quel vecchio furfante! Ma la partita non è ancora finita. Jacob van Berg verrà a cercarti, e non avrai scampo! Tu e la tua nave siete già condannati, miserabile barbone dei mari!";
			link.l1 = "Risparmia la tua lingua per il tribunale del boia, Rodenburg.";
			link.l1.go = "LucasPrisoner_2";
		break;
		
		case "LucasPrisoner_2":
			DialogExit();
			pchar.questTemp.jailCanMove = true; //разрешить пройти мимо стражи
			LAi_SetPlayerType(pchar);
			pchar.quest.Login_Joakim.win_condition.l1 = "location";
			pchar.quest.Login_Joakim.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Login_Joakim.function = "Create_Joakim";
			pchar.questTemp.HWIC.Self = "JoakimMeeting";
			SetFunctionTimerCondition("LucasQuit", 0, 0, 7, false);
		break;
	}
}
