// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("A "+ GetCityName(npchar.city) +" összes pletykája az Ön rendelkezésére áll. Mit szeretnél megtudni?",
                          "Éppen errôl beszéltünk. Biztos elfelejtette...", "Most már harmadszor zaklatsz...",
                          "Ismétled ugyanazt, mint egy papagáj...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tudod, " + NPChar.name + ", talán legközelebb.", "Rendben, valamiért elfelejtettem...",
                      "Igen, ez tényleg a harmadik alkalom...", "Igen...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "Mondja, hol találom Senora Belinda de Ribero-t?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "A kormányzói palotában, természetesen. Ô Don Fernando de Villegas unokatestvére. Ott keresheted dél után, a szieszta idején, általában délelôtt van dolga. Most éppen bajban van, úgyhogy ezt tartsd észben. De nem bánja, ha beszélni akar veled. Donna Belinda jó asszony.";
			link.l1 = "Köszönöm!";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			DialogExit();
			npchar.quest.utensil = "true";
			pchar.questTemp.Guardoftruth.Belinda = "seek";
			// ставим Белинду
			sld = GetCharacter(NPC_GenerateCharacter("GOT_Belinda", "Belinda", "woman", "towngirl", 3, SPAIN, -1, true, "quest"));
			SetFantomParamFromRank(sld, 3, true);
			sld.name = "Belinda";
			sld.lastname = "de Ribero";
			sld.dialog.FileName = "Quest\Sharlie\guardoftruth.c";
			sld.dialog.currentnode = "belinda";
			sld.greeting = "noble_female";
			LAi_SetLoginTime(sld, 13.0, 20.0);
			LAi_SetOwnerType(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Cumana_TownhallRoom", "barmen", "stay");
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
