// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("Wszystkie plotki o "+GetCityName(npchar.city)+"do usług. Czego chciałbyś się dowiedzieć?"," Właśnie o tym rozmawialiśmy. Musiałeś zapomnieć...","To już trzeci raz, kiedy mnie niepokoisz...","Powtarzasz to wszystko jak papuga...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Wiesz, "+NPChar.name+"może następnym razem.","Racja, z jakiegoś powodu zapomniałem...","Tak, to naprawdę już trzeci raz...","Tak...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "Powiedz mi, gdzie mogę znaleźć Señorę Belindę de Ribero?";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "W pałacu gubernatora, rzecz jasna. Jest kuzynką Don Fernando de Villegas. Możesz jej szukać tam po południu podczas jej sjesty, zwykle ma sprawy do załatwienia rano. Obecnie ma pewne kłopoty, więc miej to na uwadze. Ale nie będzie miała nic przeciwko rozmowie z tobą. Donna Belinda to dobra kobieta.";
			link.l1 = "Dziękuję!";
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
