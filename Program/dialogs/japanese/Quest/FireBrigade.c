
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
    string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
// ГРИФФОНДОР -->
		case "FireBrigade_fra":
			dialog.text = GetSexPhrase("","女で…しかも船長だと！これで世の中の全てを見た気がするぜ。お嬢さん、あなたは本当に見事だ。だが、 その美しさがフランス王冠にもたらした悲しみは残念だな\n")+"それがポワンシーの命令の結末さ。ひとりは牢屋行き。もうひとりは――今日、牢に入るか戦で倒れるかだ。";
			link.l1 = "ここは明らかにお前のいる場所じゃねえな。どうしてこんな優秀な士官と立派な船を、 賞金稼ぎの汚れ仕事に使わせるんだ？";
			link.l1.go = "FraOff_1";
		break;

        case "FraOff_1":
			dialog.text = "命令は議論するものじゃねえ、実行するもんだ。もし船長たちが自分勝手に命令の価値を決めてたら、 海軍なんざ成り立たねえだろうが。";
			link.l1 = "そのことをお前の部下たちに伝えろ。";
			link.l1.go = "FraOff_2";
        break;

        case "FraOff_2":
			dialog.text = "俺を追い詰めて、忠誠心と誓いを揺るがそうとしてやがるな。今の状況でそれは卑怯だぜ。\n言葉じゃなく、剣で決着をつけようじゃねえか！";
			link.l1 = "（リーダーシップ）第三の道がある。士官にふさわしくない汚れ仕事はやめろ。俺と一緒に来い――別の世界を見せてやる。";
			link.l1.go = "FraOff_HireCheck";
            link.l2 = "さあ、武器を取れ！";
			link.l2.go = "FraOff_ExitFight";
        break;

        case "FraOff_HireCheck":
            if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 80)
            {
                notification("Skill Check Failed (80)", SKILL_LEADERSHIP);
                dialog.text = "裏切り者はどこでも同じ扱いを受けるんだ。俺はそんな奴にはならねえ。構えろ！";
                link.l1 = "チャンスはあったのに、逃したな。構えろ！";
                link.l1.go = "FraOff_ExitFight";
                break;
            }
            notification("Skill Check Passed", SKILL_LEADERSHIP);
            dialog.text = "俺は王冠に忠誠を誓ったんだぜ、偉そうで堅苦しい官僚どもにじゃねえ。 あいつらは自分の失敗を隠すために俺たちを死地に送りやがる。\nだが、お前は俺の王の敵だ。それだけは見過ごせねえ。";
			link.l1 = "俺は明日にもお前の国への罪を償えるぜ――ただ、しかるべき仲介人に金を払えばな。\nそれは俺のことよりも、お前の上役どもの本性を物語ってるんじゃねえか。";
			link.l1.go = "FraOff_Sucess";
        break;

        case "FraOff_Sucess":
			dialog.text = "確かにそうだ。もう我慢するのはうんざりだぜ。フランス人には手を出さないと約束してくれるなら、 あんたの指揮下で働く用意がある。";
			link.l1 = "誰と出会うことになるかは分からないし、何も保証はできない。だが、俺は分別を持って行動することを約束する。 ようこそ、士官、俺たちの船員へ。 "+NPChar.name+"!"; // своего имени он вообще-то не называл
			link.l1.go = "FraOff_Hired";
        break;

        case "FraOff_ExitFight":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();	
        break;

        case "FraOff_Hired":
            AddBrigadierOfficer(sld, NPChar);
            DialogExit();
        break;

