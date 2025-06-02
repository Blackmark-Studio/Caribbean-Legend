// Жоаким Мерриман - португальский сумрачный гений
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbySeekIsland" && !CheckAttribute(npchar, "quest.HWICHoll.Task"))
				{
					dialog.text = "Buon dì, messere! Son il Dottor Joachim Merriman. Ho l’onore di rivolgermi al Capitano "+GetFullName(pchar)+"?";
					link.l1 = "Aye, son proprio io. Ma per tutti i diavoli, come fai a sapere il mio nome? Non ricordo d'aver mai incrociato la tua rotta prima d’ora.";
					link.l1.go = "JoakimSeekSkull";
					break;
				}
				if (CheckCharacterItem(pchar, "SkullAztec"))
				{
					dialog.text = "Sono lieto di vederti, capitano. Dal passo leggero capisco che stai per farmi davvero felice. Hai il teschio di Yum Cimil?";
					link.l1 = "Ho il teschio di cui parli. Scoppietta d’energia, come una fornace infernale.";
					link.l1.go = "JoakimFindSkull";
					break;
				}
				dialog.text = "Hai qualcos'altro da dire, capitano?";
				link.l1 = "No, signor Merriman. Me ne vado..";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "JoakimMeeting" && !CheckAttribute(npchar, "quest.HWICHoll.Task"))
				{
					dialog.text = "Buon giorno, signore! Sono il dottor Joachim Merriman. Ho l’onore di rivolgermi al Capitano "+GetFullName(pchar)+"?";
					link.l1 = "Già, son proprio io. Come diavolo conosci il mio nome? Non mi pare d’averti mai visto prima.";
					link.l1.go = "JoakimSeekSkull";
					break;
				}
				if (CheckCharacterItem(pchar, "SkullAztec"))
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("Villemstad");
					dialog.text = "Sono lieto di vederti, capitano. Dal passo svelto capisco che hai buone notizie per me. Hai forse il teschio di Yum Cimil?";
					link.l1 = "Ho il teschio di cui parli. Scoppietta d’energia, come una fornace infuriata.";
					link.l1.go = "JoakimFindSkull";
					break;
				}
				dialog.text = "Hai qualcos’altro da dire, capitano?";
				link.l1 = "No, Dottor Merriman. Me ne vado.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Buon giorno. Cercate qualcosa da me?";
			link.l1 = "No, mi dispiace.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Landlady"://хозяйка дома
			dialog.text = "Se siete venuto a cercare il dottor Merriman, non è qui. Non abita più in questa casa.";
			link.l1 = "Capisco.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady";
		break;
		
		case "Landlady_1"://хозяйка дома
			dialog.text = "Se sei venuto a cercare il dottor Merriman, devo dirti che non è in casa. Al momento è in viaggio e non so quando farà ritorno.";
			link.l1 = "Capisco.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady_1";
		break;
		
		case "Landlady_2"://хозяйка дома
			dialog.text = "Se cercavi il dottor Merriman, non lo troverai qui. Non abita più in questa casa.";
			link.l1 = "Capisco.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady_2";
		break;
		
		case "JoakimSeekSkull":
			PlaySound("Voice\English\hambit\Joakim Merriman-01.wav");
			dialog.text = "I tuoi affari non sono così segreti come credi, capitano! Ma non temere, ho una proposta per te! Sono un uomo di scienza, una sorta di filosofo naturale che studia la cultura affascinante dei pagani indiani delle Terre Spagnole e delle Indie Occidentali. Saresti così gentile da accompagnarmi a casa mia per discutere, nel mio salotto, certi dettagli che potrebbero fruttarci una fortuna?";
			link.l1 = "Hai stuzzicato sia la mia curiosità che la mia attenzione. Mostrami la rotta.";
			link.l1.go = "JoakimSeekSkull_1";
		break;
		
		case "JoakimSeekSkull_1":
			dialog.text = "Non potete rifiutare, signore! La mia dimora non è lontana da qui. Seguitemi!";
			link.l1 = "...";
			link.l1.go = "JoakimSeekSkull_2";
		break;
		
		case "JoakimSeekSkull_2":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "Villemstad_houseSp1_room", "goto", "goto1", "JoakimInRoom", -1);
		break;
		
		case "JoakimSeekSkull_3":
			PlaySound("Voice\English\hambit\Joakim Merriman-01.wav");
			dialog.text = "Qui possiamo parlare senza timore di orecchie indiscrete. Sei stato di recente dal mio vicino, Solomon Shneur. Passeggiavo nei dintorni e, perdonami capitano, per puro caso ho colto qualche dettaglio della tua conversazione con Solomon. Era tutto così intrigante che non ho potuto fare a meno di ascoltare fino in fondo!";
			link.l1 = "Una spia che teme le spie, eh?";
			link.l1.go = "JoakimSeekSkull_4";
		break;
		
		case "JoakimSeekSkull_4":
			dialog.text = "Su, su, capitano! Non è affatto come pensate! Salomone è il mio vicino, spesso viene a trovarmi. Siamo buoni amici, nonostante la differenza di fede! So delle sue sventure... come tutti a Willemstad! Salomone racconta i suoi guai a chiunque abbia orecchie, a ogni ora del giorno. Ma lasciamo stare. Quel vecchio giudeo vi avrà già parlato d’un teschio di giada nascosto insieme al suo oro su qualche isola sconosciuta. Ve ne ha fatto cenno, vero?";
			link.l1 = "Mi parlò di un teschio, ma non disse mai che fosse di giada. Disse pure che era il cranio di suo nonno, e a dire il vero pensai che fosse o qualche diavoleria cabalistica, oppure che il vecchio matto avesse qualche grillo per la testa.";
			link.l1.go = "JoakimSeekSkull_5";
		break;
		
		case "JoakimSeekSkull_5":
			dialog.text = "No, capitano, Salomone è perfettamente lucido, solo un po’ svitato. Il teschio esiste davvero. È un antico tesoro indiano, il teschio di giada di Yum Cimil! Non ho la minima idea di come quel vecchio giudeo ci abbia messo le mani sopra. Io lo cerco da mezza vita.\nCerca quell’isola dove Salomone ha nascosto il patrimonio di famiglia. Il teschio dev’essere là, nel suo baule. Portami quel teschio di giada e ti pagherò mezzo milione di pesos.";
			link.l1 = "Mezza migliaia? Non vale nemmeno la fatica— aspetta un po'... hai detto mezzo milione di pezzi da otto?! Mi prendi per il bavero? Io non ho mai visto una simile fortuna tutta insieme in vita mia!";
			link.l1.go = "JoakimSeekSkull_6";
		break;
		
		case "JoakimSeekSkull_6":
			dialog.text = "Sei ancora un giovane, capitano... Allora, ci stai? Tu mi dai il teschio di giada e io ti do in cambio cinquecentomila pezzi da otto. Affare fatto?";
			link.l1 = "Ah, una fortuna per un vecchio teschio? Ma certo che ci sto.";
			link.l1.go = "JoakimSeekSkull_7";
		break;
		
		case "JoakimSeekSkull_7":
			dialog.text = "Splendido. È sempre un piacere trattare con chi capisce il valore del guadagno. Se ti servirò ancora, mi trovi qui in casa mia. Buona fortuna!";
			link.l1 = "Grazie, dottor Merriman. Non vi farò attendere troppo a lungo.";
			link.l1.go = "exit";
			npchar.quest.HWICHoll.Task = "true";
			LAi_SetOwnerType(npchar);
			AddDialogExitQuestFunction("CheckIslandCoordinates");//вот тут-то мы и проверим, есть ли у нас координаты острова, и далее будем исходить из результата.
		break;
		
		case "JoakimFindSkull":
			PlaySound("Voice\English\hambit\Joakim Merriman-02.wav");
			dialog.text = "Oh, sì! Hai proprio ragione sulla sua potenza... Ma basta chiacchiere, fammelo vedere, sto fremendo dall’impazienza.";
			link.l1 = "Ecco, prego, prendilo. Spero di non essermi sbagliato?";
			link.l1.go = "JoakimFindSkull_1";
			DelLandQuestMark(npchar);
		break;
		
		case "JoakimFindSkull_1":
			RemoveItems(PChar, "SkullAztec", 1);
			dialog.text = "Ah, incredibile! Sì, è proprio questo. Eccellente, capitano, davvero eccellente! Finalmente! Ce l’ho con me, finalmente! Ho atteso questo momento per tanti anni!";
			link.l1 = "E il denaro che hai promesso, dottor Merriman?";
			link.l1.go = "JoakimFindSkull_2";
		break;
		
		case "JoakimFindSkull_2":
			AddMoneyToCharacter(pchar, 500000);
			dialog.text = "Oh, sì, certo! Mezzo milione di pezzi da otto. Prendili pure, te li sei guadagnati.";
			link.l1 = "È stato un piacere fare affari con te. Difficile credere che una cosa così piccola possa valere tanto...";
			link.l1.go = "JoakimFindSkull_3";
		break;
		
		case "JoakimFindSkull_3":
			dialog.text = "Piccolezza? Non sai proprio di cosa parli. Questo è... bah, la tua mente da villico non può nemmeno concepire la portata dell’incredibile potere racchiuso in questo teschio prezioso. A dirla tutta, non ho comunque tempo da perdere.\nGrazie, capitano, per ciò che hai fatto. Ora è tempo di salutarci. Devo andare.";
			link.l1 = "Addio, dottor Merriman. Chissà, forse ci rivedremo ancora.";
			link.l1.go = "JoakimFindSkull_4";
		break;
		
		case "JoakimFindSkull_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Landlady");
			sld.Dialog.Filename = "Quest\HollandGambit\Joakim.c";
			sld.dialog.currentnode = "Landlady_2";
			SetFunctionTimerCondition("Caleuche_StartTotal", 0, 0, 180, false); // таймер на Калеуче
		break;
		
		case "JoakimSeekSkull_8":
			PlaySound("Voice\English\hambit\Joakim Merriman-01.wav");
			DelLandQuestMark(npchar);
			dialog.text = "Possiamo parlare qui, capitano. So bene che siete intimo di Abigail Shneur, la figlia del mio vicino Solomon. È salpata sulla vostra nave verso il suo amante... ma, in verità, poco m’importa.";
			link.l1 = "Che vuoi dire, dottore?";
			link.l1.go = "JoakimSeekSkull_9";
		break;
		
		case "JoakimSeekSkull_9":
			dialog.text = "Se conosci Salomone, allora saprai anche della sua storia del naufragio e dei tesori perduti che avrebbe nascosto su qualche isola sconosciuta. Ha già raccontato questa storia a tutti a Willemstad.";
			link.l1 = "Perché mai dovrei aver sentito parlarne e, per giunta, crucciarmi per le sventure di quel vecchio giudeo?";
			link.l1.go = "JoakimSeekSkull_10";
		break;
		
		case "JoakimSeekSkull_10":
			dialog.text = "Non ti piace Salomone? Ti assicuro che è solo un vecchio eccentrico innocuo. Dimenticalo. Parliamo d'affari\nHo avuto lunghe chiacchierate con Salomone. Non puoi nemmeno immaginare come mi sono sentito quando ho scoperto che questo vecchio ebreo possiede un antico artefatto inestimabile che cerco da anni! Quel pazzo l'ha nascosto insieme ai suoi miseri risparmi su qualche isola e nemmeno si ricorda dove\nHo bisogno di quell'artefatto. Portamelo e ti pagherò mezzo milione di pezzi da otto.";
			link.l1 = "Mezzo milione di pezzi da otto? Ma siete impazzito, dottore. Non ho mai visto tutta quella somma nemmeno nei sogni più folli!";
			link.l1.go = "JoakimSeekSkull_11";
		break;
		
		case "JoakimSeekSkull_11":
			dialog.text = "Sei ancora un giovanotto. Allora, ci stai? Mi consegni il teschio e io ti do mezzo milione di dobloni in cambio. In più ti lascio pure il denaro di Salomone. Secondo le parole del vecchio, dev'esserci sui duecentomila pesos... Quindi settemila pezzi da otto tutti per te. Che ne dici, capitano?";
			link.l1 = "Che il diavolo mi porti! Certo che accetto! Ma come diamine dovrei trovare quest’isola?";
			link.l1.go = "JoakimSeekSkull_12";
		break;
		
		case "JoakimSeekSkull_12":
			dialog.text = "Parla con Abigail. Magari si ricorda qualcosa. Chiedi a Solomon. Vedi, se sapessi dove cercare quell’isola, mica ti chiederei aiuto, dannazione.";
			link.l1 = "Capisco. Scusa la mia domanda da sprovveduto. Ora devo solo trovare quest’isola. Tu però fatti trovare pronto con il mio pagamento, intesi?";
			link.l1.go = "JoakimSeekSkull_13";
		break;
		
		case "JoakimSeekSkull_13":
			dialog.text = "Proprio così. Mi fa piacere che ci siamo capiti, capitano. Buona fortuna con la tua ricerca. Mi troverai sempre qui, nella mia dimora.";
			link.l1 = "Non ti farò aspettare troppo a lungo, dottor Merriman. Addio!";
			link.l1.go = "JoakimSeekSkull_14";
		break;
		
		case "JoakimSeekSkull_14":
			DialogExit();
			pchar.questTemp.HWIC.Self = "SeekAbiIsland";
			AddQuestRecord("Holl_Gambit", "3-55");
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload3", true);//закроем комнату Аби
			npchar.quest.HWICHoll.Task = "true";
			LAi_SetOwnerType(npchar);
			NextDiag.CurrentNode = "First time";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
			AddMapQuestMarkCity("SentJons", false);
		break;
		
		// калеуче
		case "caleuche":
			PlaySound("Voice\English\LSC\Chymiset-03.wav");
			dialog.text = "Sìììì. Le pietre sacrificali grondano del sangue dei miei nemici! Yum Cimil mi ha concesso il suo potere di comandare i morti! Con questa forza dominerò presto anche i vivi!";
			link.l1 = "Che teatralità, Merriman. Che pensi di fare col tuo esercito di cadaveri ambulanti? Giochi a Cesare, vuoi forse conquistare il mondo?";
			link.l1.go = "caleuche_1";
			CreateLocationParticles("large_smoke", "goto", "goto37", 0.5, 0, 0, "");
		break;
		
		case "caleuche_1":
			dialog.text = "Silenzio, sciocco! Credi forse che svelerò il mio piano segreto con un monologo?! Bah, non vedo perché no, tanto non sopravvivrai a quest’incontro! Le mie legioni di non-morti occuperanno per prime tutte le grotte oscure e i sotterranei dei Caraibi. I miei avamposti saranno in ogni villaggio, pronti ad attendere il mio segnale. E quando sarà l’ora, i miei cadaveri ambulanti marceranno e copriranno le terre dei vivi!\nPeccato che non sarai vivo per assistere a ciò, miserabile anima pia, protagonista da quattro soldi! Sei entrato nel mio santuario – e non ne uscirai con la pelle! Guiderò io stesso il mio esercito delle tenebre!";
			link.l1 = "Ascolta, compare, non comandi un accidente qui, solo frottole e vento, e pure il vento se n’è già andato dal porto.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			PlaySound("Types\warrior04.wav");
			dialog.text = "Oh ho ho! Osi davvero sfidare me e i miei servitori scheletrici?! Allora guarda la mia vera natura e trema di paura!";
			link.l1 = "Vieni a prenderle.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			npchar.model = "Meriman_2";
			Characters_RefreshModel(npchar);
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			dialog.text = "";
			link.l1 = "Ahhh! Dolce Gesù!";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			PlaySound("Voice\English\hambit\Joakim Merriman-04.wav");
			dialog.text = "Adesso capisci chi ti sta davanti, verme strisciante?! Ho un conto in sospeso con te! Yum Cimil stesso mi protegge! Ingoierò la tua anima!";
			link.l1 = "D'accordo, zuccone. Balliamo.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto37", "none", "", "", "Caleuche_MerrimanTeleport", -1);
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "goto", "goto37");
			pchar.questTemp.Caleuche.Merriman_hide = "true";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Tu sei un "+GetSexPhrase("Ladro, signore! Guardie, prendetelo","Ladra, ragazza! Guardie, prendetela")+"!!!","Ma guarda un po’! È bastato che mi voltassi che già frugavi nel mio baule! Al ladro!!!","Guardie! Una rapina! Prendete il ladro!!!");
			link.l1 = "Maledizione!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
