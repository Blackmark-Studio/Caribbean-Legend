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
			dialog.text = "Che ti serve?";
			link.l1 = "Niente.";
			link.l1.go = "exit";
		break;

		case "Tomas":
			dialog.text = ""+TimeGreeting()+"! Cosa ti porta nella mia dimora?";
			link.l1 = "Il mio nome è Capitano "+GetFullName(pchar)+". Sono qui su richiesta della zingara. Vuole sapere perché hai rifiutato il suo aiuto. Sei davvero in grado di rinunciare a qualsiasi occasione, anche la più piccola, per salvare tua figlia?";
			link.l1.go = "Tomas_1";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_1":
			dialog.text = "Oh, Capitano... Vi prego di capire, ho dovuto rifiutare, ma non per mia volontà. Credetemi, darei qualsiasi cosa perché Esther si ristabilisca.";
			link.l1 = "Che diavolo ti ha spinto a rifiutare l’aiuto che ti serve come il pane?";
			link.l1.go = "Tomas_2";
		break;

		case "Tomas_2":
			dialog.text = "Vedi, la nostra famiglia è sempre stata devota. Dopo la morte di mia moglie, Olivia, solo la fede mi ha tenuto in piedi. Quando la zingara offrì il suo aiuto, accettai – avrei fatto qualsiasi cosa per salvare mia figlia. Ma... il nostro prete lo scoprì.";
			link.l1 = "Fammi indovinare: lui si oppone a simili servigi?";
			link.l1.go = "Tomas_3";
		break;

		case "Tomas_3":
			dialog.text = "Proprio così. Mi ha convinto che solo la preghiera e la volontà del Signore possono guarire mia figlia. E se mai dovessi allontanarmi da questo sentiero, cercando l’aiuto d’una ‘strega’, mi ha minacciato d’escomunica. Capisci? Escomunica!";
			link.l1 = "Quindi la salute di Esther dipende solo dalla parola del prete?";
			link.l1.go = "Tomas_4";
		break;

		case "Tomas_4":
			dialog.text = "Mia figlia ed io viviamo vicino alla chiesa. La fede è tutto per noi. Se la zingara fallisce, perderò non solo mia figlia ma anche quel poco che mi resta in questo mondo. La gente ci volterà le spalle, la chiesa ci rinnegherà. Esther ed io resteremo completamente soli.";
			link.l1 = "E se il prete desse il suo consenso? Allora lasceresti la zingara tentare?";
			link.l1.go = "Tomas_5";
		break;

		case "Tomas_5":
			dialog.text = "Sì. Se la chiesa benedisse le sue azioni... allora avrei fiducia in lei. Sono pronto a tentare qualsiasi cosa possa aiutare.";
			link.l1 = "Capisco. D’accordo, Thomas, ti aiuterò. Parlerò col tuo prete. Forse riuscirò a convincerlo.";
			link.l1.go = "Tomas_6";
		break;

		case "Tomas_6":
			dialog.text = "Tu... davvero vuoi aiutarci? Capitano, pregherò per la tua buona sorte. Ma tieni a mente... il nostro prete è cocciuto e pieno di principi, convincerlo non sarà una passeggiata.";
			link.l1 = "I principi si piegano con parole ben scelte. Aspettami, torno presto.";
			link.l1.go = "Tomas_7";
		break;

		case "Tomas_7":
			DialogExit();
			
			LAi_SetActorType(npchar);
			AddQuestRecord("DWH", "3");
			pchar.questTemp.DWH_pastor = true;
			AddLandQuestMark(characterFromId("SentJons_Priest"), "questmarkmain");
		break;
		
		case "Tomas_11":
			dialog.text = "...";
			link.l1 = "Thomas, sono riuscito a convincere il prete.";
			link.l1.go = "Tomas_12";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_12":
			dialog.text = "Davvero? Incredibile! Allora invitiamo la zingara al più presto.";
			link.l1 = "Di certo lo faremo, ma c’è un dettaglio. Il prete spera che ciò non scuota la tua fede e si aspetta sincero pentimento e buone azioni. Una di queste potrebbe essere acquistare una nuova campana per la parrocchia.";
			link.l1.go = "Tomas_13";
		break;

		case "Tomas_13":
			dialog.text = "Oh, Capitano... Una campana costa un bel gruzzolo. Forse dovrò separarmi da un gioiello della mia povera moglie. Ma per Esther, darei tutto quel che ho—e pure di più. Naturalmente, poi chiederò perdono al Signore. Andrò dal fabbro, farò l’ordinazione e troverò la zingara.\nVi prego, dite al prete che la campana sarà pronta presto. La strapperò anche dalle viscere della terra, se servirà.";
			link.l1 = "Molto bene, Thomas.";
			link.l1.go = "Tomas_14";
		break;
		
		case "Tomas_14":
			DialogExit();
			
			LAi_SetActorType(npchar);
			pchar.questTemp.DWH_pastor_PrinesDengi = true;
			AddLandQuestMark(characterFromId("SentJons_Priest"), "questmarkmain");
		break;
		
		case "Tomas_15":
			dialog.text = "...";
			link.l1 = "Ho riferito al prete quel che hai detto. Non ti metterà più i bastoni tra le ruote, quindi puoi cominciare.";
			link.l1.go = "Tomas_16";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_16":
			dialog.text = "Grazie, Capitano, per il vostro aiuto! Prendete questi cinquanta dobloni. È il minimo che possa offrirvi, e tutto ciò che ho al momento...";
			link.l1 = "Fandonie! Non ti ho aiutato per denaro. Allora, tutto è pronto per... ehm... la cura?";
			link.l1.go = "Tomas_16_1";
			link.l2 = "Ebbene, se proprio insisti... C'è altro che posso fare per te?";
			link.l2.go = "Tomas_16_2";
		break;

		case "Tomas_16_1":
			StartInstantDialog("DWH_gypsy", "gypsy_1", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.questTemp.DWH_GoodChoice = true;
		break;
		
		case "Tomas_16_2":
			StartInstantDialog("DWH_gypsy", "gypsy_1", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			AddItems(pchar, "gold_dublon", 50);
		break;
		
		case "gypsy_1":
			dialog.text = "Per preparare il rimedio che ridarà salute alla ragazza, mi serve la mangarosa – una pianta rara che cresce solo dove l’uomo ci mette raramente piede. Conosco una grotta fuori città, spesso infestata da... gentaglia. Bruciano la mangarosa per fumarla, senza sapere quanto valga davvero. Dammi una mano, "+GetSexPhrase("falconetto","tesoruccio")+", portami un po’ di mangarosa, senza quella non si combina nulla.";
			if (CheckAttribute(pchar, "questTemp.Mangarosa"))
			{
				link.l1 = "Mangarosa? Conosco bene quella pianta.";
				link.l1.go = "gypsy_VD_manga_1";
			}
			else
			{
				link.l1 = "Che ti sembra, eh?";
				link.l1.go = "gypsy_VD_no_manga";
			}
		break;

		case "gypsy_VD_no_manga":
			dialog.text = "È una pianta piuttosto alta, con foglie divise e un profumo piacevole che fa girare la testa. Non la confonderesti mai con nient’altro.";
			link.l1 = "D'accordo, andrò a cercare questa mangarosa.";
			link.l1.go = "gypsy_2";
		break;

		case "gypsy_VD_manga_1":
			dialog.text = "Lo mescoli anche con il tabacco, eh?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "amelia")
			{
				link.l1 = "No, affatto! C’è una guaritrice di nome Amelia. La usa per distillare pozioni che ti ribalterebbero la mente come una barca in tempesta.";
				link.l1.go = "gypsy_VD_manga_1_2";
			}
			else
			{
				link.l1 = "No, ma ho avuto a che fare con la mangarosa un paio di volte.";
				link.l1.go = "gypsy_VD_manga_2";
			}
		break;

		case "gypsy_VD_manga_1_2":
			dialog.text = "Allora conosci Amelia? Bene, "+GetSexPhrase("falconetto","piccioncino")+", presto mi darai del filo da torcere. Ma non è il momento per questo. Vai a prendere la mangarosa e io preparo tutto.";
			link.l1 = "Sono in rotta.";
			link.l1.go = "gypsy_2";
			AddCharacterExpToSkill(pchar, "Fortune", 200);
		break;

		case "gypsy_VD_manga_2":
			dialog.text = "Capisco, tu non sei uno qualunque, "+GetSexPhrase("falconetto","tesoruccio")+"La tua sapienza è sconfinata, la tua mente tagliente come una lama! Non temi l’ignoto, anzi, ti ci butti a capofitto dove gli altri scappano. Thomas può ringraziare la buona sorte d’averti al fianco. Ora vai, portami la mangarosa e guarirò la ragazza.";
			link.l1 = "...";
			link.l1.go = "gypsy_2";
		break;
		
		case "gypsy_2":
			DialogExit();
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			
			AddQuestRecord("DWH", "5");
			
			// поход за мангаросой
			LAi_LocationDisableOfficersGen("Antigua_Grot", true);
			locations[FindLocation("Antigua_Grot")].DisableEncounters = true;
			PChar.quest.DWH_Grot.win_condition.l1 = "location";
			PChar.quest.DWH_Grot.win_condition.l1.location = "Antigua_Grot";
			PChar.quest.DWH_Grot.function = "DWH_Grot";
		break;
		
		case "Bandit_1":
			dialog.text = "Ah-ah. Te lo dico io, Mark, quello è uno scemo. Non chiude nemmeno la porta di casa.";
			link.l1 = "Sei sicuro che la sua chioccia non stia a casa a covare?";
			link.l1.go = "Bandit_2";
			
			locCameraSleep(true);
			sld = CharacterFromID("DWH_Bandit_1");
			CharacterTurnToLoc(sld, "goto", "ass4");
			sld = CharacterFromID("DWH_Bandit_2");
			CharacterTurnToLoc(sld, "goto", "ass2");
		break;
		
		case "Bandit_2":
			DialogExit();
			
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "", -1);
			DoQuestFunctionDelay("DWH_Grot_2", 4.0);
		break;
		
		case "Bandit_3":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "Ah, ah, guarda chi si è impigliato nella nostra rete! Avanti, non restare lì impalato. Svuota le tasche, svelto, prima che ci passi la voglia di scherzare.";
			link.l1 = "Calma, mascalzoni. Son qui per affari. "+sld.name+" mi ha mandato. Ho bisogno di mangarosa.";
			link.l1.go = "Bandit_4";

			locCameraSleep(false);
			locCameraFromToPos(3.39, 1.16, -1.80, true, 3.62, -0.50, 3.63);
			sld = CharacterFromID("DWH_Bandit_2");
			CharacterTurnToLoc(sld, "goto", "goto2");
		break;

		case "Bandit_4":
			sld = CharacterFromID("DWH_gypsy");
			dialog.text = "Dici "+sld.name+" ti manda? Va bene, abbiamo la mangarosa. Dacci dieci dobloni e sarà tua.";
			if (PCharDublonsTotal() >= 10)
			{
				link.l1 = "Ecco qua.";
				link.l1.go = "Bandit_5";
			}
			link.l2 = "Denaro? E per cosa, di grazia? Non faccio l’elemosina. Ma posso offrirti due libbre d’acciaio, se preferisci!";
			link.l2.go = "Bandit_7";
		break;

		case "Bandit_5":
			dialog.text = "D'accordo, ecco la tua mangarosa. E ricorda, non ci hai mai visto.";
			link.l1 = "Heh. Non c’era bisogno d’avviso.";
			link.l1.go = "Bandit_6";
			GiveItem2Character(PChar, "cannabis7");
			RemoveDublonsFromPCharTotal(10);
		break;
		
		case "Bandit_6":
			DialogExit();
			
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			LAi_LocationDisableOfficersGen("Antigua_Grot", false);
			locations[FindLocation("Antigua_Grot")].DisableEncounters = false;
			
			if (CheckAttribute(pchar, "questTemp.DWH_GoodChoice")) SetFunctionLocatorCondition("DWH_VorovstvoSunduk", "Antigua_Grot", "box", "box1", false)
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_3";
			AddLandQuestMark(sld, "questmarkmain");
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("DWH_Bandit_"+i);
				LAi_CharacterDisableDialog(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, false, "DWH_Podkreplenie");
			}
		break;
		
		case "Bandit_7":
			DialogExit();
			
			chrDisableReloadToLocation = true;
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			GiveItem2Character(NPChar, "cannabis7");
			npchar.SaveItemsForDead = true;
			npchar.DontClearDead = true;
			LAi_SetFightMode(pchar, true);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("DWH_Bandit_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			for (i=3; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("DWH_Bandit_"+i, "citiz_48", "man", "man", sti(pchar.rank), PIRATE, 0, true, "pirate"));
				if (i==4) sld.model = "citiz_49";
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, "Antigua_Grot", "reload", "reload1");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "DWH_Grot_4");
		break;
		
		case "gypsy_3":
			if (CheckCharacterItem(PChar, "cannabis7"))
			{
				dialog.text = "...";
				link.l1 = "Dai un’occhiata, "+npchar.name+", è questa la pianta che ti serve?";
				link.l1.go = "gypsy_4";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "Hai portato quello che ti ho chiesto?";
				link.l1 = "Non ancora, ci sto lavorando.";
				link.l1.go = "exit";
				NextDiag.TempNode = "gypsy_3";
			}
		break;

		case "gypsy_4":
			dialog.text = "Sì, ci siamo. Ora ho tutto ciò che mi serve, e posso cominciare.";
			link.l1 = "...";
			link.l1.go = "gypsy_5";
			TakeItemFromCharacter(pchar, "cannabis7");
		break;

		case "gypsy_5":
			StartInstantDialog("DWH_Tomas", "Tomas_17", "Quest\MiniEvents\DarkWatersOfHealing_dialog.c");
		break;

		case "Tomas_17":
			dialog.text = "Andiamo svelti, non dobbiamo perdere tempo.";
			link.l1 = "...";
			link.l1.go = "Tomas_18";
			CharacterTurnByChr(npchar, CharacterFromID("DWH_gypsy"));
		break;

		case "Tomas_18":
			dialog.text = "Capitano, se non vi dispiace, parleremo più tardi. Ora ci attende la parte più delicata... la cura.";
			link.l1 = "Certo, Thomas. Spero che tua figlia si rimetta presto.";
			link.l1.go = "Tomas_19";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Tomas_19":
			DialogExit();
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", true);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", true);
			
			AddQuestRecord("DWH", "6");
			SetTimerFunction("DWH_Vizdorovela", 0, 0, 30);
		break;
		
		case "gypsy_6":	// если не прошли проверку ВД у священника
			dialog.text = "...";
			link.l1 = ""+npchar.name+",  Thomas non ti ha mandato via di sua volontà. Il prete l'ha minacciato di scomunica se avesse accettato il tuo aiuto.";
			link.l1.go = "gypsy_7";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_7":
			dialog.text = "L'ho capito subito, "+GetSexPhrase("tesoro","bellezza")+", che mi ha dato quel rifiuto con il cuore greve.";
			link.l1 = "C’è un modo per aiutarlo senza che la Chiesa storca il naso?";
			link.l1.go = "gypsy_8";
		break;

		case "gypsy_8":
			dialog.text = "Oh, "+GetSexPhrase("tesoro","bellezza")+", non è affar semplice, ma le rotte mi sono note, so come muovermi. Tuttavia, senza il tuo aiuto non ce la faccio, capisci.";
			link.l1 = "Ma certo, puoi contare su di me.";
			link.l1.go = "gypsy_10";
			link.l2 = "Perdonami, sopracciglio scuro, ma davvero non ho tempo per queste faccende. Ho fatto tutto ciò che potevo. Ora devo badare ai miei affari.";
			link.l2.go = "gypsy_9";
		break;
		
		case "gypsy_9":
			DialogExit();
			CloseQuestHeader("DWH");
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterDisableDialog(sld);
			sld.lifeday = 0;
			
			sld = CharacterFromID("DWH_Tomas");
			sld.lifeday = 0;
		break;
		
		case "gypsy_10":
			dialog.text = "Ecco cosa mi serve: un oggetto appartenente alla ragazza, due steli di datura, uno di ipecacuana e uno di verbena. Portami tutto questo e potrò preparare per lei un elisir curativo.";
			link.l1 = "Va bene, procurerò tutto il necessario.";
			link.l1.go = "gypsy_11";
		break;

		
		case "gypsy_11":
			DialogExit();
			AddQuestRecord("DWH", "7");
			
			LAi_CharacterDisableDialog(npchar);
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_21";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Tomas_21":
			dialog.text = "...";
			link.l1 = "Thomas, purtroppo il prete non ha dato ascolto alle mie parole. Ma io e la zingara possiamo aiutarti. Ho bisogno...";
			link.l1.go = "Tomas_22";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_22":
			dialog.text = "Mi stai forse dicendo di mettermi contro la Chiesa?";
			link.l1 = "Faremo tutto in silenzio, nessuno verrà a saperlo. Presto vostra figlia potrà di nuovo godersi la vita e passeggiare liberamente per la città, come si addice a una giovane signorina.";
			link.l1.go = "Tomas_23";
			link.l2 = "Maledizione, Thomas Morrison, vuoi che tua figlia guarisca davvero o ti nascondi dietro belle parole?";
			link.l2.go = "Tomas_24";
		break;

		case "Tomas_23":
			dialog.text = "D'accordo, accetto. Ma per l'amor del cielo, sii cauto. Non voglio chiacchiere inutili né grane.";
			link.l1 = "Assolutamente. Mi serve un oggetto personale di tua figlia. Qualcosa a cui tenga davvero.";
			link.l1.go = "Tomas_25";
			AddCharacterExpToSkill(pchar, "Sneak", 200);
		break;

		case "Tomas_24":
			dialog.text = "Va bene, accetto. Ma per l'amor del cielo, agisci con cautela. Non voglio pettegolezzi né guai inutili.";
			link.l1 = "Assolutamente. Dunque, mi serve un oggetto personale di tua figlia. Qualcosa a cui tenga davvero.";
			link.l1.go = "Tomas_25";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "Tomas_25":
			dialog.text = "Hmm... Sì! So cosa funzionerà. Aspettami qui, torno subito.";
			link.l1 = "Aspetterò...";
			link.l1.go = "Tomas_26";
		break;

		case "Tomas_26":
			DialogExit();
			SetLaunchFrameFormParam("A few minutes later...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("DWH_TomasGovotitAgain", 0.0);
			LaunchFrameForm();
		break;
		
		case "Tomas_27":
			dialog.text = "Ecco. Queste sono perle di giada. Esther non se ne separava mai, le erano molto care.";
			link.l1 = "Eccellente. Ora non ti resta che aspettare. A presto, Thomas.";
			link.l1.go = "Tomas_28";
			GiveItem2Character(PChar, "jewelry49");
		break;

		case "Tomas_28":
			DialogExit();
			AddQuestRecord("DWH", "8");

			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest/MiniEvents/DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_21";
			AddLandQuestMark(sld, "questmarkmain");
		break;

		case "gypsy_21":
			dialog.text = "Sei riuscito a procurarti tutto quel che serve?";
			if (GetCharacterItem(pchar, "cannabis1") >= 2 && GetCharacterItem(pchar, "cannabis4") >= 1 && GetCharacterItem(pchar, "cannabis3") >= 1)
			{
				link.l1 = "Ho procurato tutto il necessario.";
				link.l1.go = "gypsy_22";
			}
			link.l2 = "Ricordammi cosa devo portare.";
			link.l2.go = "gypsy_napomni";
		break;

		case "gypsy_napomni":
			dialog.text = "Ecco cosa mi serve: un oggetto appartenente alla ragazza, due steli di datura, due di ipecacuana e uno di verbena. Se mi porti tutto questo, potrò preparare per lei un infuso d’erbe.";
			link.l1 = "Benissimo, procurerò tutto il necessario.";
			link.l1.go = "gypsy_napomni_2";
		break;

		case "gypsy_napomni_2":
			DialogExit();
			NextDiag.TempNode = "gypsy_21";
		break;

		case "gypsy_22":
			dialog.text = "Eccellente. Ora posso preparare una pozione curativa per la ragazza. Sarà pronta non prima di domattina. Mi troverai come sempre, per le strade della città.";
			link.l1 = "Molto bene, ci vediamo allora.";
			link.l1.go = "gypsy_23";
			DelLandQuestMark(npchar);
			RemoveItems(pchar, "cannabis1", 2);
			RemoveItems(pchar, "cannabis4", 1);
			RemoveItems(pchar, "cannabis3", 1);
			RemoveItems(pchar, "jewelry49", 1);
		break;
		
		case "gypsy_23":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("DWH", "11");
			SetTimerFunction("DWH_GypsyPrigotovilaZelie", 0, 0, 1);
		break;
		
		case "gypsy_31":
			dialog.text = "...";
			link.l1 = "Ebbene, "+npchar.name+", la tua pozione è pronta?";
			link.l1.go = "gypsy_32";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_32":
			dialog.text = "Eccolo là, "+GetSexPhrase("tesoruccio","bellezza")+". Che la fanciulla si metta queste perle e beva fino all’ultima goccia il contenuto della fiala. In meno d’un mese sarà sana come un pesce.";
			link.l1 = "Porterò questo subito a Thomas. Addio, sopracciglio scuro.";
			link.l1.go = "gypsy_33";
			GiveItem2Character(PChar, "quest_potion");
			GiveItem2Character(PChar, "jewelry49");
		break;

		case "gypsy_33":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);

			sld = CharacterFromID("DWH_Tomas");
			LAi_SetStayType(sld);
			sld.dialog.filename = "Quest/MiniEvents/DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "Tomas_31";
			AddLandQuestMark(sld, "questmarkmain");
		break;

		case "Tomas_31":
			if (CheckCharacterItem(PChar, "quest_potion"))
			{
				dialog.text = "...";
				link.l1 = "Thomas, tutto è pronto. Esther dovrà indossare queste perle e tracannare la fiala di pozione tutta d’un fiato.";
				link.l1.go = "Tomas_32";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Tomas_31";
			}
		break;

		case "Tomas_32":
			dialog.text = "Grazie, "+pchar.name+"Vi prego, perdonatemi, non voglio perdere nemmeno un minuto...";
			link.l1 = "Ma certo, ma certo.";
			link.l1.go = "Tomas_33";
			TakeItemFromCharacter(pchar, "quest_potion");
		break;
		
		case "Tomas_33":
			DialogExit();
			
			sld = CharacterFromID("DWH_Tomas");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", true);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", true);
			
			AddQuestRecord("DWH", "6");
			SetTimerFunction("DWH_Vizdorovela", 0, 0, 30);
		break;
		
		case "Tomas_41":
			dialog.text = "Saluti, "+pchar.name+"! La mia Esther è guarita! Ora è sana come un pesce e si trova in chiesa a rendere grazie al nostro Signore per averci mandato te e la zingara!";
			link.l1 = "Thomas, sono lieto che tutto sia andato per il verso giusto! Abbi cura della ragazza, ora l’attende una lunga vita felice.";
			link.l1.go = "Tomas_42";
			DelLandQuestMark(npchar);
		break;

		case "Tomas_42":
			dialog.text = "Prendi questi trecento dobloni. Purtroppo non posso offrirti di più, perché ho dovuto indebitarmi per mettere insieme questa somma. Ma sappi che nessuna parola e nessun oro potranno mai esprimere la mia gratitudine verso di te, Capitano. Non solo mi hai liberato dal terrore per la sua vita, ma hai anche ridato speranza alla nostra famiglia. Ti sarò debitore per sempre!";
			link.l1 = "Grazie! Trecento dobloni sono una bella somma, quindi stai tranquillo – mi hai già ringraziato fin troppo!";
			link.l1.go = "Tomas_43";
			link.l2 = "Non prenderò i tuoi soldi, Thomas. Non provare nemmeno a insistere! Sarebbe meglio che comprassi a Esther un bel vestito, se lo merita.";
			link.l2.go = "Tomas_46";
		break;

		case "Tomas_43":
			dialog.text = ""+pchar.name+", vieni a trovarci quando vuoi. Sarai sempre il benvenuto nella nostra dimora. Ah, e parla anche con la zingara, voleva vederti.";
			link.l1 = "Lo considererò un onore! Ora devo congedarmi – le maree non aspettano nessun capitano.";
			link.l1.go = "Tomas_44";
			AddItems(pchar, "gold_dublon", 300);
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;

		case "Tomas_44":
			dialog.text = "Ma certo, ma certo. Che Dio ti accompagni, "+GetFullName(pchar)+"!";
			link.l1 = "Addio.";
			link.l1.go = "Tomas_45";
		break;
		
		case "Tomas_45":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", false);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", false);
			SetFunctionExitFromLocationCondition("DWH_Vizdorovela_3", PChar.location, false);
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			NextDiag.CurrentNode = "Tomas_51";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_41";
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Tomas_46":
			dialog.text = "Voi siete una persona di gran nobiltà, "+GetFullName(pchar)+"! Che la Vergine Maria sia con te! Vienici a trovare, sei sempre un ospite gradito nella nostra casa. E poi, "+pchar.name+", parla con la zingara, voleva vederti.";
			link.l1 = "Senza dubbio! Ora devo andarmene – il mare mi chiama.";
			link.l1.go = "Tomas_47";
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
		break;
		
		case "Tomas_47":
			DialogExit();
			
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("SentJons_houseS3", "reload2", false);
			LocatorReloadEnterDisable("SentJons_town", "houseS3", false);
			SetFunctionExitFromLocationCondition("DWH_Vizdorovela_3", PChar.location, false);
			
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			NextDiag.CurrentNode = "Tomas_51";
			
			sld = CharacterFromID("DWH_gypsy");
			LAi_CharacterEnableDialog(sld);
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "gypsy_44";
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.DWH_QuestCompleted = true;
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1;
			
			AddSimpleRumourCity("Have you heard? "+GetFullName(pchar)+" procured a remedy for Thomas Morrison's daughter that miraculously restored the poor girl's health!", "SentJons", 10, 1, "");
			AddSimpleRumourCity("Thomas Morrison lights a candle in the parish daily for the health of "+GetFullName(pchar)+". They say thanks to his (her) efforts, Thomas's daughter was freed from a prolonged illness.", "SentJons", 10, 1, "");
			AddSimpleRumourCity("Esther Morrison has blossomed before our eyes. As if she had never been ill. No one can really explain what made the illness retreat.", "SentJons", 10, 1, "");
		break;
		
		case "gypsy_41":
			dialog.text = "E finalmente eccoti qui, "+GetSexPhrase("falconetto","tesorino")+"! Lo sapevo che saresti tornato. Grazie al tuo aiuto, la ragazza si è ripresa e ora si muove leggera come una colomba. Tutta la città parla di lei con stupore.";
			link.l1 = "Ehi, sopracciglio scuro, non è stato solo merito mio – non darmi troppa gloria. È stato il tuo intruglio a rimetterla in sesto, quindi non sminuire il tuo contributo.";
			link.l1.go = "gypsy_42";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_42":
			dialog.text = "Hai un cuore generoso, "+GetSexPhrase("falconetto","tesoruccio")+", e una mente affilata! Sei destinato a grandi imprese – questa è la mia profezia.";
			link.l1 = "Eheh... beh, grazie, "+npchar.name+".";
			link.l1.go = "gypsy_43";
		break;
		
		case "gypsy_43": // плохой вариант
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("DWH", "9");
			CloseQuestHeader("DWH");
		break;
		
		case "gypsy_44":
			dialog.text = "Eccoti qui, "+GetSexPhrase("falconetto","piccioncino")+"! Lo sapevo che saresti tornato qui. Grazie alle tue fatiche, la fanciulla si è rimessa e adesso vola leggera come una colomba. L’intera città la ammira.";
			link.l1 = "Su, su, sei stato tu a salvare la fanciulla, e ora vuoi che io mi prenda tutta la gloria? Non va bene! Hai preparato tu la pozione, l’hai rimessa in piedi, la fama dev’esser tua.";
			link.l1.go = "gypsy_45";
			DelLandQuestMark(npchar);
		break;

		case "gypsy_45":
			dialog.text = "Hai un cuore nobile, "+GetSexPhrase("falconetto","tesoruccio")+", e un'anima nobile. Ho un dono per te – uno che qualsiasi capitano saprebbe apprezzare. Tieni. Ora i topi sulla tua nave non avranno né gioia né pace!";
			link.l1 = "Un dono per me? Per mille balene, non me l’aspettavo proprio!";
			link.l1.go = "gypsy_46";
			GiveItem2Character(PChar, "rat_poison");
		break;

		case "gypsy_46":
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				dialog.text = "La tua anima è limpida, vedo che non brucerai la mangarosa per un piacere effimero. Se mai dovessi averne urgente bisogno, vieni da me, "+GetSexPhrase("falconetto","tesorino")+"Cinque steli ti costeranno duecento dobloni.\nQuest’erba è bizzarra, non tutti la sanno scovare. Quindi non mettermi fretta – non chiedermela più spesso d’una volta al mese, tanto non riuscirei a procurartela comunque.";
			}
			else
			{
				dialog.text = "La tua anima brilla, vedo che non sei uno sciocco, capisci le erbe quanto certi cerusici. Sai trovare molte cose, anche se la sorte non sempre ti arride. C'è una pianta rara che non tutti riescono a scovare. Si chiama mangarosa. Se mai ti servirà, vieni da me, "+GetSexPhrase("falconetto","tesoruccio")+". Prenderò cinque steli, ma non li darò gratis – duecento dobloni voglio in cambio Ma quest’erba è capricciosa, quindi non mettermi fretta. Non chiedere più di una volta al mese – anche se spargi tutte le carte del destino, non la troverò prima.";
			}
			link.l1 = "Ebbene, grazie, "+npchar.name+".";
			link.l1.go = "gypsy_47";
		break;
		
		case "gypsy_47": // хороший вариант
			DialogExit();
			NextDiag.CurrentNode = "gypsy_Mangarosa";
			
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddQuestRecord("DWH", "10");
			CloseQuestHeader("DWH");
			AddQuestRecordInfo("Useful_Acquaintances", "1");
			
			SetTimerFunction("DWH_Mangarosa", 0, 0, 30);
		break;
		
		case "Tomas_51":
			dialog.text = "Capitano, continuo a pensare – dev’essere stato il Signore in persona a guidarvi qui al momento giusto! Avete salvato mia figlia, e non lo dimenticherò mai.";
			link.l1 = "Forse, Thomas. Le vie del Signore sono imperscrutabili.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Tomas_52";
			SetTimerFunction("DWH_Tomas_HelloAgain", 0, 0, 1);
		break;

		case "Tomas_52":
			dialog.text = "Gradisce un po' di vino, Capitano? Ho qualcosa di speciale per ospiti tanto graditi.";
			link.l1 = "Grazie, Thomas, ma purtroppo devo andare.";
			link.l1.go = "exit";
		break;

		case "gypsy_Mangarosa":
			dialog.text = "Che ti serve, mio falco?";
			if (CheckAttribute(pchar, "questTemp.DWH_Mangarosa"))
			{
				link.l1 = "Dimmi, sopracciglio scuro, avresti forse della mangarosa per me?";
				link.l1.go = "gypsy_Mangarosa_1";
			}
			link.l2 = "Sono passato solo per salutare. Ora devo levarmi l'ancora!";
			link.l2.go = "exit";
			NextDiag.TempNode = "gypsy_Mangarosa";
		break;
		
		case "gypsy_Mangarosa_1":
			dialog.text = "Chi altri se non io, "+GetSexPhrase("tesoro","bellezza")+", ti procurerebbe una simile rarità? Duecento dobloni – ed è tua, cinque stecche, né più né meno.";
			if (PCharDublonsTotal() >= 300)
			{
				link.l1 = "Il tuo prezzo è giusto. L’oro è tuo.";
				link.l1.go = "gypsy_Mangarosa_2";
			}
			link.l2 = "Maledizione! La mia borsa è quasi vuota. Tornerò quando la sorte mi sarà più propizia.";
			link.l2.go = "exit";
			NextDiag.TempNode = "gypsy_Mangarosa";
		break;

		case "gypsy_Mangarosa_2":
			dialog.text = "Così va meglio. Prendila. E bada di non sprecarla per sciocchezze, capisci – la mangarosa non è un'erba qualunque, in essa si cela un potere che non tutti sanno domare.";
			link.l1 = "Non temere, sopracciglio scuro, troverò un degno impiego per la sua potenza.";
			link.l1.go = "gypsy_Mangarosa_3";
			AddItems(pchar, "cannabis7", 5);
			RemoveDublonsFromPCharTotal(300);
		break;
		
		case "gypsy_Mangarosa_3":
			DialogExit();
			
			NextDiag.CurrentNode = "gypsy_Mangarosa";
			DeleteAttribute(pchar, "questTemp.DWH_Mangarosa");
			SetTimerFunction("DWH_Mangarosa", 0, 0, 30);
		break;
	}
}