// ЭЛЬ КАСАДОР -->
		case "FireBrigade_spa":
            // to_do: чек нуля?
			dialog.text = "これが指名手配犯の顔か。誇りに思ってるんだろうな、海賊。相当な努力をしたに違いねえ\nカサ・デ・コントラタシオンによれば、お前は倒したそうだ "+(Statistic_AddValue(PChar,"spa_AbordShip",0)+Statistic_AddValue(PChar,"spa_KillShip",0))+" スペイン王冠の旗を掲げた船たちだ。そして今日、俺の美しい船もその仲間入りを果たすぜ"+GetSexPhrase(".","\nスペイン艦隊も災難だぜ！病気にやられ、えこひいきや裏切りもあった……だが、女に負けるなんてな？");
			link.l1 = " お前だけが生き残ってるが、仲間は全員死んじまったんだ。\nそしてお前ももう死んでる――まだ自覚してねえだけだぜ。";
			link.l1.go = "Alonso_1";
			if(Statistic_AddValue(PChar, "spa_AbordShip", 0) + Statistic_AddValue(PChar, "spa_KillShip", 0) < 1)
			{
				Achievment_Set("ach_CL_159")
			}
		break;

		case "Alonso_1":
            dialog.text = "アルバがこの任務を受けられなかったのは残念だ。あいつならもっと上手くやっただろう。だが、 俺も何とかやり遂げてみせるぜ。";
            link.l1 = "お前は故郷の真の息子だ。祖国の英雄たちに会う覚悟をしろ、旦那。";
            link.l1.go = "Alonso_2";
            link.l2 = "狩人が獲物になったんだ。お前の演説なんざ全部無駄だったな――そんなの昔から変わらねえよ。";
            link.l2.go = "Alonso_3";
        break;

        case "Alonso_2":
            ChangeCharacterComplexReputation(PChar, "nobility", 5);
            dialog.text = "一息つかせてくれて感謝するが、これからは俺の剣が語る番だ。";
            link.l1 = "武器を取れ！";
            link.l1.go = "Alonso_ExitFight";
        break;

        case "Alonso_3":
            ChangeCharacterComplexReputation(PChar, "nobility", -5);
            dialog.text = "息抜きはありがとな、だが今度は俺の剣が語る番だぜ。";
            link.l1 = "死ぬ覚悟をしろ！";
            link.l1.go = "Alonso_ExitFight";
        break;

        case "Alonso_ExitFight":
        	SetCharacterPerk(NPChar, "Rush");
            ActivateCharacterPerk(NPChar, "Rush");
            PlaySound("Ambient\Tavern\glotok_001.wav");
            PlaySound("Types\" + LanguageGetLanguage() + "\warrior03.wav");
            SendMessage(NPChar, "lfffsfff", MSG_CHARACTER_VIEWSTRPOS, 0.0, 0.0, 0.1, XI_ConvertString("Rampage"), 255.0, 30.0, 30.0);
            MakeUnpushable(NPChar, true);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;

// ХИМЕРА -->
        case "FireBrigade_eng":
            // to_do: ты-вы у элен
            dialog.text = GetSexPhrase(PChar.Name+"！報告書にあなたの名前があまりにも頻繁に出てくるから、まるで昔から知り合いだったような気がするよ","マッカーサー嬢！あんたの後ろ盾は、あんたが何を企んでるか知ってるのかい？ああ、まあいいさ。 どうせ次はそいつが俺の仕事相手になるんだろうからな。")+"\n運がいいな。俺の上司たちは、前の命令と矛盾する急ぎの指示を出すのが大好きなんだ。 もし俺がアンティグアの古い船員どもを一掃するのに忙しくなけりゃ……まあ、いい。もう十分だ。お前のせいで本当の仕事に集中できねえじゃねえか。";
			link.l1 = "お前も俺の邪魔をしてるんだぜ。";
			link.l1.go = "Cortny_ExitFight";
		break;

        case "Cortny_ExitFight":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle("KnippelAppearance");
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();	
		break;

        case "Kneepel":
            dialog.text = "俺の船尾に鎖弾が飛んできて、危うくやられるところだったわい！わしのこの年寄りの骨がもう少し早けりゃ、 あの野郎を自分で海の悪魔のもとに送ってやったんじゃがな。ありがとうよ、船長。それに、 亡き旦那もきっと感謝しておるぞ！";
			link.l1 = "お前は誰だ？囚人か？俺の船員が解放したのか？";
			link.l1.go = "Kneepel_1";	
		break;

        case "Kneepel_1":
            dialog.text = "チャーリー・ニッペル本人だ。イギリス海軍一の砲術士だぜ！";
			link.l1 = "コートニーがあんたを探し出すのにずいぶん時間がかかったって言ってたぜ。どういう事情なんだ？";
			link.l1.go = "Kneepel_2";	
		break;

        case "Kneepel_2":
            dialog.text = "何年もの間、俺はリチャード・フリートウッドという勇敢なイギリス人船長に仕えていた。 一緒に数多くの戦いをくぐり抜け、本当の情熱――イギリス海軍――に身を捧げてきた。だが、ある日すべてが変わった。\nロンドンのお偉方は俺たちを駒として使った。俺たちは仲間を攻撃し、他人の尻拭いで制服を汚した。 そして今度は俺たちの番だ……";
			link.l1 = "ここでは誰も咎めやしねえよ。人生ってのはややこしいもんだ、特に自分の思い通りに生きられねえ時はな。";
			link.l1.go = "Kneepel_2_good";
            link.l2 = "それで、昔の罪の影がついにお前に追いついたと言えるか？";
			link.l2.go = "Kneepel_2_bad";
		break;

        case "Kneepel_2_good":
            dialog.text = "自分の国に仕えたことは後悔してねえ。ただ……ちょっと辛いんだよ、船長。特に俺の後ろ盾と、その可哀想な奥さんのことを思うとな。";
			link.l1 = "これからどうする？";
			link.l1.go = "Kneepel_3";	
		break;

        case "Kneepel_2_bad":
            TEV.NoKneepel = "";
            dialog.text = "皮肉なんていらねえ……俺たちはもう自分の罪の代償を十分に払ったんだ！";
			link.l1 = "これからどうする？";
			link.l1.go = "Kneepel_3";	
		break;

        case "Kneepel_3":
            dialog.text = "今や俺には名前も故郷もねえ。どこへでも行けるが、今は行くあてもねえんだ。連れもいねえ。 砲手はどこでも必要とされるが、どの船にも大砲があるわけじゃねえ。";
			link.l1 = "俺と一緒に来い。イングランド艦隊とはあまりいい関係じゃなかったが、その中の優秀な奴らには敬意を払ってるぜ。";
            if(!CheckAttribute(&TEV, "NoKneepel"))
                link.l1.go = "Kneepel_3_good";
            else
                link.l1.go = "Kneepel_3_bad";
            link.l2 = "大砲ならあるぜ。本当に腕が立つなら、俺の船にはいつでも本物のプロの居場所があるんだ。";
			link.l2.go = "Kneepel_3_bad";
		break;

        case "Kneepel_3_good":
            dialog.text = "家に帰れば絞首縄が待ってるし、スペイン人もオランダ人も同じだ。フランス人なんぞはごめんだぜ。だが、 あんたには腕のいい砲手が必要みたいだな。乗ったぜ、船長。チャンスがあればすぐ船室に向かう。 たまには顔を出してくれよ、ラムでも飲みながら話そうじゃねえか。\n";
			link.l1 = "乗船を歓迎するぜ。";
			link.l1.go = "Kneepel_Hired";	
		break;

        case "Kneepel_3_bad":
            dialog.text = "ありえねえ。俺はどっかのボロ船でも奪って、この群島の一番深ぇ穴にでも消えちまうさ。助けてくれてありがとな、 船長。じゃあな。";
			link.l1 = "...";
			link.l1.go = "Kneepel_Escape";	
		break;

        case "Kneepel_Escape":
            DeleteAttribute(&TEV, "NoKneepel");
            DeleteAttribute(&TEV, "boardingReloadFreeze");
            NPChar.lifeday = 0;
            LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1.0);
            PostEvent("LAi_event_boarding_EnableReload", 5000);
            DialogExit();
		break;

        case "Kneepel_Hired":
            DeleteAttribute(&TEV, "NoKneepel");
            DeleteAttribute(&TEV, "boardingReloadFreeze");
            NPChar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
            NPChar.Dialog.CurrentNode = "Knippel_officer";
            NPChar.quest.OfficerPrice = sti(PChar.rank)*200; // Артефакт
            NPChar.quest.meeting = true;
            NPChar.OfficerImmortal = true;
            NPChar.Health.HP    = 60.0;
            NPChar.Health.maxHP = 60.0;
            NPChar.OfficerWantToGo.DontGo = true;
            NPChar.loyality = MAX_LOYALITY;
            NPChar.Payment = true;
            NPChar.DontClearDead = true; 
            SaveCurrentNpcQuestDateParam(NPChar, "HiredDate");
            AddPassenger(pchar, NPChar, false);
            SetCharacterRemovable(NPChar, true);
            LAi_SetActorTypeNoGroup(NPChar);
            LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1.0);
            PostEvent("LAi_event_boarding_EnableReload", 5000);
            DialogExit();
		break;

