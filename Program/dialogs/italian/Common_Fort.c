// boal 25/04/04 общий диалог солдат форта
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
    /* // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Fort\" + NPChar.City + "_Fort.c";
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
				dialog.text = RandPhraseSimple("Una spia! Rendi la tua arma e seguimi!","Un agente nemico! Afferra "+GetSexPhrase("lui","lei")+"!");
				link.l1 = RandPhraseSimple("Taci, fifone!","Vaffanculo!");
				link.l1.go = "fight"; 
			}
			else
			{
				// eddy. проверяем, не казачок ли. -->
				if (GetRelation2BaseNation(sti(npchar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					dialog.text = RandPhraseSimple("Chi sei e cosa fai qui?","Fermo là! Chi sei? Per quale motivo stai cercando di entrare nel forte?");
					//==> по лицензии
					if (CheckNationLicence(HOLLAND))
					{
						link.l1 = "Ufficiale, io ho "+GetRusNameNationLicence(sti(npchar.nation))+", quindi sono qui per motivi legali. Ecco, per favore dai un'occhiata...";
						link.l1.go = "LicenceOk";
					}
					else
					{
						//==> по флагу
						// заглушка на пирата
						if (sti(pchar.nation) == PIRATE)
						{
    						dialog.text = RandPhraseSimple("Un pirata nel forte?! Afferratelo"+GetSexPhrase("lui","lei")+"!","È un pirata, che annusa qualcosa nel nostro forte! Alla prigione!!!");
							link.l1 = RandPhraseSimple("Sì, sono un pirata, e allora?","Ehi, prendimi se puoi...");
							link.l1.go = "fight"; 
							break;
						}
						if (findsubstr(pchar.location.from_sea, "_town" , 0) != -1) //если причалил в городе
						{
							link.l1 = "Non vedi la bandiera di "+NationNameGenitive(sti(pchar.nation))+" sulla mia albero maestro?!";
						}
						else //если причалил не в городе
						{
							link.l1 = "Ho gettato l'ancora vicino a "+XI_ConvertString(GetIslandByCityName(npchar.city)+"Gen")+" sotto la bandiera di"+NationNameGenitive(sti(pchar.nation))+"! Hai bisogno di qualcos'altro?";
						}
						// belamour legendary edition вызываюий доверие даёт возможность обмануть стражу
						if(sti(pchar.reputation.fame) < 41 && CheckCharacterPerk(pchar, "Trustworthy"))
						{
							notification("Trustworthy", "Trustworthy");
							link.l1.go = "NotPegYou";
						}
						else
						{
							if (GetSummonSkillFromName(pchar, SKILL_SNEAK) < (10+rand(50)+rand(50)))
							{
								notification("Skill Check Failed", SKILL_SNEAK);
								link.l1.go = "PegYou";
							}
							else
							{
								link.l1.go = "NotPegYou";
							}
						}
					}
				}
				// <-- eddy. проверяем, не казачок ли.
				else
				{
					if (sti(NPChar.nation) == PIRATE)
					{
						if (sti(rColony.HeroOwn)) // наш горожанин
						{
			         		switch (rand(10))
							{
								case 0:
									dialog.text = "Oh, capitano, ci siamo divertiti tanto con te in mare! Quante navi abbiamo affondato insieme sotto il tuo comando! E qui...";
									link.l1 = "E qui, amico mio, puoi deliziare i tuoi occhi con signore affascinanti, non le vedrai in mare.";
									link.l1.go = "exit";
								break;

								case 1:
									dialog.text = "Capitano, cosa abbiamo fatto per meritare questo?! Non siamo ratti di terra, vero?";
									link.l1 = "Silenzio, marinaio! Il tuo posto è molto importante e onorabile, quindi smetti di lamentarti.";
									link.l1.go = "exit";
								break;

								case 2:
									dialog.text = "Cosa sta succedendo in mare, capitano? Lo vedremo mai di nuovo?";
									link.l1 = "Ma certo, marinaio! Una volta sollevato dal dovere, puoi dirigerti al molo e goderti il mare quanto vuoi.";
									link.l1.go = "exit";
								break;

								case 3:
									dialog.text = "Voglio lamentarmi, capitano: tutti noi sentiamo la mancanza del mare. Siamo tutti completamente stufi di questo dovere terrestre!";
									link.l1 = "Mi stanco di questo lamento! Hai anche abbastanza rum qui! Servi dove sei stato posizionato dal capitano, o qualcuno sarà impiccato come esempio per gli altri.";
									link.l1.go = "exit";
								break;

								case 4:
									dialog.text = "Ti dirò in confidenza, capitano, il nuovo governatore è un corrotto e un peculatore. Ma in realtà non sono affari miei...";
									link.l1 = "Esatto, corsaro. Il tuo compito è stare al tuo posto e mantenere l'ordine. E impiccare il governatore sull'antenna è affare mio. Buon lavoro!";
									link.l1.go = "exit";
								break;

								case 5:
									dialog.text = "Grazie per non averci dimenticato, capitano! Ti seguiremmo attraverso il fuoco e l'acqua!";
									link.l1 = "Conosco il tuo tipo, furfanti! Tutto ciò che amate veramente è l'oro. C'è una festa alla taverna stasera, le bevande sono per mio conto. Non dimenticate di presentarvi.";
									link.l1.go = "exit";
								break;

								case 6:
									dialog.text = "Eh, capitano! Pensa solo, può un corsaro essere davvero un custode dell'ordine?! È passato tanto tempo da quando abbiamo fatto l'ultimo vero affare!";
									link.l1 = "Nessun tempo per rilassarsi, corsaro! Armate nemiche stanno setacciando le acque vicino alle nostre isole, e dobbiamo essere pronti per un bagno di sangue in qualsiasi momento.";
									link.l1.go = "exit";
								break;

								case 7:
									dialog.text = "Capitano, ho sentito dire che la Corona ha mandato un'altra squadra dalla nostra parte?";
									link.l1 = "Certo, corsaro. Finché viviamo, non ci sarà pace per noi. E anche all'Inferno combatteremo contro i diavoli!";
									link.l1.go = "exit";
								break;

								case 8:
									dialog.text = "Yo-ho-ho! Accidenti, era davvero un liquore forte ieri, capitano! Peccato che tu non fossi lì.";
									link.l1 = "Non è un grosso problema, me la caverò. E non vi invidio, ragazzi.";
									link.l1.go = "exit";
								break;

								case 9:
									dialog.text = "Ti dirò in confidenza, capitano, perché ci hai sempre trattato bene, ci siamo divertiti molto con una ragazza davvero carina ieri...";
									link.l1 = "Eh, corsaro, una forca è proprio quello di cui hai bisogno!";
									link.l1.go = "exit";
								break;

								case 10:
									dialog.text = "Capitano! Per favore, liberami da questo maledetto dovere! Semplicemente non riesco più a fare la parte del custode dell'ordine.";
									link.l1 = "Far la guardia notturna su una nave non è facile. Amico, il dovere è dovere, ovunque e comunque sia.";
									link.l1.go = "exit";
								break;
							}
							// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
							/* link.l2 = RandPhraseSimple("C'è un affare importante!","Ho un affare con te.");
							link.l2.go = "quests";//(перессылка в файл города) */
							break;
						}
					}
					
					//Jason --> мини-квест Дефицитный товар
					if (!CheckAttribute(pchar, "questTemp.Sharlie.FastStart") && sti(pchar.rank) < 4 && !CheckAttribute(pchar, "questTemp.Wine") && npchar.location.group == "soldiers")
					{// Addon 2016-1 Jason пиратская линейка
						string wineCity = "FortFrance";
						if(SandboxMode)
						{
							if(CheckAttribute(pchar,"HeroParam.ToCityId"))
							{
								wineCity = pchar.HeroParam.ToCityId;	
							}
						}
						if(GetCityNameByIsland(LoadedLocation.islandId) ==  wineCity && npchar.location.locator == "protector1")
						{
							dialog.text = "Ehi, compagno! Puoi farmi un piccolo favore?";
							link.l1 = "Dipende da cosa deve essere fatto.";
							link.l1.go = "Wine_soldier";
							link.l2 = "Non ho tempo per questo.";
							link.l2.go = "exit";
							pchar.questTemp.Wine = "true";
							DelLandQuestMark(npchar);
							break;
						}
						if(StartHeroType == 2)
						{
							if(LoadedLocation.id == "Santiago_fort")
							{
								dialog.text = "Ehi, amico! Puoi farmi un piccolo favore?";
								link.l1 = "Dipende da cosa deve essere fatto.";
								link.l1.go = "Wine_soldier";
								link.l2 = "Non ho tempo per questo.";
								link.l2.go = "exit";
								pchar.questTemp.Wine = "true";
								DelLandQuestMark(npchar);
								break;
							}
						}
					}
					// <-- мини-квест Дефицитный товар
					
					//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
					
					// Шарль де Мор генерал-губернатор французских колоний
					if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
					{
						switch(rand(2))
						{
							case 0: 
							dialog.text = "Vostra Eccellenza, Governatore Generale! Che posso servirle?";
							link.l1 = "Non ho bisogno di niente, grazie.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "È un grande onore per me, Signor Governatore Generale! Come posso aiutarla?";
								link.l1 = "Svolgi il tuo servizio coscienziosamente - non richiedo nulla di più da te.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "È un piacere vederti, Sua Eccellenza! Cosa può fare un umile soldato per il governatore generale delle nostre colonie?";
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
							dialog.text = "Vice Ammiraglio, Vostra Eccellenza! Mi permetta di riportare: durante il mio turno...";
							link.l1 = "Calmati, soldato, non ho bisogno del tuo rapporto. Riferisci al tuo capo.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Lieto di vederti, Viceammiraglio! Posso aiutarti in qualche modo?";
								link.l1 = "No, stavo solo controllando quanto sei attento. Sono contento che mi hai riconosciuto.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Vice Ammiraglio, questo è un onore per me! Cosa posso fare per te?";
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
							dialog.text = "Saluti, capitano! Se avete delle istruzioni per me, allora chiedo scusa: anche se sono al vostro servizio "+NationNameGenitive(sti(npchar.nation))+", rispondo solo al comandante e al governatore."; 
							link.l1 = "Ho i miei ufficiali e l'equipaggio che rispondono alla mia guida. Fai il tuo dovere, soldato.";
							link.l1.go = "exit";
							break;

							case 1:
								dialog.text = "Capitano, potresti portarmi a servire sulla tua nave? Lo stesso servizio per "+NationNameGenitive(sti(npchar.nation))+", ma preferisco il mare."; 
								link.l1 = "Sei necessario dove sei stato assegnato, quindi svolgi il tuo servizio con onore. Chiudi gli occhi per un secondo e ti porteranno al mare.";
								link.l1.go = "exit";
							break;

							case 2: 
								dialog.text = "Oh, sei fortunato: sei un capitano del vascello al servizio di "+NationNameGenitive(sti(npchar.nation))+"... E sono bloccato qui tutto il giorno."; 
								link.l1 = "Pensi che sia arrivato nei Caraibi e sia diventato capitano una settimana dopo? Sono tutti anni di duro lavoro...";
								link.l1.go = "exit";
							break;
						}
						break;
					}
					// <-- legendary edition

					switch (rand(10))
					{
						case 0: ////////////////////////////////////////
							dialog.text = "Non vedi? Sono di servizio. Smettila di infastidirmi.";
							link.l1 = "Va bene, va bene...";
							link.l1.go = "exit";
						break;

						case 1:
							dialog.text = "Stai per raccontarmi di qualche attività sospetta?";
							link.l1 = "No, per niente, e tra l'altro sono un capitano. Vedo che non stai più ascoltando? Addio.";
							link.l1.go = "exit";
						break;

						case 2: ///////////////////////////////////////////
							dialog.text = "Questo è un impianto militare, quindi non fare troppo rumore qui.";
							link.l1 = "Bene, lo terrò a mente.";
							link.l1.go = "exit";
						break;

						case 3:
							dialog.text = "Un tempo così bello, e io devo stare qui. In città, almeno ci sono ragazze, e cosa abbiamo qui? Solo topi in giro.";
							link.l1 = ""+GetSexPhrase("Mi dispiace, ma non c'è nulla che io possa fare per aiutarti - è pur sempre il tuo dovere.","Ehi! Cosa c'è che non va in me? Non sono una ragazza?")+"";
							link.l1.go = "exit";
						break;

						case 4: ///////////////////////////////////////////
							dialog.text = "Se ti piace parlare, trova qualcun altro. Devo mantenere l'ordine qui, e non ho tempo per chiacchiere inutili.";
							link.l1 = "Oh, no, sto solo controllando, se sei ancora vivo. Stavi in piedi proprio come una statua.";
							link.l1.go = "exit";
						break;

						case 5: ////////////////////////////////////////////
							dialog.text = "Probabilmente pensi che le giornate di lavoro in guarnigione siano una passeggiata? Assolutamente no! È un lavoro duro e importante. Ricordo una volta...";
							link.l1 = "Mi racconterai quella storia un'altra volta. Ora ho un po' di fretta.";
							link.l1.go = "exit";
						break;

						case 6: ////////////////////////////////////////////
							dialog.text = "Stai attento qui, sei in un forte! Sii silenzioso come un topo!";
							link.l1 = "Come dici tu, soldato.";
							link.l1.go = "exit";
						break;

						case 7:
							dialog.text = "Ehi! Hai dell'acqua, per caso? Sto morendo di sete.";
							link.l1 = "No, amico, mantieni la tua pazienza...";
							link.l1.go = "exit";
						break;

						case 8://///////////////////////////////////////////
							dialog.text = "Che noia è la vita della guarnigione, solo bifolchi come te in giro! Ora, la guarnigione della città sicuramente vive tempi migliori...";
							link.l1 = "E tu chiami questo 'essere in servizio'? In questo modo sicuramente lascerai passare una spia!";
							link.l1.go = "exit";
						break;

						case 9://///////////////////////////////////////////
							dialog.text = ""+GetSexPhrase("Sembrate un tipo forte, vero? Vi piacerebbe arruolarvi nella guarnigione del forte? Abbiamo caserme spaziose, due pasti al giorno e alcol gratis.","Oh, giovane signora, non hai idea di quanto sia piacevole incontrare una così gentile damigella in questo posto dimenticato da Dio!")+"";
							link.l1 = ""+GetSexPhrase("È certamente allettante, ma devo ancora rifiutare. Tutta quella fatica in caserma non fa per me.","Grazie per il complimento, soldato.")+".";
							link.l1.go = "exit";
						break;

						case 10:
							dialog.text = "Questo maledetto caldo... Darei volentieri metà della mia vita per tornare in Europa.";
							link.l1 = "Sì, vedo che la tua salute non è adatta al clima locale.";
							link.l1.go = "exit";
						break;
					}
					// belamour legendary edition в квестах не используется, да, и лишний раз игроков не нужно заставлять по кейсам бегать. Квесты пишите в коммоне
					/* link.l3 = "Eh... capisco. Ecco cosa "+GetSexPhrase("voleva","хотела")+" chiedere...";
					link.l3.go = "quests";//(перессылка в файл города) */
				}
			}
		break;
		
		//Jason --> мини-квест Дефицитный товар
		case "Wine_soldier":
			dialog.text = "Vedi, desidero tanto del vino... Ma non la porcheria locale fatta di frutta marcia, che si vende per due pesos al barile - voglio una bottiglia di vero vino europeo. Puoi ottenerlo in città dai mercanti. È piuttosto costoso, ma pagherò in pieno e aggiungerò perfino trecento pesos in più. Quindi, mi porterai un po'?";
			link.l1 = "E perché non puoi prenderlo da solo? Non dovrai pagare di più, aspetta solo di essere sollevato dal tuo posto e poi vai. Dov'è l'inghippo?";
			link.l1.go = "Wine_soldier_1";
		break;
		
		case "Wine_soldier_1":
			dialog.text = "Non c'è nessun trucco. Semplicemente non posso lasciare il forte per andare in città finché non ottengo il mio permesso, il che non succederà presto. Inoltre, il nostro comandante ha proibito severamente tutto il bere nel forte, maledetto! Quindi, aiuterai un soldato?";
			link.l1 = "Ebbene, perché no? Ti porterò quel vino, ho del tempo libero comunque.";
			link.l1.go = "Wine_soldier_2";
			link.l2 = "Mi dispiace, compagno, ma non posso farlo. Cerca qualcun altro per aiutarti.";
			link.l2.go = "exit";
		break;
		
		case "Wine_soldier_2":
			dialog.text = "Benissimo! Grazie mille! Oggi sto facendo la guardia, quindi vieni domani. Mi troverai in cima al forte, lì puoi passarmi la bottiglia, così nessuno se ne accorge...";
			link.l1 = "Bene. Aspettami, verrò a trovarti domani.";
			link.l1.go = "exit";
			pchar.questTemp.Wine.id = npchar.ID;
			pchar.questTemp.Wine.SName = GetFullName(npchar);
			pchar.questTemp.Wine.bottle = "true";
			npchar.lifeday = 5;
			SetFunctionTimerCondition("Wine_Exchange", 0, 0, 1, false);
			pchar.questTemp.Wine.City = GetCityNameByIsland(LoadedLocation.islandId);
			if(StartHeroType == 2) pchar.questTemp.Wine.City = "Santiago";
			Log_TestInfo(pchar.questTemp.Wine.City);
			SaveCurrentQuestDateParam("questTemp.Wine_bottle");
			AddQuestRecord("Wine", "0");
			SetFunctionLocationCondition("WineTraderQM", pchar.questTemp.Wine.City+"_town", 0);
		break;
		// <-- мини-квест Дефицитный товар
		
		//============================== ноды на разборки при распознавании =========================
		case "PegYou":
			dialog.text = RandPhraseSimple("Mi sembra una sorta di inganno. Parliamo con il comandante, "+GetSexPhrase("compagno","caro")+", e capire tutto...","Hmm... Qualcosa mi dice che non sei chi fingi di essere... Arrenditi e consegna la tua arma "+GetAddress_Form(npchar)+", e seguimi per ulteriori indagini!");
			link.l1 = RandPhraseSimple("Vaffanculo!","Quando due domeniche arrivano in una settimana...");
			link.l1.go = "fight";
			if (sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "NotPegYou":
			dialog.text = RandPhraseSimple("Oh, capisco... Tutto sembra a posto, sei libero di andare, "+GetAddress_Form(pchar)+".","Devo essere un po' stanco di stare di guardia... Sembra che tutto sia a posto, "+GetAddress_Form(pchar)+", mi dispiace.");
			link.l1 = "Nessun problema!";
			link.l1.go = "exit";
			if (sti(pchar.questTemp.stels.landFort) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
				pchar.questTemp.stels.landFort = GetDataDay();
			}
		break;
		case "LicenceOk":
			iTemp = GetDaysContinueNationLicence(HOLLAND);
			if (ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -12)
			{
				dialog.text = "Ma pensa un po'! Che sfacciataggine! Venire qui sotto le sembianze di un mercante! Il tuo ritratto è affisso in ogni caserma, maledetto! Questa volta non te la caverai! Prendetelo!";
				link.l1 = RandPhraseSimple("Arrgh!..","Ebbene, l'hai chiesto tu...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (findsubstr(pchar.location.from_sea, "_town" , 0) == -1) //если причалил не в городе
			{
				dialog.text = "Sei venuto qui per commerciare? Posso chiedere come? Dov'è la tua nave? Sai, tutto sembra molto sospetto, e sono costretto a trattenerti fino a quando non avremo risolto tutto. Arrenditi la tua arma e seguimi!";
				link.l1 = RandPhraseSimple("Fottiti!","Quando arrivano due domeniche in una settimana...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (iTemp == -1)
			{
				dialog.text = "La tua licenza deve essere revocata poiché è scaduta e per questo motivo non è valida. Consegnami la tua arma e seguimi per ulteriori indagini!";
				link.l1 = RandPhraseSimple("Vaffanculo!","Quando arrivano due domeniche in una settimana...");
				link.l1.go = "fight";	
				TakeNationLicence(HOLLAND);
				break;
			}
			if (iTemp == 0)
			{
				dialog.text = "Hmm... Tutto sembra a posto. Tuttavia, devo notare che la tua licenza scade oggi. Ti farò passare questa volta, ma dovrai comunque ottenere una nuova licenza.";
				link.l1 = "Grazie, lo farò al più presto possibile.";
				link.l1.go = "exit";			
			}
			if (iTemp > 0 && iTemp <= 10)
			{
				dialog.text = "Mmm... Tutto sembra a posto. Devo comunque far notare che la tua licenza scadrà presto. È ancora valida solo per "+FindRussianDaysString(iTemp)+". Quindi tienilo a mente, "+GetAddress_Form(npchar)+".";
				link.l1 = "Grazie, ne prenderò uno nuovo non appena possibile.";
				link.l1.go = "exit";			
			}
			if (iTemp > 10)
			{
				dialog.text = LinkRandPhrase("Bene, tutto sembra a posto. La tua licenza è valida per "+FindRussianDaysString(iTemp)+". Puoi passare.","Tutto è chiaro, "+GetAddress_Form(npchar)+". Puoi entrare e uscire liberamente dalla città, la tua licenza è valida per  "+FindRussianDaysString(iTemp)+". Scusa per il disturbo.","Tutto sembra a posto, "+GetAddress_Form(npchar)+", non ti sto più trattenendo qui.");
				link.l1 = RandPhraseSimple("Eccellente. Cordiali saluti.","Grazie, ufficiale.");
				link.l1.go = "exit";
			}
		break;

		//замечение по обнажённому оружию
		case "SoldierNotBlade":
			// belamour legendary edition если у герой офицер нации -->
			if(IsOfficerFullEquip())
			{
				dialog.text = "Capitano, vi chiedo di riporre le vostre armi: è vietato sguainarle nella nostra città.";
				link.l1 = LinkRandPhrase("Va bene, lo metto via...","Gia fatto.","Come dici tu...");
				link.l1.go = "exit";
				link.l2 = LinkRandPhrase("Vaffanculo!","Suppongo che lo userò!","Lo metterò via quando sarà il momento giusto.");
				link.l2.go = "fight";
				npchar.greeting = "soldier_common";
				NextDiag.TempNode = "First Time";
				break;
			}
			// <-- legendary edition
			dialog.text = LinkRandPhrase("Perché diavolo stai correndo in giro con una lama sguainata? Riponi subito la tua arma!","Ti ordino di infilare subito la tua arma!","Ehi, "+GetSexPhrase("compagno","ragazza")+", smetti di spaventare la gente! Infila la tua arma.");
			link.l1 = LinkRandPhrase("Bene.","Bene.","Come dici tu...");
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("Vaffanculo!","Non c'è niente di male nel sognare...","Quando due domeniche arrivano in una settimana.");
			link.l2.go = "fight";
			npchar.greeting = "soldier_common";
			NextDiag.TempNode = "First Time";
		break;
	}
}
