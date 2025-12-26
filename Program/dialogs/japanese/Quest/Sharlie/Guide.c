// гид
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "何か用か？";
			link.l1 = "いいえ、何もありません。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "guide_0":
			PlaySound("Voice\English\LE\Greguar\Greguar_01.wav");
			dialog.text = "植民地へようこそ、旦那！自己紹介させていただきます： "+GetFullName(npchar)+"。お前、懐かしい故郷から来たのか？";
			link.l1 = "ごきげんよう、旦那。私の名前は "+GetFullName(pchar)+"「ええ、今しがた船を降りたところです。」";
			link.l1.go = "guide_1";
		break;
		
		case "guide_1":
			DelLandQuestMark(npchar);
			dialog.text = "紳士を見かけたので、手を貸すべきだと思いました。この新世界には独自の掟があり、それを知らぬと高くつきます。 身分ある者同士、助け合うべきでしょう。ここには、わずかな金であなたを裏切る下賤な連中が山ほどいますから\n"+"ご案内して基本的なことをお教えしてもよろしいでしょうか？";
			link.l1 = "ご親切にどうも、旦那！喜んでお受けします。";
			link.l1.go = "guide_2";
			link.l2 = "ありがとうございます、旦那。でも自分の道は自分で探します。";
			link.l2.go = "guide_exit";
		break;
		
		case "guide_exit":
			dialog.text = "かしこまりました、旦那。ともかく、お会いできて光栄でした。この地では高貴な紳士は珍しいお客様です。 ご武運をお祈りしております！";
			link.l1 = "「あなたにも、」 "+GetFullName(npchar)+"!";
			link.l1.go = "guide_exit_1";			
		break;
		
		case "guide_exit_1":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DoQuestCheckDelay("NgtF3", 1.0);
			QuestPointerToLoc("FortFrance_town", "reload", "reload3_back");
		break;
		
		case "guide_2":
			dialog.text = "素晴らしい！カリブの町はどこも同じ造りだ。サン・ピエールの構造を覚えれば、他の港もすぐに分かるさ。";
			link.l1 = "";
			link.l1.go = "guide_tavern";		
		break;
		
		case "guide_tavern":
			dialog.text = "酒場――港の中心地だ。寝床やラム酒、噂話を手に入れたり、水夫や士官を雇ったりできる。カードで遊んだり、仕事を探したり、 密輸業者や宝の地図売りと取引することも可能だ。";
			link.l1 = "";
			link.l1.go = "guide_market";
			locCameraFromToPos(-2.08, 5.32, 68.88, true, -15.00, 0.90, 55.00);
		break;
		
		case "guide_market":
			dialog.text = "市場だ。補給が必要か？鍛冶屋には剣や鎧、弾薬があるし、薬草女は秘薬を売っている。 ジプシーや修道士はお守りを商い、ガラクタ屋は細々した品を、物作りができる奴に売っているぞ。\n";
			link.l1 = "";
			link.l1.go = "guide_brothel";
			locCameraFromToPos(-13.58, 4.11, 69.06, true, -45.00, -6.00, 52.00);
		break;
		
		case "guide_brothel":
			dialog.text = "売春宿。腕の立つ女と過ごす時間ほど気分を高めてくれるものはないさ。\n活力が足りないときは立ち寄って、新しい自分になって出てこいよ。";
			link.l1 = "";
			link.l1.go = "guide_bank";
			locCameraFromToPos(-2.75, 7.07, 61.10, true, 60.00, -6.60, 42.65);
		break;
		
		case "guide_bank":
			dialog.text = "銀行。お金の借入や投資ができるし、ペソをドゥブロン金貨に両替できる。宝石を売るならここが一番だ。";
			link.l1 = "";
			link.l1.go = "guide_prison";
			locCameraFromToPos(3.07, 7.64, 51.99, true, 45.00, -8.30, 4.50);
		break;
		
		case "guide_prison":
			dialog.text = "牢獄さ。中にいるのは本当の悪党なんてほとんどいなくて、大半は流れ者だ。\n奴らから仕事が欲しいなら、司令官に話してみな。ちょっとした賄賂で牢の扉が開くぜ。";
			link.l1 = "";
			link.l1.go = "guide_townhall";
			locCameraFromToPos(-50.52, 5.79, 38.60, true, -47.65, 3.95, 33.52);
		break;
		
		case "guide_townhall":
			dialog.text = "総督邸。商人や船長たちが重要な用件でここに集まる。\n総督とは良好な関係を保て――彼の一言で、その国の対応が決まるぞ。";
			link.l1 = "";
			link.l1.go = "guide_12";
			locCameraFromToPos(3.14, 7.39, 37.55, true, 1.06, 8.45, 14.14);
		break;
		
		case "guide_12":
			dialog.text = "俺が引き止めてるかい、友よ？";
			link.l1 = "旦那、私は兄を探しに来ました。兄はサン・ピエールにいると聞いています。多少なりとも重要な人物ですから、 総督ならきっとご存じのはずでしょう……";
			link.l1.go = "guide_13";
			SetCameraDialogMode(npchar);
		break;
		
		case "guide_13":
			dialog.text = "ああ、なるほど。我々の総督はジャック・ディエル・デュ・パルケです。きっとすぐにお会いできるでしょう。";
			link.l1 = "他に誰に聞けばいいんだ？いきなり閣下を煩わせたくはないんだが。";
			link.l1.go = "guide_14";
		break;
		
		case "guide_14":
			dialog.text = "もしあなたの兄上がマルティニークで有名なら、町の人々に聞いてみなさい――誰かが知っているはずです。それで、お名前は？";
			link.l1 = "ミシェル・ド・モンペール。";
			link.l1.go = "guide_15";
		break;
		
		case "guide_15":
			dialog.text = "名前は聞いたことがあるが、会ったことはないな。周りに聞いてみるか、いっそ総督のところへ行くといい。幸運を祈る、 旦那。また話そう！";
			link.l1 = "「ありがとう」 "+GetFullName(npchar)+"!";
			link.l1.go = "guide_16";
		break;
		
		case "guide_16":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			LAi_group_MoveCharacter(npchar, "FRANCE_CITIZENS"); // пока идем заниматься Мишелем
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestCheckDelay("NgtF3", 1.0);
			QuestPointerToLoc("FortFrance_town", "reload", "reload3_back");
		break;
		
		case "guide_21":
			dialog.text = "ああ、またお前か！騎士団の要塞に足を踏み入れたと聞いたぜ。どうやら偉い連中と付き合ってるらしいな。 兄貴は見つかったのか？";
			link.l1 = "見つけた……ある意味でな。";
			link.l1.go = "guide_22";
		break;
		
		case "guide_22":
			dialog.text = "お許しください、しかしその答えからはあまり喜びが感じられませんね……";
			link.l1 = "確かに。次の船で故郷へ帰れると期待していたが、運命は俺を嘲笑っている。ここに足止めされて、 いつまでいることになるか分からないし、その上、水夫の仕事まで覚えなきゃならないんだ。";
			link.l1.go = "guide_23";
		break;
		
		case "guide_23":
			dialog.text = "驚きはしませんよ。ユリシーズ号での航海の噂は広まっていますからね。気を落とさないでください――船を所有し、船長の称号を持つことは大したものです。船を購入するつもりなのでしょう？";
			link.l1 = "ああ、くそっ、やるしかない。でも、造船所がどこかも知らねえし、航海の仕方もわからねえし、金の工面もできねえ。 何もわからん！";
			link.l1.go = "guide_24";
		break;
		
		case "guide_24":
			dialog.text = "金はないが、それ以外のことならお任せを。案内の続きをいたしましょうか？";
			link.l1 = "おっしゃる通り――知識は力だ。";
			link.l1.go = "guide_25";
			link.l2 = "ありがとう、旦那、でもここからは自分で何とかします。";
			link.l2.go = "guide_exit_11";
		break;
		
		case "guide_exit_11":
			dialog.text = "お会いできて光栄です。資金のことなら町の有力者に相談するといい――たとえば店の商人などにね\n"+"「幸運を祈る」 "+pchar.name+"――大胆になれば、きっとうまくいくさ。";
			link.l1 = "";
			link.l1.go = "guide_exit_12";			
		break;
		
		case "guide_exit_12":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "guide_25":
			dialog.text = "それじゃあ、俺について来い！まずは船だ。";
			link.l1 = "";
			link.l1.go = "guide_shipyard";
		break;
		
		case "guide_shipyard":
			dialog.text = "造船所。ここで船の購入や修理ができる。主に小型船体だが、たまに良い船も入る。大砲や洒落た帆もあるぞ。";
			link.l1 = "";
			link.l1.go = "guide_port";
			locCameraFromToPos(-23.25, 7.74, 77.79, true, -27.85, 5.36, 73.65);
		break;
		
		case "guide_port":
			dialog.text = "桟橋――海への玄関口だ。船を手に入れれば、ここにお前の船が停泊することになる。\n今のうちに航海士、会計士、砲術士を雇っておけ――海での暮らしがぐっと楽になるぜ。";
			link.l1 = "";
			link.l1.go = "guide_portoffice";
			locCameraFromToPos(-8.55, 4.06, 91.31, true, 40.00, -8.00, 0.00);
		break;
		
		case "guide_portoffice":
			dialog.text = "港役所。ここで船を係留するか、まっとうな仕事――貨物運搬、護衛、郵便配達――を引き受けられる。\n仕事を多くこなせばこなすほど、報酬も良くなるぞ。";
			link.l1 = "";
			link.l1.go = "guide_store";
			locCameraFromToPos(48.38, 9.48, 43.95, true, 43.69, 5.47, 48.13);
		break;
		
		case "guide_store":
			dialog.text = "店だ。船長たちは食料、ラム酒、薬、火薬、弾薬を求めてここに来る。\n何か足りないものがあれば、酒場の密輸業者を探せ。\n優秀な主計長がいなければ、交易は時間と金の無駄になるぜ。";
			link.l1 = "";
			link.l1.go = "guide_gate";
			locCameraFromToPos(-21.10, 6.60, 45.21, true, -30.00, 3.70, 45.00);
		break;
		
		case "guide_gate":
			dialog.text = "荒野への門。危険だが、砦に向かったり、財宝を探したり、別の居住地へ渡るのに役立つ。";
			link.l1 = "";
			link.l1.go = "guide_45";
			locCameraFromToPos(50.58, 5.74, 23.21, true, 100.00, 0.00, 20.00);
			//AddQuestRecordInfo("Guide_OnLand", "1");
		break;
		
		case "guide_45":
			dialog.text = "すべての植民地がよそ者を歓迎するわけじゃねえ。\n夜まで待ちたくねえなら、海で別の旗を掲げて忍び込むか、交易許可証を買うんだな。";
			link.l1 = "";
			link.l1.go = "guide_46";
		break;
		
		case "guide_46":
			dialog.text = "よく聞けよ、相棒。\nちょっと遊ばねえか？門の外で模擬決闘だ。";
			link.l1 = "かしこまりました！完璧ですね。";
			link.l1.go = "guide_47";
			link.l2 = "ありがとうございます、旦那。でもここからは私が引き受けます。";
			link.l2.go = "guide_exit_11";
		break;
		
		case "guide_47": // телепортируем за городские ворота
			DialogExit();
			LAi_SetActorType(npchar);
			DoQuestReloadToLocation("FortFrance_ExitTown", "goto", "goto19", "Guide_ExitTown");
		break;
		
		case "guide_49":
			dialog.text = "旦那、剣術にはお詳しいとお見受けしますが？";
			link.l1 = "はっ！俺はすでに一度白兵戦を生き延びたし、しかも――";
			link.l1.go = "guide_50";
			if (GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) == "unarmed")
			{
				GiveItem2Character(pchar, "blade_05");
				EquipCharacterByItem(Pchar, "blade_05");
			}
		break;
		
		case "guide_50":
			dialog.text = "素晴らしい。参りましょうか？";
			link.l1 = "踊ろうぜ！";
			link.l1.go = "guide_56";
			npchar.quest.guide_win = 0;
		break;
		
		case "guide_56": // махач
			LAi_SetPlayerType(pchar);
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_Delete("EnemyFight");
			if (MOD_SKILL_ENEMY_RATE <= 6)	// На первых трёх сложностях Валинье будет ослаблен
			{
				LAi_SetHP(npchar, LAi_GetCharacterMaxHP(npchar) * 0.7, LAi_GetCharacterMaxHP(npchar) * 0.7);
				npchar.rank = 1;
				SetSelfSkill(npchar, 1, 1, 1, 1, 1);
			}
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			// ставим проверяльщики
			LAi_SetCheckMinHP(pchar, 1, true, "Guide_HeroFail");
			LAi_SetCheckMinHP(npchar, 1, true, "Guide_HeroWin");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			//DoQuestCheckDelay("GuideFight_tutorial", 1.0);
		break;
		
		case "guide_57": // побил гида с первого раза
			dialog.text = "お前……お前は剣の扱いをよく知っている男だな。よくやった、旦那。まだ稽古が必要だが、本物の剣士になる素質はあるぞ。";
			link.l1 = "「メルシー・ボクー。さて、これからどうする？」";
			link.l1.go = "guide_62"; // нода на выход
			if (MOD_SKILL_ENEMY_RATE >= 6)
			{
				link.l2 = "もっと練習しろって？本気かよ？このうんざりする場所に足を踏み入れてから、 ずっとその見下した口調にはうんざりなんだよ！";				//Пасхалка Корсары 2 для сложности СФ и выше
				link.l2.go = "guide_64";
			}
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 80);
		break;
		
		case "guide_58": // побил гида со второго или третьего раза
			dialog.text = "ずっと良くなったじゃないか！ほら、集中すればできるんだ。もっと稽古が必要だな。いつか立派な剣士になれるぜ。";
			link.l1 = "「メルシー・ボクー。さて、これからどうする？」";
			link.l1.go = "guide_62"; // нода на выход
			AddComplexSelfExpToScill(20, 20, 20, 20);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
		break;
		
		case "guide_59": // побили первый раз
			dialog.text = "勝ったぞ、旦那。もっと素早く動いて、俺の突きを捌いてみろ、後ろに跳べ。再戦するか？";
			link.l1 = "ウイ！容赦はしないぜ、旦那！";
			link.l1.go = "guide_56";
			link.l2 = "いや、もうたくさんだ。授業はここまでにしよう。で、これからどうする？";
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_60": // побили второй раз
			dialog.text = "「また俺の勝ちだ」 "+pchar.name+"！主導権を失うな。俺の攻撃を受け止めて、フェイントしろ。強い一撃を繰り出しそうになったら――飛び退くか、受け流せ。ただ防御するだけじゃ駄目だ。もう一度！";
			link.l1 = "来い、旦那、今度こそお前を叩きのめしてやる！";
			link.l1.go = "guide_56";
			link.l2 = "いや、もうたくさんだ。授業はこれで終わりにしよう。さて、これからどうする？";
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_61": // побили третий раз
			dialog.text = "「お前はまだ学ぶことが山ほどあるぜ」 "+pchar.name+"。心配するな、剣術を身につける時間はまだたっぷりあるさ。だが気をつけろ、 武器の扱い方を覚えるまでは無茶はするなよ。";
			link.l1 = "考えておくよ、旦那。でも言わせてもらうが、あんたは運が良すぎたぜ！この忌々しい暑さ……それだけが、俺があんたをぶちのめさなかった理由だ。くそっ、剣術の稽古はここまでにしよう。さて、 これからどうする？";
			link.l1.go = "guide_62"; // нода на выход
		break;
		
		case "guide_62":
			dialog.text = "さて、これでお別れの時です、旦那。お会いできて光栄でした。私の案内や訓練があなたの役に立ち、 今後もお役に立てば幸いです。またいつかお会いできるかもしれませんね。\nさて、必要なお金についてですが――この町の偉い人たちに話をしてみてください。今日案内した場所をすべて回って、 そこの主人たちに話しかけてみましょう。あちこちで聞き込みをしてみてください。 ジャングルや砦にも足を運んでみるといいでしょう。仕事を探すのもよし……まあ、私は神父でも裁判官でもありませんから、人の家を覗いて、 開いている箱に何か面白いものがないか探してみるのも一つの手です。ただし、住人の目を盗んでやるんですよ。 さもないと衛兵に捕まりますからね。\nご武運を。 "+pchar.name+"、あなたの中には本物の偉大さの火花が宿っていると強く感じます。それを大きな炎に育てるために、 全力を尽くしてください！";
			link.l1 = "ありがとうございます、旦那。私の方こそ光栄でした。ご武運を！";
			link.l1.go = "guide_63";
		break;
		
		case "guide_63":
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			DoQuestReloadToLocation("FortFrance_Town", "quest", "quest2", "");
		break;
		
		case "guide_64": // решили убить Валинье
			dialog.text = "黙りなさい、旦那！これ以上の無礼は許しません。しかし、新しい環境への反応も理解できますので、 今回はあなたの無礼を大目に見ましょう。ただし、これからは言葉に気をつけなさい。それでは、ごきげんよう、de Maure様。";
			link.l1 = "気を悪くしないでくれ、ヴァリニー旦那。今ここがルーヴルだったら、そちらこそ言葉遣いに気をつけるはずだ！ 田舎者に最後の教訓を叩き込む時だ。覚悟しろ！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Guide_DlgExit_64");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
