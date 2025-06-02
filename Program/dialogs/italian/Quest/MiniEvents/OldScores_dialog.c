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
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "Cosa vuoi, amico?";
			link.l1 = "Niente.";
			link.l1.go = "exit";
		break;

		case "OS_Matros_sluh":
			if (!CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe" && sti(pchar.rank) >= 5)
			{
				dialog.text = RandPhraseSimple("Ehi, "+GetSexPhrase("compare","ragazza")+", hai visto il mio stivale da qualche parte? Qualche lurido furfante me l’ha fregato mentre dormivo sbronzo sotto il tavolo della taverna.","Si dice che ieri ci sia stata una rissa nella taverna... Ma chi ci fosse di mezzo, nessuno lo sa. La mia faccia sembra intatta. Credo.","Per tutti i diavoli dell’oceano, ieri avevo la borsa piena d’oro! Dove diamine s’è cacciata adesso?!");
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "OS_Matros_sluh";

				SetQuestHeader("OS");
				AddQuestRecord("OS", "1");
				pchar.questTemp.OS_Start = true;
				pchar.questTemp.OS_Tavern_1 = true;
				AddLandQuestMark(characterFromId("PuertoPrincipe_tavernkeeper"), "questmarkmain");
			}
			else
			{
				switch (rand(2))
				{
					case 0:
						dialog.text = "Ehi, "+GetSexPhrase("compare","ragazza")+", hai visto il mio stivale in giro? Qualche lurido furfante me l’ha soffiato mentre dormivo sbronzo sotto il tavolo della taverna.";
						link.l1 = "Stai più attento, o ci lasci pure l’altro occhio.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;

					case 1:
						dialog.text = "Si dice che ieri ci sia stata una rissa nella taverna... Ma chi se le sia date di santa ragione, chi può dirlo. La mia faccia pare intera. Credo.";
						link.l1 = "Forse han pensato che la tua faccia ha già preso bastonate a sufficienza.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;

					case 2:
						dialog.text = "Per tutti i diavoli degli abissi, ieri avevo la borsa piena d’oro! Dov’è finita adesso, maledizione?!";
						link.l1 = "Per un vero pirata, l’oro non è il bottino più prezioso. La libertà vale assai di più.";
						link.l1.go = "exit";
						NextDiag.TempNode = "OS_Matros_sluh";
					break;
				}
			}
		break;

		case "OS_Matros_again":
			switch (rand(2))
			{
				case 0:
					dialog.text = "Cos'altro vuoi? Non vedi che la testa mi scoppia? Vattene al diavolo.";
					link.l1 = "Forse se bevessi di meno, potresti sembrare un vero uomo invece che un relitto fradicio.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 1:
					dialog.text = "Lasciami stare... Mi scoppia la testa!";
					link.l1 = "Notevole che tu abbia ancora la testa attaccata al collo.";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;

				case 2:
					dialog.text = "Maledetto tu sia... Lasciami in pace, non vedi che non sono in condizione di ciarlare!";
					link.l1 = "...";
					link.l1.go = "exit";
					NextDiag.TempNode = "OS_Matros_again";
				break;
			}
		break;
		
		case "OS_Matros":
			dialog.text = "Fatti da parte! Non vedi che sono al limite? Le mie mani fremono dalla voglia di spaccare qualche mascella.";
			link.l1 = "Calmati, marinaio. Voglio solo sapere cosa è successo ieri alla taverna.";
			link.l1.go = "OS_Matros_2";
			DelLandQuestMark(npchar);
		break;

		case "OS_Matros_2":
			dialog.text = "Maledizione e dannazione! Sei tu "+GetSexPhrase("un altro dei tanti amanti di quella sguaiata servetta svitata","un parente")+"? Che diavolo vuoi, che tu possa essere gettato in mare da una tempesta! Vuoi sfidarmi a duello, eh? O tirerai fuori la lama qui e adesso?";
			if (pchar.sex == "woman")
			{
				link.l1 = "Un parente? Non direi proprio. Ma tu, compare, non mi sembri averne una gran considerazione di lei, eh?";
				link.l1.go = "OS_Matros_3_scrit";
			}
			else
			{
				link.l1 = "Un amante? Direi proprio di no. Quella sgualdrina pare puntare più sulla quantità che sulla qualità nelle sue conquiste, non trovi?";
				link.l1.go = "OS_Matros_3_scrit";
				link.l2 = "Dei suoi affari non me ne importa un fico secco. Dimmi solo cos'è successo, e ti lascerò in pace. Sei stato tu a farla andare su tutte le furie, vero?";
				link.l2.go = "OS_Matros_3_fortuna";
			}
		break;
		
		case "OS_Matros_3_scrit":
			dialog.text = "Quella femmina è furba come una gatta da stiva affamata: arraffa quel che trova e poi si vede! Mi fissava tutta la sera, ammiccando come una micia in cerca di briciole in taverna. Ma appena ho tentato di gettare l’ancora nel suo porto – ha strillato così forte che pure i pesci della baia si sono inabissati per lo spavento!";
			link.l1 = "Forse avevi tracannato troppo rum e ti sei fatto avanti con troppa audacia?";
			link.l1.go = "OS_Matros_4";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "OS_Matros_3_fortuna":
			dialog.text = "Quella diavolessa è schizzinosa quanto un marinaio affamato dopo mesi di navigazione – arraffa il primo che capita e poi si vedrà! Mi lanciava occhiate tutta la sera, civettando come una gatta di taverna in cerca d’avanzi. Ma appena ho tentato di gettare l’ancora nel suo porto – ha strillato così forte che i pesci nella baia sono scappati negli abissi!";
			link.l1 = "Forse avevi tracannato troppo rum e ti sei fatto avanti con troppa sfacciataggine?";
			link.l1.go = "OS_Matros_4";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "OS_Matros_4":
			dialog.text = "Forse avevo alzato un po’ il gomito, ma ricordo limpido come un mare piatto quel che accadde laggiù. Non ero io a darle la caccia – era lei che mi girava attorno come uno squalo che fiuta il sangue. Mi stava addosso per tutto il dannato giorno!";
			if (pchar.sex == "woman")
			{
				link.l1 = "E per una faccenda così da nulla sei già pronto a menar le mani col primo che incontri? O c'è stato forse qualcos'altro quella sera?";
			}
			else
			{
				link.l1 = "Ascolta bene, hai detto 'un altro amante'. Sai qualcosa delle sue scappatelle?";
			}
			link.l1.go = "OS_Matros_5";
		break;

		case "OS_Matros_5":
			dialog.text = "Dopo che le sue urla si sono placate, i miei compagni di bordo mi dissero che stavo sprecando il fiato tentando la sorte con lei. Pare che abbia già uno spasimante in città, tutto pappa e ciccia col nostro capitano.";
			link.l1 = "Affascinante. Hai notato qualcos’altro di strano? Forse qualcuno che si avvicinava al bancone durante il trambusto?";
			link.l1.go = "OS_Matros_6";
		break;

		case "OS_Matros_6":
			dialog.text = "Maledetto tutto... La testa mi scoppia come una chiglia sugli scogli, e tu vieni qui con le tue dannate domande. Non ho visto né sentito un accidente. Faresti meglio a mollare qualche peso invece di tormentare un vecchio lupo di mare con questo interrogatorio.";
			if (sti(pchar.Money) >= 100)
			{
				link.l1 = "Ecco cento pesos. Sta' attento a non tracannare fino a perdere il senno e finire di nuovo sotto l'incantesimo di quella servetta, eh?";
				link.l1.go = "OS_Matros_7_harizma";
			}
			link.l2 = "Te la caverai senza il mio denaro. Altrimenti finirai solo ubriaco fradicio a importunare di nuovo quella cameriera.";
			link.l2.go = "OS_Matros_7_fortuna";
		break;
		
		case "OS_Matros_7_harizma":
			DialogExit();
			
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddQuestRecord("OS", "3");
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.OS_Tavern_2 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_waitress"), "questmarkmain");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
					sld.dialog.currentnode = "OS_Matros_again";
				}
			}
		break;
		
		case "OS_Matros_7_fortuna":
			DialogExit();
			
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddQuestRecord("OS", "3");
			pchar.questTemp.OS_Tavern_2 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_waitress"), "questmarkmain");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.dialog.filename = "Quest\MiniEvents\OldScores_dialog.c";
					sld.dialog.currentnode = "OS_Matros_again";
				}
			}
		break;
		
		case "OS_Dialog_1":
			if (pchar.sex == "woman")
			{
				dialog.text = "Ehi, Jack! Hai una sgualdrina del porto nei tuoi alloggi! Ah-ah! Guarda che roba — una vera diavoletta, niente male! Chissà, ha già frugato in tutte le nostre casse o l’abbiamo interrotta sul più bello?";
				link.l1 = "...";
			}
			else
			{
				dialog.text = "Ehi, Jack! Guarda un po’ chi abbiamo qui – un topo di stiva! Ah-ah! Guarda che canaglia! S’è già ficcato tra i nostri forzieri, il furfante strisciante!";
				link.l1 = "...";
			}
			link.l1.go = "OS_Dialog_2";
		break;

		case "OS_Dialog_2":
			StartInstantDialog("OS_Jack", "OS_Dialog_3", "Quest\\MiniEvents\\OldScores_dialog.c");
		break;

		case "OS_Dialog_3":
			if (pchar.sex == "woman")
			{
				dialog.text = "Una gallinella audace, eh. Mettersi a sgattaiolare nel covo di Jack Veils — ci vuol fegato, pochi ci provano. Allora, che ti porta qui, bella? Sei venuta a farci divertire, forse?";
				link.l1 = "Distrarvi? Ah! Siete proprio dei sognatori, signori. Sono qui per riprendermi ciò che avete rubato. Credevate davvero che la vostra miserabile scenetta passasse inosservata?";
			}
			else
			{
				dialog.text = "Un vero verme audace, per Dio. Sfondare la porta di casa di Jack Veils non è roba da tutti. Dunque, che affari ti portano qui?";
				link.l1 = "Diciamo solo che sto recuperando della roba rubata. O davvero pensavate, signori miei, che la vostra miserabile messinscena passasse inosservata?";
			}
			link.l1.go = "OS_Dialog_4";
		break;

		case "OS_Dialog_4":
			StartInstantDialog("OS_capWolf", "OS_Dialog_5", "Quest\MiniEvents\OldScores_dialog.c");
		break;

		case "OS_Dialog_5":
			if (pchar.sex == "woman")
			{
				dialog.text = "Prestazione pietosa?! Che il diavolo mi arrostisca, ti scuoio vivo e faccio vele con la tua pelle! Ah-ah! Ma forse prima potremmo... divertirci un po' con te, eh?";
				link.l1 = "Vedo che hai fretta di incontrare il tuo creatore? Bene, non ti farò aspettare – avanti, maledetti canaglie!";
			}
			else
			{
				dialog.text = "Farsa pietosa? Che il diavolo mi porti via, ti scuoio la schiena e ne faccio una vela! Basta ciarle – la tua ora è giunta, cane miserabile!";
				link.l1 = "Se è così che la volete, allora avanti, canaglie!";
			}
			link.l1.go = "OS_Dialog_bitva";
		break;
		
		case "OS_Dialog_bitva":
			DialogExit();
			
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("OS_Jack");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			sld = CharacterFromID("OS_capWolf");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "OS_VernuliBochonok");
		break;
		
		case "Zaharia_1":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = ""+sld.name+", dov'è il mio gin?! Se non ce l'hai, ti mando io stesso a dar da mangiare ai pesci in fondo al porto!";
			link.l1 = "...";
			link.l1.go = "Zaharia_2";
			CharacterTurnByChr(npchar, sld);
			//locCameraFromToPos(-2.53, 2.00, 1.26, false, 0.03, 0.00, -1.11);
		break;

		case "Zaharia_2":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = "...";
			link.l1 = "L’ho appena consegnato io stesso. Ecco qui.";
			link.l1.go = "Zaharia_3";
			CharacterTurnByChr(npchar, pchar);
			TakeItemFromCharacter(pchar, "cask_gin");
			Log_Info("You gave the barrel of gin");
		break;

		case "Zaharia_3":
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			dialog.text = "Bene vedere che la mia fiducia in te non è andata sprecata, "+sld.name+". Passa dai miei alloggi domani per i tuoi dobloni.";
			link.l1 = "...";
			link.l1.go = "Zaharia_4";
			CharacterTurnByChr(npchar, sld);
		break;
		
		case "Zaharia_4":
			DialogExit();
			
			//ChangeShowIntarface();
			LAi_SetStayType(pchar);
			
			sld = CharacterFromID("OS_Zaharia");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
			sld.lifeday = 0;
			sld.location = "None";
			
			DoQuestFunctionDelay("OS_RazgovorTavern", 1.5);
		break;
		
		case "Tavern_1":
			dialog.text = "Capitano, riguardo quella targa...";
			link.l1 = "Quale targa? Ah, quella... Perdinci, non ho bisogno di tali onorificenze. Non crucciarti per me.";
			link.l1.go = "Tavern_2";
		break;

		case "Tavern_2":
			dialog.text = "Posso offrirti qualcosa di molto meglio! Da oggi in poi, avrai sempre vitto e alloggio gratuiti nella mia taverna, e da bere quanto vorrai! Uno del tuo calibro merita senz’altro simili onori!";
			link.l1 = "Ah, questo sì che mi va a genio! Privilegi simili li apprezzo davvero! Fino a quando le nostre rotte si incroceranno ancora, "+npchar.name+".";
			link.l1.go = "Tavern_3";
		break;
		
		case "Tavern_3":
			DialogExit();
			
			LAi_SetPlayerType(pchar);
			AddQuestRecord("OS", "5");
			AddQuestUserData("OS", "sSex", GetSexPhrase("","а"));
			pchar.questTemp.OS_Tavern_FreeBuhlo = true;
			ChangeShowIntarface();
			
			sld = CharacterFromID("PuertoPrincipe_tavernkeeper");
			sld.dialog.filename = "Common_Tavern.c";
			sld.dialog.currentnode = "First Time";
			LAi_SetBarmanType(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			
			for (i=1; i<=3; i++)
			{
				if (CharacterIsAlive("OS_Matros_"+i))
				{
					sld = CharacterFromID("OS_Matros_"+i);
					sld.lifeday = 0;
				}
			}
			
			PChar.quest.OS_AttackSea.win_condition.l1 = "location";
			PChar.quest.OS_AttackSea.win_condition.l1.location = "Cuba1";
			PChar.quest.OS_AttackSea.function = "OS_AttackSea";
			
			// вражеский корабль атакует в море
			sld = CharacterFromID("OS_Pirate");
			DeleteAttribute(sld, "AlwaysFriend");
			DeleteAttribute(sld, "ShipEnemyDisable");
			sld.AlwaysEnemy = true;
			LAi_SetImmortal(sld, false);
			
			PChar.quest.TPZ_Potopil.win_condition.l1 = "NPC_Death";
			PChar.quest.TPZ_Potopil.win_condition.l1.character = "OS_Pirate";
			PChar.quest.TPZ_Potopil.function = "OS_Pobeda";
		break;
		
		
		
		
		
		
		
	}
}