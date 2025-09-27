// полковник Фокс - бравый командир морской пехоты 'морские лисы'.
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
			if (CheckAttribute(pchar, "questTemp.Terrapin_KathyReward"))
			{
				dialog.text = "Mit szeretne, uram? Ó... az én... várj! Ön az a francia kapitány, aki megmentette a lányomat Levasseur szolgáinak mocskos kezeitôl! ";
				link.l1 = "Látom, hogy Catherine már mesélt rólam...";
				link.l1.go = "terrapin";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.Usurer") && !CheckAttribute(npchar, "quest.utensil"))
			{
				dialog.text = "Mit akar, uram?";
				link.l1 = "Jó napot, ezredes úr. Néhány 'nem mindennapi' ügy miatt jöttem önhöz. Rá tudna szánni egy kis idôt rám?";
				link.l1.go = "guardoftruth";
				break;
			}
			// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "eng_reward")
			{
				dialog.text = "Ha nem tévedek, ön az a "+GetSexPhrase("kapitány","női kapitány")+" , aki segített embereimnek a küldetés végrehajtásában Sint Maartenen? "+TimeGreeting()+"!";
				link.l1 = ""TimeGreeting()+", Ezredes úr. Igen, én vagyok az.";
				link.l1.go = "FMQN";
				break;
			}
			dialog.text = "Mit akar, uram?";
			link.l1 = "Semmi, ezredes. Elmegyek.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "guardoftruth":
			dialog.text = "Szóval köpje már ki, ha már idáig eljutott...";
			link.l1 = "Nemrég szálltál fel egy szkúnárra, amely Rollie the Cap, egy holland kalóz parancsnoksága alatt állt, és a kapitányt ide, Szent Jánosra hoztad.";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Kapitány? Ó, ne nevettessetek! Ennek a bûnözô söpredéknek nincs joga, hogy így hívják. Elfogtam egy átkozott kalózt, egy farkascsorda fejét, aki angol kereskedôket és kereskedôket rabolt ki és gyilkolt meg. És gondoskodtam róla, hogy ô és a degeneráltjai azt kapják, amit megérdemelnek - egész Szent János végignézte, ahogy felakasztják ôket a mólón!";
			link.l1 = "Azt hiszem, akkor nem fogom tudni kikérdezni ezt a gazembert... Ezredes, talán tudna segíteni nekem? A kalóznál volt valami, ami nem az övé volt - az arany füstölô. Találtak nála valamit, ami hasonlít rá?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "Nem, átkutattuk, és annak a gazembernek nem volt semmiféle holmija, ráadásul bizonyára mindet tisztességes kereskedôktôl vették el! És ami az ön aggodalmát illeti... hmm nem, nem találtuk meg. És mit kereshet egy füstölô egy kalózhajón? Tényleg azt hiszi, hogy volt köztük pap?";
			link.l1 = "Nem, nem hiszem. Rollie, a sapka, a willemstadi uzsorástól vette, aki egy másik kalóztól vette. A füstölô szép és drága, és igyekszem visszaadni jogos tulajdonosának. Gondolom, Rollie úgy szemet vetett rá, mint egy szarka.";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "Az igazság az, hogy Rollie-nak üres raktér és néhány láda dublonnal volt tele, amikor a hajójára léptünk és elfoglaltuk. Semmi más, csak szemét. Se értéktárgyak, se aranyfüstölô. Egy kalózhoz nem illô tárgyakra emlékeznék.\nGyanítom, hogy az az átkozott kalóz Dominikán rejtegette a megtakarításait. Mi is ott szálltunk le, és átkutattuk a környéket, de nem találtunk semmit. De nem maradtunk a szigeten, és nem kutattuk fel a mélyét, mert rengeteg vadember volt ott.";
			link.l1 = "Hm... A kalóz a többi lopott holmijával együtt valahol Dominikán rejthette el a fazekat... Kár. Kihallgatták a kalózt, a kivégzés elôtt?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "Igen... és ô csak elkezdett nevetni az arcomba. De nem igazán érdekeltek a rejtekhelyei. Rollie-t, a kapitányt felakasztották, és ez a legfontosabb.";
			link.l1 = "Értem. Köszönöm a történetet és az idejét, ezredes. Viszontlátásra...";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			DialogExit();
			npchar.quest.utensil = "true";
			AddQuestRecord("Guardoftruth", "24");
			Island_SetReloadEnableGlobal("Dominica", true);//patch-7
			// заполняем сундук
			pchar.GenQuestBox.Shore27 = true;
			pchar.GenQuestBox.Shore27.box1.money = 30000;
			pchar.GenQuestBox.Shore27.box1.items.gold_dublon = 100;
			pchar.GenQuestBox.Shore27.box1.items.chest = 1;
			pchar.GenQuestBox.Shore27.box1.items.icollection = 1;
			pchar.GenQuestBox.Shore27.box1.items.jewelry40 = 15;
			pchar.GenQuestBox.Shore27.box1.items.jewelry41 = 22;
			pchar.GenQuestBox.Shore27.box1.items.jewelry42 = 8;
			pchar.GenQuestBox.Shore27.box1.items.jewelry43 = 20;
			pchar.GenQuestBox.Shore27.box1.items.jewelry44 = 33;
			pchar.GenQuestBox.Shore27.box1.items.jewelry45 = 16;
			pchar.GenQuestBox.Shore27.box1.items.jewelry46 = 58;
			pchar.GenQuestBox.Shore27.box1.items.jewelry35 = 1; // кадило
			pchar.quest.GuardOT_finddominicachest.win_condition.l1 = "item";
			pchar.quest.GuardOT_finddominicachest.win_condition.l1.item = "jewelry35";
			pchar.quest.GuardOT_finddominicachest.function = "GuardOT_DominicaChest";
		break;
		
		case "terrapin":
			dialog.text = "Többször is, kapitány! Az ön becsületes és bátor tette aligha volt elvárható egy franciától. Hálával tartozom önnek, mint katona és mint apa. Nincs számomra semmi értékesebb ezen a világon, mint a lányom...";
			link.l1 = "Örülök, hogy segítségére lehettem, és remélem, hogy tetteimmel idôvel meggondolja magát a franciák iránt.";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "Egy ilyen tiszteletreméltó és nagylelkû úriember jelenléte, mint ön, aki az életét kockáztatta egy ismeretlen angol lányért, lényegesen felmelegíti a kapcsolatomat honfitársaival!";
			link.l1 = "A patkányok között minden nemzetnél vannak becsületes emberek, ezredes úr...";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "És ezt be is bizonyítottad! Jutalom vár rád, kapitány. Persze, a lány élete megfizethetetlen, de Jonathan Fox mindig megfizeti az adósságát, esküszöm! Ön igazi katona, ezért az én ajándékom az ön számára egy katona ajándéka. Tessék, nézze meg.\nEz egy blunderbuss, egy kiváló haditengerészeti muskéta, egy kézzel is használható. Különleges nyilakkal töltheted meg, amelyek még a legtartósabb cuiraszt is mindig átütik. Kartácsot is lô, és szilárd szerkezete lehetôvé teszi, hogy szögtöltetekkel töltsd meg. Tessék, vedd el, most már a tiéd.";
			link.l1 = "Ilyen kiváló ajándék egy katonának, köszönöm, ezredes úr!";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			Log_Info("Kaptál egy bunkósbotot");
			Log_Info("Kaptál 10 nyílvesszôt");
			Log_Info("Kaptál 10 szögtöltetet");
			Log_Info("Megkaptad a szigonynyilak készítésének útmutatóját.");
			Log_Info("Megkaptad az útmutatót a szögtöltet elkészítéséhez.");
			GiveItem2Character(pchar, "pistol8");
			TakeNItems(pchar, "harpoon", 10);
			TakeNItems(pchar, "GunEchin", 10);
			GiveItem2Character(pchar, "recipe_harpoon"); 
			GiveItem2Character(pchar, "recipe_GunEchin"); 
			PlaySound("interface\important_item.wav");
			dialog.text = "Egy kis adag lôszert és az elkészítésükhöz szükséges utasításokat is átadom neked. Kár lenne, ha nem használnád ki maximálisan az erejét!";
			link.l1 = "Köszönöm, ezredes úr. Nem utasítok vissza egy ilyen ajándékot, de szeretném, ha tudnád, hogy nem jutalomból tartogattam Katalint. Egyszerûen nem hagyhattam, hogy a védtelen lánynak bármi baja essen.";
			link.l1.go = "terrapin_4";
		break;
		
		case "terrapin_4":
			dialog.text = "Tudom, kapitány úr. Kétszeresen is megtiszteli önt. Katalint valósággal elragadtattad, és nem könnyû feladat pozitív benyomást tenni rá. Ismétlem, hálával tartozunk önnek, amiért megmentette ôt. Tartozom neked!";
			link.l1 = "Nos, én köszönöm az ajándékot, ezredes. Adja át Catherine-nek üdvözletemet, és kívánom, hogy legközelebb hallgasson az apjára.";
			link.l1.go = "terrapin_5";
		break;
		
		case "terrapin_5":
			dialog.text = "Úgy lesz, kapitány! Viszlát, és jó utat!";
			link.l1 = "Viszlát, ezredes.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Terrapin_KathyReward");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterComplexReputation(pchar, "fame", 5);
			ChangeCharacterNationReputation(pchar, ENGLAND, 20);
		break;
		
		// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "Olvastam a jelentést. Tetteit nagyra értékelem, ezért meg kell jutalmazni. Harmincezer pezó az expedíciós szolgálatokért és fegyverek a katonás hôsiességért. Fogadja el ezt a pengét és ezt az arquebust. Mostantól mind a tiéd!";
			link.l1 = "Köszönöm, uram.";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "Mindenképpen, kapitány. A brit gyarmatok, a hatóságok és személyesen én magam is szeretettel és tisztelettel jutalmazom. Köszönöm, hogy nem hagytad cserben az embereimet, és segítetted ôket a küldetésükben!";
			link.l1 = "Örömmel, ezredes...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			dialog.text = "Most pedig kérem, bocsásson meg - más dolgom van. Isten éltessen, kapitány "+pchar.lastname+".";
			link.l1 = "Viszontlátásra, "+GetAddress_Form(NPChar)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglandComplete");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
