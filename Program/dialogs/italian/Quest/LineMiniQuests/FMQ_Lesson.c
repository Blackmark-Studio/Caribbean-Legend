// Addon-2016 Jason, французские миниквесты (ФМК) Последний урок
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "Un errore lampante. Avvisa quei diavoli di sviluppatori.";
			link.l1 = "Oh, lo farò.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "greguar":
			PlaySound("Voice\English\LE\Greguar\Greguar_04.wav");
			pchar.quest.FMQL_delete_guide.over = "yes";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Fortfrance");
			if (CheckAttribute(pchar, "questTemp.HWIC") || pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "Oh, "+GetFullName(pchar)+"! Sei proprio cambiato, amico mio, e vedo che il vento ti è favorevole! Si comincia a parlare di te, lo sai? Impari in fretta, monsieur, sono davvero fiero di te. Che la fortuna e la sorte ti sorridano ancora in futuro! È sempre un piacere rivederti!";
				link.l1 = "Monsieur Gregoire Valinnie, che incontro! Vi devo molto per le mie umili imprese. È un piacere incontrarvi! Che la sorte vi arrida!";
				link.l1.go = "greguar_exit_1";
			}
			else
			{
				dialog.text = "Oh, "+GetFullName(pchar)+"! Sei cambiato, amico mio, e pure con successo! Parlano già di te, lo sai? Impari in fretta, messere, devo dire che mi rendi fiero.";
				link.l1 = "Monsieur Gregoire Valinnie, che incontro! Vi devo molto per i miei modesti successi. Un vero piacere conoscervi! Lasciate che indovini, avete una proposta d'affari per me?";
				link.l1.go = "greguar_1";
			}
		break;
		
		case "greguar_1":
			dialog.text = "Aho! Proprio così. Sarò breve, il tempo è denaro. Allora, uno squadrone reale olandese che navigava dal Brasile a Curaçao, carico di merci di grande valore strategico, è stato teso un’imboscata dagli inglesi tra Trinidad e la terraferma. Un fluyt della Compagnia è riuscito a fuggire e ad arenarsi sulla Costa di Boca de la Serpienta. Sono riusciti a mettere in salvo parte del carico, ma non per molto – sono stati assaliti da una tribù indiana locale.\nSecondo le mie informazioni, hanno sterminato tutti gli olandesi su quella costa e portato il bottino al loro villaggio. Gli indiani hanno pure preso le armi da fuoco olandesi, ma hanno subito gravi perdite. Questa è la nostra occasione! Inglesi e olandesi si stanno ancora scannando in quella regione e nessuno si preoccupa della fluyt dispersa. Almeno per ora... Tu hai una nave e un equipaggio. Possiamo salpare, sbarcare e finire il lavoro con quei selvaggi. Il carico vale una fortuna ed è parecchio.\nHo già inviato una piccola spedizione a esplorare – tutto ciò che potevo permettermi, sai, brutti tempi per le casse. Ho un compratore fidato, puoi contare sulla mia spada e sui miei mercenari. Mezzo a te e mezzo a me, e abbiamo una settimana per arrivare. Allora, amico mio, ci stai?";
			link.l1 = "Perdonatemi, messere, ma passo. Son appena tornato da un viaggio infernale, non abbiamo tempo per riparazioni né per reclutare uomini. Anche in questo sperduto angolo di mondo, non si può avere tutto.";
			link.l1.go = "greguar_exit";
			link.l2 = "Mi pare un affare rischioso, ma sento odore di buon guadagno e avventura! Certo che ci sto! Non perdiamo altro tempo!";
			link.l2.go = "greguar_2";
		break;
		
		case "greguar_exit":
			dialog.text = "Peccato. Sta a te decidere, allora. Buon vento, monseniore, io ci andrò comunque. Un uomo deve pur tentare, eh?";
			link.l1 = "Buon vento, messer Valinnie!";
			link.l1.go = "greguar_exit_1";
		break;
		
		case "greguar_exit_1":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload5_back", "none", "", "", "", 20.0);
		break;
		
		case "greguar_2":
			dialog.text = "Ottima scelta, compare! Un po’ di moneta in più non fa mai male, vero? E tuo fratello, come se la cava?";
			link.l1 = "Un po' di moneta in più non fa mai male. Michel? Mio fratello sta bene e si annoia. A volte lo invidio... È ora di levare l’ancora!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_Begin");
		break;
		
		case "greguar_3":
			PlaySound("Voice\English\QuestMan02.wav");
			dialog.text = "Facile come bere un bicchier d’acqua! Quelli erano i pivelli scampati alla scaramuccia con gli olandesi. Dobbiamo addentrarci nell’entroterra, la mia spedizione dev’essere laggiù!";
			link.l1 = "Sembrava fin troppo facile... ma è presto per festeggiare, messer Valinnie. Dai un’occhiata laggiù...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_SecondCoastBattle");
		break;
		
		case "greguar_4":
			PlaySound("Voice\English\LE\Greguar\Greguar_05.wav");
			dialog.text = "Maledetti selvaggi! Quasi ci hanno fregato! Ora son certo che in quel villaggio sono rimaste solo donne e mocciosi. Avanti, ci muoviamo!";
			link.l1 = "Non sono poi così sicuro che tu abbia parlato di moschetti, non li ho visti... Bah, al diavolo. Muoviamoci!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQL_GoToJungle");
		break;
		
		case "greguar_5":
			PlaySound("Voice\English\LE\Greguar\Greguar_06.wav");
			dialog.text = "Che vuoi dire? Gli olandesi e noi li avremo fatti fuori tutti quanti!";
			link.l1 = "";
			link.l1.go = "greguar_6";
		break;
		
		case "greguar_6":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Prosper_fmql")) sld = CharacterFromID("FMQL_Prosper");
			else sld = CharacterFromID("FMQL_mercen");
			sld.dialog.currentnode = "prosper_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "greguar_7":
			dialog.text = "Fuggire? Sei impazzito? Siamo quasi arrivati! Hai forse paura di un branco di selvaggi dipinti?";
			link.l1 = "";
			link.l1.go = "greguar_8";
		break;
		
		case "greguar_8":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Prosper_fmql")) sld = CharacterFromID("FMQL_Prosper");
			else sld = CharacterFromID("FMQL_mercen");
			sld.dialog.currentnode = "prosper_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "greguar_9":
			dialog.text = "Il peggio del peggio, capitano. Me ne torno in Europa. Sono disgustato! Da te, da questi codardi e da questa maledetta regione!";
			link.l1 = "...";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_10":
			DialogExit();
			DoQuestReloadToLocation("shore18", "goto", "goto8", "FMQL_JungleExit");
		break;
		
		case "greguar_11":
			dialog.text = "Fiu! Ce l'abbiamo fatta!";
			link.l1 = "Ma a che prezzo! Guarda! Quasi tutta la nostra ciurma è crepata. Dovremmo battere in ritirata, Gregoire, non c’è certezza che altri tagliagole non ci attendano. E poi, siamo troppo pochi per portarci via il bottino.";
			link.l1.go = "greguar_12";
		break;
		
		case "greguar_12":
			dialog.text = "Maledizione! È triste, ma hai ragione, "+pchar.name+": anche se i selvaggi sono tutti crepati, non riusciremo a portar via il carico prima che gli Olandesi o gli Inglesi mettano piede qui. Dobbiamo filarcela subito! Al diavolo questa maledetta costa!";
			link.l1 = "...";
			link.l1.go = "greguar_10";
		break;
		
		case "greguar_13":
			dialog.text = "Fiu! Ce l’abbiamo fatta! Bel lavoro, "+pchar.name+"Avanti, andiamo nella tana dei selvaggi a riscuotere il nostro bottino! Ormai niente ci può fermare!";
			link.l1 = "Dobbiamo sbrigarci finché quegli inglesi e olandesi si scannano tra loro. All’arrembaggio!";
			link.l1.go = "greguar_14";
		break;
		
		case "greguar_14":
			DialogExit();
			DoQuestCheckDelay("FMQL_RunToGrabbing", 1.0);
		break;
		
		case "greguar_15":
			dialog.text = "Abbiamo fatto bene, "+pchar.name+" Ora dobbiamo solo smerciare il carico senza destare sospetti. Ho un compratore fidato, ci aspetta alla baia di Lamentin a mezzanotte. Non portare ufficiali e stai lontano dal luogo prima dell’incontro, il cliente è un tipo assai nervoso.";
			link.l1 = "Affari sono affari. La merce va venduta e bisogna farlo senza rischi, altrimenti il mio debito con Poincy crescerà ancora di più. Va bene, sarò lì entro mezzanotte.";
			link.l1.go = "greguar_16";
		break;
		
		case "greguar_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.quest.FMQL_goods_timer.win_condition.l1 = "Timer";
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.hour  = 0.0;
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQL_goods_timer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQL_goods_timer.function = "FMQL_MeetingOnLamanten";
			AddQuestRecord("FMQ_Lesson", "7");
			LAi_LocationDisableOfficersGen("Shore38", true); // may-16
			LAi_LocationFightDisable(&Locations[FindLocation("Shore38")], true);
			locations[FindLocation("Shore38")].DisableEncounters = true;
			Pchar.GenQuest.Hunter2Pause = true;
		break;
		
		case "greguar_17":
			PlaySound("Voice\English\Master_01.wav");
			pchar.quest.FMQL_goods_over.over = "yes";// лесник снято прерывание на встречу.
			dialog.text = "È fatta. Il carico è sbarcato, il cliente è qui. Lasciami parlare io.";
			link.l1 = "...";
			link.l1.go = "greguar_18";
		break;
		
		case "greguar_18":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=3; i++)
			{
				sld = CharacterFromID("FMQL_contra_"+i);
				if (i == 2) 
				{
					LAi_CharacterEnableDialog(sld);
					AddLandQuestMark(sld, "questmarkmain");
				}
			}
		break;
		
		case "greguar_19":
			dialog.text = "Sorpresa, maledetti canaglie!";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_LookOnGuards");
		break;
		
		case "greguar_20":
			PlaySound("Voice\English\OliverTrast01.wav");
			dialog.text = "Ah, Johnny, che tipo! Grande! Hai qualcosa da dire, "+pchar.name+"?";
			link.l1 = "No. Anzi, sì! Che diavolo?!";
			link.l1.go = "greguar_21";
		break;
		
		case "greguar_21":
			dialog.text = "Non stuzzicare il morto, monseniore. Dove sono finiti i tuoi modi?.. I soldi sono qui, il carico lo gestisco io coi miei compari. Non li ho mandati alla costa, sarebbe stato uno spreco. Soprattutto mandare Johnny laggiù. Vedi quel pelle rossa con la colubrina in mano? Sai, a Johnny la sua tribù non è mai andata troppo a genio.";
			link.l1 = "Capisco... E adesso? Vuoi farmi fuori anche a me?";
			link.l1.go = "greguar_22";
		break;
		
		case "greguar_22":
			dialog.text = "Ebbene, dovrei farlo. Ma ho il cuore tenero. Va’, e prendi un quarto del bottino. Il carico e il resto dell’oro restano qui con me. Non fare lo spaccone, questi non sono i selvaggi del continente. Non hai alcuna speranza.";
			link.l1 = "E dove sono la tua nobiltà e le tue buone maniere, Gregoire? Non me l’aspettavo proprio da te. Me ne vado, ma non dimenticherò questa cosa.";
			link.l1.go = "greguar_23";
			link.l2 = "Non faccio l’eroe, mai fatto. Vi ammazzerò tutti e basta! Prima queste signore, poi la scimmia col cannone a mano, e infine te!";
			link.l2.go = "greguar_25";
		break;
		
		case "greguar_23":
			dialog.text = "Non ci sono né nobili né furfanti su questa spiaggia, messere. Qui ci sono solo cinque uomini, un cannone grosso e una vittima. Succede sempre così da queste parti, ma tu hai fatto l’unica scelta giusta. Ben fatto. Lo sai che al posto tuo potevano esserci altri due, proprio qui, proprio ora? Sono quasi uguali a te. Ma tu sei qui e loro no, e credo che proprio per questo faranno una brutta fine.";
			link.l1 = "Non afferro...";
			link.l1.go = "greguar_24";
		break;
		
		case "greguar_24":
			dialog.text = "Un giorno capirai. Loro non hanno ricevuto la lezione finale. Tu sì. Non c’è di che. Addio, messere. Benvenuto nei Caraibi!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_PeaceFinal");
		break;
		
		case "greguar_25":
			dialog.text = "Ahh... Non sei certo il mozzo più sveglio che abbia mai istruito. Pazienza... ognuno per sé e il diavolo per tutti!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQL_BattleOnBeach");
		break;
		
		case "mercen":
			PlaySound("Voice\English\pirat_guard_4.wav");
			dialog.text = "Tempismo perfetto! Siamo appena sfuggiti all’orda dei Caribi, stavano puntando verso di te e, a giudicare dal tuo aspetto, li hai già incontrati. Il loro villaggio è qui vicino, ma i nostri guai stanno solo per cominciare.";
			link.l1 = "";
			link.l1.go = "prosper_2";
		break;
		
		case "prosper":
			dialog.text = ""+GetFullName(pchar)+"! Sei arrivato! E perché non mi stupisce! Tempismo perfetto, compare. Siamo appena riusciti a sfuggire all’orda dei Caraibi, si dirigevano proprio verso di te e, a giudicare dal tuo aspetto, li hai già incontrati.";
			link.l1 = "Prospera! E son stupito! Torni a bucar pellirosse, eh? Spero che Selina stia bene?";
			link.l1.go = "prosper_1";
		break;
		
		case "prosper_1":
			dialog.text = "Che sciocco sono stato a unirmi a questa spedizione, mi chiedo se mia figlia mi rivedrà mai. Selina? Beh, lei sta a casa e sogna di te! I giovani di Martinica ormai hanno perso ogni speranza... Sai, non rimpiango più di aver comprato questo moschetto. Un’arma solida. Affidabile. E anche un motivo in più per buttarmi in un’altra impresa da suicida, anche se ora lo è un po’ meno da quando sei arrivato tu. Il loro villaggio è qui vicino, ma i nostri guai stanno solo per cominciare.";
			link.l1 = "";
			link.l1.go = "prosper_2";
		break;
		
		case "prosper_2":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_3":
			dialog.text = "Non tutti. Il nostro esploratore è stato colpito ma è comunque riuscito a trovare il loro covo. Il capo in persona sta arrivando con la sua scorta. E hanno moschetti olandesi. Sono più numerosi e furibondi come il diavolo. Il capo è il guerriero più feroce della loro tribù, i suoi uomini sono veri demoni. Dobbiamo decidere in fretta, qui e ora. O li affrontiamo, o battiamo in ritirata. A dirla tutta, preferirei scappare...";
			link.l1 = "";
			link.l1.go = "prosper_4";
		break;
		
		case "prosper_4":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_7";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_5":
			dialog.text = "Non li hai visti tu, brav’uomo! Quei ‘selvaggi’ hanno i moschetti, e li sanno usare maledettamente bene. Qualcuno deve avergli insegnato, su questo non c’è dubbio! Quindi non azzardarti a darmi ancora del codardo!";
			link.l1 = "Calmiamoci e decidiamo il da farsi. C’è ancora tempo.";
			link.l1.go = "prosper_6";
		break;
		
		case "prosper_6":
			int n = 0;
			for (i=1; i<=5; i++)
			{
				if (GetCharacterIndex("FMQL_sailor_"+i) != -1) n++;
			}
			dialog.text = "Ascolto, "+pchar.name+".";
			if (n > 2 && GetSummonSkillFromName(pchar, SKILL_SNEAK) > 30)
			{
				link.l1 = "Li faremo vedere noi, ragazzi! Dietro questa collina ci sono merci e dobloni che aspettano solo noi! Siamo qui per questo e non ce ne andiamo da nessuna parte. Nessun branco di pellirosse, anche armati di moschetti, potrà fermarci! Sotterriamo quei bastardi e finiamo il lavoro! Siamo in numero sufficiente, possiamo coglierli di sorpresa. Quattro uomini li accoglieranno col fuoco dai fianchi, gli altri si piazzeranno qui. Tagliamo le loro fila e facciamoli fuori!";
				link.l1.go = "prosper_8";
			}
			else
			{
				if (n > 0)
				{
					link.l1 = "Li daremo battaglia, ragazzi! Dietro questa collina ci sono merci e denaro! Siamo venuti per prenderli e non ce ne andiamo. Nessun branco di pellirosse, anche armati di moschetti, potrà fermarci! Seppelliamo quei bastardi e portiamo a termine il lavoro!";
					link.l1.go = "prosper_7";
				}
				else
				{
					link.l1 = "Le probabilità ci sono tutte contro, dannazione. E non scordarti degli olandesi che ci stanno alle calcagna.";
					link.l1.go = "prosper_9";
				}
			}
		break;
		
		case "prosper_9":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_9";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "prosper_7":
			DialogExit();
			pchar.questTemp.FMQL = "battle";
			AddDialogExitQuestFunction("FMQL_PrepareAttack");
		break;
		
		case "prosper_8":
			DialogExit();
			pchar.questTemp.FMQL = "sneak";
			AddDialogExitQuestFunction("FMQL_PrepareSneakAttack");
		break;
		
		case "prosper_9x":
			dialog.text = "Siamo vivi e siamo tornati a casa! Giuro, ne ho abbastanza d’avventure... per i prossimi mesi, ahah! Devo raggiungere mia figlia, vienici a trovare, "+pchar.name+". E per favore, sii prudente.";
			link.l1 = "Nessuna promessa, Prosper. Che il vento ti sia favorevole!";
			link.l1.go = "prosper_10";
		break;
		
		case "prosper_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 10.0);
		break;
		
		case "prosper_11":
			pchar.quest.FMQL_prosper_dead.over = "yes";
			LAi_RemoveCheckMinHP(npchar);
			PlaySound("Voice\English\pirat_guard_4.wav");
			dialog.text = "Ti avevo avvertito, capitano, di stare all’erta! Avevo dei sospetti su quel bastardo.";
			link.l1 = "Prospero! Grazie! Ma come?";
			link.l1.go = "prosper_12";
		break;
		
		case "prosper_12":
			sTemp = "";
			if (CheckAttribute(pchar, "questTemp.FMQL.PirateDead")) sTemp = "Poor lad, even though he was a pirate.";
			dialog.text = "Johnny s’è fatto troppo ciarliero. Il pellerossa sulla spiaggia, quello. È venuto al bordello e ha provato a rimorchiare una ragazza. L’hanno mandato a quel paese, Johnny s’è infuriato, ha cominciato a urlare che presto sarebbe diventato ricco, non appena lui e i suoi compari avrebbero fatto fuori un capitano nella giungla. Ho capito l’antifona e sono corso dal tuo ufficiale, che pure si è già fatto una certa fama in città."+sTemp+" Ti sono grandemente debitore, "+pchar.name+", quindi non c’è bisogno che tu mi ringrazi troppo.";
			link.l1 = "E comunque, grazie di cuore, Prosper! Qua la situazione era davvero tosta... troppo tosta. Vuoi unirti alla mia ciurma? Mi serve proprio un ufficiale come te. Oggigiorno è dura trovare uomini fedeli, soprattutto tiratori scelti.";
			link.l1.go = "prosper_13";
		break;
		
		case "prosper_13":
			dialog.text = "No, amico mio. Ho dei doveri verso mia figlia. Mi ha fatto giurare di abbandonare le mie avventure. Quella era l’ultima, maledizione, che peccato, ma voglio più bene a mia figlia che a tutto il resto del mondo. Addio, "+pchar.name+". E... Selina parla sempre di te. Forse, un giorno potresti venirci a trovare?";
			link.l1 = "Chi lo sa, magari lo farò... Addio, Prosper! Che tua figlia trovi un buon marito... (tra sé) Lezione imparata, monsieur Gregoire, lezione imparata... a ciascuno il suo, diceva... Me ne ricorderò.";
			link.l1.go = "prosper_14";
		break;
		
		case "prosper_14":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 15.0);
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
			AddQuestRecord("FMQ_Lesson", "15");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
		break;
		
		case "contra":
			DelLandQuestMark(npchar);
			dialog.text = "Chi diavolo sei tu?";
			link.l1 = "Abbiamo la mercanzia. Ti interessa?";
			link.l1.go = "contra_1";
		break;
		
		case "contra_1":
			dialog.text = "Ah. Molto interessato. Soprattutto il mio cliente. Quanto si guadagna?";
			link.l1 = ""+FindRussianQtyString(sti(pchar.questTemp.FMQL.Sanl))+" di legno di ferro, "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Silk))+" di seta navale, "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Rope))+" di corda e "+FindRussianQtyString(sti(pchar.questTemp.FMQL.Oil))+" di resina.";
			link.l1.go = "contra_2";
		break;
		
		case "contra_2":// Addon 2016-1 Jason пиратская линейка
			iTotalTemp = 2200*sti(pchar.questTemp.FMQL.Sanl)+1600*sti(pchar.questTemp.FMQL.Silk)+1000*sti(pchar.questTemp.FMQL.Rope)+900*sti(pchar.questTemp.FMQL.Oil);
			dialog.text = "Molto bene. 2200 pesos per ogni pezzo di legno di ferro, 900 pesos per la resina, 1600 pesos per la seta navale e 1000 pesos per le gomene. Vediamo un po'... Ebbene, ebbene."+iTotalTemp+" pesos. Affare fatto?";
			link.l1 = "Affare fatto!";
			link.l1.go = "contra_3";
		break;
		
		case "contra_3":
			LAi_Fade("", "");
			FMQL_CreateGuidesWarriors();
			dialog.text = "Splendido! Portane ancora. Gli olandesi non smettono mai d’esser generosi coi pellirosse... E chi sono 'sti ospiti? Che diavolo?!";
			link.l1 = "";
			link.l1.go = "contra_4";
		break;
		
		case "contra_4":
			DialogExit();
			sld = CharacterFromID("Guide_y");
			sld.dialog.currentnode = "greguar_19";
			AddMoneyToCharacter(sld, iTotalTemp);
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "FMQL_beach":
			pchar.quest.FMQL_pirate_dead.over = "yes";
			LAi_RemoveCheckMinHP(npchar);
			dialog.text = "Sì, capitano. Ho levato le ancore con la testa piena di rum, e non per caso.";
			link.l1 = "Tu? Ma come diavolo?!";
			link.l1.go = "FMQL_beach_1";
		break;
		
		case "FMQL_beach_1":
			dialog.text = "Mi dispiace, capitano. Dovevo scolarmi un bicchiere o due dopo quel casino con gli indiani. C’era una ragazza, ho preso una stanza per cento pesos e lei... lei...";
			link.l1 = "Cosa? Ti hanno derubato?";
			link.l1.go = "FMQL_beach_2";
		break;
		
		case "FMQL_beach_2":
			sld = CharacterFromID("FMQL_Prosper");
			dialog.text = "No! Si è innamorata! Maledizione, dovevo filarmela da lì! Ma poi spunta fuori il tuo compare, urlandomi contro per quella feccia, il tuo ex compagno, che vuole farti fuori e ammazzarti.";
			if (LAi_GetCharacterHP(sld) > 0)
			{
				link.l1 = "Ben fatto, Prosper...";
				link.l1.go = "FMQL_beach_3";
			}
			else
			{
				link.l1 = "Prosper... Mi dispiace tanto. Mi prenderò cura di tua figlia. Ho imparato la lezione, messer Gregoire... Come dicevi? A ognuno il suo? Devo ricordarmelo.";
				link.l1.go = "FMQL_beach_3";
			}
		break;
		
		case "FMQL_beach_3":
			dialog.text = "Andiamo, capitano?";
			link.l1 = "Sì. Grazie per il tuo servizio. Tieniti alla larga dal bicchiere e ti risparmieremo da quella bellezza. Andiamo.";
			if (CheckAttribute(pchar, "questTemp.FMQL.ProsperDead")) link.l1.go = "FMQL_beach_5";
			else link.l1.go = "FMQL_beach_4";
		break;
		
		case "FMQL_beach_4": // Проспер жив
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload_sea", "none", "", "", "FMQL_PirateNormal", 10.0);
			sld = CharacterFromID("FMQL_Prosper");
			sld.Dialog.currentnode = "prosper_11";
			sld.MusketerDistance = 20;
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0); 
		break;
		
		case "FMQL_beach_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "FMQL_PirateNormal", 10.0);
			if (sti(pchar.money) >= 20000) DoQuestFunctionDelay("FMQL_MoneyForSelina", 0.5);
			else
			{
				pchar.quest.FMQL_money_20k.win_condition.l1 = "Money";
				pchar.quest.FMQL_money_20k.win_condition.l1.value = 20000;
				pchar.quest.FMQL_money_20k.win_condition.l1.operation = ">=";
				pchar.quest.FMQL_money_20k.function = "FMQL_MoneyForSelina";
			}
			chrDisableReloadToLocation = false;
			InterfaceStates.Buttons.Save.enable = true; // разрешим сохраняться
			AddQuestRecord("FMQ_Lesson", "10");
			CloseQuestHeader("FMQ_Lesson");
			pchar.questTemp.FMQL = "end";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
