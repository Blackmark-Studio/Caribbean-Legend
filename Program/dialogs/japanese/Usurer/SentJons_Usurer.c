// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("ご質問は何でしょうか？","ご用件をお伺いしましょうか？"),"「その質問は、つい最近も私に尋ねましたね…」","ああ、さては……また同じところをぐるぐる回ってるんじゃないか？","聞きなさい、ここで財務を担当しているのは私です、質問にはお答えしません…","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えが変わった……","今は話すことは何もありません。"),"うーん、俺の記憶はどこへ行っちまったんだ…","ご名答です、申し訳ありません……","承知しました……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// --> Sinistra Длинные тени старых грехов	
			if (CheckAttribute(pchar, "questTemp.DTSG_KnippelDolg"))
			{
				link.l1 = "あなたの債務者の一人についてお話ししたいのですが。";
				link.l1.go = "DTSG_KnippelDolg";
			}
			// <-- Длинные тени старых грехов
		break;
		
		// --> Sinistra Длинные тени старых грехов	
		case "DTSG_KnippelDolg":
			DeleteAttribute(pchar, "questTemp.DTSG_KnippelDolg");
			dialog.text = "どれだ？";
			if (sti(pchar.reputation.nobility) > 50)
			{
				link.l1 = "（ご挨拶）確かにチャーリー・ニッペルでございます。";
				link.l1.go = "DTSG_KnippelDolg_VD_2";
			}
			else
			{
				link.l2 = "（名誉）よくもまあ、そんなに落ち着いて俺に話しかけられるな。お前は俺の部下に賞金稼ぎを差し向けたじゃねえか。";
				link.l2.go = "DTSG_KnippelDolg_2";
			}
		break;
		
		case "DTSG_KnippelDolg_VD_2":
			dialog.text = "「チャーリーですか？しかし、彼はもう私の債務者ではありません。彼の借金はずいぶん前に返済されました、旦那。」";
			link.l1 = "本当か？もし秘密でなければ、誰にだ？";
			link.l1.go = "DTSG_KnippelDolg_VD_3";
		break;
		
		case "DTSG_KnippelDolg_VD_3":
			dialog.text = "違います。彼の船長、リチャード・フリートウッドによるものです。本物の紳士で、 誰もが彼のような友人を持つべきですよ。";
			link.l1 = "ご覧の通り、今は俺がチャーリーの船長だ。フリートウッド旦那が……彼を俺の下に移したんだ。彼が約束を守って、あんたに支払いを済ませたと知って安心したよ。";
			link.l1.go = "DTSG_KnippelDolg_VD_4";
		break;
		
		case "DTSG_KnippelDolg_VD_4":
			dialog.text = "「だからこそお尋ねなのですね。」";
			link.l1 = "それだけじゃない。チャーリーのことはよく知っているだろう？彼は逮捕されて、以前には傭兵まで差し向けられたんだ。 \nなぜだか心当たりはあるか？何しろ、君は実に…多様な人々と取引があるからな。";
			link.l1.go = "DTSG_KnippelDolg_VD_5";
		break;
		
		case "DTSG_KnippelDolg_VD_5":
			dialog.text = "チャーリーが逮捕された？驚きましたよ、旦那、私は何も知りませんでした。彼の…敵についても同様です。あのような善良で神を畏れる男が…";
			link.l1 = "それは反論できませんね。まあ、とにかくありがとう。司令官が私から保釈金を受け取ってくれることを願っています。";
			link.l1.go = "DTSG_KnippelDolg_VD_6";
		break;
		
		case "DTSG_KnippelDolg_VD_6":
			dialog.text = "保釈金のための資金が必要な時は、どうぞ遠慮なくまたお越しください――好条件でお貸ししますよ。";
			link.l1 = "ははは、本気か？金貸しは所詮金貸しだ。保釈金くらい自分で払えるさ。じゃあな。";
			link.l1.go = "DTSG_KnippelDolg_VD_7";
		break;
		
		case "DTSG_KnippelDolg_VD_7":
			DialogExit();
			
			LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
			//LAi_LocationDisableOfficersGen("SentJons_town", false);
			LAi_LocationDisableOfficersGen("SentJons_bank", false);
			AddQuestRecord("DTSG", "11");
			pchar.questTemp.DTSG_AntiguaZalog = true;
			AddLandQuestMarkToPhantom("SentJons_prison", "SentJonsJailOff");
		break;
		
		case "DTSG_KnippelDolg_2":
			dialog.text = "賞金稼ぎだと？お前の仲間を追ってる？何の話だ……";
			link.l1 = "否定するな。素直に白状すれば紳士らしく解決しよう。\nだが、とぼけるつもりなら、こちらも手荒にいかせてもらうぞ。";
			link.l1.go = "DTSG_KnippelDolg_3";
		break;
		
		case "DTSG_KnippelDolg_3":
			dialog.text = "い、いえ、何かの間違いです！…衛兵！！殺されると脅されています！";
			link.l1 = "「ったく、勘弁してくれよ……」";
			link.l1.go = "DTSG_KnippelDolg_4";
		break;
		
		case "DTSG_KnippelDolg_4":
			DialogExit();
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_AntiguaStrazhBank_1", "sold_eng_"+(rand(7)+1), "man", "man", 10, ENGLAND, 0, false, "soldier"));
			GiveItem2Character(sld, "blade_10");
			EquipCharacterByItem(sld, "blade_10");
			GiveItem2Character(sld, "pistol1");
			EquipCharacterByItem(sld, "pistol1");
			ChangeCharacterAddressGroup(sld, "SentJons_bank", "reload", "reload1");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_AntiguaStrazhBank";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			LAi_SetHP(sld, 140+MOD_SKILL_ENEMY_RATE*10, 140+MOD_SKILL_ENEMY_RATE*10);
			AddLandQuestMarkToPhantom("SentJons_prison", "SentJonsJailOff");
		break;
		// <-- Длинные тени старых грехов
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
