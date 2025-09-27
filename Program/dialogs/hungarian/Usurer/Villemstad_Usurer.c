// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdései vannak?", "Miben segíthetek?"), "Nemrég próbálta ezt a kérdést feltenni nekem...", "Igen, hadd találjam ki... Már megint körbe-körbe jársz?",
                          "Figyelj, én itt a pénzügyekkel foglalkozom, nem válaszolok kérdésekre...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Jelenleg nincs mirôl beszélnem."), "Umph, hová tûnt a memóriám...",
                      "Kitaláltad, sajnálom...", "Megértem...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "Mynheer, van egy szokatlan ügyem. Tudom, hogy egy Gaius Marchais nevû francia kalóz nemrégiben eladott neked két különleges tárgyat: egy arany ostensort és egy arany fazekat. Szeretném megvásárolni ôket tôled.";
                link.l1.go = "guardoftruth";
			}
			if (CheckAttribute(npchar, "quest.GOT_chest") && CheckCharacterItem(pchar, "chest"))
			{
				link.l1 = "Hoztam neked egy kis ládányi dublont.";
                link.l1.go = "guardoftruth_3";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "Ó, igen! Természetesen emlékszem rájuk! Igen, valóban eredeti, és ami még fontosabb, drága tárgyak voltak. De elkésett, kapitány, már nincsenek nálam. Már eladtam ôket.";
			link.l1 = "Hihetetlen! És ki érdeklôdött az ilyen egyházi tárgyak iránt? Mynheer, kinek adtad el ôket? Szeretném megpróbálni visszavásárolni ôket...";
			link.l1.go = "guardoftruth_1";
			npchar.quest.utensil = "true";
		break;
		
		case "guardoftruth_1":
			dialog.text = "Hm, és miért kellene kiadnom az ügyfeleim nevét?";
			if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && pchar.questTemp.HWIC.Detector == "self_win")
			{
				link.l1 = "Talán azért, mert jó barátja vagyok Matthias Beck kormányzó szemében, és kérhetek tôle megfelelô szankciót az ön számára?";
				link.l1.go = "guardoftruth_2_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && pchar.questTemp.HWIC.Detector == "holl_win")
				{
					link.l1 = "Talán azért, mert jó kapcsolatban állok a Holland Nyugat-indiai Társasággal, és nagy segítséget nyújtottam sok holland telepesnek a szigetvilágban?";
					link.l1.go = "guardoftruth_2_2";
				}	
				else
				{
					link.l1 = "Talán azért, mert én fizetek érte?";
					link.l1.go = "guardoftruth_2_3";
					npchar.quest.GOT_chest = "true";
				}
			}
		break;
		
		case "guardoftruth_2_1":
			dialog.text = "Á, persze, hogy te vagy "+GetFullName(pchar)+", magának a kormányzónak a barátja, aki felfedte Lucas Rodenburg bûnös összeesküvését... Hogy tudnék errôl megfeledkezni? Persze, hogy elmondom.";
			link.l1 = "Akkor csupa fül vagyok.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_2_2":
			dialog.text = "Á, igen, te vagy "+GetFullName(pchar)+", a kalóz 'szellemhajó nagy hódítója'. Hogy is felejthettem volna el? Persze, hogy elárulom.";
			link.l1 = "Akkor csupa fül vagyok.";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_2_3":
			dialog.text = "Rendben, akkor. Egy ládáért, ami tele van aranydublonnal, gondolom, mesélek neked azokról, akik megelôztek téged a vásárlásban.";
			if (CheckCharacterItem(pchar, "chest"))
			{
				link.l1 = "Tessék, tessék. Ezek nagyon kedves tárgyak számomra...";
				link.l1.go = "guardoftruth_3";
			}
			else
			{
				link.l1 = "Rendben, elhozom neked, amit kértél. Ezek nagyon kedves tárgyak számomra...";
				link.l1.go = "exit";
			}
		break;
		
		case "guardoftruth_3":
			RemoveItems(pchar, "chest", 1);
			Log_Info("Kaptál egy láda dublont");
			PlaySound("interface\important_item.wav");
			dialog.text = "Csodálatos. Ebben az esetben hajlandó vagyok megosztani önnel néhány információt.";
			link.l1 = "Csupa fül vagyok.";
			link.l1.go = "guardoftruth_4";
			DeleteAttribute(npchar, "quest.GOT_chest");
		break;
		
		case "guardoftruth_4":
			dialog.text = "Az aranyfüstölôt egy Rolande Moses nevû férfi vásárolta, ismertebb nevén Rollie, a sapkás. Hogy ennek a hentesnek miért volt szüksége egy értékes egyházi tárgyra, arra nem tudok rájönni, de valamiért leírhatatlanul el volt ragadtatva tôle... Egyébként kétlem, hogy magával Rollie-val találkozna.";
			link.l1 = "Miért van ez?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "Mert ez a magányos angol kereskedôk lelkes rablója nemrégiben pont Fox ezredes mancsába került a szkúnájával. Tudja, hogy ki az? ";
			link.l1 = "Naná! A 'tengeri rókák parancsnoka' a Antiguán található St. Jonesban...";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "Nos, akkor megérti, miért nem látjuk többé szegény Rolande-ot. Az ezredes lefoglalta a szkúnáját a legénységének minden túlélôjével együtt, és St. Jonesba szállította ôket, ahol valószínûleg már nyakkendôt kötöttek a nyakukba.";
			link.l1 = "Értem. És az ostensory?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "Az ostensory-t nemrégiben szerezte meg Senora Belinda de Ribero Cumana-ból. Egy nagyon neves senora, aki rokona magának Fernando de Villegasnak, Cumana kormányzójának. Gondolom, ajándékként akarta elhozni a templomnak.";
			link.l1 = "Senora Belinda de Ribero? Megtalálom ôt Cumana-ban, igaz?";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "Igen, biztosan. Ô maga mondta, hogy egyenesen hazafelé tart Willemstadból.";
			link.l1 = "Rendben. Köszönöm, "+npchar.name+", nagy segítség voltál!";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "Bármikor, mynheer. Látogasson meg idôrôl idôre!";
			link.l1 = "Kívánom, hogy a gazdag ügyfelek kövér pénztárcával és szûkös aggyal... Ha-ha!";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			DialogExit();
			AddQuestRecord("Guardoftruth", "23");
			pchar.questTemp.Guardoftruth.Usurer = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
