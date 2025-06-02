// boal 25/04/04 общий диалог солдат
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	int DeceptionChance  = 0;
	int DeceptionPenalty  = 0;
	if(CheckAttribute(pchar,"StealtDeceptionPenalty")) DeceptionPenalty = sti(pchar.StealtDeceptionPenalty);
	
	DeceptionChance = sti(GetSummonSkillFromName(pchar, SKILL_SNEAK)*100/110);
	if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE) 
	{
		DeceptionChance = sti(GetSummonSkillFromName(pchar, SKILL_SNEAK)*100/310);
		if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	}
	if(sti(pchar.reputation.fame) < 41 && CheckCharacterPerk(pchar, "Trustworthy"))
	{
		DeceptionChance = 100;
		if(DeceptionChance - DeceptionPenalty > 50) DeceptionChance -= DeceptionPenalty;
	}
	if(DeceptionChance > 90) DeceptionChance = 90;
	// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
    /* // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Soldier\" + NPChar.City + "_Soldier.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <-- */
    int iTest, iTemp;
	string sTemp;
    iTest = FindColony(NPChar.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			sTemp = npchar.location;
			if (findsubstr(sTemp, "_townhall" , 0) != -1) AddDialogExitQuest("MainHeroFightModeOff");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "First time":			
            NextDiag.TempNode = "First time";
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				// заглушка на пирата
				if (sti(pchar.nation) == PIRATE)
				{
    				dialog.text = RandPhraseSimple("Pirati in città?! Non ci posso credere... Arrestateli "+GetSexPhrase("lui","lei")+"!!","Questo è un pirata! Afferra "+GetSexPhrase("lui","lei")+"!!!");
					link.l1 = RandPhraseSimple("Sono un pirata, e allora?","Eh, puoi provare...");
					link.l1.go = "fight"; 
					break;
				}
				else
				{
					if (DeceptionChance > (10+rand(150)+rand(150)))
					{
						dialog.text = RandPhraseSimple("Chi sei tu e cosa stai facendo qui?","Fermati subito! Chi sei e con quale diritto stai cercando di entrare in città?");
						link.l2 = "Ho gettato l'ancora vicino a "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" sotto la bandiera di "+NationNameGenitive(sti(npchar.nation))+". Cosa non capisci? (Probabilità di inganno "+DeceptionChance+"%%)";
						link.l1.go = "NotPegYou";
					}
					else
					{
						dialog.text = RandPhraseSimple("Una spia! Arrenditi la tua arma e seguimi!","Un agente nemico! Cattura "+GetSexPhrase("lui","lei")+"!");
						link.l1 = RandPhraseSimple("Taci, fifone!","Fanculo!");
						link.l1.go = "fight"; 
					}
				}
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (GetNationRelation(sti(NPChar.nation), GetBaseHeroNation()) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					// грамота Винсенто
					if(CheckAttribute(pchar, "questTemp.Guardoftruth") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "santiago")
					{
						dialog.text = RandPhraseSimple("Chi sei e cosa stai facendo qui?","Fermati subito lì! Chi sei tu, e con quale diritto stai cercando di entrare in città?");
						link.l1 = "Guarda questo documento, soldato. Sono qui con il permesso dell'Inquisitore, Padre Vincento.";
						link.l1.go = "vincento"; 
						break;
					}
					if(CheckAttribute(pchar, "questTemp.Guardoftruth.Trinidad") && CheckCharacterItem(pchar, "VerifyPaper") && npchar.city == "portspein")
					{
						dialog.text = RandPhraseSimple("Chi sei e cosa stai facendo qui?","Fermati subito lì! Chi sei tu e con quale diritto stai cercando di entrare in città?");
						link.l1 = "Guarda questo documento, soldato. Sono qui con il permesso dell'Inquisitore, Padre Vincento.";
						link.l1.go = "vincento"; 
						break;
					}
					if (PChar.location == "Maracaibo_Plantation")
					{
						dialog.text = LinkRandPhrase("Comportati bene e non disturbare gli schiavi.","Avanti, muoviti!","Ah, sei tu. Vai avanti, siamo già stati informati su di te.");
						link.l1 = "...";
						link.l1.go = "exit";
						break;
					}
					dialog.text = RandPhraseSimple("Chi sei e cosa stai facendo qui?","Fermati subito! Chi sei e con quale diritto stai cercando di entrare in città?");
					//==> по лицензии
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "Ufficiale, io ho "+GetRusNameNationLicence(HOLLAND)+", quindi sono qui per motivi legali. Qui, per favore dai un'occhiata...";
						link.l1.go = "LicenceOk";
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l2 = "Non vedi la bandiera di "+NationNameGenitive(sti(pchar.nation))+"sul pennone della mia nave?! (Probabilità di inganno "+DeceptionChance+"%%)";
						}
						else //если причалил не в городе
						{
							link.l2 = "Ho gettato l'ancora vicino a "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" sotto la bandiera di "+NationNameGenitive(sti(pchar.nation))+". Cosa non capisci? (Probabilità di inganno "+DeceptionChance+"%%)";
						}
						if (DeceptionChance < (10+rand(50)+rand(50)))
						{
							link.l2.go = "PegYou";
						}
						else
						{
							link.l2.go = "NotPegYou";
						}
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (sti(pchar.nation) == PIRATE)
						{
    						dialog.text = RandPhraseSimple("Pirati in città?! Non ci posso credere... Prendetelo!","È un pirata! Prendetelo!");
							link.l1 = RandPhraseSimple("Sì, sono un pirata - e allora?","Ehi, prendimi se ci riesci...");
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = "Non vedi la bandiera di "+NationNameGenitive(sti(pchar.nation))+" sulla mia nave?! (Probabilità di inganno "+DeceptionChance+"%%)";
						}
						else //если причалил не в городе
						{
							link.l1 = "Ho gettato l'ancora vicino a "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" sotto la bandiera "+NationNameGenitive(sti(pchar.nation))+". Cosa non capisci? (Probabilità di inganno "+DeceptionChance+"%%)";
						}
						if (DeceptionChance < (10+rand(50)+rand(50)))
						{
							link.l1.go = "PegYou";
						}
						else
						{
							link.l1.go = "NotPegYou";
						}
					}
				}
				// <-- eddy. проверяем, не казачок ли.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn) == true) // наш горожанин
						{
			         		switch (rand(10))
							{
								case 0:
									dialog.text = "Oh, capitano, ci siamo divertiti così tanto con te in mare! Quante navi abbiamo affondato insieme sotto il tuo comando! E ora...";
									link.l1 = "E qui, amico mio, puoi deliziare i tuoi occhi con signore affascinanti, non le vedrai in mare.";
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = "Capitano, cosa abbiamo fatto per meritare questo?! Non siamo ratti di terra, vero?";
									link.l1 = "Silenzio, marinaio! Il tuo posto è molto importante e onorabile, quindi smetti di lamentarti.";
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = "Cosa succede in mare, capitano? Lo vedremo mai di nuovo?";
									link.l1 = "Ma certo, marinaio! Una volta liberato dal dovere, puoi dirigerti verso il molo e goderti il mare quanto vuoi.";
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = "Voglio lamentarmi, capitano: a tutti noi manca il mare. Siamo tutti completamente stufi di questo dovere terrestre!";
									link.l1 = "Mi stanco di questo piagnisteo! Hai abbastanza rum anche qui! Servi dove sei stato posto dal capitano, o qualcuno sarà impiccato come esempio per gli altri.";
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = "Ti dirò in confidenza, capitano, il nuovo governatore è un corruttore e un peculatore. Ma in realtà non sono affari miei...";
									link.l1 = "Esattamente, corsaro. Il tuo compito è stare al tuo posto e mantenere l'ordine. E impiccare il governatore sull'antenna è il mio compito. Buon lavoro!";
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = "Grazie per non averci dimenticato, capitano! Ti seguiremmo attraverso il fuoco e l'acqua!";
									link.l1 = "Conosco il tuo tipo, mascalzoni! Tutto ciò che davvero amate è l'oro. C'è una festa alla taverna stasera, offro io da bere. Non dimenticate di venire.";
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = "Eh, capitano! Ci pensi, può un corsaro essere davvero un custode dell'ordine?! È da tanto tempo che non ci occupiamo del vero affare!";
									link.l1 = "Nessun tempo per rilassarsi, corsaro! Le armate nemiche stanno perlustrando le acque vicino alle nostre isole, e dobbiamo essere pronti per un bagno di sangue in qualsiasi momento.";
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = "Capitano, ho sentito dire che la Corona ha mandato un'altra squadra dalla nostra parte?";
									link.l1 = "Certo, corsaro. Finché viviamo, non ci sarà pace per noi. E persino all'Inferno combatteremo i diavoli!";
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = "Yo-ho-ho! Accidenti, quello era davvero un alcol forte ieri, capitano! Peccato che tu non ci fossi.";
									link.l1 = "Non è un grosso problema, me ne farò una ragione. E non vi invidio, ragazzi.";
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = "Ti dirò in confidenza, capitano, perché ci hai sempre trattato bene, ci siamo divertiti molto con una bella ragazza ieri...";
									link.l1 = "Ehi, corsaro, una forca è proprio quello di cui hai bisogno!";
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = "Capo! Per favore, liberami da questo maledetto dovere! Semplicemente non riesco più a fare la parte del custode dell'ordine.";
									link.l1 = "La guardia notturna su una nave non è semplice. Amico, il dovere è dovere, ovunque e comunque sia.";
									link.l1.go = "exit";
								break;
							}
							// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
							/* link.l2 = RandPhraseSimple("C'è un affare importante!","Ho un affare con te.");
							link.l2.go = "quests";//(перессылка в файл города) */
							break;
						}
						else
						{ // пираты, не наши
							if (sti(pchar.GenQuest.Piratekill) > 20)
							{
								dialog.text = RandPhraseSimple("Allarme! Qui c'è un pazzo armato e malato!","Alle armi, alle armi! C'è qui qualche bastardo pazzo!");
								link.l1 = RandPhraseSimple("Eh? Cosa?","Eh, perché stai facendo questo?");
								link.l1.go = "pirate_fight";
							}
							else
							{
							    /* dialog.text = LinkRandPhrase(RandPhraseSimple("Avete un affare con me, capitano?","Vado avanti e indietro per affari, se hai bisogno di qualcosa, chiedi, non esitare."),RandPhraseSimple("Capitano, sono molto occupato, quindi cerchi altri interlocutori.","C'è qualcosa che non va, capitano? Se non ci sono domande, posso andare?"),"Fate largo, capitano, ho fretta.");
							link.l1 = LinkRandPhrase("Scusa, amico, io "+GetSexPhrase("Si è confuso","обозналась")+" ","Va bene, occupati dei tuoi affari.","No, niente.");
							link.l1.go = "exit";
							link.l2 = LinkRandPhrase(RandPhraseSimple("Ho un paio di domande per te.","Ho un affare con te."),RandPhraseSimple("Vedo che sei di fretta. Una domanda e sarai libero.","Io "+GetSexPhrase("voleva","desiderava")+" chiedere qualcosa."),"I tuoi affari possono aspettare. Volevo chiederti una cosa "+GetSexPhrase("voleva","voleva")+".");
							    link.l2.go = "quests";//(перессылка в файл города) */
								
								//Экку Korsar - что-то они больно вежливые для пиратов были...
								dialog.text = RandPhraseSimple("Cosa vuoi? Passa oltre.","Smetti di bloccare la strada, indietreggia.");
					            link.l1 = RandPhraseSimple("Sai? Non abbaiare!","Riduci il tuo ardore. Non lo raffredderò in fretta!");
					            link.l1.go = "exit";
						    	/* link.l2 = LinkRandPhrase(RandPhraseSimple("Ho un paio di domande per te.","Ho un affare con te."),RandPhraseSimple("Vedo che hai fretta. Una domanda e sarai libero."," Io "+GetSexPhrase("voleva","voleva")+" chiedere qualcosa."),"Le tue faccende possono aspettare. Ecco cosa voglio chiederti "+GetSexPhrase("хотел","voleva")+".");
							link.l2.go = "quests";//(перессылка в файл города) */
							}
							break;
						}
					}
					else
					{ //если негодяй, имеющий НЗГ к дружественной или нейтральной нации
						if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
						{
							dialog.text = RandPhraseSimple("Solo guarda  "+GetSexPhrase("a quel mascalzone! Ha osato mostrare il suo volto","a quel furfante! Ha osato mostrare il suo volto")+" in "+XI_ConvertString("Colony"+npchar.city)+". Afferra "+GetSexPhrase("lui","lei")+"!!!","Ah, ti ho riconosciuto, "+GetSexPhrase("birbante","birbante")+"! Afferra "+GetSexPhrase("lui","lei")+"!!!");
							link.l1 = RandPhraseSimple("Argh!..","Ebbene, l'hai chiesto tu...");
							link.l1.go = "fight";
							break;						
						}
					}

					// --> девица в джунглях
					if(rand(2) == 1 && CheckAttribute(pchar,"GenQuest.EncGirl") && CheckAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers"))
					{
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 1)	
						{
							dialog.text = "Oh, guarda chi c'è! Signora "+pchar.GenQuest.EncGirl.name+" lei stessa ci ha onorato con la sua presenza! Mi chiedo come hai osato? Ti stavamo cercando! Per favore, procedi verso il dungeon - la tua cella è pronta e ti aspetta. ";
							link.l1 = "Che assolute sciocchezze stai dicendo!? Io e il mio "+GetSexPhrase("cavaliere","compagno")+" stavamo facendo una passeggiata nella giungla, raccogliendo fiori. Lasciami in pace! Dove sono i modi di questi martinetti?! Non appena vedono una ragazza attraente, iniziano a tormentarla! "+GetSexPhrase("Mia cara, per favore dì a quei testardi di andarsene e lasciare in pace una donna onesta!","Tesoro, per favore, di' a quei testa di legno...")+"!";
							link.l1.go = "GirlEnc_1";
						}
						if(sti(pchar.GenQuest.EncGirl.MeetSoldiers) == 2)	
						{
							dialog.text = "Oh, eccoti, bellissima! Tuo padre ha messo in allarme l'intera guarnigione per trovarti e riportarti a casa.";
							link.l1 = "Vattene! So dove sto andando e non ho bisogno del tuo aiuto! Capitano, dì loro di togliere le mani da me.";
							link.l1.go = "GirlEnc_2";						
						}
						DeleteAttribute(pchar,"GenQuest.EncGirl.MeetSoldiers");
					}
					// <-- девица в джунглях
					
					// --> Sinistra Длинные тени старых грехов
					if(CheckAttribute(pchar, "questTemp.Knippel.Soldiers_1"))
					{
						switch(0)
						{
							case 0: 
							dialog.text = "Ascolta, Charlie, abbiamo dei nuovi reclute al forte. Verdi come l'erba... Potresti passare e mostrare loro come mirare?";
							link.l1 = "Se il capitano Fleetwood ed io non salpiamo nei prossimi giorni - con piacere.";
							link.l1.go = "Knippel_Soldiers_1";
							break;
						}
						break;
					}
					
					if(CheckAttribute(pchar, "questTemp.Knippel.Soldiers_2"))
					{
						switch(0)
						{
							case 0: 
							dialog.text = "Charlie, il mio turno sta per finire, che ne dici di un drink?";
							link.l1 = "Con piacere, compagno! Lascia che veda solo cosa vuole il capitano.";
							link.l1.go = "Knippel_Soldiers_2";
							break;
						}
						break;
					}
					
					if(CheckAttribute(pchar, "questTemp.Knippel.Soldiers_3"))
					{
						switch(0)
						{
							case 0: 
							dialog.text = "Buona notte, Charlie! Non sembri in forma. Tutto a posto?";
							link.l1 = "Mi hanno svegliato nel bel mezzo della notte, cosa ne pensi? Non posso prendere una pausa.";
							link.l1.go = "Knippel_Soldiers_3";
							break;
						}
						break;
					}
					// <-- Длинные тени старых грехов

					// --> belamour ночной приключенец
					if(CheckAttribute(pchar,"GenQuest.NightAdventureSolNum") && npchar.index == pchar.GenQuest.NightAdventureSolNum)
					{
						dialog.text = "La vita di un soldato è programmata - fare la guardia, pattugliare... Cosa vuoi, "+GetAddress_Form(NPChar)+"?";
						link.l1 = "Ascolta, è stato con te che un ubriaco ha avuto una rissa qui di recente? Beh, anche se, a quanto pare, sì, con te...";
						link.l1.go = "NightAdventure_CitizenHomieSolder";
						break;
					}
					// <-- ночной приключенец
					
					//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
					
					// Шарль де Мор генерал-губернатор французских колоний
					if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Vostra Eccellenza, Governatore Generale! Come posso servire?";
							link.l1 = "Non ho bisogno di nulla, grazie.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "È un grande onore per me, signor Governatore Generale! Come posso aiutarla?";
								link.l1 = "Svolgi il tuo servizio coscienziosamente - Non richiedo nulla di più da te.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Buon vederti, Sua Eccellenza! Che cosa può fare un umile soldato per il governatore generale delle nostre colonie?";
								link.l1 = "Personalmente, non ho bisogno di nulla da te. Continua a servire.";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// Вице-адмирал на службе нации узнается без мундира
					if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Vice Ammiraglio, Vostra Eccellenza! Permettetemi di riportare: durante il mio turno...";
							link.l1 = "Calmati, soldato, non ho bisogno del tuo rapporto. Riporta al tuo ufficiale.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Lieta di vederti, Vice Ammiraglio! Posso aiutarti in qualcosa?";
								link.l1 = "No, stavo solo controllando quanto sei attento. Sono contento che tu mi abbia riconosciuto.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Vice Ammiraglio, è un onore per me! Cosa posso fare per te?";
								link.l1 = "Servi "+NationNameGenitive(sti(npchar.nation))+", soldato! È la cosa migliore che tu possa fare.";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// Офицер с патентом
					if(IsOfficerFullEquip() && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Saluti, capitano! Se hai delle istruzioni per me, allora ti chiedo scusa: anche se sono al tuo servizio "+NationNameGenitive(sti(npchar.nation))+", rispondo solo al comandante e al governatore."; 
							link.l1 = "Ho i miei ufficiali e l'equipaggio a rispondere alla mia guida. Fai il tuo dovere, soldato.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Capitano, puoi prendermi al servizio sulla tua nave? Lo stesso servizio per "+NationNameGenitive(sti(npchar.nation))+", ma preferisco il mare."; 
								link.l1 = "Hai bisogno dove sei stato assegnato, quindi svolgi il tuo servizio con onore. Chiudi gli occhi per un secondo, e lo porteranno al mare.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Oh, sei fortunato: sei il capitano della nave al servizio di "+NationNameGenitive(sti(npchar.nation))+"... E sono bloccato qui tutto il giorno."; 
								link.l1 = "Pensi che sia appena arrivato ai Caraibi e sia diventato un capitano una settimana dopo? Sono tutti anni di duro lavoro...";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// <-- legendary edition
					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = "Non vedi? Sono in servizio. Smettila di infastidirmi.";
							link.l1 = "Bene, bene...";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "Stai per raccontarmi di qualche attività sospetta?";
							link.l1 = "No, per niente, e a proposito, sono un capitano. Vedo che non stai più ascoltando? Addio.";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "Questa è una struttura militare, quindi non fare troppo rumore qui.";
							link.l1 = "Bene, lo terrò a mente.";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "Un tempo così bello, e io devo stare qui. In città, ci sono almeno delle ragazze, e cosa abbiamo qui? Solo topi in giro.";
							link.l1 = ""+GetSexPhrase("Simpatizzo, ma non c'è nulla che io possa fare per aiutare - è il tuo dovere dopo tutto.","Ehi! Cosa c'è che non va in me? Non sono una ragazza?")+"";
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "Se ti piace parlare, trova qualcun altro. Devo mantenere l'ordine qui, e non ho tempo per chiacchiere inutili.";
							link.l1 = "Oh, no, sto solo controllando, se sei ancora vivo. Stavi in piedi proprio come una statua.";
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = "Probabilmente pensi che le giornate di guarnigione siano una passeggiata? Assolutamente no! È un lavoro duro e importante. Ricordo una volta... ";
							link.l1 = "Mi racconterai quella storia un'altra volta. Sono un po' di fretta ora.";
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = "Stai attento qui, sei in un forte! Sii silenzioso come un topo!";
							link.l1 = "Come dici tu, soldato.";
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = "Ehi! Hai per caso dell'acqua? Sto morendo di sete.";
							link.l1 = "No, amico, sii paziente...";
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = "Che noia è la vita di guarnigione, solo rozzoni come te nei dintorni! Ora, la guarnigione della città sicuramente si diverte di più...";
							link.l1 = "E tu chiami questo 'essere in servizio'? In questo modo, di sicuro, lascerai passare una spia!";
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = ""+GetSexPhrase("Sembri un tipo forte, vero? Ti piacerebbe arruolarti nella guarnigione del forte? Abbiamo caserme spaziose, due pasti al giorno e liquore gratis.","Oh, giovane signora, non hai idea di quanto sia piacevole incontrare una bella damigella in questo culo del mondo!")+"";
							link.l1 = ""+GetSexPhrase("È certamente allettante, ma devo ancora rifiutare. Tutta quella marcia militare semplicemente non fa per me.","Grazie per il complimento, soldato.")+".";
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = "Questo maledetto caldo... Darei volentieri metà della mia vita per tornare in Europa.";
							link.l1 = "Sì, vedo che la tua salute non è adatta al clima locale.";
							link.l1.go = "exit";
						break;

					}
					// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
					/* link.l3 = "Un momento. Volevo chiedere una cosa "+GetSexPhrase("voleva","хотела")+"...";
					link.l3.go = "quests";//(перессылка в файл города) */				
				}
			}
		break;
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = RandPhraseSimple("Mi sembra una sorta di trucco. Parliamo con il comandante, "+GetSexPhrase("compagno","caro")+", e capire tutto...","Hmm... Qualcosa mi dice che non sei chi fingi di essere... Arrenditi e consegna la tua arma "+GetAddress_Form(npchar)+", e seguimi per ulteriori indagini!");
			link.l1 = RandPhraseSimple("Vaffanculo!","Quando due domeniche arrivano in una settimana...");
			link.l1.go = "fight";
			if (!CheckAttribute(pchar,"questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		
		case "NotPegYou":
			dialog.text = RandPhraseSimple("Oh, capisco... Tutto sembra a posto, sei libero di andare, "+GetAddress_Form(pchar)+".","Devo essermi un po' stancato a stare di guardia... Sembra che tutto sia a posto, "+GetAddress_Form(pchar)+", mi dispiace.");
			link.l1 = "Nessun problema!";
			link.l1.go = "exit";
			if (!CheckAttribute(pchar,"questTemp.stels.landSolder") || sti(pchar.questTemp.stels.landSolder) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landSolder = GetDataDay();
			}
		break;
		
		case "vincento":
			dialog.text = RandPhraseSimple("Oh, capisco... Sembra tutto a posto, sei libero di andare, "+GetAddress_Form(pchar)+".","Vediamo ora... Beh, sembra tutto in ordine, "+GetAddress_Form(pchar)+", mi dispiace.");
			link.l1 = "Questo ti insegnerà!";
			link.l1.go = "exit";
		break;
		
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				dialog.text = "Solo a pensarci! Che insolente! Venire qui sotto le vesti di un mercante! Le tue facce sono affisse in ogni caserma, maledetto! Questa volta non te la caverai! Afferratelo!";
				link.l1 = RandPhraseSimple("Arrgh!..","Ebbene, l'hai chiesto tu...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (pchar.location != "LosTeques_town" && findsubstr(pchar.location.from_sea, "_town" , 0) == -1) //если причалил не в городе 300912
			{
				dialog.text = "Sei venuto a fare commercio qui? Posso chiedere come? Dov'è la tua nave? Sai, tutto sembra molto sospetto, e sono costretto a trattenerti fino a quando non capiremo tutto. Arrenditi la tua arma e seguimi!";
				link.l1 = RandPhraseSimple("Vaffanculo!","Quando due domeniche arrivano in una settimana...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (iTemp == -1)
			{
				dialog.text = "La tua licenza deve essere revocata poiché è scaduta e per questo motivo non è valida. Consegnami la tua arma e seguimi per ulteriori indagini!";
				link.l1 = RandPhraseSimple("Vaffanculo!","Quando due domeniche arrivano in una settimana...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Mmm... Tutto sembra a posto. Devo però notare che la tua licenza scade oggi. Ti lascio passare questa volta, ma dovrai comunque rinnovare la licenza.";
				link.l1 = "Grazie, ne prenderò uno nuovo al più presto.";
				link.l1.go = "exit";			
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = "Mmm... Sembra tutto a posto. Devo però notare che la tua licenza scadrà presto. È ancora valida solo per "+FindRussianDaysString(iTemp)+". Quindi tienilo a mente, "+GetAddress_Form(npchar)+".";
				link.l1 = "Grazie, ne prenderò uno nuovo appena possibile.";
				link.l1.go = "exit";			
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase("Bene, tutto sembra in ordine. La tua licenza è valida per un altro "+FindRussianDaysString(iTemp)+". Puoi passare.","Tutto è chiaro, "+GetAddress_Form(npchar)+". Puoi liberamente entrare ed uscire dalla città, la tua licenza è valida per un altro "+FindRussianDaysString(iTemp)+". Scusa per il disturbo.","Tutto sembra a posto, "+GetAddress_Form(npchar)+", non ti sto più trattenendo qui.");
				link.l1 = RandPhraseSimple("Eccellente. Cordiali saluti.","Grazie, ufficiale.");
				link.l1.go = "exit";
			}
		break;
		//============================== ноды маяка Порт Рояля =========================
		case "PortRoyal_Mayak":
			dialog.text = RandPhraseSimple("Ehi, compagno, non rompere nulla nel faro.","Questo faro è un oggetto molto importante per la città. Fai attenzione!");
			link.l1 = RandPhraseSimple("Va bene, non preoccuparti.","Bene, non preoccuparti.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Mayak";
		break;
		case "PortRoyal_Gans":
			dialog.text = LinkRandPhrase("Non avvicinarti ai cannoni - è un'installazione militare!","Gli estranei non sono ammessi vicino ai cannoni!","Se ti noto in giro vicino ai cannoni, sei finito!");
			link.l1 = RandPhraseSimple("L'ho capito.","Bene, ho capito.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_Gans";
		break;

		// --> генератор "A damsel in the jungle"
		case "GirlEnc_1":
			dialog.text = "E chi sei tu, capitano? Non sarai mica un complice del ladro più notorio di questa colonia?";
			link.l1 = "A chi hai appena chiamato complice del crimine?! Sei colpito dal sole o cosa?! Ehi, allontana le tue zampe dalla ragazza!";
			link.l1.go = "GirlEnc_11";
			link.l2 = "Veramente, ho "+GetSexPhrase("ho conosciuto lei","ho conosciuto lei")+" recentemente...";
			link.l2.go = "GirlEnc_12";
		break;

		case "GirlEnc_11":
			dialog.text = ""+GetSexPhrase("Signore","Signorina")+", abbiamo un ordine di arrestarla e portarla al dungeon. E se pensi di poterci fermare, ti sbagli.";
			link.l1 = "Vediamo, allora...";
			link.l1.go = "GirlEnc_11End";
		break;

		case "GirlEnc_11End":
			DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "GirlEnc_12":
			dialog.text = "Davvero? In tal caso, ti consiglierei di controllare le tue tasche. Quella signora è una professionista, lo sai";
			link.l1 = "Grazie, lo farò. Come ho potuto fare una figura così sciocca...";
			link.l1.go = "GirlEnc_12End";		
		break;		
		
		case "GirlEnc_12End":
			pchar.money = sti(pchar.money) - makeint(sti(pchar.money)/20);
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;
		
		case "GirlEnc_2":
			dialog.text = ""+GetSexPhrase("Signore","Signorina")+", abbiamo l'ordine di trovare quella signora e portarla a suo padre.";
			link.l1 = "Ebbene, un ordine è un ordine - vai avanti, allora.";
			link.l1.go = "GirlEnc_2End";
			link.l2 = "Troppo tardi per questo, perché sto già parlando con suo padre.";
			link.l2.go = "GirlEnc_21";
		break;
		
		case "GirlEnc_2End":
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			LAi_CharacterDisableDialog(sld);
			sld.lifeDay = 0;	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddQuestRecord("JungleGirl", "11");	
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));	
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();			
		break;
		
		case "GirlEnc_21":
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < rand(100))
			{
				dialog.text = "Capitano, abbiamo un ordine, e se pensi di poterci fermare, ti sbagli.";
				link.l1 = "Vediamo, allora...";
				link.l1.go = "GirlEnc_21End";
			}
			else
			{
				dialog.text = "Eh, "+GetSexPhrase("sei un uomo fortunato","sei una ragazza fortunata")+". Suo padre ha promesso una generosa ricompensa a chi la riporterà da lui.";
				link.l1 = "Non disperare - hai ancora molte ricompense davanti a te.";
				link.l1.go = "exit";			 
			}
		break;
		
		case "GirlEnc_21End":
			DialogExit();
			AddQuestRecord("JungleGirl", "12");
			AddQuestUserData("JungleGirl","sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			CloseQuestHeader("JungleGirl");
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
			sld.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");				
		break;
		// <-- генератор "A damsel in the jungle"
		// --> belamour ночной приключенец
		case "NightAdventure_CitizenHomieSolder":
			dialog.text = "Sì, con me. Lascia che si sieda dietro le sbarre, a pensare al suo comportamento. E se sei venuto a minacciarmi per lui, allora credimi: posso arrivare anche al comandante del forte.";
			link.l1 = "Sì, non sono venuto per minacciare, ma per chiederti di ritirare le tue pretese contro di lui. Vedi, è un vecchio conoscente mio, si è solo ubriacato, ma per un ubriaco, sai, il mare è profondo fino alle ginocchia ...";
			link.l1.go = "NightAdventure_CitizenHomieSolder_1";
		break;
		
		case "NightAdventure_CitizenHomieSolder_1":
			dialog.text = "Insomma, mi ha dato un occhio nero mentre ero in servizio, e ora dovrebbe essere rilasciato? Perché dovrebbe accadere?";
			link.l1 = "Che ne dici di cinquecento pesos come scusa per il suo comportamento?";
			link.l1.go = "NightAdventure_CitizenHomieSolder_2";
		break;
		
		case "NightAdventure_CitizenHomieSolder_2":
			dialog.text = "Pensi questo? Ha offeso il mio onore, e pensi che possa essere perdonato per cinquecento pesos? Pensi che il mio onore possa essere comprato?";
			link.l1 = "...";
			link.l1.go = "NightAdventure_CitizenHomieSolder_3";
		break;
			
		case "NightAdventure_CitizenHomieSolder_3":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderNM")
			{
				DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
				pchar.quest.NightAdventure_SeaExit.over = "yes";
				pchar.quest.NightAdventure_JungleExit.over = "yes";
				SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
				dialog.text = "No, Capitano, è tutto giusto. Se l'è meritato. E ti chiedo di non distrarmi più dal mio servizio.";
				link.l1 = "Beh, hai ragione.";
				link.l1.go = "exit";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderGM")
			{
				dialog.text = "Mille. E nemmeno un peso in meno.";
				link.l1 = "No, forse non sono pronto a pagare così tanto per un livido.";
				link.l1.go = "NightAdventure_CitizenHomieSolder_3NM";
				if (sti(pchar.money) >= 1000)
				{
					link.l2 = "Oh... Va bene, aspetta. Ecco una penna e un pergamento subito. Scrivi che stai rinunciando a qualsiasi reclamo contro il mio amico.";
					link.l2.go = "NightAdventure_CitizenHomieSolder_3GM";
				}
			}
		break;
		
		case "NightAdventure_CitizenHomieSolder_3NM":
			DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			dialog.text = "Allora ti chiedo di non distrarmi più dal mio servizio.";
			link.l1 = "Non lo farò.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_CitizenHomieSolder_3GM":
			DeleteAttribute(pchar,"GenQuest.NightAdventureSolNum");
			pchar.GenQuest.NightAdventureToPrisoner = true;
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Eccoti qui.";
			link.l1 = "Buona fortuna nel lavoro.";
			link.l1.go = "exit";
		break;
		// <-- ночной приключенец
		
		// --> Sinistra Длинные тени старых грехов
		case "Knippel_Soldiers_1":
			dialog.text = "E magari insegnare loro alcuni dei tuoi segreti, così non li porti alla tomba con te?";
			link.l1 = "Eh-eh, uh, no, compagno, i miei segreti sono solo miei, e che tipo di segreti sarebbero allora?";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_1");
			pchar.questTemp.Knippel.Soldiers_2 = true;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Knippel_Soldiers_2":
			dialog.text = "Capito, stai per tirarti indietro di nuovo, come sempre.";
			link.l1 = "Ebbene, se il pesce scivola via - è un cattivo pescatore. È come con le palle di cannone - una buona non ti delude mai, basta mirare bene...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_2");
			pchar.questTemp.Knippel.Soldiers_3 = true;
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "Knippel_Soldiers_3":
			dialog.text = "Almeno tu non ti alzi ogni notte. E passi più tempo sulla nave che sulla terraferma. A chi stai parlando?";
			link.l1 = "Ah, cosa sai tu delle difficoltà del servizio, compagno! Com'era nella Marina Reale!.. Non puoi nemmeno immaginare.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_3");
			LAi_CharacterDisableDialog(npchar);
		break;
		// <-- Длинные тени старых грехов
		
		//замечение по обнажённому оружию
		case "SoldierNotBlade":
			// belamour legendary edition если у герой офицер нации -->
			if(IsOfficerFullEquip())
			{
			dialog.text = "Capitano, vi chiedo di riporre le vostre armi: è vietato sguainarle nella nostra città.";
			link.l1 = LinkRandPhrase("Va bene, lo metterò via...","Gia fatto.","Come dici tu...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Vaffanculo!","Immagino che lo userò!","Lo metterò via quando sarà il momento giusto.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;
			}
			// <-- legendary edition
			dialog.text = LinkRandPhrase("Ehi, cosa ti prende a sventolare così quella arma?! Riponila subito!","Ti ordino di riporre subito la tua arma!","Ehi, "+GetAddress_Form(NPChar)+", smetti di spaventare la gente! Metti via la tua arma.");
			link.l1 = LinkRandPhrase("Va bene, lo metto via...","Gia fatto.","Come dici tu...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Vaffanculo!","Immagino che lo userò!","Lo metterò via quando sarà il momento giusto.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;

		case "pirate_fight":
			DialogExit();
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_Attack(NPChar, Pchar);
			DoQuestFunctionDelay("TownPirate_battle", 0.5);
		break;
	}
}
