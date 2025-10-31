// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Gyerünk, mit akarsz?",
                          "Épp errôl beszéltünk. Biztos elfelejtetted...", "Ma már harmadszor beszélsz valami kérdésrôl...",
                          "Figyelj, ez egy bolt. Az emberek itt vásárolnak. Ne zavarjon!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tudod, " + NPChar.name + ", talán legközelebb.", "Rendben, valamiért elfelejtettem...",
                      "Igen, ez tényleg a harmadik alkalom...", "Hm, nem fogom...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//Jason --> Португалец
			if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "Findcloves" && !CheckAttribute(npchar, "quest.Portugal"))
			{
   				link.l1 = "Figyelj, szükségem van néhány divatos ruhára. Drága, úgy akarok kinézni, mint egy igazi nemes. Van valami ilyesmi?";
				link.l1.go = "Portugal_cloves";
			}
			//<-- Португалец
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "maarten")
			{
				link.l1 = "A 'Admirable' nevû gálya nemrég hozott neked egy rakomány bôröket. Emlékszik rá?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		//Jason --> Португалец
		case "Portugal_cloves":
			dialog.text = "Nemes ruhák? Persze, van itt egy készletem: nadrág, bunda, selyem ing és csizma. 20,000 pezóba kerül. A ruhák nagyon jó minôségûek, kényelmesek, és figyelemre méltó a megjelenésük, ezért nem fogadok el kevesebbet érte.";
			if (sti(pchar.money) >= 20000)
			{
				link.l1 = "Nagyszerû! Add ide!";
				link.l1.go = "Portugal_cloves_1";
			}
			link.l2 = "Hm... Jelenleg nincs ennyi pénzem.";
			link.l2.go = "Portugal_cloves_nomoney";
		break;
		
		case "Portugal_cloves_nomoney":
			dialog.text = "Akkor gyere vissza, ha lesz pénzed.";
			link.l1 = "Rendben, akkor majd visszajössz, ha lesz pénzed. Visszajövök!";
			link.l1.go = "exit";
		break;
		
		case "Portugal_cloves_1":
			AddMoneyToCharacter(pchar, -20000);
			GiveItem2Character(pchar, "suit_1");
			Log_Info("Drága ruhákat kaptál");
			PlaySound("interface\important_item.wav");
			dialog.text = "Tessék, tessék.";
			link.l1 = "Köszönöm!";
			link.l1.go = "exit";
			npchar.quest.Portugal = "true";
			sld = characterFromId("PortugalDoctor");
			sld.dialog.currentnode = "Portugal_doctor_4";
			DelLandQuestMark(characterFromId("Marigo_trader"));
			AddLandQuestMark(characterFromId("PortugalDoctor"), "questmarkmain");
			QuestPointerDelLoc("marigo_town", "reload", "reload6_back");
			QuestPointerToLoc("marigo_town", "reload", "houseF1");
		break;
		//<-- Португалец
		case "guardoftruth":
			dialog.text = "Igen. Idôben megérkezett, kipakolta az árut, és én kifizettem, ahogy megbeszéltük. Miért kérdezed?";
			link.l1 = "A hajó kapitánya Gaius Marchais, régi ismerôsöm. Szóval megpróbálom megtalálni ôt. Meg tudná mondani, hogy mit csinált ezután? Esetleg adott neki további szállítmányt, vagy említette, hogy hová akar menni?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Semmi ilyesmi. Nem ajánlottam neki semmilyen szállítmányt, nem is kérte. Nem osztotta meg velem a jövôbeli terveit. Már nem is emlékszem minden részletre, tudja, hány ember jött és ment ki innen azóta? Kipakolt és elhajózott, és ez minden, amit elmondhatok róla.";
			link.l1 = "Jól van, rendben. Nos, azért köszönöm. Minden jót!";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			DialogExit();
			AddQuestRecord("Guardoftruth", "11");
			pchar.questTemp.Guardoftruth = "maarten1";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}
