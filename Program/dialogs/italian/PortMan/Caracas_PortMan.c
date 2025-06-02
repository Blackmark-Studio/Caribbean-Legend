// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Che tipo di domande?","Cosa vuoi, "+GetAddress_Form(NPChar)+"?"),"Hai già provato a farmi una domanda "+GetAddress_Form(NPChar)+"...","Stai parlando di qualche problema per la terza volta oggi...","Guarda, se non hai nulla da dirmi riguardo agli affari del porto, non disturbarmi con le tue domande.","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ho cambiato idea.","Non ho nulla di cui parlare."),"Mai mente.","Infatti, già la terza volta...","Mi dispiace, ma per ora non sono interessato alle questioni del porto.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			// belamour legengary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet"))
			{
				if(pchar.questTemp.SharkGoldFleet == "toCarPortOffice" || pchar.questTemp.SharkGoldFleet == "start" || pchar.questTemp.SharkGoldFleet == "afterGvik" || pchar.questTemp.SharkGoldFleet == "buyincar")
				{
					link.l1 = "La verità è che sto per andare a Porto Bello un giorno di questi con un carico di merci acquistate da te nella colonia. Ho pensato: forse hai qualche tipo di carico o affari che posso fare lungo il cammino... Per una tariffa, ovviamente.";
					link.l1.go = "SharkGoldFleet";
				}
				if(pchar.questTemp.SharkGoldFleet == "LightVar")
				{
					if(!bImCasual) pchar.quest.SharkGoldFleetToCPO10.over = "yes";
					link.l1 = "Ciao di nuovo. Ho consegnato la tua lettera a Porto Bello. Lì mi hanno chiesto di darti una risposta.";
					link.l1.go = "SharkGoldFleet_09";
				}
				if(pchar.questTemp.SharkGoldFleet == "DifficultVar")
				{
					if(!bImCasual) pchar.quest.SharkGoldFleetToCPO10.over = "yes";
					link.l1 = "Salve. Sono venuto da Porto Bello. Il vostro collega dell'autorità portuale locale mi ha chiesto di consegnarvi questa lettera.";
					link.l1.go = "SharkGoldFleet_13";
				}
			}
			//<-- на пару с Акулой
		break;
		
		// belamour на пару с Акулой -->
		case "SharkGoldFleet":
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet.Fail21"))
			{
				pchar.questTemp.SharkGoldFleet = "toCurierDie";
				AddQuestRecord("SharkGoldFleet", "5");
				SGF_CreateCurierInWorld("");
				dialog.text = "Grazie per la tua preoccupazione, ma non ho casi del genere. C'era effettivamente un incarico, ma sei arrivato letteralmente un paio di giorni in ritardo: ho inviato un veloce corriere lugger per questo scopo.";
				link.l1 = "Capito... Beh, grazie per questo.";
				link.l1.go = "exit";
			}
			else
			{
				if(!bImCasual) pchar.quest.SharkGoldFleet21.over = "yes"; 
				if(!bImCasual) pchar.quest.SharkGoldFleet30.over = "yes"; 
				if(GetCompanionQuantity(pchar) > 1)
				{
					pchar.questTemp.SharkGoldFleet = "toCurierWait";
					AddQuestRecord("SharkGoldFleet", "10");
					SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
					dialog.text = "Vedo che non hai nemmeno una nave. Devi essere un ricco mercante. Hmm ... Ma conosco tutti i mercanti locali con squadroni a vista, ma non ti conosco. Quindi non biasimarmi, ma non posso fidarmi di te con nulla di serio.";
					link.l1 = "Capito... Bene, grazie per questo.";
					link.l1.go = "exit";
				}
				else
				{
					if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
					{
						pchar.questTemp.SharkGoldFleet = "toCurierWait";
						AddQuestRecord("SharkGoldFleet", "11");
						SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
						dialog.text = "Mmm... Ho un compito. Solo che la tua nave non va bene. Mi serve una nave che sia veloce e potente allo stesso tempo, e la tua non soddisfa pienamente questi requisiti. Almeno allo stesso tempo. Quindi per favore perdonami.";
						link.l1 = "Capito... Beh, grazie per questo.";
						link.l1.go = "exit";
					}
					else
					{
						if(!CheckAttribute(pchar,"questTemp.SharkGoldFleet.LicenceOk"))
						{
							pchar.questTemp.SharkGoldFleet = "toCurierWait";
							AddQuestRecord("SharkGoldFleet", "12");
							SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
							dialog.text = "Ho qualcosa da fare... E tu hai una buona nave. Semplicemente non sembra un mercante. E, da quanto posso vedere, non hai una licenza a lungo termine dalla Compagnia Olandese delle Indie Occidentali. Non ti offendere, ma non sembri un mercante. Non posso correre quel rischio.";
							link.l1 = "Capito... Beh, grazie per questo.";
							link.l1.go = "exit";
						}
						else
						{
							if(pchar.questTemp.SharkGoldFleet != "toCarPortOffice" || GetSquadronGoods(pchar, GOOD_COFFEE) < 300 || GetSquadronGoods(pchar, GOOD_CHOCOLATE) < 300)
							{
								pchar.questTemp.SharkGoldFleet = "toCurierWait";
								AddQuestRecord("SharkGoldFleet", "13");
								SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
								dialog.text = "Devo fare qualcosa... E tu hai una buona nave. Solo che ora non capisco che cosa stai andando a commerciare... Hai detto che stavi andando a Porto Bello per vendere la merce, ma, per quanto ne so, non l'hai comprata da noi nella colonia. Non te la prendere, ma non sembri un mercante. Non posso correre quel rischio.";
								link.l1 = "Capito... Beh, grazie per questo.";
								link.l1.go = "exit";
							}
							else
							{
								dialog.text = "Devo fare qualcosa. Certo, non ti conosco... Ma, a dire la verità, ricordo solo i mercanti con squadroni a loro nome. Il resto - no. Sì, e tu hai una licenza a lungo termine, si può vedere subito un mercante esperto. La tua nave, comunque, è interessante. Perché faresti commercio su una fregata?";
								link.l1 = "Hah, questa non è una fregata ordinaria. Può raggiungere velocità molto elevate anche con la stiva piena. È sempre più facile sfuggire ai pirati piuttosto che combatterli, non è vero? Anche se la mia nave ha una capacità inferiore rispetto alle navi mercantili ordinarie, il rischio è molto più basso.";
								link.l1.go = "SharkGoldFleet_01";
							}
						}
						
					}
					
				}
			}
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "Mmm, ma hai ragione! Gli spagnoli sanno come costruire navi, vero? Sì, sì, ho notato subito che questo bel uomo era uscito dai nostri cantieri navali. E sì, mi è stato effettivamente detto oggi che hai comprato una partita di caffè e cacao dal nostro mercante per la rivendita a Porto Bello. Ottimo affare, ti dico. Le persone non familiari con il commercio non sanno che questi prodotti qui sono economici, grazie alle piantagioni, e a Porto Bello sono molto richiesti, dal momento che da lì vanno alla metropoli.";
			link.l1 = "Ebbene, è tutto qui, signore. Per pochi pesos, non guiderei la mia barca così lontano.";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "Ebbene, a dir la verità, ho un affare per te. Ed è molto buono che tu abbia una nave così veloce, che può anche difendersi in caso di emergenza.";
			link.l1 = "Aspetta, signore... Il tuo caso suggerisce che devo combattere...?";
			link.l1.go = "SharkGoldFleet_03";
		break;
		
		case "SharkGoldFleet_03":
			dialog.text = "No, no! In effetti, il mio compito è semplice quanto possibile. Ho bisogno che tu consegni una lettera all'Autorità Portuale di Porto Bello. La lettera è sigillata e non può essere aperta. Nessuno deve parlare neanche di essa, corrispondenza... personale. Consegnare personalmente. Il termine è di dieci giorni. Poi sarà irrilevante.";
			link.l1 = "Così semplice? E quanto riceverò per questo?";
			link.l1.go = "SharkGoldFleet_04";
		break;
		
		case "SharkGoldFleet_04":
			dialog.text = "Cinque mila pesos. Consideralo per non dover inviare un corriere a Porto Bello.";
			link.l1 = "E quali erano le tue domande su di me e la mia nave?";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			dialog.text = "Non importa. È solo che la corrispondenza è abbastanza importante, e devo essere sicuro che raggiungerà il destinatario. E quindi niente di speciale. Burocrazia... Per una persona comune, questi documenti non sono di alcun interesse.";
			link.l1 = "Bene, sono d'accordo. Facciamo avere qui i tuoi documenti. Non appena arrivo a Porto Bello, li porterò al tuo collega. Me la caverò in dieci giorni, non preoccuparti.";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			dialog.text = "Un attimo. Mi dispiace, ho completamente dimenticato il tuo nome. Puoi dirmelo per favore? Devo annotarlo nei documenti.";
			link.l1 = "Il mio nome è Andreas Garcia.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "Grazie. Quindi... Ottimo. Ricorda che sei tu che devi consegnare questo documento direttamente nelle mani del destinatario. Ecco a te. Il premio ti sarà dato dal capo dell'Autorità Portuale a Porto Bello. Buon viaggio!";
			link.l1 = "Grazie! Ora, mi scusi.";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			DialogExit();
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToPB10", 0, 0, 10, false);
			else NewGameTip("Exploration mode: timer is disabled.");
			AddCharacterSkillDontClearExp(pchar, SKILL_LEADERSHIP, 1);
			AddCharacterSkillDontClearExp(pchar, SKILL_SNEAK, 1);
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_SharkGoldFleet_1");
			AddQuestRecord("SharkGoldFleet", "14");
			pchar.questTemp.SharkGoldFleet = "toPBPortOffice";
		break;
		
		case "SharkGoldFleet_09":
			RemoveItems(PChar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_2");
			dialog.text = "Ottimo! Mi hai aiutato molto. Ci sono state delle difficoltà?";
			link.l1 = "No, non ci sono state difficoltà. È vero, il tuo collega ha maledetto te: ha detto che siete tutti avari qui, perché non mandate una nave corriere, ma mercanti di passaggio, e addirittura facendo pendere il pagamento sul destinatario. Ha minacciato che avrebbe scritto un reclamo a L'Avana ...";
			link.l1.go = "SharkGoldFleet_10";
		break;
		
		case "SharkGoldFleet_10":
			dialog.text = "Cosa?! Sono io il brontolone?! Cosa si crede di essere? Prima di tutto, tieni i tuoi cinque... no, sei mila pesos! Sto piangendo onestamente!";
			link.l1 = "Grazie. È bello vedere che il tuo collega si sbagliava sul tuo conto.";
			link.l1.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_11":
			AddMoneyToCharacter(pchar, 6000);
			dialog.text = "E in secondo luogo, questo furfante sembra aver dimenticato come due mesi fa mi abbia scaricato tutte le spese per il mantenimento di una nave mercantile che andava da Caracas a Porto Bello, e da lì a L'Avana! E avevamo concordato che avrebbe pagato per la seconda parte del viaggio! E non ha mai restituito il debito, ma ha promesso che avrebbe saldato tutto il mese scorso! E io sono ancora un avaro ... Sì, scriverò io stesso una denuncia contro di lui a L'Avana!";
			link.l1 = "Ebbene, hai le passioni del cantiere di Madrid, ovviamente ...";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			AddQuestRecord("SharkGoldFleet", "20");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date)
			pchar.questTemp.SharkGoldFleet = "LightVarToShark";
			SetFunctionLocationCondition("SharkGoldFleetToShark", "Curacao", false);
			dialog.text = "No, a pensarci ... Che sfacciato! Va bene, me ne occuperò di nuovo ... E ora ti chiedo di scusarmi: ho degli affari urgenti da sbrigare. È stato un piacere fare affari con te!";
			link.l1 = "E buona fortuna a te!";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_13":
			RemoveItems(PChar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_2");
			dialog.text = "Ottimo! Mi hai aiutato molto. Anche se, ho inviato loro un corriere su una scialuppa, e mi hanno risposto con una nave di passaggio. Eh... E dopo tutto si lamentano ancora che abbiamo avari seduti qua.";
			link.l1 = "Ebbene, forse hanno risparmiato i soldi per il corriere ...";
			link.l1.go = "SharkGoldFleet_14";
		break;
		
		case "SharkGoldFleet_14":
			AddMoneyToCharacter(pchar, 5000);
			AddQuestRecord("SharkGoldFleet", "20");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date)
			pchar.questTemp.SharkGoldFleet = "DifficultVarToShark";
			SetFunctionLocationCondition("SharkGoldFleetToShark", "Curacao", false);
			dialog.text = "Non 'forse', ma sicuramente, ti dico! Va bene, non importa. Ecco, prendi il tuo lavoro. E ora ho un sacco di lavoro, mi scuso.";
			link.l1 = "Ebbene, forse hanno risparmiato i soldi per il corriere...";
			link.l1.go = "exit";
		break;
		// <-- на пару с Акулой
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
