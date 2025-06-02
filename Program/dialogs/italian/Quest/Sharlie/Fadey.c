// Фадей Московит
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int rate;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.Sharlie"))
			{
				if (pchar.questTemp.Sharlie == "fadey")
				{
					dialog.text = "Cosa posso fare per voi, Monsieur? Non parlo con chi non conosco. Se siete venuto a fare due chiacchiere o a chiedere quando arriva il Treno d’Argento spagnolo a Maracaibo nel 1640, temo di deludervi. Non spreco il mio tempo in chiacchiere vuote.";
					link.l1 = "Buon pomeriggio, Monsieur Fadey. Forse non avete ancora l’onore di conoscermi, ma certo conoscete mio fratello. Permettetemi di presentarmi: Charles de Maure, fratello di Michel de Monper.";
					link.l1.go = "Sharlie";
					break;
				}
				if (pchar.questTemp.Sharlie == "takeknife" && !CheckAttribute(pchar, "questTemp.Persian"))
				{
					dialog.text = "Ahah, di nuovo tu, Charles! Kak dela? Che c’è stavolta?";
					link.l1 = "Hai detto che ti hanno derubato... Hai già trovato i furfanti?";
					link.l1.go = "Sharlie_8";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "fadey")
				{
					dialog.text = "Allora Charles, sei già andato a parlare con quel selvaggio?";
					link.l1 = "Ho... È per questo che sono tornato da te.";
					link.l1.go = "Tichingitu";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu") && pchar.questTemp.Sharlie.Tichingitu == "dublon")
				{
					dialog.text = "Ah, sei ancora tu, mio caro amico! Allora, hai portato il riscatto in dobloni per l’indiano?";
					if (CheckAttribute(pchar, "questTemp.Sharlie.Tichingitu80"))
					{
						if (PCharDublonsTotal() >= 80) // belamour legendary edition
						{
							link.l1 = "Sì. Ecco a te le tue 80 dobloni.";
							link.l1.go = "Tichingitu_7";
						}
						else
						{
							link.l1 = "No, non ho ancora raccolto abbastanza.";
							link.l1.go = "exit";
						}
					}
					else
					{
						if (PCharDublonsTotal() >= 100) // belamour legendary edition
						{
							link.l1 = "Sì. Ecco a te i tuoi cento dobloni.";
							link.l1.go = "Tichingitu_7";
						}
						else
						{
							link.l1 = "No, non ne ho raccolto abbastanza, ancora.";
							link.l1.go = "exit";
						}
					}
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "begin")
				{
					dialog.text = "Ah, ma guarda chi si vede, Monsieur de Maure in persona! Entra, avanti, non restare lì impalato! Che vento ti porta nella mia tana?";
					link.l1 = TimeGreeting()+", Fadey, mio fratello mi ha mandato da te. Ha detto che mi daresti una mano a trovar qualche lavoretto.";
					link.l1.go = "trial";
					// опоздал
					if (CheckAttribute(pchar, "questTemp.Trial.late")) {
						link.l1.go = "trial_late";
					}
					break;
				}
				if (pchar.questTemp.Sharlie == "trial" && !CheckAttribute(npchar, "quest.vodka"))
				{
					dialog.text = "Ah, sei tu! Cosa ti porta da queste parti, Monsieur de Maure?";
					link.l1 = TimeGreeting()+", Fadey. Mio fratello mi ha raccomandato di non parlarti di questa faccenda, ma proprio non ho saputo resistere... ";
					link.l1.go = "vodka";
					break;
				}
				// belamour legendary edition пиратская линейка -->
				if(CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves") && pchar.questTemp.Mtraxx.GiveMeSlaves == "Baster")
				{
					dialog.text = "Ah, vecchio amico! Avanti, avanti, "+pchar.name+"! Come va?";
					link.l1 = TimeGreeting()+", Fadey. Lieto di vederti. In verità, ho affari importanti da sbrigare. Oro nero.";
					link.l1.go = "Slaves";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Mtraxx.GiveMeSlaves") && pchar.questTemp.Mtraxx.GiveMeSlaves == "FindGold")
				{
					dialog.text = "Ah, sei ancora tu, caro amico! Hai messo le mani sul bottino? Hai trovato abbastanza dobloni?";
					if(PCharDublonsTotal() >= 150)
					{
						link.l1 = "Sì, Monsieur Fadey! Ecco il vostro oro.";
						link.l1.go = "Slaves_2";
					}
					else
					{
						link.l1 = "No, sono appena passato. Sto ancora cercando la cifra giusta.";
						link.l1.go = "exit";
					}
					
					link.l2 = "Fadey, mi è appena venuta un’idea. Non ho più bisogno degli schiavi. Perdonami, ci vediamo più tardi!";
					link.l2.go = "Slaves_3";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Baster")
				{
					dialog.text = "Ah, mio vecchio amico! Entra pure, avanti, "+pchar.name+"! Come va, compare?";
					if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves"))
					{
						if(pchar.questTemp.Mtraxx.GiveMeSlaves == "Deal" || pchar.questTemp.Mtraxx.GiveMeSlaves == "WithoutSlaves")
						{
							link.l1 = TimeGreeting()+" , ho di nuovo bisogno del tuo aiuto.";
						}
					}
					else
					{
						link.l1 = TimeGreeting()+", Fadey. Lieto di vederti. Ho da discutere affari con te.";
					}
					link.l1.go = "pistols";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "FindMoney")
				{
					dialog.text = "Ah, sei di nuovo tu, mio caro amico! Allora, hai trovato il denaro?";
					if(PCharDublonsTotal() >= 300)
					{
						link.l1 = "Li ho qui, Monsieur Fadey! Ecco le tue 300 dobloni.";
						link.l1.go = "pistols_4D";
					}
					if(sti(Pchar.money) >= 40000)
					{
						link.l2 = "Li ho qui, Monsieur Fadey! Ecco i vostri 40.000 pesos.";
						link.l2.go = "pistols_4P";
					}
					if(PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000) 
					{
						link.l3 = "No, sono solo di passaggio. Sto ancora cercando la giusta somma.";
						link.l3.go = "exit";
					}
					link.l4 = "Perdonami, Fadey, ma non posso permettermelo. Proverò a cavarmela da solo. A presto!";
					link.l4.go = "pistols_x";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "Today")
				{
					dialog.text = "Entra pure, entra, "+pchar.name+"! Vedo nei tuoi occhi che bruci dalla voglia di sentire dei miei trionfi.";
					link.l1 = "Proprio così, Fadey. Confido che tu abbia ciò che desidero.";
					link.l1.go = "pistols_5";
					break;
				}
				if(CheckAttribute(pchar,"questTemp.Mtraxx.MagicBox") && pchar.questTemp.Mtraxx.MagicBox == "FindMoney")
				{
					dialog.text = "Ah, sei di nuovo tu, mio caro amico! Allora, hai trovato il denaro?";
					if(PCharDublonsTotal() >= 300)
					{
						link.l1 = "Prendi 300 dobloni. Chiederò ai marinai di portare questa cassa sulla mia nave. Ah, che farei senza di te, Fadey?! Non hai idea di quanto mi hai tirato fuori dai guai!";
						link.l1.go = "pistols_5D";
					}
					if(sti(Pchar.money) >= 40000)
					{
						link.l2 = "Prendi 40.000 pesos. Chiederò ai marinai di portare questa cassa sulla mia nave. Ah, cosa farei senza di te, Fadey?! Non hai idea di quanto mi hai tirato fuori dai guai!";
						link.l2.go = "pistols_5P";
					}
					if(PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000) // возможность найти без отказа
					{
						link.l3 = "No, sono appena passato. Sto ancora cercando di mettere insieme abbastanza.";
						link.l3.go = "exit";
					}
					link.l4 = "Perdonami, Fadey, sono al verde. Tieniti la caparra, spero basti a coprire le tue spese per questa faccenda, e proverò a cavarmela da solo. Addio!";
					link.l4.go = "pistols_x";
					break;
				}
				// <-- legendary edition
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "seek")
				{
					dialog.text = "Ah, Marchiato... Voglio dire "+pchar.name+"Avanti, forza, che novità hai per me?";
					link.l1 = TimeGreeting()+", Fadey. Lieto di vederti. Son venuto a parlarti d’affari.";
					link.l1.go = "guardoftruth";
					break;
				}
				if (CheckAttribute(pchar, "questTemp.Guardoftruth.Baster_church") && pchar.questTemp.Guardoftruth.Baster_church == "find" && !CheckAttribute(npchar, "quest.utensil"))
				{
					dialog.text = TimeGreeting()+", "+pchar.name+" Scommetto che fremi dalla voglia di sapere cosa ho scoperto dopo quella mia chiacchierata con il prete.";
					link.l1 = "Ma certo che lo sono! Com’è andata allora?";
					link.l1.go = "guardoftruth_9";
					break;
				}
				if (CheckAttribute(npchar, "quest.utensil") && PCharDublonsTotal() >= 250)
				{
					dialog.text = "Ah perdonami, son così distratto dal tintinnio che porti in tasca!";
					link.l1 = "Tanta avidità, Fadey! Ecco il tuo oro.";
					link.l1.go = "guardoftruth_11";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "guadeloupe")
				{
					dialog.text = "Ahah, mio vecchio amico! Entra pure, entra, "+pchar.name+"Allora, hai qualche novità?";
					link.l1 = "Salve, Fadey. Ancora una volta imploro il tuo aiuto.";
					link.l1.go = "guardoftruth_14";
					break;
				}
				dialog.text = "Che sei, una statua? Se hai qualcosa da dire, sputa il rospo, altrimenti fila via, "+pchar.name+"!";
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "start" && CheckNCountPersian() > 0)
				{// персидские клинки
					link.l2 = "Guarda un po', Fadey. Direi che questa è una shamshir persiana, forse una di quelle trafugate dalla tua collezione?";
					link.l2.go = "persian";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "one" && CheckNCountPersian() > 0)
				{
					link.l2 = "Ho buone notizie per te. Ho qui un altro shamshir persiano per te.";
					link.l2.go = "persian_6";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "two" && CheckNCountPersian() > 0)
				{
					link.l2 = "Ho una terza shamshir persiana. Proprio come volevi, l’ho riportata appena ho potuto.";
					link.l2.go = "persian_9";
				}
				if (CheckAttribute(pchar, "questTemp.Persian") && pchar.questTemp.Persian == "cirass")
				{
					link.l2 = "Sono qui per la questione dell’armatura leggera di cui abbiamo parlato.";
					link.l2.go = "persian_13";
				}
				if(CheckAttribute(npchar, "quest.ropes") && GetDataDay() == 20) // торговля канатами
				{
					link.l3 = "Fadey, vorrei comprare un po’ della tua rinomata cima.";
					link.l3.go = "ropes";
				}
				link.l1 = "Fadey, ho bisogno del tuo aiuto.";
				link.l1.go = "help";
 				link.l9 = "No, nulla per ora.";
				link.l9.go = "exit";
			}
			else
			{
				dialog.text = "Cosa posso fare per voi, monsieur? Non parlo con chi non conosco.";
				link.l1 = "Oh, sono passato solo per curiosare chi abita qui.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "Sharlie":
			DelLandQuestMark(npchar);
			QuestPointerDelLoc("baster_town", "reload", "houseSp1");
			dialog.text = "Ah, dunque sei il fratellino del caro Michel! Questo cambia le carte in tavola! Avanti, avanti, Monsieur, accomodati pure. Vuoi forse alzare un bicchiere di vodka in onore del nostro incontro? Ho ancora qualche bottiglia in serbo, e sarebbe un piacere condividerne una col fratello di un buon amico, da!";
			link.l1 = "Perdonatemi, Monsieur Fadey, ma questa notte il bere non fa per me. Preferirei andare subito al sodo.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "Cosa dite mai! Questo rum locale è brodaglia annacquata rispetto alla vodka russa! Non sapete cosa vi perdete, che il Mare mi inghiotta se mento! Va bene, veniamo agli affari allora. Sono tutt’orecchi, Charles.";
			link.l1 = "Monsieur, temo che ciò che sto per dirvi vi risulterà alquanto sgradito, ma ahimè, il dovere mi impone di parlarvi! Michel mi ha confidato che gli dovete una discreta somma persa al gioco con lui. Inoltre mi ha ordinato di riscuotere il denaro da voi, perché mio fratello... al momento non può venire di persona.";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Oh, giovanotto! Ma certo che ricordo tutto e ammetto d'esser debitore a tuo fratello. Un debito di gioco è sacro, rispettar la parola è l'unica cosa che ci salva dall'anarchia sanguinaria e dai briganti più feroci! Ma ti supplico, cerca di capire la mia situazione! Mi è capitata una brutta faccenda di recente – son stato derubato con una faccia tosta inaudita!\nMaledetti furfanti han preso tutto, ogni cosa guadagnata in anni di fatiche, i miei denari e la mia collezione inestimabile! Al momento proprio non posso saldare il debito, no\nMa, Monsieur de Maure, non rinnego i miei obblighi! Ti chiedo solo un po' di comprensione. Dal momento che non ho più una moneta bucata addosso, ti offro quest’eccellente pugnale raro. Guarda qui!\nÈ un vero capolavoro d’acciaio, orgoglio della mia collezione rubata. E poi fu incantato dagli sciamani indiani e cela poteri nascosti assai forti! Gli indiani lo chiamavano l’Artiglio del Capo\nNon avrei mai voluto privarmene, ché mi costò assai più del mio debito, ma data la situazione e il legame con tuo fratello maggiore, son pronto a dartelo. Prendilo, è un affare da non lasciarsi scappare!";
			link.l1 = "Preferirei di gran lunga il denaro a un coltello...";
			link.l1.go = "Sharlie_3";
		break;
		
		case "Sharlie_3":
			dialog.text = "Ma io non ho denaro e invece possiedo questo raro artefatto incantato! Davvero credi, drogato mio, che ti offrirei quest’incredibile pugnale magico invece di qualche misera moneta d’argento, se не fosse нужда? I pesos si trovano ovunque, persino per strada! Devi ammetterlo, mi trovo in un bel pasticcio. Il cuore mi si spezza solo a pensare di separarmi da questa meraviglia d’artigianato, ma un debito di gioco è questione d’onore, quindi sono disposto a dartelo solo a te, anche se mi è carissimo, perché sei un vero uomo d’onore e un sincero amico.";
			link.l1 = "D'accordo, visto che giuri di non avere nemmeno un soldo, mi prendo questo tuo pugnale magico. Speriamo di spuntare un buon prezzo...";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			dialog.text = "'Venderlo'!? Fuori dai piedi, stall- voglio dire Charles! Ma dai, non posso credere alle mie orecchie! Sto cedendo il mio bene più prezioso, che in Europa varrebbe almeno dieci volte tanto, e tu mi dici con quella faccia tosta che andrai a impegnarlo!? Questo pugnale, giovanotto, ha salvato una vita! Lascia che ti racconti—";
			link.l1 = "E quale sarebbe questo potere nascosto di cui parlavi?";
			link.l1.go = "Sharlie_5";
		break;
		
		case "Sharlie_5":
			dialog.text = "Oh, oh oh! Ora, Charles, sono un buon cristiano, sai, mica uno di quegli stregoni indiani. Non posso conoscere tutti i segreti nascosti di questa lama. Ma esistono, oh sì! Stringi questo pugnale fra le mani e sentirai tu stesso la forza che cela! Prendilo, figliolo! Allora, che ne dici? Senti qualcosa?";
			link.l1 = "Hm... Non sento nulla. Però, si adatta bene alla mia mano.";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = "Ah ah! Ecco qua! Ma questa è solo la minima delle sue virtù. Se brandirai questo pugnale in battaglia, vedrai che mostrerà la sua potenza in mille modi spettacolari! Allora, lo prendi?";
			link.l1 = "Ebbene, ho forse scelta? Me lo prendo, visto che non hai uno scudo bucato…";
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			GiveItem2Character(pchar, "knife_01");
			PlaySound("interface\important_item.wav");
			//Log_Info("You've received the Chief's Claw'");
			sld = ItemsFromID("knife_01");
			sld.Weight = 1.5;
			sld.price = 0;
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddMapQuestMarkCity("FortFrance", false);
			dialog.text = "Grazie, Charles. Non te ne pentirai, oh, questo te lo giuro! Tieni qui. E salutami Michel, mi raccomando! Digli di passare ogni tanto, appena ne avrà l’occasione.";
			link.l1 = "Oh, glielo dirò io...";
			link.l1.go = "exit";
			link.l2 = "Hai detto che eri stato derubato... Hai trovato i colpevoli?";
			link.l2.go = "Sharlie_8";
			pchar.questTemp.Sharlie = "takeknife";
			AddQuestRecord("Sharlie", "18-1");
			sld = characterFromId("Mishelle");	
			sld.greeting = "mishelle_2";
			
			// Sinistra - Старт квеста "Деньги на деревьях"
			PChar.quest.MOT_BarbieSpawn.win_condition.l1 = "location";
			PChar.quest.MOT_BarbieSpawn.win_condition.l1.location = "BasTer_town";
			PChar.quest.MOT_BarbieSpawn.win_condition = "MOT_BarbieSpawn";
			//убрать запрет боёвок на Мартинике
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_townhall")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_prison")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_fort")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortFrance_ammo")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("LeFransua_town")], false);
			LocatorReloadEnterDisable("FortFrance_townhall", "reload2", false);
			LocatorReloadEnterDisable("FortFrance_townhall", "reload3", false);
			sld = &Locations[FindLocation("FortFrance_prison")];
			sld.locators_radius.item.detector1 = 0.5;
		break;
		
		case "Sharlie_8":
			dialog.text = "Il problema è che non è così. Quei mascalzoni hanno svuotato tutta la casa, portandosi via tutto l’argento, l’oro, i miei risparmi di anni di fatiche. Di solito non mi cruccio: un vero gentiluomo, anche se perde tutto ciò che possiede, non deve mai mostrare emozione! Il denaro deve essere così sotto il suo rango che non vale neanche la pena pensarci. Ma il peggio è che mi hanno portato via la mia magnifica collezione di shamshir persiani! Non esiste nulla di simile, né nel Nuovo né nel Vecchio Mondo. Spade di cavalleria persiane davvero straordinarie...";
			link.l1 = "Spade persiane, dici? Suona piuttosto interessante. Sei un collezionista, dunque?";
			link.l1.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = "Ebbene, mi piace collezionare cose rare... Senti, Charles, forse potresti darmi una mano in questa faccenda...";
			link.l1 = "Aiuto? Ma come, di grazia? Intendi acciuffare quei furfanti?";
			link.l1.go = "Sharlie_10";
		break;
		
		case "Sharlie_10":
			dialog.text = "No. Non m'importa granché dei ladri. Vorrei riavere le mie sciabole persiane da cavalleria. Se le recuperi, saprò ricompensarti a dovere, te lo giuro.";
			link.l1 = "Hm. Ma dove dovrei mai cercarli? Per tutti i Caraibi? O magari in capo al mondo?";
			link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = "Beh, forse le scorgerai sulle isole dai mercanti di strada, quei furfanti non hanno neanche idea del valore di quelle sciabole da cavalleria e di sicuro le svenderanno per quattro soldi. Quindi, se vedi da qualche parte le spade persiane, portamele. Pensi di saperle riconoscere?";
			link.l1 = "Penso proprio di sì. Va bene, terrò gli occhi aperti e se vedo qualche lama strana che corrisponde alla descrizione, te la porterò senz'altro.";
			link.l1.go = "Sharlie_12";
			link.l2 = "Sai, non sono un intenditore di armi pregiate. Temo di non poterti essere d’aiuto. Sarebbe disonesto da parte mia alimentare vane speranze.";
			link.l2.go = "Sharlie_13";
		break;
		
		case "Sharlie_12":
			dialog.text = "Benone! Spero che tu abbia fortuna a scovare quegli artefatti, e ti assicuro che ne varrà la pena. Buona caccia, filibustiere—ehm, volevo dire capitano! Eh già, Charles, puoi crederci? Ho subito un altro tentativo di furto di recente!\nUn ladro ha cercato di intrufolarsi in casa mia pochi giorni fa.\nNe ho avuto abbastanza! Ma stavolta non gli è andata bene: l’ho acciuffato, gli ho dato una bella lezione e l’ho consegnato alle guardie della prigione in città. Spero che presto penzoli dalla forca!";
			link.l1 = "Pensi che sia uno dei furfanti che ti hanno fregato le shamshir?";
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "start";
			// --> скимитар 021012
			pchar.questTemp.Persian.skimitar = "true";
			pchar.quest.Persian.win_condition.l1 = "item";
			pchar.quest.Persian.win_condition.l1.item = "blade_23";
			pchar.quest.Persian.function = "Persian_FindSkimitar";
		break;
		
		case "Sharlie_13":
			dialog.text = "Peccato, ma è inutile piangere sulla luna. Eh sì, Charles, puoi crederci? Hanno cercato di derubarmi di nuovo, proprio di recente!\nUn furfante ha provato a intrufolarsi in casa mia solo pochi giorni fa.\nQuesta volta ho perso la pazienza! Ma non l'ho lasciato scappare: l'ho preso, gli ho dato una bella lezione e l'ho spedito dritto in prigione. Non si può gioire sulla disgrazia altrui. Spero che presto gli facciano fare il ballo della corda!";
			link.l1 = "Pensi che sia uno di quei furfanti che ti hanno fregato le sciabole?";
			link.l1.go = "Sharlie_14";
			pchar.questTemp.Persian = "end";
		break;
		
		case "Sharlie_14":
			dialog.text = "No, non credo proprio. Era in cerca di denaro. L’ho beccato nella mia stanza mentre frugava nei miei bauli.\nUn indio venuto da qualche giungla sperduta della Terraferma spagnola. Sembra uno spaventapasseri, niente общего с местными: tutto coperto di pitture di guerra e vestito con un costume sgargiante... Se ti va, puoi scendere nelle segrete e vedere tu stesso quel buffone, finché respira ancora.";
			link.l1 = "Hm... Forse passerò a trovarlo.";
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = "Avanti, dai un’occhiata a questo carosello di mostri... Va bene, Charles, è stata una bella chiacchierata. Buon vento per il ritorno in Martinica, che Eolo ti sia propizio!";
			link.l1 = "Tutto il meglio, Fadey.";
			link.l1.go = "exit";
			SetQuestHeader("Tichingitu");
			AddQuestRecord("Tichingitu", "1");
			pchar.questTemp.Sharlie.Tichingitu = "true";
			AddDialogExitQuestFunction("SetTichingituJail");
			SetFunctionTimerCondition("FreeTichingituOver", 0, 0, 10, false);
			pchar.questTemp.Sharlie = "takeknife";
		break;
		
		case "Tichingitu":
			DelLandQuestMark(npchar);
			dialog.text = "Ma che curioso! Ti ascolto.";
			link.l1 = "Fadey, ho parlato con quell’indio. E sono venuto da te per chiederti aiuto a tirarlo fuori. Quel poveraccio cercava solo un tozzo di pane...";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "Hahaha, e tu ci hai creduto davvero? Giovinotti d’oggi, così facili da abbindolare...";
			link.l1 = "Fadey, sarò pure più giovane di te, ma anche io so distinguere la verità dalle frottole. E poi, davvero credi che l’impiccagione sia la pena giusta per un simile reato? Mi pare un tantinello esagerato. Dalle nostre parti te la caveresti con qualche frustata, o al massimo un marchio per chi proprio non la smette.";
			link.l1.go = "Tichingitu_2";
		break;
		
		case "Tichingitu_2":
			dialog.text = "Eccessivo!? Quello scellerato ha fatto irruzione in casa mia! Un selvaggio simile non doveva mai mettere piede qui! Tu al mio posto cosa avresti fatto? Scommetto che gli avresti rovesciato le budella e l’avresti dato in pasto ai vermi, eh?!";
			link.l1 = "No, non lo farei, Fadey, sei ancora furioso per la tua collezione di shamshir rubata. Se non fosse successo, saresti più propenso a rifilare a questo pellirosse uno sculaccione come si deve e un calcio nel didietro, sbaglio forse?";
			link.l1.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			dialog.text = "Ahhhh, Charles... Sei proprio come tuo fratello... Horosho. Risolviamola come veri gentiluomini d’affari. Se vuoi tanto questo indiano, ricompensami per il danno morale e la roba rotta che ha combinato, e io dirò al comandante che non ho intenzione di sporgere denuncia. Che ne dici?";
			link.l1 = "Quanto?";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			dialog.text = "Ah, già cominci a capire come si живёт qui nei Caraibi, Charles. Centocinquanta dobloni d’oro, e non uno di meno.";
			link.l1 = "Fadey, che il Signore abbia pietà...";
			link.l1.go = "Tichingitu_5";
		break;
		
		case "Tichingitu_5":
			dialog.text = "Va bene, va bene. Cento dobloni d’oro. Ma questa è la mia ultima offerta. E parliamo di dobloni, non di pesos. Il nostro banchiere saprà sicuramente tirar fuori quella cifra per lo scambio.";
			if(PCharDublonsTotal() >= 100) // belamour legendary edition
			{
				link.l1 = "Ho la somma che ti serve proprio adesso. Ecco qua, prendi i tuoi cento dobloni.";
				link.l1.go = "Tichingitu_7";
			}
			if(CheckCharacterPerk(pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l2 = "(Affidabile) Fadey, ascolta... Capisco il tuo disappunto, ma sono l’unico disposto a compensarti con veri dobloni per questo fastidio.";
				link.l2.go = "Tichingitu_7_TW";
			}
			else notification("Perk Check Failed", "Trustworthy");
			link.l3 = "D'accordo, andrò a procurarti ciò che ti serve.";
			link.l3.go = "Tichingitu_6";
		break;
		
		case "Tichingitu_7_TW":
			dialog.text = "Hai un destino qui, amico mio, lo vedo chiaro. Va bene! Ottanta dobloni – e non uno di meno!";
			link.l1 = "";
			link.l1.go = "Tichingitu_6";
			pchar.questTemp.Sharlie.Tichingitu80 = true;
		break;
		
		case "Tichingitu_6":
			dialog.text = "E sbrigati, Charles! Hai solo dieci giorni prima che lo impicchino.";
			link.l1 = "Lo terrò a mente. Addio!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "dublon";
		break;
		
		case "Tichingitu_7":
			if(CheckAttribute(pchar,"questTemp.Sharlie.Tichingitu80"))
			{
				RemoveDublonsFromPCharTotal(80);
				DeleteAttribute(pchar,"questTemp.Sharlie.Tichingitu80");
			}
			else RemoveDublonsFromPCharTotal(100); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Benissimo. Ora ti scrivo una lettera con il mio sigillo, un attimo solo... ecco fatto. Consegnala al comandante e potrai portarti via il tuo indiano. Non capisco perché ti stia così a cuore, ma affari tuoi. Che farai, lo porterai a una mascherata come curiosità? Ahah, che idea!";
			link.l1 = "Dio vede tutto, Fadey. Salvare la vita d’un uomo è un gesto nobile.";
			link.l1.go = "Tichingitu_8";
		break;
		
		case "Tichingitu_8":
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1_Fadey");
			PlaySound("interface\important_item.wav");
			dialog.text = "Sono d'accordo con la tua prima affermazione, ma la seconda è discutibile, Charles. E se ti capitasse di salvare un assassino o uno stupratore dalla giustizia che lo aspetta alla forca? Bah, comunque, non è più affar mio. Che Dio ti accompagni. Vai dal comandante prima che il tuo amico dalla pelle rossa sbiadisca con un cappio al collo...";
			link.l1 = "Vado per la mia strada. Ci si vede dopo, Fadey.";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie.Tichingitu = "pay";
			SetFunctionLocationCondition("Tichingitu_AddQuestMark", "baster_prison", false);
			QuestPointerToLoc("BasTer_town", "reload", "reload_jail");
			QuestPointerDelLoc("baster_town", "reload", "houseSp1");
		break;
		
		case "vodka":
			dialog.text = "Sembri tetro, amico mio! Immagino tu stia per portarmi cattive notizie?";
			link.l1 = "Ecco qua tutta la storia, sì. Sarò schietto con te, Fadey: Michel m’ha detto che mi hai fregato con questa ‘zampa del capo’, una vera porcheria. Dice che non è nessun artefatto, e potrei comprarlo da qualsiasi mercante di strada per poche centinaia di pesos. Ho chiesto in giro tra i venditori di ferraglia. Proprio quel prezzo mi hanno sparato.";
			link.l1.go = "vodka_1";
			npchar.quest.vodka = "true";
		break;
		
		case "vodka_1":
			dialog.text = "Oh, Monsieur de Maure... Sono ferito! Tuo fratello mi ha sorpreso. Questi ciarlatani da quattro soldi in strada possono dire ciò che vogliono, ma lui! Dimmi tu, Charles, se qualcuno ti portasse una vecchia spada a due mani dai tempi di Carlo Magno e volesse vendertela, quanto saresti disposto a pagare?";
			link.l1 = "Una spadona a due mani? Mi prendi per il culo, Fadey? Che diavolo dovrei farmene di una vecchia lama da boia arrugginita? Siamo nel diciassettesimo secolo, per mille fulmini! Non ci spenderei neanche un reale, figurati un peso!";
			link.l1.go = "vodka_2";
		break;
		
		case "vodka_2":
			dialog.text = "Ah, vedi la tua miopia ora, amico mio! Con quell’atteggiamento non arriverai mai lontano. E se mi avessi portato un tale artefatto, ti avrei pagato trecento dobloni. Vuoi sapere perché? Perché è un’antichità, un tesoro storico difficile da trovare ai nostri giorni! Tu non capisci, ma già giudichi! \nCon Dio e la Sua Beata Madre come testimoni, l’artiglio del Capo è un pugnale di maestria, le mie fonti dicono che fu di proprietà di Cortés in persona. IL Hernán Cortés! Il leggendario conquistador che rase al suolo Tenochtitlán e catturò l’imperatore degli Aztechi! E tu te ne ridi e dici che è spazzatura comune!\nInoltre, ti ho già detto che non è un pugnale qualunque, è un pugnale incantato! Sei ancora così novizio che non hai visto tutte le meraviglie dei Caraibi? Incantesimi e magie, rituali e maledizioni? Charles, questa è la Nuova Terra, patria dei Maya e degli Aztechi, la cui conoscenza di simili arti diaboliche ha raggiunto altezze per noi cristiani inimmaginabili!\nQuesto pugnale cela poteri nascosti. Ahimè, nessuno sa ancora quali siano. Hai un’occasione unica, incredibile, di scoprire da solo di cosa sia capace, eppure insisti a dire che è “una porcheria” e che il tuo povero vecchio Fadey voleva imbrogliarti!\nSe solo avessi abbastanza denaro per coprire il mio debito con tuo fratello, te lo ricomprerei su due piedi con il tuo spregevole denaro... Questo è un oggetto di grande valore, la cui importanza va ben oltre il semplice denaro, da!";
			link.l1 = "Va bene, va bene, calmati Fadey. Ti credo. I tuoi argomenti sono piuttosto convincenti e l’ardore infuocato che mostri è o prova della tua sincerità oppure della tua impareggiabile furberia.";
			link.l1.go = "vodka_3";
		break;
		
		case "vodka_3":
			dialog.text = "Grazie! Hai fatto bene, Charles, a non prendertela e venire dritto da me per chiedere spiegazioni. Ora spero che la faccenda sia chiusa, sì?";
			link.l1 = "Sì, Monsieur Fadey. Completamente. Ora, vi prego, concedetemi di congedarmi...";
			link.l1.go = "vodka_4";
		break;
		
		case "vodka_4":
			PlaySound("Voice\English\sharlie\Fadey Moskovit-04.wav");
			dialog.text = "Fermati, Charles! Sarò schietto, mi piace il tuo stile. Magari tu ed io potremmo diventare grandi amici, un giorno. E perché non muovere adesso il primo passo verso questa amicizia? Ho due bottiglie di eccellente vodka russa che si stanno rinfrescando nell’acqua di sorgente, giù in cantina. Che ne dici, vogliamo aprirne una e brindare alla salute di tuo fratello?";
			link.l1 = "Hm. Mi rincresce, Monsieur Fadey, ma è già ora che levi l’ancora. Ho una certa fretta, ahimè.";
			link.l1.go = "vodka_no";
			link.l2 = "L'ultima volta mi avevi già offerto e avevo rifiutato... Sarebbe scortese rifiutare due volte. Va bene, Fadey. Ci sto!";
			link.l2.go = "vodka_5";
		break;
		
		case "vodka_no":
			dialog.text = "Peccato. Rispetto alla vodka, il rum è acqua sporca, un brodino da quattro soldi. Ma visto che hai fretta, non ti trattengo oltre. Buona caccia, Charles!";
			link.l1 = "Altrettanto a voi, Monsieur Fadey...";
			link.l1.go = "exit";
		break;
		
		case "vodka_5":
			dialog.text = "Ecco ciò che mi piace sentire! Splendido! Siediti pure e riposa le gambe! Prego, Monsieur, sentiti come a casa mentre vado a prendere la vodka. Oh, quanto mi sono mancati questi pomeriggi in compagnia! Ah, la vodka è fresca come il mare all’alba, ti piacerà, alla salute! Lascia che ti porti anche un po’ di cetriolini e prosciutto affumicato.";
			link.l1 = "...";
			link.l1.go = "vodka_6";
		break;
		
		case "vodka_6":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "bottle";
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "BasTer_houseSp1";
			sld.startLocator = "sit2";
			DoQuestReloadToLocation("BasTer_houseSp1", "sit", "sit2", "Sharlie_DrinkWithFadey");
			NextDiag.CurrentNode = "vodka_7";
		break;
		
		case "vodka_7":
			dialog.text = "";
			link.l1 = "Ohibò... Allora, dimmi, Fadey, c-come diavolo funziona la faccenda? Hic! Ci siamo scolati... d-due bottiglioni di vodka... per la miseria! – tu sembri freddo come il marmo, e io... ebbro come una ciurma in festa. Com’è possibile, eh?";
			link.l1.go = "vodka_8";
		break;
		
		case "vodka_8":
			dialog.text = "Charles, amico mio, rilassati. Che c'entra una puzzola in tutto questo? Abbiamo appena scolato dell’ottima vodka. Fatti una dormita e ti sveglierai pimpante come uno scoiattolo. Anche la testa ti sarà leggera, senza un filo di mal di testa. Vedrai.";
			link.l1 = "S-sì, vodka... è... è davvero magnifica, questa vodka. Non ho mai bevuto nulla di simile.";
			link.l1.go = "vodka_9";
		break;
		
		case "vodka_9":
			dialog.text = "Ah! Hai colto nel segno! Quel tipo di vodka veniva preparato secondo ricette segrete e spedito dalla mia madrepatria, la Russia, e persino laggiù non tutti sanno farla come si deve. Io compro solo il meglio! Proprio come questa qui che tu ed io abbiamo avuto il privilegio di assaggiare.";
			link.l1 = "M-ma dimmi, Fadey: c-come fai a tracannare così tanto e non perdere la testa? C-come ci riesci, eh? S-svelami il trucco. M-magari mi tornerà utile un giorno... Hic!";
			link.l1.go = "vodka_10";
		break;
		
		case "vodka_10":
			dialog.text = "Ah! Ma non puoi certo paragonarti a me, giovane Charles! Guardati, secco come un rametto. E poi non sei abituato ai veri boccali, eh! Ma visto che siamo compagni veri, ti svelerò qualche trucco del vecchio lupo di mare: come tracannare e non pisciarti addosso.";
			link.l1 = "P-per piacere, f-fa'... hic!";
			link.l1.go = "vodka_11";
		break;
		
		case "vodka_11":
			dialog.text = "Ebbene, se vuoi bere e non finire subito sotto il tavolo, devi seguire alcune regole fondamentali. Primo, mai bere a stomaco vuoto. Mangia qualcosa di sostanzioso prima di cominciare la bisboccia.\nSecondo, non dimenticare uno spuntino dopo ogni bicchiere: carne o pesce sono l’ideale, qualcosa di saporito e salato. Terzo, non sciacquare la bocca con la vodka, mandala giù tutta d’un fiato.\nInoltre, un piccolo – non più di mezzo boccale – sorso prima del pasto principale prepara il corpo a ricevere carichi pesanti di liquore. Non esagerare col primo assaggio, altrimenti l’effetto sarà l’opposto e ti demolirai ancora prima di mollare gli ormeggi.\nInfine, la disciplina è tutto: allenati regolarmente a bere dosi moderate di rum o altro spirito e diventerai più resistente alle sue insidie.";
			link.l1 = "Hm-mm... C-così si fa, eh! Prometto che... hic!.. mi ricorderò tutte le tue istru-zioni, Fadey. G-grazie. E ora penso proprio che mi convenga darmi al sonno, ché non mi sento affatto in forma in questo momento.";
			link.l1.go = "vodka_12";
		break;
		
		case "vodka_12":
			dialog.text = "Riposa un po', Charles. È stata una bella serata, tu ed io! Che la fortuna ti assista nella caccia!";
			link.l1 = "A-a-addio, Fadey! Io vado da... hic! ...il Donatore di Desideri!";
			link.l1.go = "vodka_13";
		break;
		
		case "vodka_13":
			DialogExit();
			sld = ItemsFromID("potionrum");
			sld.shown = false;
			sld = ItemsFromID("lcheer");
			sld.shown = false;
			pchar.questTemp.CanDrink = true; // Шарль теперь знает секреты выпивки, это ему потом пригодится
			LAi_SetSitType(npchar);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			NextDiag.CurrentNode = "First time";
		break;
		
		case "trial":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
			pchar.quest.Sharlie_TrialOver.over = "yes"; //снять таймер
			dialog.text = "Come, ha davvero detto che ti avrei dato una mano?";
			link.l1 = "Beh, più o meno. Mi aiuterai, tu che sei fratello del mio vecchio amico? Non ti sto mica chiedendo l’elemosina come un pidocchioso. Ti chiedo solo di darmi una chance per farmi qualche doblone.";
			link.l1.go = "trial_1";
		break;
		
		case "trial_late":
			dialog.text = "Oh Charles! Sei in ritardo. Se fossi arrivato prima, avrei avuto qualcosa di giusto per te, ma ora – pazienza. Non ti preoccupare, gironzola per le città, parla con la gente. C’è un mare di faccende da sbrigare ai Caraibi.";
			link.l1 = "Capisco, che peccato. Addio!";
			link.l1.go = "trial_late_1";
		break;
		
		case "trial_late_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Trial");
		break;

		case "trial_1":
			dialog.text = "Hm. No, non ti rifiuterò, ovviamente. Se vuoi sfamare un uomo, non dargli un pesce, ma una canna da pesca, non è vero, Monsieur de Maure? Quindi ti serve un impiego... Semplice. Parlerò con un mio conoscente, ti raccomanderò. Il resto dipenderà solo da come te la caverai con l’incarico.";
			link.l1 = "Magnifico. Con chi devo parlare?";
			link.l1.go = "trial_2";
		break;
		
		case "trial_2":
			dialog.text = "Passa al negozio domani. Un tale di nome Gerard LeCroix ti aspetterà lì. Avrà del lavoro per te. Resterà in questa colonia solo fino a domani sera. Fai in fretta e svolgi il compito come si deve. Non farmi fare brutta figura.";
			link.l1 = "Affare fatto. Grazie, Fadey!";
			link.l1.go = "trial_3";
		break;
		
		case "trial_3":
			DialogExit();
			SetFunctionTimerCondition("Trial_StartLine", 0, 0, 1, false); // таймер
			pchar.questTemp.Trial = "start";
			AddQuestRecord("Trial", "1");
		break;
		// belamour legendary edition пиратская линейка -->
		case "Slaves":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "Ah, come posso aiutarti, amico mio?";
			link.l1 = "Fadey, ascolta, ho davvero bisogno di comprare cinquanta schiavi dai contrabbandieri. Il problema è che per loro sono uno sconosciuto e mi serve che tu mi presenti. Senza di te, non mi daranno nemmeno retta, e si tratta della vita o della morte di una persona assai importante.";
			link.l1.go = "Slaves_1";
		break;
		
		case "Slaves_1":
			dialog.text = "Oh ho! Allarghi i tuoi affari, vedo! Che bel colpo! Ti darò una mano, caro amico. Ma come ben sai, non lavoro per aria. Ci vorranno 150 dobloni d’oro per persuadere il venditore delle tue nobili intenzioni nell’acquisto dei negri e, ovviamente, qualcosa in più per il mio faticoso impegno...";
			if(PCharDublonsTotal() >= 150)
			{
				link.l1 = "Non mi aspettavo di meno, Monsieur Fadey! Ecco il vostro oro.";
				link.l1.go = "Slaves_2";
			}
			else
			{
				link.l1 = "Vado subito dall’usuraio! Tieni duro, Monsieur Fadey, torno tra un baleno!";
				link.l1.go = "exit";
				pchar.questTemp.Mtraxx.GiveMeSlaves = "FindGold"; 
			}
			
			link.l2 = "Fadey, mi pare d’aver trovato una soluzione e non m’occorrono più i negri. Perdonami. Ci si rivede!";
			link.l2.go = "Slaves_3";
		break;
		
		case "Slaves_2":
			RemoveDublonsFromPCharTotal(150);
			pchar.questTemp.Mtraxx.GiveMeSlaves = "kapster";
			locations[FindLocation("Shore29")].DisableEncounters = true; //энкаутеры закрыть
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1 = "Hour";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1.start.hour = 22.00;
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l1.finish.hour = 23.00;
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2 = "Timer";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l2.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l3 = "location";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.win_condition.l3.location = "Shore29";
			pchar.quest.Mtraxx_GiveMeSlavesKapster.function = "MtraxxGiveMeSlavesKapsterInShore"; // прибыли
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1 = "Timer";
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.hour  = 23.0; // не пришли, значит гудбай
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Mtraxx_GiveMeSlavesKapster_Late.function = "MtraxxGiveMeSlavesKapsterInShoreLate"; // опоздание
			AddQuestRecord("Roger_3", "23");
			dialog.text = "Eccellente, amico mio. Ma se cerchi di prendermi in giro con la scusa di questo acquisto e le tue intenzioni sono farlocche, mi farai andare su tutte le furie. Non vorrai certo questo, vero? Domani, alle dieci, al tramonto, sulla spiaggia di Capster: ti fisso un incontro, non farmi lo scherzo di tirarti indietro.";
			link.l1 = "Non hai nulla da temere, tornerò per la merce.";
			link.l1.go = "exit";
		break;
		
		case "Slaves_3":
			DialogExit();
			AddQuestRecord("Roger_3", "22");
			pchar.questTemp.Mtraxx.GiveMeSlaves = "WithoutSlaves";
		break;
		
		case "pistols":
			DelMapQuestMarkCity("baster");
			DelLandQuestMark(npchar);
			dialog.text = "Ciao ciao! Dimmi, buon uomo, quale vento ti porta nella mia umile dimora?";
			link.l1 = "Ho bisogno di armi. I mercanti locali non riescono a racimolare la quantità che mi serve, ma credo che tu possa darmi una mano.";
			link.l1.go = "pistols_1";
		break;
		
		case "pistols_1":
			dialog.text = "Prima di tutto, mio caro amico, dimmi esattamente di che cosa hai bisogno. Poi ti dirò senza tanti giri di parole se posso darti una mano.";
			link.l1 = "Mi servono trenta pistole da soldato, due moschetti a miccia, settanta cartucce per loro e novanta pozioni curative.";
			link.l1.go = "pistols_2";
		break;
		
		case "pistols_2":
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves"))
			{
				if(pchar.questTemp.Mtraxx.GiveMeSlaves == "Deal" || pchar.questTemp.Mtraxx.GiveMeSlaves == "WithoutSlaves")
				{
					dialog.text = pchar.name+", mi stai facendo paura. Prima cinquanta negri, poi le armi. Vuoi forse scatenare una rivolta di schiavi, amico mio?";
					link.l1 = "Molto sveglio, Fadey. Come ti ho già detto, tutto questo serve a salvare una persona di gran conto. Non temere, la tireremo fuori dalle grinfie degli spagnoli, così la tua reputazione qui resterà intatta.";
					link.l1.go = "pistols_3";
					break;
				}
			}
			dialog.text = "È un sollievo sentirlo. Posso dare una mano.";
			link.l1 = "Mi fa piacere sentirlo. Quanto vuoi?";
			link.l1.go = "pistols_4";
		break;
		
		case "pistols_3":
			dialog.text = "Sono lieto che tu ti sia spiegato. E se davvero si tratta di una faccenda con gli Spagnoli, allora ti darò una mano. Ma se scopro che mi hai preso in giro, ti giuro che sarò furibondo.";
			link.l1 = "Abbi un po’ di fiducia in me, Fadey. Quanto vuoi?";
			link.l1.go = "pistols_4";
		break;
		
		case "pistols_4":
			dialog.text = "Bene, dunque... pistole e un paio di moschetti, con polvere da sparo e palle per ciascuno... Dunque... non posso promettere che troverò proprio tutto quello che hai chiesto, ma farò il possibile. Intanto, mi serve un acconto di 40.000 pesos, oppure 300 dobloni se preferisci.";
			if(PCharDublonsTotal() >= 300)
			{
				link.l1 = "Prendi i dobloni, Fadey. Guarda caso, ne ho un po’ addosso proprio adesso.";
				link.l1.go = "pistols_4D";
			}
			if(sti(Pchar.money) >= 40000)
			{
				link.l2 = "Tutti i miei dobloni sono finiti, prendi i pesos, Fadey.";
				link.l2.go = "pistols_4P";
			}
			if(PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000) // возможность найти без отказа
			{
				link.l3 = "Devo parlare col mio banchiere. Torno subito!";
				link.l3.go = "exit";
				pchar.questTemp.Mtraxx.MagicBox = "FindMoney";
			}
			link.l4 = "Perdonami, Fadey, ma non posso permettermelo. Cercherò di arrangiarmi da solo. Ci vediamo!";
			link.l4.go = "pistols_x";
		break;
		
		case "pistols_4D":
			SetFunctionTimerCondition("Mtraxx_MagicBoxready", 0, 0, 1, false);
			RemoveDublonsFromPCharTotal(300);
			pchar.questTemp.Mtraxx.MagicBox = "Tomorow";
            dialog.text = "Vieni domani, "+pchar.name+", e ti procurerò il materiale che ti serve.";
			link.l1 = "Allora non ti intralcerò. Ci vediamo domani!";
			link.l1.go = "exit";
		break;
		
		case "pistols_4P":
			AddMoneyToCharacter(pchar, -40000);
			SetFunctionTimerCondition("Mtraxx_MagicBoxready", 0, 0, 1, false);
            pchar.questTemp.Mtraxx.MagicBox = "Tomorow";
            dialog.text = "Vieni domani, "+pchar.name+", e ti procurerò il materiale che ti serve.";
			link.l1 = "Allora non ti intralcio. Ci vediamo domani!";
			link.l1.go = "exit";
		break;
		
		case "pistols_X":
			DialogExit();
			DeleteAttribute(pchar,"questTemp.Mtraxx.MagicBox");
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
		break;
		
		case "pistols_5":
			dialog.text = "Ebbene, figliolo, ho avuto la fortuna di trovare tutto ciò che volevi, e in tempi così stretti. Dovresti essermene grato! Ora, il saldo finale. Dammi esattamente la stessa somma che mi hai dato come acconto, e prendi le tue armi.";
			if(PCharDublonsTotal() >= 300)
			{
				link.l1 = "Prendi 300 dobloni. Farò portare le armi alla mia nave dai miei uomini. Cosa farei senza di te, Fadey? Non hai idea di quanto mi hai tirato fuori dai guai!";
				link.l1.go = "pistols_5D";
			}
			if(sti(Pchar.money) >= 40000)
			{
				link.l2 = "Prendi 40.000 pesos. Farò portare le armi sulla mia nave dai miei uomini. Che farei senza di te, Fadey? Non hai idea di quanto mi hai tirato fuori dai guai!";
				link.l2.go = "pistols_5P";
			}
			if(PCharDublonsTotal() < 300 || sti(Pchar.money) < 40000) // возможность найти без отказа
			{
				link.l3 = "Ebbene, maledizione, come ho fatto a scordarmi dei soldi? Tornerò presto.";
				link.l3.go = "exit";
				pchar.questTemp.Mtraxx.MagicBox = "FindMoney";
			}
			link.l4 = "Perdonami, Fadey, sono al verde. Tieni pure l’anticipo, spero basti a coprire le tue spese con quest’affare, e cercherò di cavarmela da solo. Ci si rivede!";
			link.l4.go = "pistols_x";
		break;
		
		case "pistols_5D":
			Log_Info("Fadey's weapons are loaded on the ship");
			RemoveDublonsFromPCharTotal(300);
			pchar.questTemp.Mtraxx.MagicBox = "Full";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
            dialog.text = "Aiutare chi è nel bisogno è un onore. Aiutare chi paga è un piacere. La prossima volta che passi per Basse-Terre, non mancare di venirmi a salutare.";
			link.l1 = "È assurdo – essere a Basse-Terre e non vedere il mio amico Fadey! Fino alla prossima volta!";
			link.l1.go = "exit";
		break;
		
		case "pistols_5P":
			Log_Info("Fadey's weapons are loaded on the ship");
			AddMoneyToCharacter(pchar, -40000);
			pchar.questTemp.Mtraxx.MagicBox = "Full";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves")) DeleteAttribute(pchar,"questTemp.Mtraxx.GiveMeSlaves");
            dialog.text = "Aiutare chi è nel bisogno è un onore. Aiutare chi paga è un vero piacere. La prossima volta che passi per Basse-Terre, non scordarti di venire a salutarmi.";
			link.l1 = "Che assurdità - essere a Basse-Terre e non vedere il mio amico Fadey! Alla prossima!";
			link.l1.go = "exit";
		break;
		// <-- legendary edition

		case "guardoftruth":
			dialog.text = "Ebbene, chi mai dubiterebbe che tu sia qui per affari, amico mio! Sfortunatamente niente acquavite da offrirti ora, l'ho scolata tutta. Dimmi, in che guai ti sei cacciato stavolta?";
			link.l1 = "Un certo corsaro offrì alla parrocchia locale una croce pettorale d’oro con lapislazzuli in cambio dell’assoluzione dei suoi peccati. Un oggetto raro e di gran valore. Il guaio è che questa croce fu rubata a un’altra parrocchia. E durante il furto, ammazzarono pure un prete.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "O Vergine Immacolata! Ma guarda un po’!";
			link.l1 = "Aye. Rappresento i parrocchiani derubati e cerco di restituire la croce ai suoi veri padroni.";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Un gesto nobile, assai devoto. Cerchi forse di guadagnarti il favore dell’Onnipotente?";
			link.l1 = "Ma il prete locale si rifiuta di restituirmela, nonostante tutto ciò che gli ho raccontato. Non capisco. Come si può tranquillamente lasciare una croce rubata, macchiata dal sangue d’un innocente, nella Casa del Signore? È una bestemmia!";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Ebbene, tecnicamente ogni calice consacrato reca il sangue dell’Innocente Cristo... ma sto divagando. Immagino che tu voglia il mio aiuto, vero?";
			link.l1 = "Lo so! Hai una certa influenza a Basse-Terre. Godi di rispetto, quindi magari il prete darà retta alle tue parole.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = ""+pchar.name+", hai già raccontato tutta la storia di questa croce rubata al nostro prete?";
			link.l1 = "Ma certo! Ho fatto appello ai suoi sentimenti religiosi, alla solidarietà cristiana, perfino a quella sua maledetta coscienza per l’amor di Dio, ma lui ha tappato le orecchie.";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Hm... Hai provato con qualche altro trucco per convincerlo?";
			link.l1 = "Vuoi che lo corrompa? Non intendo ungere la mano a un prete. Se fosse un banchiere, un mercante, o persino un governatore, magari risolverei la faccenda così, ma un prete no!";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Mio caro ingenuo amico, se davvero le orecchie del prete sono sorde ai richiami della coscienza, di certo le sue mani saranno ben pronte ad accogliere l’oro... O magari il contrario. Ti darò una mano, ché lasciare un bottino così maledetto qui porterà solo guai peggiori in futuro. Tuttavia, la faccenda avrà il suo prezzo."link.l1 ="Perché non mi stupisce? Quanto stavolta?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Passa domani, "+pchar.name+", Non posso ancora dire il prezzo. Ma quella croce rubata sarà tua, puoi contarci.";
			link.l1 = "Va bene, Fadey, non ti scoccerò oltre, allora. Ci vediamo domani!";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			DialogExit();
			pchar.questTemp.Guardoftruth.Baster_church = "wait";
			SetFunctionTimerCondition("GuardOT_FadeyTimer", 0, 0, 1, false);
			AddQuestRecord("Guardoftruth", "29");
		break;
		
		case "guardoftruth_9":
			dialog.text = "Come promesso, ho la croce. Quanto ai dettagli... ah, lasciamo perdere... tutte sciocchezze perdonate dal sangue prezioso del nostro Salvatore.";
			link.l1 = "Quanto ti devo?";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "Duecentocinquanta dobloni. Per coprire le mie spese, e naturalmente non disdegnerei qualche moneta in più per il mio nobile aiuto...";
			if(PCharDublonsTotal() >= 250) // belamour legendary edition
			{
				link.l1 = "Aye aye, Monsieur Fadey. Ecco il vostro oro.";
				link.l1.go = "guardoftruth_11";
			}
			else
			{
				link.l1 = "Devo recuperare l’oro dalla mia cabina. Torno subito.";
				link.l1.go = "exit";
				npchar.quest.utensil = "true";
			}
		break;
		
		case "guardoftruth_11":
			DeleteAttribute(npchar, "quest.utensil");
			dialog.text = "Va bene. Ecco la croce rubata.";
			link.l1 = "Grazie, Fadey. Non puoi nemmeno immaginare quanto tu abbia fatto per me!";
			link.l1.go = "guardoftruth_12";
		break;
		
		case "guardoftruth_12":
			RemoveDublonsFromPCharTotal(250); // belamour legendary edition
			GiveItem2Character(pchar, "jewelry34");
			//Log_Info("You've received a golden cross with lazurite");
			PlaySound("interface\important_item.wav");
			dialog.text = "Sono sempre lieto d’aiutare un amico di buon cuore – e soprattutto generoso. Passa più spesso, chissà che non ci scoli una bottiglia di vodka, quando me la spediranno dalla madrepatria.";
			link.l1 = "Con gran piacere!";
			link.l1.go = "guardoftruth_13";
		break;
		
		case "guardoftruth_13":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Guardoftruth.Baster_church");
			AddQuestRecord("Guardoftruth", "30");
		break;
		
		case "guardoftruth_14":
			dialog.text = "Ebbene, ebbene, il mare non t’ha ancora inghiottito! Racconta, dunque. Quali sventure ti han portato stavolta alla mia porta?";
			link.l1 = "Non so se chiamarle sventure o altro, ma eccomi qui. Fadey, il primo giorno che ci siamo incontrati mi hai dato un pugnale raro, l'Artiglio del Capo. Ora so che prima apparteneva a un uomo chiamato Archibald Calhoun. Ti prego, dimmi tutto ciò che sai su quest’uomo.";
			link.l1.go = "guardoftruth_15";
		break;
		
		case "guardoftruth_15":
			dialog.text = "Niente ti sfugge, "+pchar.name+"   Vedi tutto a occhio nudo, proprio come tuo fratello. Sì, ho vinto questo pugnale a dadi da Calhoun. Chi sia? Non ne ho la minima idea. Ci siamo incontrati per caso in taverna, abbiamo scambiato due parole, bevuto qualcosa, e lui ha cominciato a raccontarmi di certi peccati del passato che gli pesavano sull’anima...";
			link.l1 = "E che sei, il suo confessore? Che peccati?";
			link.l1.go = "guardoftruth_16";
		break;
		
		case "guardoftruth_16":
			dialog.text = "Archibald era divorato dal ricordo di un uomo che, per colpa sua, fu torturato a morte dall’Inquisizione insieme ad altre anime innocenti che aveva mandato all’altro mondo. Continuava a chiamarsi Giuda. Sosteneva che Dio lo stesse castigando per i suoi peccati e che l’Inquisizione gli desse la caccia.\nHa detto che l’inquisitore spagnolo Vincento in persona lo vuole morto e ha mandato mercenari a braccarlo per tutti i Caraibi. Poi il rum ha preso il sopravvento sul buonsenso e ci siamo messi a giocare d’azzardo per questo vecchio pugnale.";
			link.l1 = "È tutto qui? Non l’hai più rivisto?";
			link.l1.go = "guardoftruth_17";
		break;
		
		case "guardoftruth_17":
			dialog.text = "Ma certo che no, ormai ha tirato le cuoia. Una ciurma di miserabili filibustieri ha mandato il suo fluyt a fare compagnia a Davy Jones, e tutta la ciurma dritta nelle fauci di Mictlantecuhtli. A dire il vero, girava voce che li avessero assaliti dei professionisti travestiti da pirati... uomini dell’Inquisizione. Pare che padre Vincento non manchi mai la sua preda, così dicono.";
			link.l1 = "Archibald Calhoun è vivo. L’ho visto di recente insieme a un certo William Paterson. Ora fa il suo primo ufficiale.";
			link.l1.go = "guardoftruth_18";
		break;
		
		case "guardoftruth_18":
			dialog.text = "Oh ho, che sorpresa! Almeno Archibald può tirare il fiato all’ombra del Capitano Paterson. Sta in buona compagnia. Gli spagnoli temono Patterson come la peste. Non oseranno tramare contro Archibald finché resta sotto la sua protezione.";
			link.l1 = "Conosci Paterson?";
			link.l1.go = "guardoftruth_19";
		break;
		
		case "guardoftruth_19":
			dialog.text = "Chi non conosce William Paterson!? È un novellino dei Caraibi, proprio come te. E proprio come te s’è già fatto una fama che fa tremare i ponti. Il signor Patterson è il più fidato compare del colonnello Fox e un pezzo grosso anche per Lord Windsor in persona, il Governatore Generale di tutte le colonie inglesi nei Caraibi. Si fa spesso vedere al palazzo del governatore a Port Royal, in Giamaica.";
			link.l1 = "Capito. Grazie per l'informazione, Fadey!";
			link.l1.go = "guardoftruth_20";
		break;
		
		case "guardoftruth_20":
			dialog.text = "Oh, non farci caso, compare. Passa a trovarmi quando vuoi! Buona caccia!";
			link.l1 = "Sicuramente!";
			link.l1.go = "guardoftruth_21";
		break;
		
		case "guardoftruth_21":
			DialogExit();
			pchar.questTemp.Guardoftruth.Archy = "portroyal";
			AddQuestRecord("Guardoftruth", "62");
			// эскадру Патерсона - в Порт-Рояль
			Group_SetAddress("Willy_group", "Jamaica", "quest_ships", "quest_ship_1");
			pchar.quest.GuardOT_jamaica.win_condition.l1 = "location";
			pchar.quest.GuardOT_jamaica.win_condition.l1.location = "Jamaica";
			pchar.quest.GuardOT_jamaica.function = "GuardOT_PortRoyalArrive";
		break;
		
		// персидские клинки
		case "persian":
			dialog.text = "Diamo un'occhiata, "+pchar.name+"... Sì! È proprio uno di quelli! Bravo figliolo, m'hai rallegrato la giornata! Dove l'hai scovato?";
			link.l1 = "Non importa. Quel che conta è che sia tornato a te.";
			link.l1.go = "persian_1";
		break;
		
		case "persian_1":
			dialog.text = "Ti pagherò profumatamente per un’indagine accurata. Trecento dobloni d’oro dovrebbero bastare a ricompensare il tuo disturbo...";
			link.l1 = "Mi paghi con quei dobloni che mi hai già spillato, eh? Beh, non che mi lamenti. Ecco la tua sciabola.";
			link.l1.go = "persian_2";
		break;
		
		case "persian_2":
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "one";
			dialog.text = "Grazie, amico mio! Ti ringrazio per la spada e per le tue parole pungenti. Hai più saggezza di quanto sembri, "+pchar.name+", ma i legami d’amicizia valgono più dell’oro. A proposito di oro, - ti pago fino all’ultimo. Prendi pure i tuoi dobloni.";
			link.l1 = "Grazie.";
			link.l1.go = "persian_3";
		break;
		
		case "persian_3":
			TakeNItems(pchar, "gold_dublon", 300);
			//Log_Info("You've received 300 doubloons");
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = "E parlando dei legami d’amicizia, specialmente il tuo e il mio, "+pchar.name+"Ho qualcosa che ti interesserà parecchio.";
			link.l1 = "Fammi indovinare, ancora acquavite?";
			link.l1.go = "persian_4";
		break;
		
		case "persian_4":
			dialog.text = "Ah! La vodka è buona, ma non è l’unica cosa per cui la mia patria è famosa. C’è un materiale speciale che solo la Russia produce. Lo faccio arrivare qui dai miei contatti per commerciare. Ogni capitano lo desidera, perché migliora qualsiasi nave. Parlo delle funi di canapa\nFuni immuni all’umidità e al sale del mare. Si dice che sia il miglior materiale per il sartiame\nOgni mese, me ne arriva una certa quantità da Reval. Di solito, a metà mese ho qualche centinaio di gomene nel mio magazzino. Quindi, "+pchar.name+", I am offering to sell you a batch of fifty coils. Ten doubloons a coil\nI have only two terms: first, I will keep your ropes until the 20th of every month; second, you can buy only the whole batch. Fifty coils for five hundred doubloons. Confidentially speaking, "+pchar.name+", they say that there are certain places where you can resell those ropes for a much greater price, but what do I know!\I am completely satisfied with the current state of my operation and don't need to find resellers myself. If you find a good merchant, you can turn a fine profit.";
			link.l1 = "Capito. È un’offerta da non perdere, Fadey! Credo proprio che accetterò la tua proposta. Quindi, ogni ventesimo giorno del mese, cinquecento dobloni per cinquanta pezzi?";
			link.l1.go = "persian_5";
		break;
		
		case "persian_5":
			AddQuestRecordInfo("Unique_Goods", "2");
			dialog.text = "Va’. Raccogli il tuo acquisto. Ma aspetta, aspetta, caro! Oltre questa scimitarra, che mi hai restituito per pura bontà d’animo, ce n’erano altre due. Ti supplico, se mai le trovi, riportamele e ti pagherò più che generosamente per la loro restituzione.";
			link.l1 = "Certamente, Fadey. Se li trovo, li riporterò indietro.";
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = "Buone notizie per te. Ho rimediato un altro shamshir persiano.";
				link.l2.go = "persian_6";
			}
			npchar.quest.ropes = "true";
		break;
		
		case "persian_6":
			dialog.text = "Oh, mio caro amico! Mi hai asciugato le lacrime, per mille sabbie! Fammi vedere... Ah! Eccola qui, la mia preziosa scimitarra! Tieni, come promesso, trecento dobloni di ricompensa.";
			link.l1 = "Grazie!";
			link.l1.go = "persian_7";
		break;
		
		case "persian_7":
			TakeNItems(pchar, "gold_dublon", 300);
			//Log_Info("You've received 300 doubloons");
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			pchar.questTemp.Persian = "two";
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 2);
			dialog.text = "Accetta la mia gratitudine e questo dono modesto ma assai utile. A me non serve, ma tu – o il tuo carpentiere di bordo – lo troverete prezioso.\nGuarda che anello raffinato! Ora è tuo. Ma non è un semplice anello qualunque: è incantato. Facilita il lavoro con il legno e le riparazioni della nave. Molti maestri d'ascia ne andrebbero matti, ma io lo serbavo per un’occasione speciale. Prendilo, amico mio, possa alleggerire il fardello sulle tue spalle!";
			link.l1 = "Porti davvero con te un sacco di gingilli curiosi. Grazie, Fadey!";
			link.l1.go = "persian_8";
		break;
		
		case "persian_8":
			GiveItem2Character(pchar, "talisman7");
			//Log_Info("You've received the Scarab amulet");
			PlaySound("interface\important_item.wav");
			dialog.text = "Rimane solo una scimitarra della mia collezione perduta da ritrovare. Conto su di te, "+pchar.name+", e con un po' di fortuna. Se lo trovi, non esitare a tornare subito da me.";
			link.l1 = "Senz'altro! A presto...";
			link.l1.go = "exit";
			if (CheckNCountPersian() > 0)
			{
				link.l2 = "Perché dovrei affrettarmi? La spada è con me.";
				link.l2.go = "persian_9";
			}
		break;
		
		case "persian_9":
			dialog.text = "Oh, grazie al cielo che ho chiesto aiuto proprio a te, "+pchar.name+"Sei un uomo miracoloso, amico mio! Fammi vedere... Ohh! È lei, è proprio lei. Mia adorata! Che bellezza! Mille grazie, brav'uomo, mi inchino davanti a te! Ecco, ecco il tuo denaro. Quattrocento dobloni, neanche un soldo di meno! Non sarò certo tirchio.";
			link.l1 = "Grazie, Fadey. È stato un piacere dare una mano.";
			link.l1.go = "persian_10";
		break;
		
		case "persian_10":
			TakeNItems(pchar, "gold_dublon", 400);
			//Log_Info("You've received 400 doubloons");
			sTemp = CheckNIdentifyPersian();
			RemoveItems(pchar, sTemp, 1);
			PlaySound("interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 500);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			ChangeCharacterNationReputation(pchar, FRANCE, 3);
			Achievment_Set("ach_65");
			dialog.text = "La mia collezione di sciabole è finalmente di nuovo al completo! Nessun cane oserà più metterci le mani sopra, te lo garantisco! Per te, bravo ragazzo, ho una ricompensa davvero speciale. Fra due settimane, un mercante mi porterà da Europa una corazza da schermidore di gran pregio. Ordinata da un nobilotto, è un pezzo raro come pochi.\nSe ti interessa, posso cedertela per sole settecento doppie d’oro. Al nobile racconterò che la merce è andata persa durante il viaggio.";
			link.l1 = "Che c’è di tanto speciale in quest’armatura?";
			link.l1.go = "persian_11";
		break;
		
		case "persian_11":
			dialog.text = "È comodissimo e resistente, eppure protegge quanto una corazza di ferro. E guarda che stile! Torna tra un paio di settimane per dargli un’occhiata. Ma non tardare più di un mese, altrimenti lo rivendo al committente.";
			link.l1 = "Affare fatto. Passerò da casa tua tra due settimane.";
			link.l1.go = "persian_12";
		break;
		
		case "persian_12":
			DialogExit();
			pchar.questTemp.Persian = "time";
			SetFunctionTimerCondition("Persian_CirassLamport", 0, 0, 14, false); // таймер
		break;
		
		case "persian_13":
			dialog.text = "Sì, è già stato consegnato e ti sta aspettando. Hai portato il denaro?";
			if(PCharDublonsTotal() >= 700) // belamour legendary edition
			{
				link.l1 = "Sì. Ecco settecento dobloni.";
				link.l1.go = "persian_14";
			}
			else
			{
				link.l1 = "Maledizione. Ho dimenticato i soldi sulla nave. Li porto subito!";
				link.l1.go = "exit";
			}
		break;
		
		case "persian_14":
			RemoveDublonsFromPCharTotal(700); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "cirass8"); 
			//Log_Info("You've received wicker armour");
			AddCharacterExpToSkill(pchar, "Sneak", 300);
			dialog.text = "Sì, buon uomo! Ecco, prenda. Quest’armatura di vimini Le sarà utilissima, glielo garantisco. Non troverà niente di simile in tutti i Caraibi!";
			link.l1 = "Sì, vedo bene. Grazie! Non vedo l’ora di provarlo addosso...";
			link.l1.go = "persian_15";
		break;
		
		case "persian_15":
			dialog.text = "Perché aspettare? Avanti, fammi vedere come ti sta.";
			link.l1 = "Sarà fatto. A più tardi, Monsieur Fadey!";
			link.l1.go = "persian_16";
		break;
		
		case "persian_16":
			DialogExit();
			pchar.questTemp.Persian = "end";
			pchar.quest.Persian_CirassLamportOver.over = "yes"; //снять прерывание
		break;
		
		// торговля канатами
		case "ropes":
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes"))
			{
				dialog.text = "Entra pure, caro amico. La mercanzia è pronta per te. 2125 dobloni per duecentocinquanta pezzi.";
				if (PCharDublonsTotal() >= 2125)
				{
					link.l1 = "Tutto come d'accordo. Prendi i dobloni.";
					link.l1.go = "ropes_1";
				}
				else
				{
					link.l1 = "Lasciami solo prendere le monete dalla mia cabina.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Entra pure, caro amico. La mercanzia ti aspetta, pronta all’acquisto. Cinquecento dobloni per cinquanta pezzi.";
				if (PCharDublonsTotal() >= 500)
				{
					link.l1 = "Tutto come pattuito. Prendi il denaro.";
					link.l1.go = "ropes_1";
				}
				else
				{
					link.l1 = "Lascia solo che prenda le monete dalla mia cabina.";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.FadeyRopes) >= 1 && !CheckAttribute(pchar, "questTemp.FadeyRopesBlock")) // увеличить объём поставок канатами
			{
				link.l4 = "Fadey, potremmo ingrandire un po’ i nostri affari? Son pronto a comprare da te cinque volte più mercanzia! Credo che entrambi ci guadagneremmo assai. Che ne dici?";
				link.l4.go = "UpgradeRopes";
			}
			if(sti(pchar.questTemp.FadeyRopes) >= 1 && CheckAttribute(pchar, "questTemp.FadeyRopesPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок канатами, если в первый раз не принесли
			{
				link.l4 = "Fadey, ho portato il denaro! Tremila dobloni d’oro, come pattuito.";
				link.l4.go = "UpgradeRopes_Agreed";
			}
		break;
		
		case "ropes_1":
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes")) RemoveDublonsFromPCharTotal(2125);
			else RemoveDublonsFromPCharTotal(500); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Piacere di aver fatto affari con te, "+pchar.name+". Ordinerò ai miei uomini di portare le corde sulla tua nave.";
			link.l1 = "Grazie!";
			link.l1.go = "ropes_2";
		break;
		
		case "ropes_2":
			dialog.text = "Se ti servono ancora delle corde, torna tra un mese.";
			link.l1 = "Benissimo, Fadey. A più tardi!";
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.UpgradeRopes")) AddCharacterGoods(pchar, GOOD_ROPES, 250);
			else AddCharacterGoods(pchar, GOOD_ROPES, 50);
			DeleteAttribute(npchar, "quest.ropes");
			SetFunctionTimerCondition("Ropes_FadeyAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 200);
			pchar.questTemp.FadeyRopes = sti(pchar.questTemp.FadeyRopes) + 1; // счётчик покупок
		break;
		
		// уменьшение НЗГ
		case "help":
			if (!CheckAttribute(npchar, "quest.relation_info"))
			{
				dialog.text = "Cosa posso fare per te, caro amico mio?";
				link.l1 = "Sei un uomo di peso, Fadey. Amico del governatore, e, a dar retta alle chiacchiere, con agganci pure a corte. Potresti forse perorare la mia causa dinanzi alle autorità, se mai dovessi ficcarmi nei guai con la legge?";
				link.l1.go = "relation_info";
				break;
			}
			dialog.text = "In che modo posso esserti d’aiuto, amico mio?";
			if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l1 = "Ho dei guai con le autorità inglesi.";
				link.l1.go = "relation";
				pchar.GenQuest.FadeyNation = ENGLAND;
			}
			if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0 && !CheckAttribute(npchar, "quest.relation"))
			{
				link.l2 = "Ho avuto dei guai con le autorità francesi.";
				link.l2.go = "relation";
				pchar.GenQuest.FadeyNation = FRANCE;
			}
			if (ChangeContrabandRelation(pchar, 0) <= 5)
            {
                Link.l5 = "Ho un grosso grattacapo con quei contrabbandieri.";
				Link.l5.go = "contraband";
            }
			link.l9 = "Scusami, penso di potermela cavare da solo.";
			link.l9.go = "exit";
		break;
		
		case "relation_info":
			dialog.text = "Oh ho ho, mio buon uomo, chi mai ti ha raccontato simili fandonie? Tutti mentono, ragazzo mio. Ma visto che sei il fratello di Michel e un mio buon compare, posso tentare di sistemare la faccenda per te. Posso solo intercedere presso le autorità inglesi o francesi, sia chiaro, le mie conoscenze hanno pur sempre dei limiti. Con gli spagnoli e gli olandesi non ci faccio affari.\nTi avverto anche che la mia influenza basta giusto a tirarti fuori dai guai da quattro soldi. Posso convincerli a chiudere un occhio su qualche marachella o a placare uno scatto d’ira, ma non venirmi a chiedere miracoli se ti metti a scatenare guerre!\nE bada bene: posso rabbonire una sola nazione alla volta, Francia o Inghilterra, mica posso dividermi in due come pane raffermo. E, si capisce, servirà anche qualche moneta sonante per ungere le ruote. Se le mie condizioni ti vanno a genio, non esitare a bussare alla mia porta.";
			link.l1 = "Grazie, Fadey. Me ne ricorderò.";
			link.l1.go = "exit";
			npchar.quest.relation_info = "true";
		break;
		
		case "relation":
			rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.FadeyNation), 0));
			if (rate <= 10)
			{
				dialog.text = "Ma certo. Le tue imprese – o meglio, le tue disgrazie – sono già leggenda. Posso sistemare il tuo piccolo guaio, sai? Con la giusta dose di dobloni, tutto si aggiusta in queste acque. Trecento dobloni d’oro e ti tiro fuori dalla pentola del diavolo.";
				if (PCharDublonsTotal() >= 300) // belamour legendary edition
				{
					link.l1 = "Magnifico! Ecco l’oro.";
					link.l1.go = "agree";
					iTotalTemp = 300;
				}
				link.l2 = "Allora è proprio il momento giusto per andare a prendere quelle monete.";
				link.l2.go = "exit";
			}
			else
			{
				if (rate <= 20)
				{
					dialog.text = "Ma certo. Ho sentito parlare delle tue imprese – o meglio, disavventure. Posso sistemare il tuo problemino, sai? Un po’ d’oro al momento giusto nelle mani giuste e il gioco è fatto. Seicento dobloni d’oro e ti tiro fuori dal pentolone.";
					if (PCharDublonsTotal() >= 600) // belamour legendary edition
					{
						link.l1 = "Magnifico! Ecco l’oro.";
						link.l1.go = "agree";
						iTotalTemp = 600;
					}
					link.l2 = "Allora è proprio il momento giusto per me di andare a prendere le monete.";
					link.l2.go = "exit";
				}
				else
				{
					dialog.text = "Ehi, ti sei cacciato proprio in un bel guaio! Non posso proprio liberarti da всей этой кутерьмы, ma posso almeno attutire il colpo di tuono che sta per abbattersi sul tuo capo peccatore. E poi, in ogni momento, possiamo riprovare con una bustarella, se hai monete e voglia. Settecento dobloni d’oro ed io comincerò a rabbonire la tempesta che ti si prepara.";
					if (PCharDublonsTotal() >= 700) // belamour legendary edition
					{
						link.l1 = "Sono stufo di quei segugi della corona che mi danno la caccia. Prendi l’oro.";
						link.l1.go = "agree";
						iTotalTemp = 700;
					}
					link.l2 = "Allora è proprio il momento giusto per me d’andare a prendere le monete.";
					link.l2.go = "exit";
				}
			}
		break;
		
		case "agree":
			RemoveDublonsFromPCharTotal(iTotalTemp); // belamour legendary edition
			PlaySound("interface\important_item.wav");
			dialog.text = "Va bene, dammi una decina, quindicina di giorni. Nel frattempo fisserò un incontro e sbrigherò un paio di faccende. In due settimane sarà tutto fatto. ";
			link.l1 = "Grazie, Fadey! Ti aspetterò...";
			link.l1.go = "agree_1";
		break;
		
		case "agree_1":
			DialogExit();
			SetFunctionTimerCondition("ChangeNationRelationFromFadeyComplete", 0, 0, 10+rand(5), false);
			pchar.GenQuest.FadeyNation.Rate = abs(ChangeCharacterNationReputation(pchar, sti(pchar.GenQuest.FadeyNation), 0));
			npchar.quest.relation = "true";
		break;
		
		case "contraband":
			dialog.Text = "Perché sei andato a farli incazzare, amico mio? I contrabbandieri non sono i peggiori filibustieri da queste parti, e con loro puoi sbarcare il lunario. Va bene, ti do una mano, so come ammansirli... Ma mi devi settecento dobloni, senza fiatare.";
			if (PCharDublonsTotal() >= 700) // belamour legendary edition
			{
				Link.l1 = "Va bene, Fadey, accetto. Prendi il tuo oro.";
				Link.l1.go = "Contraband_Agreed";
			}
			Link.l2 = "Non ho così tanto oro con me adesso. Tornerò più tardi!";
			Link.l2.go = "exit";
		break;
		
		case "Contraband_Agreed":
			dialog.Text = "Bene, ci penserò io a sistemare la faccenda, non ti crucciare. Torneranno a fare affari con te, proprio come ai vecchi tempi.";
			Link.l1 = "Grazie!";
			Link.l1.go = "exit";
			ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
			RemoveDublonsFromPCharTotal(700); // belamour legendary edition
			PlaySound("interface\important_item.wav");
		break;
		
		case "UpgradeRopes":
			dialog.text = "Ho-ho, vedo che la tua bottega va a gonfie vele e pure la fame cresce! Hai ragione, la nostra merce è pregiata e i prezzi non son esagerati. Ma bada bene, qui ci vogliono investimenti! Un affare del genere esige mano ferma e testa fine, per far girar tutto a dovere.";
			link.l1 = "Mi presenterei forse con una proposta simile senza avere qualche centinaio di dobloni nascosti sotto il giubbotto?";
			link.l1.go = "UpgradeRopes_1";
		break;
		
		case "UpgradeRopes_1":
			dialog.text = "So che hai delle monete nel forziere, e non solo due spicci, scommetto che ce ne stanno almeno cinquanta! Ma il nostro affare non è roba comune – qui non si tratta solo di spostare merci, ma di trovare... diciamo, una via nascosta. Per roba di questa portata, bisogna investire sul serio, non solo pagare, se vuoi farci un guadagno! E per non vedere i tuoi soldi sparire come nebbia al vento. Se sei pronto a separarti da tremila dobloni d’oro, ti do la mia parola che tutto sarà fatto a dovere, come tra vecchi amici, e non ti spennamo sul prezzo.";
			if (PCharDublonsTotal() >= 3000)
			{
				Link.l1 = "Tremila dobloni! Eh, devo ammetterlo, perfino i mercanti più floridi nelle storie più incredibili raramente sentono simile generosità! Pochi hanno il fegato d’investire così lautamente in un’impresa del genere. Ma io, per mia fortuna, sono tra quei pochi. Ecco qui il vostro denaro, monsieur Fadey.";
				Link.l1.go = "UpgradeRopes_Agreed";
			}
			Link.l2 = " Tremila dobloni d’oro! Non sono pronto per una somma simile, Fadey. Purtroppo. Tornerò più tardi.";
			Link.l2.go = "UpgradeRopes_Potom";
			link.l3 = "Tremila, dici? Eh... A dirla tutta, una cifra così merita rispetto per la tua audacia. Ma devo confessare: non fa per me.";
			link.l3.go = "UpgradeRopes_2";
		break;
		
		case "UpgradeRopes_2":
			dialog.text = "Che giravolta! Arrivi con una proposta e subito te ne tiri indietro! Ammetto, sono deluso, ma non lascerò che questo rovini la nostra amicizia. Teniamola come prima: il nostro accordo resta - cinquanta gomene a dieci dobloni l’una, ogni mese, il giorno 20.";
			link.l1 = "Bene che tu mi comprenda, Fadey. Mi piacerebbe anche cambiare idea, ma simili spese son fuori dalla mia portata. Ahimè, le mie risorse qui sono scarse.";
			link.l1.go = "UpgradeRopes_3";
		break;
		
		case "UpgradeRopes_3":
			dialog.text = "Ebbene, se questa è la tua scelta, non c’è altro da dire. Questo non guasterà la nostra amicizia. Passa pure a trovarmi, "+GetSexPhrase("buon messere","bella dama")+".";
			link.l1 = "Addio.";
			link.l1.go = "exit";
			pchar.questTemp.FadeyRopesBlock = true;
		break;
		
		case "UpgradeRopes_Potom":
			DialogExit();
			pchar.questTemp.FadeyRopesBlock = true;
			pchar.questTemp.FadeyRopesPotom = true;
		break;
		
		case "UpgradeRopes_Agreed":
			dialog.text = "Ah, questo sì che è ragionare! Non sei tipo da chiacchiere vuote, tu agisci e basta. Per gente d’affari come te c’è sempre uno sconto a scovare! Quindici per cento su tutte le spedizioni future! Ecco il nostro patto: duecentocinquanta gomene di canapa pronte per te ogni mese. Le ritiri come sempre il venti, pagando duemilacentoventicinque dobloni per tutto, senza resto.";
			link.l1 = "Perfetto, Fadey! Sei dannatamente facile per far affari. Sono certo che il successo ci sorriderà. Fino alla prossima, allora!";
			link.l1.go = "exit";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "2_1");
			pchar.questTemp.UpgradeRopes = true;
			pchar.questTemp.FadeyRopesBlock = true;
			DeleteAttribute(pchar, "questTemp.FadeyRopesPotom");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}