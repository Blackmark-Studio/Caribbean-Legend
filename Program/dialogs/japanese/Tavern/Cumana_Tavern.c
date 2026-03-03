// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("「すべての噂は」 "+GetCityName(npchar.city)+" お役に立ちますぜ。何を知りたいんだ？","ちょうどその話をしていたところだぜ。お前、忘れちまったのか…","もうこれで三度目だぞ、俺にちょっかい出すのは…","お前、オウムみたいに同じことばかり繰り返してるじゃねえか…","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「知ってるか、」 "+NPChar.name+"、また今度にしようか。","ああ、何かの理由で忘れちまったんだよな……","ああ、本当にこれで三度目だな……","ああ……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "utensil" && !CheckAttribute(npchar, "quest.utensil"))
			{
				link.l1 = "教えてくれ、どこでベリンダ・デ・リベロ夫人を見つけられるんだ？";
                link.l1.go = "guardoftruth";
			}
		break;
		
		case "guardoftruth":
			dialog.text = "総督の宮殿にいるさ、もちろん。彼女はドン・フェルナンド・デ・ビリェガスの従姉妹なんだ。 昼過ぎのシエスタの時間にそこへ行けば会えるぜ、朝はたいてい用事があるからな。 今はちょっと厄介ごとを抱えてるから、それは覚えておけよ。でも、お前と話すのは気にしないはずだ。 ドーニャ・ベリンダはいい女さ。";
			link.l1 = "ありがとう！";
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