// МЕЙФЕНГ -->
        case "FireBrigade_hol":
			dialog.text = "ここまで来るはずだったのはお前じゃねえ。美鳳は商会の牙、俺の戦隊は復讐の刃だ。それを両方ともぶっ壊したんだ。 そんなこと…ありえねえ。";
			link.l1 = "奴らは俺を獣みたいに追い立てやがった。\nそして俺は――追い詰められた獣のように戦った。\n死ぬか戦うかって時は、頭が冴えるもんだ。\n結局、最後に残る疑問はひとつだけだ。伝説のジーベックの船室まで辿り着けるのか――それとも無理か、だ。";
			link.l1.go = "Longway_1";
		break;

		case "Longway_1":
			dialog.text = GetSexPhrase("","珍しいな――女が指揮を執ってるなんて。そうそうあることじゃねえ。 ")+"俺を待ってたのか？";
			link.l1 = "ああ。梅鳳は歴史ある船だ。俺がオランダ人を出し抜いた時、遅かれ早かれお前が俺を追ってくると分かってた。 立派な最期になるはずだったが……この有様を見てみろよ。";
			link.l1.go = "Longway_2";
		break;

		case "Longway_2":
			dialog.text = "敵を知り、己を知ることこそ勝利の鍵だ。\nさて、お前は自分の意志で選んだな。俺の艦隊と自分の条件で戦うことを。\n死ぬ覚悟もできていた。だが勝ったのはお前だ。\n今や俺の命はお前の手の中だ。\nどうして俺をとどめささねえんだ？";
			link.l1 = "（リーダーシップ）俺はな、ただ会社の野望のためだけに伝説の船長を沈める意味なんて感じねえんだ。 俺もお前と同じ立場だったことがある――ただの駒さ。他人の利益のために働き、他人の命令に従ってきた。俺がかつて自分で選んだものを、お前にも差し出すぜ――自由だ。";
            if (GetSummonSkillFromName(PChar, SKILL_LEADERSHIP) >= 50)
                link.l1.go = "Longway_Success";
            else
                link.l1.go = "Longway_Failed";
            link.l2 = "すべての船長には最後の言葉を言う権利があるからな。覚悟しろ！";
			link.l2.go = "Longway_ExitFight";
		break;

		case "Longway_ExitFight":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
            AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;

		case "Longway_Failed":
            notification("Skill Check Failed (50)", SKILL_LEADERSHIP);
			dialog.text = "自由は与えられるものじゃねえ。自分で奪い取るもんだ。\n選択を語る奴がみんな、それを与えられるわけじゃねえ。\n避けられねえ道もある。やり遂げなきゃならねえ命令もある。\n俺の道はここだ。俺の命令は、最後まで立ち続けることだ。";
			link.l1 = "死を選ぶのか？";
			link.l1.go = "Longway_Failed_over";
		break;

		case "Longway_Failed_over":
			dialog.text = "いや。俺は自分自身でいることを選ぶぜ。";
			link.l1 = "じゃあ、戦おうぜ！";
			link.l1.go = "Longway_ExitFight";
		break;

		case "Longway_Success":
            notification("Skill Check Passed", SKILL_LEADERSHIP);
			dialog.text = "お前はローデンブルクとは違うな。あいつは俺を道具としか見ていなかった。だが、 お前は俺を対等な存在として見ている。自分を犠牲にすることは美徳じゃねえ。お前の条件を聞く準備はできてるぜ。";
			link.l1 = "簡単な話だ。俺の旗艦で航海士になれ。あるいは、望むなら自分の船を持って、俺の旗の下で航海してもいい。 もう会社の後始末をしたり、やつらの秘密を隠したりする必要はねえ。俺は自由だ――その自由をお前にもやるぜ。";
			link.l1.go = "Longway_Success_over";
		break;

		case "Longway_Success_over":
			dialog.text = "俺はいろいろ見てきたぜ。血、金、裏切りってな。会社は金は払うが、敬意は払わねえ。船はくれるが、鎖は外さねえ。 だが……あんたは選択肢をくれる。約束を守ってくれるなら――ロングウェイはもう他人の意志で狩る猟犬じゃなくなる。人間になれる。船長になれる。あるいは――進むべき航路を知る船長の隣に立つこともできるんだ。";
			link.l1 = "クルーへようこそ、Longway航海士。";
			link.l1.go = "Longway_Hired";
		break;

		case "Longway_Hired":
			sld = InitLongwayFP("Longway_FP", NPChar);
			NPChar.lifeday = 0;
			LAi_group_MoveCharacter(NPChar, LAI_GROUP_PLAYER);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);

			AddDialogExitQuest("pchar_back_to_player");
			PostEvent("LAi_event_boarding_EnableReload", 5000);
			DialogExit();
		break;
	}
}

