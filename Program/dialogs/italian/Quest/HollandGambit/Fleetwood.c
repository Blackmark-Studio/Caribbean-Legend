// Ричард Флитвуд - английский капитан
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "Start_main")
				{
					dialog.text = "Saluti, capitano! Non lasciarti ingannare dal mio aspetto, sto bene, quasi cieco, ma me la cavo. Permettimi di presentarmi: sono Richard Fleetwood.";
					link.l1 = "Buon giorno, è un piacere far la vostra conoscenza, sono il capitano "+GetFullName(pchar)+".";
					link.l1.go = "First_Task";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "GotoPortoffice")
				{
					if (sti(Pchar.Ship.Type) != SHIP_NOTUSED)
					{
						dialog.text = "Ti ho ordinato di ormeggiare la tua nave. Hai della cera nelle orecchie, perbacco?";
						link.l1 = "Certo che sì. Me ne occupo io.";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "Dunque, sei di nuovo qui. Prendi il comando della 'Valkyrie' – la mia ciurma è già informata dei dettagli – e salpa per Bridgetown. Fai visita a ogni persona d’interesse in città e spargi le chiacchiere di cui abbiamo discusso. Poi preparati all’attacco di quel bastardo. Non cambiare nave né formare uno squadrone, altrimenti fiuterà la trappola e non si farà vedere. \nDevi abbordare la sua nave e portarla a St. John's. È fondamentale che tu trovi il diario di bordo del pirata, è l’unica prova che potremo mai avere del coinvolgimento di Lucas Rodenburg. Sono certo che te la caverai. Che il vento ti sia favorevole, capitano.";
						link.l1 = "Grazie! Porterò a termine il lavoro come abbiamo stabilito.";
						link.l1.go = "First_Task_3";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
					}
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "MirageTake")//а вот теперь начинается перебор кораблей
				{
					pchar.quest.ToAntiguaMirageOver.over = "yes"; //снять таймер
					int iMir = 0;
					int iVal = 0;
					for(i = 0; i < COMPANION_MAX; i++)
					{
						iTemp = GetCompanionIndex(PChar, i);
						if(iTemp > 0)
						{
							sld = GetCharacter(iTemp);
							pchar.questTemp.HWIC.Eng.CompanionIndex = sld.Index;
							if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE)
							{
							iMir = 1;
							RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = 1;//чистый корпус
							SetShipSailsFromFile(sld, "ships/parus_silk.tga");
							SetSailsColor(sld, 0);//белый хлопковый парус
							DeleteAttribute(sld, "ship.sails");//починить паруса
							DeleteAttribute(sld, "ship.masts");//вернуть мачты
							}
							if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA) iVal = 1;
						}
					}//установили признак наличия кораблей в эскадре.
					if (iMir == 1 && iVal == 0)//потеряли Валькирию
					{
						dialog.text = "Sei tornato, capitano... So già tutto del tuo viaggio.";
						link.l1 = "Ah sì? Allora saprai bene che...";
						link.l1.go = "Fleetwood_lostVal";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
					if (iMir == 0 && iVal == 1)//потеряли Мираж
					{
						dialog.text = "Sei tornato, capitano... So già tutto del tuo viaggio.";
						link.l1 = "Ah sì? Allora saprai che...";
						link.l1.go = "Fleetwood_lostMir";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
					if (iMir == 0 && iVal == 0)//а это вообще плохо
					{
						dialog.text = "Sei tornato, capitano... So già tutto sul tuo viaggio.";
						link.l1 = "Ah sì? Allora saprai che...";
						link.l1.go = "Fleetwood_lostFull";
						DelLandQuestMark(npchar);
						DelMapQuestMarkCity("SentJons");
						break;
					}
						dialog.text = "Sei tornato, capitano... So già tutto del tuo viaggio.";
						link.l1 = "Ah sì? Allora dovresti sapere che...";
					link.l1.go = "Fleetwood_complete";
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					break;
				}
				if (pchar.questTemp.HWIC.Eng == "toAntigua")
				{
					dialog.text = "Salute, amico mio! Che piacere vederti! Hai forse Abigail a bordo della tua nave?";
					link.l1 = "Purtroppo no, Richard. Ha rifiutato di venire con me, perché la sua partenza sarebbe un colpo troppo duro per suo padre, che ormai ha perso anche l’ultimo scudo. Ho deciso di sistemare la faccenda e trovare il denaro di Salomone e quell’isola maledetta...";
					link.l1.go = "Fleetwood_LastTask";
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					break;
				}
				dialog.text = "Serve altro, capitano?";
				link.l1 = "No, sto già andando via.";
				link.l1.go = "exit";		
				NextDiag.TempNode = "First time";
			}
				dialog.text = "Altro, capitano?";
				link.l1 = "No, me ne vado già.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Fleetwood_abordage":
			PlaySound("Voice\English\hambit\Richard Flitwood-03.wav");
			dialog.text = "Maledetto filibustiere! Hai vinto l’abbordaggio, ma il mio dovere lo compirò comunque. Ho già dato ordine di accendere la santabarbara: la mia nave salterà in aria assieme al tuo ‘Vascello Fantasma’. Non affonderai mai più un solo legno inglese. Morirò con onore!";
			link.l1 = "Mi spiace deluderti, Fleetwood, ma ti sbagli di grosso. Non ci sono filibustieri a bordo della mia nave, ci ho già avuto a che fare in passato. Avevo bisogno di te e questa barca era una bella trappola.\nBasta chiacchiere, ora devo farti secco e filarmela da questo tuo bagnarola in fiamme!";
			link.l1.go = "Fleetwood_abordage_1";
		break;
		
		case "Fleetwood_abordage_1":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.questTemp.HWIC.Holl = "FleetwoodCapture";
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
		case "First_Task":
			dialog.text = "Charlie mi ha già informato del tuo brillante arrembaggio alla carovana commerciale nemica. Lieto di conoscerti, l’Inghilterra ha bisogno di capitani arditi come te. Ora lascia che ti riveli qualcosa di grande importanza.";
			link.l1 = "Ascolto, signor Fleetwood.";
			link.l1.go = "First_Task_1";			
		break;
		
		case "First_Task_1":
			dialog.text = "Un pirata sta seminando il caos in tutto l’arcipelago, spacciandosi per l’Olandese Volante, quel vascello fantasma di cui parlano le storie di mare. Finge d’essere il leggendario Olandese Volante, ma io giurerei che sia davvero olandese, anche se di volare non ne è capace. Credo proprio sia un mercenario al soldo di Lucas Rodenburg, il vice-direttore della Compagnia Olandese delle Indie Occidentali.\nRodenburg ha dichiarato una specie di guerra d’ombre all’Inghilterra: questa ‘nave fantasma’ attacca solo bastimenti che battono bandiera inglese. Per la Compagnia è essenziale indebolire la nostra presa su queste acque, senza scatenare una guerra aperta.\nÈ un po’ che gli do la caccia, ma il capitano di quella carretta è un vecchio lupo di mare e la nave sguscia via come un’anguilla.\nVisto che affrontarlo a viso aperto è una follia, dovremo batterlo d’astuzia, e il recente attentato alla mia vita potrebbe tornarci comodo. Che ne dici, capitano? Hai il fegato o ti tremano le gambe?";
			link.l1 = "Neanche per sogno. Sarebbe un piacere aiutarti a stanare e mandare a fondo quel bastardo. Tanto volevi chiedermelo, dico bene?";
			link.l1.go = "First_Task_2";	
		break;
		
		case "First_Task_2":
			dialog.text = "Hai ragione. Ora, parliamo dei dettagli. I miei uomini spargeranno la voce che sono quasi morto e che ho venduto la mia nave, la 'Valkyrie', a te. Poi passeremo alla nostra piccola messinscena. Tu fingerai di essere un mercante che ha comprato la brigantina da me e che si è sbarazzato di quasi tutti i cannoni. \nIl tuo compito sarà quindi di salpare per Barbados e raccontare a chiunque che le tue stive sono piene di merci di valore e le tue tasche gonfie di monete. Falli sapere che presto prenderai il largo. Devi sembrare un mercante avido, sempliciotto ma ricco.\nQuel dannato olandese riceve informazioni sulle navi mercantili proprio a Bridgetown. Nessuno sa chi gliele passi. Sono tutti sospettati – dal mercante locale al governatore, anche se quest’ultima idea fa venire i brividi.\nPrendi il comando della mia 'Valkyrie' e del suo equipaggio. Ma prima lascia qui tutte le tue navi, ho già parlato con il maestro di porto, ti costerà 10.000 pesos al mese per la tua ammiraglia.\nAppena hai fatto, torna da me e organizzerò il resto. Ah, capitano, non dimenticarti di prendere la tua parte per la carovana d’argento e i diecimila per il maestro di porto, il denaro è nel comò.";
			link.l1 = "Ho capito, signor Fleetwood. Vado a far visita al maestro di porto.";
			link.l1.go = "exit";	
			pchar.questTemp.HWIC.Eng = "GotoPortoffice";
			bDisableFastReload = false;//откроем быстрый переход
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
			AddLandQuestMark(characterFromId("SentJons_PortMan"), "questmarkmain");
		break;
		
		case "First_Task_3":
			DialogExit();
			pchar.questTemp.HWIC.TakeQuestShip = "true";//все ПУ недоступны для стоянки до поры, также корабль нельзя продать
			pchar.questTemp.HWIC.EngEquip = "true"; //форма солдат
			pchar.questTemp.HWIC.Eng = "GotoBridgetown";
			GetValckiriaToCharacter(pchar);
			pchar.quest.Knippel_Officer.win_condition.l1 = "location";
			pchar.quest.Knippel_Officer.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Knippel_Officer.function = "KnippelToOfficer";
			pchar.questTemp.HWIC.Eng.BridgeCounter = 0;//счетчик посещений неписей Бриджтауна по квесту
			AddQuestRecord("Holl_Gambit", "2-5");
			AddMapQuestMarkCity("Bridgetown", false);
			AddLandQuestMark(characterFromId("Bridgetown_trader"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_shipyarder"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_Mayor"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_usurer"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_PortMan"), "questmarkmain");
			AddLandQuestMark(characterFromId("Bridgetown_Hostess"), "questmarkmain");
		break;
		
		//изымаем корабль
		case "Fleetwood_lostMir":
			dialog.text = "Sì, so bene che hai fallito la tua missione di catturare la nave pirata. Tutti i miei piani sono andati in malora. Ti tolgo la 'Valkyrie'. Ora puoi anche andartene, non ho più bisogno dei tuoi servigi.";
			link.l1 = "Mi rincresce davvero per questo. Addio, messer Fleetwood.";
			link.l1.go = "Fleetwood_RemoveShip";
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
		break;
		
		case "Fleetwood_lostVal":
			dialog.text = "Sì, so bene che hai perso la 'Valkyrie'. È stato assolutamente inaccettabile... Mi prendo la nave pirata catturata. Ora puoi andare, non ho più bisogno dei tuoi servigi.";
			link.l1 = "Mi rincresce davvero per questo. Addio, messer Fleetwood.";
			link.l1.go = "Fleetwood_RemoveShip";
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_MIRAGE;
		break;
		
		case "Fleetwood_lostFull":
			dialog.text = "Sì, so bene che sei un impiccio raro, un vero pasticcione. Non hai catturato la nave dei pirati e hai pure perso la mia 'Valkyrie'. Mi hai deluso profondamente. Fuori dai piedi!";
			link.l1 = "Mi rincresce davvero per questo. Addio, signor Fleetwood.";
			link.l1.go = "exit";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Knippel");
			AddDialogExitQuestFunction("LandEnc_OfficerFired");//Книппеля из офицеров
			sld = characterFromId("Knippel");
			ChangeCharacterAddressGroup(sld, "SentJons_houseH1", "goto", "goto1");//Книппеля домой
			pchar.questTemp.HWIC.Eng = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			pchar.questTemp.HWIC.Detector = "eng_fail";
			AddSimpleRumourCity("They say that you have failed some secret assignment of Richard Fleetwood. Well, you have got nothing to do on Antigua now...", "SentJons", 20, 3, "");
		break;
		
		case "Fleetwood_RemoveShip":
			DialogExit();
			AddDialogExitQuestFunction("Fleetwood_RemoveShip");
			pchar.questTemp.HWIC.Eng = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			pchar.questTemp.HWIC.Detector = "eng_fail";
			AddSimpleRumourCity("They say that you have failed some secret assignment of Richard Fleetwood. Well, you have got nothing to do on Antigua now...", "SentJons", 20, 3, "");
		break;
		
		case "Fleetwood_complete":
			pchar.questTemp.HWIC.Eng.ShipType = SHIP_VALCIRIA;
			AddDialogExitQuestFunction("Fleetwood_RemoveShip");	
			if (CheckCharacterItem(pchar, "JacobJournal"))//проверяем журнал
			{
				dialog.text = "Sì, sono al corrente che hai portato a termine il nostro piano. Hai fatto fuori quel maledetto bucaniere e preso il suo vascello. Ma come si chiama davvero quella nave?";
				link.l1 = "Miraggio";
				link.l1.go = "Abigile";
			}
			else//нет журнала - нет продолжения квеста
			{
				dialog.text = "Sì, sono al corrente che hai portato a termine il nostro piano. Hai fatto fuori quel maledetto pirata e catturato la sua nave. Riprenderò la mia 'Valkyrie'. Puoi tenerti il vascello del pirata come bottino. Consideralo anche una sorta di... risarcimento. La tua nave, ormeggiata in porto, è andata a fuoco quando l’incendio si è propagato dai moli. Mi scuso per il disagio, "+pchar.name+"... Spero che la nave fantasma ti renda miglior servizio.\nHo ordinato che il tuo nuovo vascello venga ripulito da ogni incrostazione e alghe. La tua bellezza sarà pure vestita di nuove vele di cotone finissimo.\nInfine, accetta il tuo premio di 100.000 pesos e questo strumento di navigazione. Ho sempre desiderato donarlo a un marinaio di valore, e tu in mare hai dato prova d'essere tale! Ebbene, è giunta l’ora dei commiati, ho concluso i miei affari qui e debbo far vela per l’Europa. Che la fortuna ti sia propizia, capitano!";
				link.l1 = "Anche a te, Richard!";
				link.l1.go = "exit";
				LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", true);//закроем Флитвуда в комнате и пусть там сидит
				pchar.questTemp.HWIC.Eng = "end";
				pchar.questTemp.HWIC.Detector = "eng_win_half";
				CloseQuestHeader("Holl_Gambit");
			}
			AddMoneyToCharacter(pchar, 100000);
			GiveItem2Character(pchar, "bussol");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.EngEquip");
			AddSimpleRumourCity("They say that you and Richard Fleetwood has planned some military operation and you have personally destroyed that elusive pirate who has been robbing our trade ships. You are a real hero, captain!", "SentJons", 20, 3, "");
		break;
		
		case "Abigile":
			dialog.text = "Miraggio? Un nome assai appropriato, direi... Ora riprenderò la mia 'Valkyrie' da te, e in cambio potrai tenerti la nave dei pirati come bottino. Ti servirà anche come risarcimento, in un certo senso. La tua nave ancorata in porto è andata a fuoco quando l’incendio si è propagato dai moli. Mi dispiace, "+pchar.name+"... Spero che la nave fantasma ti porti più fortuna.\nHo ordinato che ripuliscano il tuo nuovo vascello da tutta quella dannata sporcizia e alghe. Le vestiranno anche la tua signora con vele nuove di miglior cotone.\nE infine, accetta la tua ricompensa di 100.000 pesos e questo strumento di navigazione, che ho sempre desiderato consegnare a un vero lupo di mare... Hai fatto un lavoro degno, sono fiero di te! Hai per caso il diario di bordo di quel bastardo?";
			link.l1 = "Sì, certo. Eccolo, prendilo pure. Voglio chiederti una cosa, tra i tirapiedi di Lucas Rodenburg c’è per caso qualche... asiatico?";
			link.l1.go = "Abigile_1";			
		break;
		
		case "Abigile_1":
			RemoveItems(PChar, "JacobJournal", 1);
			dialog.text = "Sì, c’è. Il cinese Longway, capitano della sua nave privata 'Meifeng'. L’hai letto nel diario del bucaniere? Vediamo un po’...(leggendo) Eh già. Come sospettavo, dietro tutto questo c’era Lucas Rodenburg! Bah, poco importa, ora non sono più affari nostri... Il nostro governatore generale saprà come sistemare quel bastardo. Lucas Rodenburg dovrà pagare per tutto ciò che ha combinato!";
			link.l1 = "Hm, interessante, e come farà il governatore generale inglese a 'sistemare' la faccenda con un suddito d'Olanda?";
			link.l1.go = "Abigile_2";			
		break;
		
		case "Abigile_2":
			dialog.text = "Ci sono sempre fili politici da tirare, mio caro amico... L'Olanda dovrà ammettere d'aver iniziato la guerra dei commerci contro l'Inghilterra, ma dubito che lo faranno. Invece, daranno tutta la colpa a Rodenburg. Lucas potrebbe perdere la sua posizione, oppure no. In ogni caso, la sua carriera ne uscirà malconcia. \nMa non è affar nostro, capitano. Tu hai portato a termine il tuo compito con abilità. Ed è proprio per questo che ho un altro affare assai delicato da affidarti.";
			link.l1 = "Ascolto, Richard. Chi sarà il prossimo nemico della corona inglese da far sparire stavolta?";
			link.l1.go = "Abigile_3";			
		break;
		
		case "Abigile_3":
			dialog.text = "No, questa volta vorrei chiederti di occuparsi di una faccenda più personale e pacifica. Permettimi di raccontarti una breve storia che, tra l'altro, riguarda anche la tua 'Mirage'.";
			link.l1 = "Avanti.";
			link.l1.go = "Abigile_4";			
		break;
		
		case "Abigile_4":
			dialog.text = "Ero in una scorreria, a caccia della nave fantasma, un mese prima che ci incontrassimo. Era a sud della Martinica, non lontano dal meridiano 64 gradi e 41 primi. Sentimmo il fragore di una battaglia in lontananza, ma il vento era troppo fiacco, così non arrivammo in tempo. Un fluyt inglese fu affondato dalla nave fantasma vicino a un isolotto che nemmeno è segnato sulle carte.\nNon sono riuscito ad acchiappare il pirata e decisi di visitare quell’isola, sperando di trovare superstiti. E li trovai. Un paio di profughi ebrei, padre e figlia. La ragazza si chiamava Abigail ed era una bellezza! Un miracolo in carne ed ossa… Li imbarcai e li portai a Curaçao, anche se suo padre, Solomon, non mi mostrò alcuna gratitudine.\nPer quello che ho capito, pensava che fossi io il pirata che aveva affondato la loro nave — il vecchio non capisce nulla di navi, né delle differenze tra loro. Durante quel breve viaggio io e Abigail diventammo amici, o, a dire il vero, ci innamorammo l’uno dell’altra. Non sembra una storia da romanzo?\nE ora ho scoperto che quel bastardo di Rodenburg fa la corte alla mia Abigail già da un po’, pensa un po’! Avevo intenzione di portarla qui, una volta risolto il problema dei soldi persi di suo padre — ha nascosto ogni moneta che possedeva proprio su quell’isola che ti dicevo. Non sono riuscito a trovare il punto esatto. Non possiamo più aspettare.\nPoiché la mia salute ancora non mi consente di prendere il mare, ti chiedo di andare a Willemstad, trovare Abigail e portarla qui. Di’ che vieni da parte mia e si fiderà di te.";
			link.l1 = "Non vedo alcun problema in questa faccenda. Son pronto a salpare subito.";
			link.l1.go = "Abigile_5";			
		break;
		
		case "Abigile_5":
			PlaySound("Voice\English\hambit\Richard Flitwood-02.wav");
			dialog.text = "Eccellente! Sono lieto di poter contare su di te, "+pchar.name+" Il tuo lavoro sarà ben ricompensato, non temere per questo.";
			link.l1 = "Non ti farò aspettare troppo. A presto, Richard!";
			link.l1.go = "Abigile_6";			
		break;
		
		case "Abigile_6":
			DialogExit();
			npchar.greeting = "fleetwood_2";
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			LocatorReloadEnterDisable("Villemstad_houseSp2", "reload2", true);//закроем спальню Аби
			AddQuestRecord("Holl_Gambit", "2-16");
			pchar.questTemp.HWIC.Eng = "toAbigile";
			sld = characterFromId("Bridgetown_tavernkeeper");
			sld.model = "barmen_3";
			sld.name = "Harry";
			sld.lastname = "Fletcher";//перерисуем бармена Бриджтауна
			sld.greeting = "barmen_1";
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_2";
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("Villemstad", false);
		break;
		
		case "Fleetwood_LastTask":
			dialog.text = ""+pchar.name+", hai davvero deciso di cercare l’isola? Son colpito dalla tua generosità. L’hai trovata?";
			link.l1 = "Sì, l'ho fatto. Purtroppo, è qui che iniziano le cattive notizie. Sono scampato a malapena a quel dannato posto con la pelle intera... Ancora mi viene un brivido solo a pensarci...";
			link.l1.go = "Fleetwood_LastTask_1";
		break;
		
		case "Fleetwood_LastTask_1":
			dialog.text = "Che diavolo è successo laggiù? Dimmi tutto, amico mio, non tenermi sulle spine!";
			link.l1 = "Sono sbarcato sull’isola e mi sono diretto alla grotta dove probabilmente Salomone aveva nascosto il suo forziere. Era davvero lì. Ma appena l’ho toccato, una forza sconosciuta mi ha scaraventato indietro. Ho sentito un boato e sono stato gettato a terra a tre metri dalla cassa...";
			link.l1.go = "Fleetwood_LastTask_2";
		break;
		
		case "Fleetwood_LastTask_2":
			dialog.text = "Incredibile!";
			link.l1 = "Ci sono quasi rimasto secco – mi sono beccato delle belle graffiature. Mentre riprendevo i sensi, dei rumori spaventosi mi ronzavano in testa, e quella creatura orrenda è sbucata fuori dalla terra... oh Dio, che bestia!";
			link.l1.go = "Fleetwood_LastTask_3";
		break;
		
		case "Fleetwood_LastTask_3":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "Richard, non sono impazzito. È successo davvero, anche se faccio fatica a crederci io stesso. Era il cadavere mummificato e dipinto di un indio, con un mazzo di piume sulla testa. Quella creatura ha borbottato qualcosa, poi ha tirato fuori una clava indiana enorme e mi si è avventata contro!";
			link.l1.go = "Fleetwood_LastTask_4";
		break;
		
		case "Fleetwood_LastTask_4":
			dialog.text = "";
			link.l1 = "Santo cielo... Ancora non capisco come diavolo sia riuscito a cavarmela con quella bestia... L’ho colpita talmente tante volte che avrebbe steso una dozzina d’uomini, eppure stava ancora in piedi... Quando finalmente ripresi fiato, aprii quel maledetto forziere... Dentro non c’erano dobloni, ma qualcos’altro sì. Guarda qui, un oggetto davvero curioso!";
			link.l1.go = "Fleetwood_LastTask_5";
		break;
		
		case "Fleetwood_LastTask_5":
			RemoveItems(PChar, "GastonHead", 1);
			dialog.text = "B-r-r... terribile..."+pchar.name+", aspetta... certo che è lui! Quella è la testa del bastardo che ha provato ad accoppare me accecandomi col pepe!";
			link.l1 = "Lo conosci? Si chiama Gaston, è l’oste di Bridgetown e un sostenitore di van Berg, quel capitano della nave fantasma. L’ho riconosciuto subito, ma non so chi l’abbia ammazzato né come la sua testa mozzata sia finita nello scrigno di Salomone su quell’isola sconosciuta!";
			link.l1.go = "Fleetwood_LastTask_6";
		break;
		
		case "Fleetwood_LastTask_6":
			dialog.text = "Hai ragione, è davvero una storia inquietante e oscura. Roba da stregoni...";
			link.l1 = "Proprio così. Non aveva senso tornare da Abigail senza il denaro. Son venuto qui per raccontarti la faccenda. Forse tu, Richard, riuscirai a capirci qualcosa in questo marasma...";
			link.l1.go = "Fleetwood_LastTask_7";
		break;
		
		case "Fleetwood_LastTask_7":
			dialog.text = "Io? Non ci capisco un’acca qui, proprio come te... Ma una cosa te la dico con certezza: ho un brutto presentimento, accidenti a questa storia..."+pchar.name+"Ascoltami adesso. Vai a controllare Bridgetown per assicurarti che... Gaston sia sparito per sempre. Poi, ti chiedo di venire alla Laguna Bianca di Curaçao tra venti giorni. Charlie Knippel ti aspetterà lì. Io raccoglierò il denaro per il padre di Abigail. Lo darò a Charlie, e tu lo porterai a Solomon e accompagnerai Abigail ad Antigua. Questa volta non ci saranno intralci, devi capirlo. Va', amico mio!";
			link.l1 = "Va bene, Richard. Spiego le vele subito.";
			link.l1.go = "Fleetwood_LastTask_8";
		break;
		
		case "Fleetwood_LastTask_8":
			DialogExit();
			pchar.questTemp.HWIC.Eng = "toBarbados";
			AddQuestRecord("Holl_Gambit", "2-21");
			SetFunctionTimerCondition("HWICEng_toBarbadosOver", 0, 0, 20, false);//чтобы не тянули
			AddSimpleRumourCity("Oh, captain, I have heard that Richard Fleetwood really admires you. Trust me, his praise costs a lot. You must be a very important person...", "SentJons", 20, 3, "");
			AddMapQuestMarkCity("Bridgetown", false);
			AddLandQuestMark(characterFromId("Bridgetown_tavernkeeper"), "questmarkmain");
		break;
		
