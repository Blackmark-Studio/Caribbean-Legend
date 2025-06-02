// диалоги персонажей по квесту Мангароса
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
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
			dialog.text = "Cosa vuoi, forestiero?";
			link.l1 = "Niente.";
			link.l1.go = "exit";
		break;
		
		// Амелия - знахарка-цыганка
		case "amelia":
			dialog.text = "Cosa vuoi nella mia dimora?";
			if (CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "amelia")
			{
				link.l1 = "Il tuo nome è Amelia, giusto? Sono venuto a chiederti di una pianta. Manga Rosa.";
				link.l1.go = "amelia_1";
			}
			else
			{
				link.l1 = "Non ho ancora nulla da raccontarti. Ma un giorno tornerò...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "amelia";
		break;
		
		case "amelia_1":
			dialog.text = "Interessante! E chi t’ha parlato di me, giovane coraggioso?";
			link.l1 = "Una della tua ciurma. Diceva che conosci i segreti di questa pianta e che puoi insegnarmi a preparare pozioni speciali con essa...";
			link.l1.go = "amelia_2";
		break;
		
		case "amelia_2":
			dialog.text = "Prima di tutto, mostrami la pianta di cui parli. Forse non ne sai un accidente e stai solo facendo perder tempo al sottoscritto. Dov’è la tua Manga Rosa?";
			if (CheckCharacterItem(pchar, "cannabis7"))
			{
				link.l1 = "Ecco, dai un'occhiata.";
				link.l1.go = "amelia_3";
			}
			else
			{
				link.l1 = "Hm...";
				link.l1.go = "amelia_exit";
			}
		break;
		
		case "amelia_exit":
			dialog.text = "E cosa volevi mostrarmi? Non hai la Manga Rosa. Fuori dai piedi, compare, prima che mi girino le palle. La chiacchierata finisce qui.";
			link.l1 = "Ma...";
			link.l1.go = "exit";
			NextDiag.TempNode = "amelia_wait";
		break;
		
		case "amelia_wait":
			dialog.text = "Ancora tu? Non portarmi rogne, ragazzo...";
			if (CheckCharacterItem(pchar, "cannabis7"))
			{
				link.l1 = "Calmati, Amelia. L'ho perso da qualche parte l'ultima volta. Ecco, ti ho portato la Manga Rosa. Dai un'occhiata.";
				link.l1.go = "amelia_3";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "amelia_exit";
			}
			NextDiag.TempNode = "amelia_wait";
		break;
		
		case "amelia_3":
			dialog.text = "Vediamo un po'... Pare che tu sappia qualcosa a riguardo. E vorresti che ti svelassi i segreti delle mie pozioni?";
			link.l1 = "Esatto. E, se ho capito bene, non per beneficenza...";
			link.l1.go = "amelia_4";
		break;
		
		case "amelia_4":
			dialog.text = "Hai capito bene, giovanotto! Non sembri proprio uno scimunito. Ebbene, posso insegnare qualcosa a chi cerca il sapere e non spreca questa pianta rara per farne fumo da bucanieri...";
			link.l1 = "Amelia, prima che iniziamo a mercanteggiare... saresti così gentile da raccontarmi qualche nozione di base sulle pozioni che posso preparare con la Manga Rosa?";
			link.l1.go = "amelia_5";
		break;
		
		case "amelia_5":
			dialog.text = "Nessun mercanteggio, compare. Ti dirò io il prezzo e sarai tu a decidere se pagare o meno. Non sperare in sconti o trattative, questa non è una fiera. Quanto alla tua domanda... Puoi preparare pozioni speciali di Manga Rosa che rafforzeranno le tue capacità fisiche. Possono renderti più forte, resistente o veloce, oppure possono trasformare il tuo corpo rendendoti più possente in ogni aspetto, ma una simile pozione avrà un effetto meno potente rispetto alle prime due.";
			link.l1 = "Molto interessante. Dimmi il tuo prezzo.";
			link.l1.go = "amelia_6";
		break;
		
		case "amelia_6":
			dialog.text = "Posso insegnarti tre ricette. Per ogni ricetta voglio una pianta e cinquecento monete d’oro.";
			link.l1 = "Raccontami di più su queste pozioni. A cosa serve ognuna di esse?";
			link.l1.go = "amelia_7";
		break;
		
		case "amelia_7":
			dialog.text = "Devi essere un vero maestro nell’arte dell’alchimia se vuoi preparare anche una sola pozione. Ogni pozione dura al massimo due giorni, a seconda di quando la bevi; se la tracanni a mezzanotte, durerà quasi due giorni interi.\nLa prima pozione ti dona forza e resistenza. Combatterai meglio, subirai meno ferite e potrai portare più peso.\nLa seconda ti rende più svelto, agile, instancabile, e migliora pure la tua mira.\nLa terza ha effetti doppiamente più deboli rispetto alle due precedenti, ma ti regala fascino, sicurezza e un pizzico di fortuna in più.\nTutte le pozioni a base di Manga Rosa fanno bene alla salute. Devi berne solo una per volta, mai mischiarle, altrimenti ti faranno più male che bene: ti beccheresti un bell’avvelenamento!\nAllora, bel capitano, sei pronto a pagare subito per questa sapienza, o hai bisogno di rimuginarci su?";
			if (CheckCharacterItem(pchar, "cannabis7") && PCharDublonsTotal() >= 500)
			{
				link.l1 = "Sì, sono pronto.";
				link.l1.go = "amelia_8";
			}
			link.l2 = "Devo rifletterci un po'. Questa è una decisione di gran peso.";
			link.l2.go = "exit";
			NextDiag.TempNode = "amelia_next";
		break;
		
		case "amelia_next":
			if (!CheckAttribute(npchar, "quest.ChickenGod") && CheckCharacterItem(pchar, "talisman11")) {
				if (CheckAttribute(npchar, "quest.recipe_power") || CheckAttribute(npchar, "quest.recipe_fast") || CheckAttribute(npchar, "quest.recipe_total")) {
					link.chickengod = "Amelia, you seem to have a knack for such things. Can you tell me if there is a demand for such stones among your people? I find them everywhere - it's like everyone is obsessed with them!";
					link.chickengod.go = "chickengod";
				}
			}
			
			if (CheckAttribute(npchar, "quest.ChickenGod") && !CheckAttribute(npchar, "quest.ChickenGod.Complete") && GetCharacterItem(pchar, "talisman11") >= 113) {
				link.chickengod = "Here you go, Amelia. Just as you ordered: one hundred and thirteen adder stones.";
				link.chickengod.go = "chickengod_collected";
			}
		
			if (CheckAttribute(npchar, "quest.recipe_all"))
			{
				dialog.text = "Ah, sei tu, giovanotto! Allora, le mie pozioni ti sono state d’aiuto?";
				link.l1 = "L’hanno fatto davvero, Amelia. Ti ringrazio!";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Ah, sei tu, giovanotto! Vuoi comprare qualche ricetta?";
				if (CheckCharacterItem(pchar, "cannabis7") && PCharDublonsTotal() >= 500)
				{
					link.l1 = "Esatto. Ecco perché son qui.";
					link.l1.go = "amelia_8";
				}
				
				link.l2 = "Non ancora, Amelia. Sono solo passato a farti visita.";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "amelia_next";
		break;
		
		case "amelia_8":
			dialog.text = "Molto bene. Che tipo di ricetta vuoi comprare?";
			if (!CheckAttribute(npchar, "quest.recipe_power"))
			{
				link.l1 = "La ricetta per l’infuso di forza e resistenza.";
				link.l1.go = "power";
			}
			if (!CheckAttribute(npchar, "quest.recipe_fast"))
			{
				link.l2 = "La ricetta per l’elisir d’agilità e d’instancabilità.";
				link.l2.go = "fast";
			}
			if (!CheckAttribute(npchar, "quest.recipe_total"))
			{
				link.l3 = "La ricetta d’un intruglio complicato.";
				link.l3.go = "total";
			}
		break;
		
		case "power":
			dialog.text = "Bene. L'ho chiamata la 'Marea Infernale'. Tieni, prendi queste istruzioni. Leggile con attenzione. E non scordare mai come si usa, maledizione!";
			link.l1 = "Grazie, Amelia...";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosapower");
			SetAlchemyRecipeKnown("mangarosapower");
			npchar.quest.recipe_power = true;
		break;
		
		case "fast":
			dialog.text = "Bene. L’ho chiamata la ‘Burrasca’. Tieni, prendi questo manuale. Leggilo con attenzione. E non ti scordar mai come si usa, maledizione!";
			link.l1 = "Grazie, Amelia...";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosafast");
			SetAlchemyRecipeKnown("mangarosafast");
			npchar.quest.recipe_fast = true;
		break;
		
		case "total":
			dialog.text = "Va bene. L’ho chiamato ‘Abbraccio del Mare’. Tieni, prendi queste istruzioni. Leggile con attenzione. E non scordare mai come si usa, dannazione!";
			link.l1 = "Grazie, Amelia...";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosatotal");
			SetAlchemyRecipeKnown("mangarosatotal");
			npchar.quest.recipe_total = true;
		break;
		
		case "recipe_exit":
			DialogExit();
			NextDiag.CurrentNode = "amelia_next";
			RemoveDublonsFromPCharTotal(500);
			RemoveItems(pchar, "cannabis7", 1);
			Log_Info("You have given 500 doubloons and one Manga Rosa");
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(npchar, "quest.recipe_power") && CheckAttribute(npchar, "quest.recipe_fast") && CheckAttribute(npchar, "quest.recipe_total"))
			{
				npchar.quest.recipe_all = true;
				CloseQuestHeader("mangarosa");
			}
		break;
		
		case "chickengod":
			dialog.text = "Bax de adder, davvero! Vale poco, ma può servire a chi sa come usarlo. Portami centotredici di questi, e ti aprirò uno dei miei scrigni.";
			link.l1 = "Quella è proprio una montagna di pietre! Perché non mi dici prima a che diavolo ti servono?";
			link.l1.go = "chickengod_1";
		break;
		
		case "chickengod_1":
			dialog.text = "No, caro, se devi chiederlo, allora questa conoscenza non ti serve ancora.";
			link.l1 = "E che cosa c’è dentro al forziere che hai così generosamente promesso di aprire?";
			link.l1.go = "chickengod_2";
		break;
		
		case "chickengod_2":
			dialog.text = "Un sacco di cose utili per capitani che non schifano il lavoro sporco. Non farmi perdere tempo, caro, tanto tutti quei sassolini non li raccatti comunque.";
			link.l1 = "Questo lo vedremo!";
			link.l1.go = "exit";
			
			npchar.quest.ChickenGod = true;
		break;
		
		case "chickengod_collected":
			dialog.text = "Ah-ah-ah! Era solo uno scherzo, caro!";
			link.l1 = "Le beffe cadranno su di te quando ti bruceranno, strega, nella tua lurida tana!";
			link.l1.go = "chickengod_collected_1";
		break;
		
		case "chickengod_collected_1":
			dialog.text = "Non è questo il mio destino, caro... Hai reso questa zingara fiera! Prendi, questo forziere è tuo da saccheggiare.";
			link.l1 = "Grazie, Amelia. Ma spero davvero che lì dentro ci sia qualcosa d’utile oltre alle tue vecchie mutande...";
			link.l1.go = "exit";
			
			TakeNItems(pchar, "talisman11", -113);
			npchar.quest.ChickenGod.Complete = true;
			AddDialogExitQuestFunction("ChickenGod_AmeliaOpenChest");
		break;
	}
} 
