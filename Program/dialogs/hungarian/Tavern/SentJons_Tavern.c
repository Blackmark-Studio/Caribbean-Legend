// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdései vannak?", "Miben segíthetek, " + GetAddress_Form(NPChar) + "?"), "Nemrég próbáltál feltenni nekem néhány kérdést, " + GetAddress_Form(NPChar) + "...", "Az egész nap folyamán ez a harmadik alkalom, hogy valamilyen kérdésrôl beszélsz...",
                          "További kérdések, gondolom?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Jelenleg nincs mirôl beszélnem."), "Umph, hová tûnt a memóriám...",
                      "Igen, ez tényleg a harmadik alkalom...", "Nem, milyen kérdéseket?...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason, Сага, Тени прошлого
			if (CheckAttribute(PChar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "sentjons")
			{
				link.l1 = "Raymond Bakert keresem, egy volt hóhért. Tudja, hogy él-e még, és hol találom meg?";
				link.l1.go = "baker";
			}
			//Jason, суп из черепахи
			if (CheckAttribute(PChar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "baster" && !CheckAttribute(npchar, "quest.terrapin"))
			{
				link.l1 = "Mr. Jones-t keresem. Tudna segíteni a keresésben, haver?";
				link.l1.go = "terrapin";
			}
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok")
			{
				link.l1 = "Figyeljen, nem érkezett ide a városba egy alkimista, egy orvos? Olasz, harminc év körüli, a neve Gino Gvineili. Hallottál róla valamit?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Сага, Тени прошлого
		case "baker":
			dialog.text = "A mi kedves dagadékunk népszerûbb lett, mint Fox ezredes! Életben van, szegény fickó. De most nincs a városban. Miután Raymond megtudta, hogy a hozzád hasonló komoly emberek érdeklôdnek iránta, elsietett, eladta a kunyhóját aprópénzért, és eltûnt a széllel együtt.";
			link.l1 = "Hová tûnt a széllel?";
			link.l1.go = "baker_1";
		break;
		
		case "baker_1":
			dialog.text = "Ó, ki tudja. Elment hajóorvosnak az elsô hajóra, ami arra járt. Csakhogy az a hajó csak ma jött vissza, és még senki sem látta Bakert partra szállni.";
			link.l1 = "Hogy találom meg a kapitányt?";
			link.l1.go = "baker_2";
		break;
		
		case "baker_2":
			dialog.text = "Miért gondolod, hogy meg kell keresned? Biztos vagyok benne, hogy már a szokásos módon berúgott a kabinjában. A szivárgó vödrét úgy hívják 'Callow Meggy'. Ilyen a kapitány, ilyen a neve...";
			link.l1 = "Köszönöm a segítséget, haver!";
			link.l1.go = "baker_3";
		break;
		
		case "baker_3":
			DialogExit();
			AddQuestRecord("Shadows", "2");
			pchar.questTemp.Saga.Shadows = "baldmaggy";
			pchar.quest.Saga_ShadowsMaggy.win_condition.l1 = "location";
			pchar.quest.Saga_ShadowsMaggy.win_condition.l1.location = "Antigua";
			pchar.quest.Saga_ShadowsMaggy.function = "Saga_SetBaldMaggy";
		break;
		
		//суп из черепахи
		case "terrapin":
			dialog.text = "Mr. Jones? Csak viccelsz velem, pajtás. Tudod, hány kibaszott Jones van ezen a szigeten? Ennél pontosabban kell fogalmaznod.";
			link.l1 = "Van egy felnôtt húga, Molly. Azt mondják, elképesztôen gyönyörû.";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "Nem, semmi ilyesmi nem jut eszembe. Bocs, haver...";
			link.l1 = "Rendben, ha nem tudod, akkor nem tudod...";
			link.l1.go = "exit";
			npchar.quest.terrapin = "true";
		break;
		
		case "guardoftruth":
			dialog.text = "Nem, nem hallottam. És csak egy alkimista van a városban, John Murdock gyógyszerész. Figyelemre méltó bájitalai vannak - minden betegséget meggyógyítanak.";
			link.l1 = "Gondolod, hogy ô maga fôzi ezeket a bájitalokat?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Jó kérdés. Néha megkérdezem magamtól, hogy John egyáltalán nem úgy néz ki, mint a gyógyszeres üvegek, gyógynövények és porok ismerôje. Inkább hasonlít egy volt katonára, egy zsoldosra... ez közelebb áll az igazsághoz.";
			link.l1 = "Hát, azt hiszem, a férfi túlképzett...";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Talán az is. De egy dolgot biztosan tudok, valaki lakik a második emeleten. Az ablak állandóan le van húzva. Még akkor is, amikor John lent van, csörömpölés hallatszik, mint az üveg fiolák és üvegek, valamint a forró gyógynövények szaga, és éjszaka sem alszik ki a villany. Ezért gyanakszom arra, hogy annak a szobának a lakója az, aki John gyógyszereit készíti elô eladásra.";
			link.l1 = "Hm. Érdekes megfigyelés. Köszönöm, haver!";
			link.l1.go = "exit";
			pchar.questTemp.Guardoftruth = "merdok1";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