//---------------------------------------------против всех-----------------------------------------------
		
		case "InTerksShore":
			DelLandQuestMark(npchar);
			pchar.quest.Fleetwood_ShoreOver.over = "yes";//снять таймер
			dialog.text = "Suppongo che tu sia il bastardo che ha rapito la mia Abigail. Charlie non è tornato da me, quindi dev’essere anche questa colpa tua.";
			link.l1 = "Hai ragione, signor Fleetwood. Sono proprio io. Charlie mi ha aiutato a guadagnarmi la fiducia di Abigail grazie alla lettera che le hai scritto. Ma andiamo subito al sodo... Hai portato il denaro?";
			link.l1.go = "InTerksShore_1";
		break;
		
		case "InTerksShore_1":
			dialog.text = "Ce l'ho. Ma prima voglio vedere Abigail. Devo esser certo che sia viva e intatta, ché non mi fiderò mai della parola di un bastardo.";
			link.l1 = "Non credete, signore, d’esser in grado di dettar legge qui?";
			link.l1.go = "InTerksShore_2";
			// belamour legendary edition -->
			link.l2 = "Non voglio più giocare a questo gioco. Abi resta con me, e tu rimani su questa spiaggia! Al fuoco!";
			link.l2.go = "InTerksShore_2a";
		break;

		case "InTerksShore_2a"://массовая драка на необитаемом острове
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)//офицеры Флитвуда
			{
				sld = characterFromId("FlOfficer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=7; i++)//засада Флитвуда
			{
				sld = GetCharacter(NPC_GenerateCharacter("EnemySailor_"+i, "sold_eng_"+i, "man", "man", 18, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 18, 30, 30, "blade_19", "pistol2", "bullet", 40);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				if (i >= 1 && i < 3) ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto2");
				else ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto9");
			}
			for (i=1; i<=7; i++)//наши - к бою!
			{
				sld = characterFromId("OwrSailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "FleetwoodDiedInShore");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;

		case "InTerksShore_2":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			dialog.text = "Lo capisco bene, ma non sono uno sprovveduto. Niente discorsi di denaro finché non vedo Abigail. Allora? Sto aspettando.";
			link.l1 = "Bene. Ora è il momento di scoprire le mie carte, Capitano Fleetwood. Ho organizzato questo nostro incontro non per denaro. Beh, certo, mi farebbe comodo, ma prima ho bisogno di te.";
			link.l1.go = "InTerksShore_3";
		break;
		
		case "InTerksShore_3":
			dialog.text = "Io? La faccenda si fa sempre più intrigante... Credo di cominciare a capire cosa succede davvero qui. Dimmi, Abigail è viva? Vive ancora o l’hai fatta fuori, bastardo?";
			link.l1 = "Suppongo che ti lascerò nell’ignoranza circa la sua sorte. Sappi solo una cosa – non è qui. Ha recitato la sua parte alla perfezione, ora tu sei nelle mie mani. Ah, l’amore… che incanto! Cos’altro poteva farmi tirar fuori la volpe dalla tana, portandola allo scoperto? Ah-ah-ah!";
			link.l1.go = "InTerksShore_4";
		break;
		
		case "InTerksShore_4":
			dialog.text = "Non rallegrarti troppo presto, furfante. Ti ho preparato un bel comitato d’accoglienza su quest’isola, e non si sa ancora chi tiene chi per le palle! Quindi preparati, hai un bel po’ da raccontarmi – su Abigail, su Charlie… e mi pagherai per averli fatti soffrire!";
			link.l1 = "Sto già tremando dalla paura! Meglio chiuderla qui, signore. Preparatevi a scendere all’inferno, ché in paradiso non c’è posto per voi.";
			link.l1.go = "InTerksShore_5";
		break;
		
		case "InTerksShore_5"://массовая драка на необитаемом острове
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for (i=1; i<=3; i++)//офицеры Флитвуда
			{
				sld = characterFromId("FlOfficer_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=1; i<=7; i++)//засада Флитвуда
			{
				sld = GetCharacter(NPC_GenerateCharacter("EnemySailor_"+i, "sold_eng_"+i, "man", "man", 18, ENGLAND, -1, false, "soldier"));
				FantomMakeCoolFighter(sld, 18, 30, 30, "blade_19", "pistol2", "bullet", 40);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				if (i >= 1 && i < 3) ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto2");
				else ChangeCharacterAddressGroup(sld, "Shore56", "goto", "goto9");
			}
			for (i=1; i<=7; i++)//наши - к бою!
			{
				sld = characterFromId("OwrSailor_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "FleetwoodDiedInShore");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
	}
}