// TO_DO
void AddBrigadierOfficer(ref sld, ref NPChar)
{
    string sTemp = NationShortName(NPChar.nation);
    sld = GetCharacter(NPC_GenerateCharacter("FraBrigadier", NPChar.model, "man", NPChar.model.animation, 30, FRANCE, -1, false, "quest"));
    float num = 1.0;
    switch (MOD_SKILL_ENEMY_RATE)
	{
		case  1: num = 0.5;  break;
		case  2: num = 0.6;  break;
		case  3: num = 0.7;  break;
		case  4: num = 0.8;  break;
		case  5: num = 0.9;  break;
		case  6: num = 1.0;  break;
		case  7: num = 1.1;  break;
		case  8: num = 1.2;  break;
		case  9: num = 1.3;  break;
		case 10: num = 1.5;  break;
	}
    num = stf(NPChar.Rank) / num;
    FantomMakeCoolFighter(sld, MakeInt(num+2), 70, 70, BLADE_LONG, "", "", 100);
    RemoveAllCharacterItems(sld, true);
    GiveItem2Character(sld, NPChar.equip.blade);
    EquipCharacterbyItem(sld, NPChar.equip.blade);
    sTemp = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
    if(sTemp != "")
    {
        GiveItem2Character(sld,   sTemp);
        EquipCharacterbyItem(sld, sTemp);
        sTemp = LAi_GetCharacterBulletType(NPChar, GUN_ITEM_TYPE);
        LAi_SetCharacterBulletType(sld, sTemp);
        LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, sTemp);
        sTemp = LAi_GetCharacterGunpowderType(NPChar, GUN_ITEM_TYPE);
        if(sTemp != "") AddItems(sld, sTemp, 30 + rand(20));
    }
    sld.name = NPChar.name;
    sld.lastname = NPChar.lastname;
    sld.greeting = "officer_hire";
    sld.Dialog.Filename = "Enc_Officer_dialog.c";
    sld.quest.meeting = true;
    sld.quest.OfficerPrice = sti(PChar.rank)*200; // Артефакт
    Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
    sld.OfficerImmortal = true;
    sld.Health.HP    = 60.0;
    sld.Health.maxHP = 60.0;
    sld.OfficerWantToGo.DontGo = true;
    sld.loyality = MAX_LOYALITY;
    AddDialogExitQuest("pchar_back_to_player");
    AddDialogExitQuestFunction("LandEnc_OfficerHired");
    NPChar.lifeday = 0;
    LAi_SetActorType(NPChar);
    LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
    PostEvent("LAi_event_boarding_EnableReload", 5000);
}
