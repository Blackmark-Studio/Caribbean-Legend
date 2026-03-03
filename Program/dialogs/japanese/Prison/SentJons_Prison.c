// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "話せ、聞いてやる";
			link.l1 = "俺の勘違いだった。じゃあな。";
			link.l1.go = "Exit";
			
			// --> Sinistra Длинные тени старых грехов
			if(CheckAttribute(pchar,"questTemp.DTSG_AntiguaZalog"))
			{
				link.l1 = "最近、この街の兵士の一人がチャーリー・ニッペルを逮捕して拘留したんだ。まだここにいるか？"; 
				link.l1.go = "DTSG_AntiguaZalog_2";
			}
			// <-- Длинные тени старых грехов
		break;
		
		// --> Sinistra Длинные тени старых грехов
		case "DTSG_AntiguaZalog_2":
			dialog.text = "そうだが、なぜそんなことを聞くんだ？";
			link.l1 = "実はな、チャーリーは俺の部下の一人なんだ。奴が何の罪で捕まったのか知りたいんだよ。 連れて行った兵士どもは何も教えてくれなかったんだ。"; 
			link.l1.go = "DTSG_AntiguaZalog_3";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_AntiguaZalog_3":
			dialog.text = "そうだ。これは広く知られていない。残念だが、旦那にも教えられん。国家機密だ。";
			link.l1 = "つまり、保釈は無理ってことか？"; 
			link.l1.go = "DTSG_AntiguaZalog_4";
		break;
		
		case "DTSG_AntiguaZalog_4":
			dialog.text = "その通りだ。貴重な部下を失うのは辛いことだろうが、俺にもお前にもどうすることもできねえ。申し訳ないな、船長。";
			link.l1 = "保釈はなし、か。じゃあ……賠償金はどうだ？しかもたっぷりとな。あんたにも部下全員にも分け前が行き渡るようにな。"; 
			link.l1.go = "DTSG_AntiguaZalog_5";
		break;
		
		case "DTSG_AntiguaZalog_5":
			dialog.text = "賄賂だと？大胆だな、船長。しかし、どれだけ金を積まれても、 チャーリーを逃がしたと知れたら俺たちはあいつらの怒りからは逃れられねえ。";
			link.l1 = "もしかして……だが、せめてあいつと話すことはできねえのか？"; 
			link.l1.go = "DTSG_AntiguaZalog_6";
		break;
		
		case "DTSG_AntiguaZalog_6":
			dialog.text = "なぜだ？お前にはあいつを救い出すことも、脱獄を手伝うこともできねえんだ、だから……好きにしろ。あいつは独房の一つにいるぞ。";
			link.l1 = "はっ、もしあいつが自分の罪状を話して、お前がそんなに気にしてる国家機密までバラしたらどうするんだ、役人？"; 
			link.l1.go = "DTSG_AntiguaZalog_7";
		break;
		
		case "DTSG_AntiguaZalog_7":
			dialog.text = "そんなことは気にしちゃいない。なぜかはすぐに分かるさ。\nさあ、俺が気が変わる前に元部下と話してこい。";
			link.l1 = "ありがとうございます。"; 
			link.l1.go = "DTSG_AntiguaZalog_8";
		break;
		
		case "DTSG_AntiguaZalog_8":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_AntiguaZalog");
			pchar.questTemp.jailCanMove = true;
			
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto9");
			
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_Killer", "sold_eng_10", "man", "man", sti(pchar.rank), PIRATE, -1, false, "quest"));
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Killer";
			LAi_SetStayType(sld);
			sld.talker = 5;
			GiveItem2Character(sld, "blade_14");
			EquipCharacterbyItem(sld, "blade_14");
			GiveItem2Character(sld, "pistol4");
			EquipCharacterbyItem(sld, "pistol4");
			AddItems(sld, "purse2", 1);
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "reload", "reload12");
			sld.rank = 30;
			SetSelfSkill(sld, 80, 80, 80, 80, 80);
			LAi_SetHP(sld, 200+MOD_SKILL_ENEMY_RATE*20, 200+MOD_SKILL_ENEMY_RATE*20);
			LAi_SetImmortal(sld, true);
		break;
		
		case "DTSG_AntiguaTrevoga_2":
			dialog.text = "必要ないぞ、船長。言っただろう、あんたもあの間抜けなチャーリーと同じ牢に放り込まれるところだったんだ。 だがまず第一に、総督はあんたが抵抗せずに逮捕されたことを評価している。そして第二に、最近金貸しが訪ねてきて、 あいつの叫び声が宮殿の窓を割りかけたことにはご立腹だったがな…";
			link.l1 = "俺の逮捕を要求したのか？"; 
			link.l1.go = "DTSG_AntiguaTrevoga_3";
			DelLandQuestMark(npchar);
		break;
		
		case "DTSG_AntiguaTrevoga_3":
			dialog.text = "奴は頼んだんじゃねえ、要求したんだ。そして閣下は何かを要求されるのがお嫌いだ。 だからあの高利貸しは追い出されたのさ。";
			link.l1 = "おもしろいな。さて……"; 
			link.l1.go = "DTSG_AntiguaTrevoga_4";
		break;
		
		case "DTSG_AntiguaTrevoga_4":
			dialog.text = "今度は 船長、あんたも同じことをするんだ。\nそれと、答えのない質問はするなよ。";
			link.l1 = "俺はチャーリー・ニッペルなしじゃここを出ねえぞ。"; 
			link.l1.go = "DTSG_AntiguaTrevoga_H1";
			link.l2 = "お願いです、旦那、チャーリー・ニッペルと話をさせてください。せめて、何があったのかだけでも……"; 
			link.l2.go = "DTSG_AntiguaTrevoga_Ch1";
		break;
		
		case "DTSG_AntiguaTrevoga_H1":
			dialog.text = "その場合は、あいつに会いに行け。牢屋じゃなくて、あの世でな。";
			link.l1 = "そうか、あいつは死んじまったか……"; 
			link.l1.go = "DTSG_AntiguaTrevoga_H2";
			ChangeCharacterComplexReputation(pchar, "authority", 1);
		break;
		
		case "DTSG_AntiguaTrevoga_H2":
			dialog.text = "あんた、やけに鋭いな、船長。だがな、誰がやったかも理由も俺は絶対に教えねえってこと、わかってるだろうな。";
			link.l1 = "そうか？"; 
			link.l1.go = "DTSG_AntiguaTrevoga_H3";
		break;
		
		case "DTSG_AntiguaTrevoga_H3":
			dialog.text = "そのとおりだ。これ以上俺の我慢を試すな――イギリス兵を殺した罪でお前を独房にぶち込むよう命じる前にな。";
			link.l1 = "お前の牢から出られる奴はほとんどいねえみたいだし、俺は絶対に入りたくねえな。良い一日を、 なんて言う気にもなれねえよ。"; 
			link.l1.go = "DTSG_AntiguaTrevoga_5";
		break;
		
		case "DTSG_AntiguaTrevoga_Ch1":
			dialog.text = "チャーリー・ニッペルは誰とも話さない。\nもしかしたら創造主とは話すかもしれんがな……";
			link.l1 = "死んだのか？"; 
			link.l1.go = "DTSG_AntiguaTrevoga_Ch2";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "DTSG_AntiguaTrevoga_Ch2":
			dialog.text = "判決はすでに執行された。詳細は教えられん。これ以上しつこく聞かない方がいい――お前にとって悪い結果になるかもしれんぞ。独房だけじゃ済まん。わかったな、ド・モール船長？";
			link.l1 = "よく分かった。じゃあな。"; 
			link.l1.go = "DTSG_AntiguaTrevoga_5";
		break;
		
		case "DTSG_AntiguaTrevoga_5":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.DTSG_AntiguaTrevoga");
			AddQuestRecord("DTSG", "10");
			CloseQuestHeader("DTSG");
			ChangeCharacterComplexReputation(pchar, "authority", -10);
			AddCrewMorale(Pchar, -30);
		break;
		// <-- Длинные тени старых грехов
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
