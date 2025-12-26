// Джон Мердок, он же Йохан ван Мерден, соратник Роденбурга
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	int iTemp;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
		if (!CheckAttribute(pchar, "questTemp.HWIC.Self") && LAi_grp_playeralarm > 0)
		{
			dialog.text = "旦那、こんな時に世間話とはとんでもなく間が悪いぜ。駐屯兵全員がお前を探してるんだ。 さっさとずらかった方がいいぞ…";
			link.l1 = "心配しないでくれ。長居はしないさ。";
			link.l1.go = "exit";
			break;
		}
		// продажа алхимического набора, если провалил гамбит
		if (CheckAttribute(pchar, "questTemp.HWIC.Detector") && !CheckAttribute(npchar, "quest.alchemy"))
		{
			bOk = (findsubstr(pchar.questTemp.HWIC.Detector, "_fail" , 0) != -1) || (pchar.questTemp.HWIC.Detector == "eng_win_half");
			if (bOk)
			{
				dialog.text = "ようこそ、船長。興味深い提案にご関心はありませんか？ ";
				link.l1 = "この辺りの連中はみんなそんな話を持ちかけてくるみたいだし、私は好奇心が強いんだ。何の話だ？ ";
				link.l1.go = "alchemy";
				break;
			}
		}
		// Страж Истины
		if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok1")
		{
			dialog.text = "ごきげんよう。私の薬局へようこそ。ほとんどの病気や体調不良に効く薬を取り揃えております。何をお求めですか？";
			link.l1 = "聞いてくれ、ジョン、お前の家の二階に誰か住んでるって噂があるんだが……";
			link.l1.go = "guardoftruth";
			break;
		}
//-----------------------------------------за Голландию------------------------------------------------
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.location.from_sea == "SentJons_town" && pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "ごきげんよう。私の薬局にお越しいただき嬉しく思います。ほとんどの病気や不調に効く薬を取り揃えております。 何をお求めでしょうか？";
				link.l1 = "こんにちは、マードックさん。私はルーカス・ローデンブルクの代理で参りました。 リチャード・フリートウッドに関する件について話し合うために、あなたのもとへ送られてきたのです。";
				link.l1.go = "Knippel_exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "こんにちは。どんなお悩みですか？咳止めの薬も下痢止めの粉もありますよ！";
				link.l1 = "こんにちは、マードックさん。私はルーカス・ローデンブルクの代理で参りました。 リチャード・フリートウッドに関する件で、あなたと話をするようにと彼に言われました。";
				link.l1.go = "Knippel";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "KillMerdok")
			{
				dialog.text = "ああ、ローデンブルクの雇われ犬が来やがったな……エルキュール、ロンウェイ、ちょっと出てきてくれ。\nこいつを殺せ！";
				link.l1 = "待ってくれ、処方箋があるんだ！";
				link.l1.go = "Merdok_fight";
				break;
			}
			dialog.text = "こんにちは。私の薬局へようこそ、お会いできて嬉しいです。ほとんどの病気や不調に効く薬を取り揃えております。 何をお求めですか？";
			link.l1 = "今のところ何もありません、ありがとう。私はとても元気です。";
			link.l1.go = "exit";
			break;
		}
//----------------------------------------------за Англию---------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "MerdokMeeteng")
			{
			dialog.text = "やあ、招かれざる客だな。仮面で顔を隠してもいないし、強盗にも見えない。ということは、 貧乏な薬屋の俺に他の用があるんだろう。もしかして下痢止めでも欲しいのか？";
			link.l1 = "やあ、ヨハン・ファン・メルデン。エルキュール・トンザグからの挨拶を持ってきたぜ。名前を知ってるようだな。";
			link.l1.go = "Merdok_talk";
			DelLandQuestMark(npchar);
			break;
			}
//--------------------------------------------против всех--------------------------------------------------
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "HuntFleetwood")
				{
					dialog.text = "ああ、ここにいたのか。さて、エルキュールにはもう会ったか？ ";
					link.l1 = "ああ。話はまとまった。ジョン、俺はエルキュールを助けるつもりだ。 それとリチャード・フリートウッドについて君にいくつか質問がある。";
					link.l1.go = "About_Fleetwood";
					break;
				}
				if (GetQuestPastDayParam("questTemp.Wait_Fleetwood") > 6 && pchar.questTemp.HWIC.Self == "WaitFleetwood")
				{
					dialog.text = "こんにちは！お会いできて嬉しいです、 "+pchar.name+"!";
					link.l1 = "やあ、ジョン。フリートウッドについて何か分かったか？";
					link.l1.go = "About_Fleetwood_9";
					pchar.quest.Wait_FleetwoodOver.over = "yes"; //снять таймер
					break;
				}
				if (pchar.questTemp.HWIC.Self == "HWICSelf_fail")
				{
					dialog.text = "遅かったな。鳥はもう巣立ったぜ。チャーリー・クニッペルがウィレムスタッドを訪れて、 リチャードのためにあそこから女を連れてきた。今ごろ、あいつらは軍艦隊と一緒に一、 二日中にイングランドへ向けて出航するさ。フリートウッドはもういねえ、この世で二度と会うことはねえよ。";
					link.l1 = "くそっ。リチャードのことをすっかり忘れて時間を忘れてしまった。じゃあな。";
					link.l1.go = "About_Fleetwood_17";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileOnShip")
				{
					dialog.text = "「お帰りなさい。」 "+pchar.name+"！今はあんたに頼むことはねえ。フリートウッドの情報もねえし、 チャーリー・クニッペルもまだキュラソーから戻ってきてねえんだ……";
					link.l1 = "奴は絶対に戻らないさ。奴も、奴のブリガンティンもな。";
					link.l1.go = "Abigile";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInHouse")
				{
					dialog.text = "おや、お客さんだな！やあ、チャーリー！こんにちは、お嬢さん！";
					link.l1 = "こんにちは、ジョン！私の女性の同行者であり、 リチャードの婚約者である魅力的なアビゲイル・シュヌールを紹介させてください。";
					link.l1.go = "Abigile_7_1";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInRoom")
				{
					dialog.text = "声を潜めろ……次はどうするつもりだ？";
					link.l1 = "次か？本当は少し眠りたいが、残念ながらそんな暇はない。これからフリートウッドを隠れ家から引きずり出して、 エルキュールの仕事を片付けるつもりだ。";
					link.l1.go = "Abigile_9";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "LetterToFleetwood")
				{
					dialog.text = "書き終わったのか？見せてみろ……なんてこった、チャーリー、お前は本物の狂人だな！ちょっと細かく書きすぎじゃないか？ シュヌール嬢の指とか耳とか顔のくだりとかさ？お前、間違いなく異常な才能があるぜ。くそっ、吐きそうだ！";
					link.l1 = "俺はハッタリだよ、ジョン。あの娘を殺す気はねえ。指一本くらいはもぎ取ってやれるが……それ以上はしねえさ。どうせあと九本残ってるんだしな。";
					link.l1.go = "Abigile_15";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "FleetwoodAgree")
				{
					dialog.text = "うまくいったのか？目を見ればわかる――やったんだな！";
					link.l1 = "ああ。フリートウッドは俺の条件を飲んだ。罠の顎が閉じつつある。あとは待つだけだ。";
					link.l1.go = "Abigile_23";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "FleetwoodDied")
				{
					dialog.text = "ああ、おかえり、友よ！何か話せることはあるか？";
					link.l1 = "フリートウッドは死んだ。すべて計画通りに進んだ。俺が浜辺に待ち伏せを仕掛けておいた島に奴はやって来た。 奴もなかなか手強かったが、結局は無駄だった。あの浜辺を生きて去ったのは俺だけだ。";
					link.l1.go = "Abigile_27";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "MeetTonzag")
				{
					dialog.text = "Alright "+pchar.name+"、あなたに重大な提案がある。これから話すことは非常に危険だが、フリートウッドを片付けた手際を見れば、 君ならやれると確信している。君には…難題を解決する稀有な才能があるようだ。";
					link.l1 = "光栄だよ。もっと話してくれ。";
					link.l1.go = "Lucas";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SeekAbiIsland")
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					dialog.text = "「お帰りなさい。」 "+pchar.name+"！俺にいい知らせはあるか？";
					link.l1 = "ジョン、これからは枕の下にナイフを隠して寝なくてもいいぞ。ルーカスはもうお前の脅威じゃない。 あいつは逮捕されて牢に入れられたし、近いうちにオランダへ送られて、反乱や殺人未遂、 その他の悪事で裁かれることになる。";
					link.l1.go = "Lucas_10";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "VanbergDestroyed")
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("SentJons");
					dialog.text = "お会いできて嬉しいです "+pchar.name+"！生きてたのか――それは良かったぜ。何か新しい情報はあるか？";
					link.l1 = "ああ。ヴァン・ベルクはもう戻ってこない。おっしゃった通り、奴は俺を追い詰めて、一番厄介な時に襲いかかってきた。 ヴァン・ベルクは手強い相手だったが、最後には俺が奴を叩きのめした。";
					link.l1.go = "Final";
					break;
				}
			dialog.text = "他に何かご用ですか？";
			link.l1 = "いいや、ジョン、何もない。俺は行くぞ。";
			link.l1.go = "exit";
			break;
			}
			dialog.text = "こんにちは。私の薬屋にお越しいただき嬉しいです。ほとんどの病気や不調に効く薬を取り揃えております。 何をお求めですか？";
			link.l1 = "今のところ何もありません、ありがとう。私はとても元気です。";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

//--------------------------------------------за Голландию-----------------------------------------------------
		case "Knippel_exit":
			dialog.text = "何のことをおっしゃっているのか、私には全く分かりません、旦那。ルーカス・ローデンブルクとは誰です？ 私はオランダ人とは一切関わりがありません。何かの間違いでしょう。";
			link.l1 = "「何だと？ローデンブルク旦那が俺をお前のところに寄越したんだぞ！」";
			link.l1.go = "Knippel_exit_1";
		break;
		
		case "Knippel_exit_1":
			dialog.text = "もう一度言わせてもらうが、マインヘール・ローデンブルクという男は知らん。オランダ人についても、 俺は関わりたくない。この世で我慢ならんものが二つある――他人の文化を受け入れられない奴と、オランダ人だ。だから薬がいらねえなら、俺の仕事の邪魔をしないでくれ。";
			link.l1 = "ますます奇妙だな……";
			link.l1.go = "exit";
		break;

		case "Knippel":
			dialog.text = "ほうほう……お前はローデンブルク旦那のところから来たのか？よし、話を聞こう。";
			link.l1 = "フリートウッド船長と人目につかない場所で会う段取りをつける必要がある。\nフリートウッド旦那がぜひとも捕まえたがっているオランダ私掠船長、ヤコブ・ファン・ベルグから『ミラージュ』 号を借りたんだ。\n近いうちに『ミラージュ』号がドミニカ沖に都合よく停泊していると、彼に知らせておきたい。 ";
			link.l1.go = "Knippel_1";
		break;
		
		case "Knippel_1":
			dialog.text = "ジェイコブが自分の船を譲ったのか？ふむ、つまり今は誰かにフリートウッド旦那へ「ミラージュ号」 がまもなくドミニカ沖に現れると伝えてほしいんだな。特別な理由でリチャード本人には言えないからってわけか……";
			link.l1 = "その通りです。ローデンブルク旦那がこの件はあなたに相談するよう勧めてくれました。";
			link.l1.go = "Knippel_2";
		break;
		
		case "Knippel_2":
			dialog.text = "この場合、必要なのはチャーリー・クニッペルだ。フリートウッドの忠実な友人……そして彼のスパイでもある。彼と話し、リチャードに伝えたいことは何でも言うといい。ただし気をつけろ、 クニッペルは一見単純そうに見えるが、決して馬鹿じゃない。\n彼は海岸からそう遠くない小屋にいるはずだ。そこにいるだろう。";
			link.l1 = "なるほど。ありがとうございます、マードックさん。では、ごきげんよう！";
			link.l1.go = "Knippel_3";
		break;
		
		case "Knippel_3":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "toKnippel";
			AddQuestRecord("Holl_Gambit", "1-16");
			AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
		break;
		
		case "Merdok_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			sld = characterFromId("Tonzag");
			PlaySound("Voice\English\hambit\Ercule Tongzag-04.wav");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			//а вот и китаец нарисовался
			sld = characterFromId("Longway");
			LAi_SetWarriorType(sld);
			FantomMakeCoolFighter(sld, 18, 40, 40, "blade_08", "pistol1", "bullet", 70);
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayEnemy"))//враг
			{
				ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
				LAi_group_MoveCharacter(sld, "EnemyFight");
				PlaySound("Voice\English\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayFriend"))//друг
			{
				LAi_warrior_DialogEnable(sld, true);
				sld.Dialog.Filename = "Quest\HollandGambit\Longway.c";
				sld.dialog.currentnode = "Longway_hire";
				ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				PlaySound("Voice\English\hambit\Longway-02.wav");
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LongwayNeutral")) sld.lifeday = 0;//нейтрал - просто нет
            LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattle");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//-------------------------------------------------за Англию-----------------------------------------------------
		case "Merdok_talk":
			dialog.text = "本当か？あの哀れなガストンはとっくに地獄で焼かれていると思っていたぜ。";
			link.l1 = "そうかもしれねえが、ガストンみたいな奴は他にいねえよ。 あいつの首を秘密の島のユダヤ人の古い財宝の中で見つけたんだ。でも、それでもお前に挨拶を送ってきやがった。 それに、俺たちには共通の敵――ローデンブルク旦那がいるとも言ってたぜ。トンザグは、 お前がルーカスにとって重要な書類を持ってるかもしれねえって言ってた。 その書類であいつをキュラソーの隠れ家からおびき出せるかもしれねえってな。";
			link.l1.go = "Merdok_talk_1";			
		break;
		
		case "Merdok_talk_1":
			dialog.text = "彼の言う通りだ。ローデンブルクが眠れぬ夜を過ごしているのは、私の保管しているこの記録のせいだ。 どうやら彼がまだここに居座っているのも、それが理由らしい。実は、 彼は本国の連合州にある会社の取締役委員会で楽な職を約束されていたんだ。 この記録にはルーカスの過去と現在についての興味深い情報が多く含まれていて、それが世間に広まれば、 彼の出世の望みは完全に潰えるだろう。その場合、せめて絞首刑ではなく斬首で済むことを願うしかないな。\n";
			link.l1 = "記録を渡せ、俺が敵の始末をつけてやる。";
			link.l1.go = "Merdok_talk_2";			
		break;
		
		case "Merdok_talk_2":
			dialog.text = "俺のことをバカだと思ってるんだろう。俺がまだ生きてるのは、まだそれを持ってるからだ。 お前が今ルーカスの手先じゃないって、どうやって信じろってんだ？";
			link.l1 = "俺の言葉を信じるしかねえ――さもなくば死ぬだけだ。";
			link.l1.go = "Merdok_talk_3";			
		break;
		
		case "Merdok_talk_3":
			PlaySound("Voice\English\hambit\John Mardock-07.wav");
			dialog.text = "答えを間違えたな、ここで死んでもらうぜ！ロンウェイ、攻撃だ！";
			link.l1 = "おおっと、中国野郎が影から出てきやがったな！心配すんな、二人まとめて俺がチョップスイにしてやるぜ！";
			link.l1.go = "Merdok_fightEng";			
		break;
		
		case "Merdok_fightEng":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешим драться
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");	
			sld = characterFromId("Longway");
			FantomMakeCoolFighter(sld, 20, 50, 50, "blade_08", "pistol1", "bullet", 80);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "SentJons_TownCave", "monsters", "monster8");
			PlaySound("Voice\English\hambit\Longway-02.wav");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "Merdok_AfterBattleEng");
            DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
//----------------------------------------против всех-------------------------------------------------------
		case "MC_InHouse":
			PlaySound("Voice\English\hambit\John Mardock-02.wav");
			dialog.text = "やっと目を覚ましたな。もうこのまま起きないんじゃないかと心配してたぜ。";
			link.l1 = "「……何だ？お前は誰だ？ここは一体どこだ？どうやってここに来たんだ？」";
			link.l1.go = "MC_InHouse_1";	
		break;
		
		case "MC_InHouse_1":
			dialog.text = "落ち着いて、一度にそんなに質問しないでくれ、興奮しすぎるのは体によくないぞ。俺の名前はジョン・マードック、 ここセント・ジョンズの薬剤師だ。お前はフリートウッドの手下どもとの喧嘩で気を失ったんだ。正直、 あいつらにかなりやられたな……ここにお前を運んできたのはエルキュールだ。そして、まあ、俺の薬や治療でお前の傷の手当ては済ませておいたぞ。";
			link.l1 = "エルキュール？誰だ？通りで俺を助けてくれたあの男か？ ";
			link.l1.go = "MC_InHouse_2";			
		break;
		
		case "MC_InHouse_2":
			dialog.text = "ああ、そいつだ。ところで、あいつがお前と話したがってる。町で会う必要があるぞ。まだ歩けるか？よし。 夜になったら出発しろ――俺の家の一階の扉の裏から始まる秘密の抜け道を使え。暗くなるまで絶対に外に出るな――フリートウッドの手下どもがお前を探してるからな。";
			link.l1 = "ああ…俺の船はどこだ？";
			link.l1.go = "MC_InHouse_3";			
		break;
		
		case "MC_InHouse_3":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "あなたの船は差し押さえられ、乗組員たちはフリートウッドの部下に殺されるのを恐れて散り散りになった。申し訳ない。 ";
				link.l1 = "くそっ……";
			}
			else
			{
				dialog.text = "彼女は港にいる、いつもの場所だ。";
				link.l1 = "ふう……それを聞いて安心した。彼女を失ったかと思ったよ。";
			}
			link.l1.go = "MC_InHouse_4";			
		break;
		
		case "MC_InHouse_4":
			dialog.text = "エルキュールに会うべきだ。秘密の抜け道を通って夜に街へ行け。向こうから声をかけてくるはずだ。\n今は休むといい、俺は仕事に戻らねばならん。";
			link.l1 = "わかった、ジョン。それから……助けてくれて、治療までしてくれてありがとう！";
			link.l1.go = "MC_InHouse_5";
		break;
		
		case "MC_InHouse_5":
			NextDiag.CurrentNode = "First time";
			DialogExit();
			npchar.greeting = "merdok_2";
			AddQuestRecord("Holl_Gambit", "3-12");
			pchar.questTemp.HWIC.Self = "MainBegin";//новый флаг квеста
			sld = characterFromId("Bridgetown_tavernkeeper");
			sld.model = "barmen_3";
			sld.greeting = "barmen_1";
			sld.name = "Harry";
			sld.lastname = "Fletcher";//перерисуем бармена Бриджтауна
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", true);//закрыть выход из аптеки через дверь
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);//открыть подземелье из дома
			LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false);//открыть дом из подземелья
			pchar.quest.Tonzag_Meeting.win_condition.l1 = "location";
			pchar.quest.Tonzag_Meeting.win_condition.l1.location = "SentJons_town";
			pchar.quest.Tonzag_Meeting.win_condition.l2 = "Night";
			pchar.quest.Tonzag_Meeting.function = "TonzagMeeting";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);	
		break;
		
		case "About_Fleetwood":
			DelLandQuestMark(npchar);
			dialog.text = "フリートウッドのことか？あいつについて何を知りたいんだ？";
			link.l1 = "すべてだ。知っていることを全部話せ。エルキュールがなぜアンティグアに来たのか、お前には隠し事じゃないはずだ。 俺はあいつの味方だ。";
			link.l1.go = "About_Fleetwood_1";
		break;
		
		case "About_Fleetwood_1":
			dialog.text = "よろしい。王立…いや、コモンウェルス海軍のリチャード・フリートウッド船長だ…くそっ、あの狂信者クロムウェルが権力を握って名前を変えたことを、つい忘れてしまう。まあ、それはともかく、 フリートウッドは腕の立つ戦士で、経験豊富な船乗りだ。彼は『ヴァルキリー』というブリッグを指揮している――これがまた素晴らしい船で、精鋭の水兵と海兵隊を乗せている。彼は連合州全体、 特にオランダ西インド会社に対して私的な戦争を仕掛けている。数え切れないほどのオランダ商船を襲い、 保険料を天井知らずに跳ね上げた。キュラソーの総督は彼の首に史上最高額の賞金をかけている。";
			link.l1 = "ふむ……「コモンウェルス海軍」の士官が海賊になるなんて、ちょっと珍しいな……";
			link.l1.go = "About_Fleetwood_2";
		break;
		
		case "About_Fleetwood_2":
			dialog.text = "ああ、その通りだ。彼はまさに綱渡りをしている。イギリスは公式には彼の行動を認めず、関わることも拒否しているが、 実際には裏で彼を後押ししているんだ。私には、 彼がカリブのイギリス諜報組織と何らかの形で繋がっていると考える理由があるし、あの連中は決して侮れないぞ\n";
			link.l1 = "真面目な男か……これだけか？エルキュールが自分の助手の一人について話していたな……もう一人のチャーリー……なんて名前だったか……キャニスター？キャノンボール？";
			link.l1.go = "About_Fleetwood_3";
		break;
		
		case "About_Fleetwood_3":
			dialog.text = "「クニッペル？ああ、そんな奴がいる。チャーリー・クニッペルは元々イギリス海軍の砲術長だったが、 今は引退している。今は陸で静かな生活を送っているが、セント・ジョンズではフリートウッドの目と耳だ。だから、 あいつには気をつけろ。それに、リチャードのことを問いただそうなんて思うな――下手すりゃ牢屋行きか、それ以上の目に遭うぞ。」";
			link.l1 = "なるほど。他にフリートウッドについて特筆すべきことがあれば教えてくれないか？";
			link.l1.go = "About_Fleetwood_4";
		break;
		
		case "About_Fleetwood_4":
			dialog.text = "アンティグアの十六歳から六十歳まで、すべての女の憧れの的だった男さ。それ以上言うことはないだろう。まあ、 今どうなったかは知ってるだろう。今じゃベッドに寝たきりで、傷を舐めてるだけさ。";
			link.l1 = "奴にも何か弱点や悪癖があるはずだ…";
			link.l1.go = "About_Fleetwood_5";
		break;
		
		case "About_Fleetwood_5":
			dialog.text = "どういう意味だ？";
			link.l1 = "まあ、もしかしたら賭け事が好きだったり、大酒飲みだったり、女に目がないとか――そんな感じかもな。結婚してるのか？";
			link.l1.go = "About_Fleetwood_6";
		break;
		
		case "About_Fleetwood_6":
			dialog.text = "いいえ、独身です。あなたが挙げたことについては――彼にそういう評判はありません。";
			link.l1 = "なるほど。しかし、彼にもまだ何か特別なところがあるのでは？あんな奴でも弱点くらいあるはずだ！";
			link.l1.go = "About_Fleetwood_7";
		break;
		
		case "About_Fleetwood_7":
			dialog.text = "わからないな。いいか、こうしよう。1週間後に私のところへ来てくれ、その間にフリートウッドの私生活を調べておくよ。どうだ？";
			link.l1 = "取引成立だ。ありがとう、ジョン！一週間後にここに来るよ。";
			link.l1.go = "About_Fleetwood_8";
		break;
		
		case "About_Fleetwood_8":
			DialogExit();
			pchar.questTemp.HWIC.Self = "WaitFleetwood";
			SaveCurrentQuestDateParam("questTemp.Wait_Fleetwood");
			SetFunctionTimerCondition("Wait_FleetwoodQM", 0, 0, 7, false);
			SetFunctionTimerCondition("Wait_FleetwoodOver", 0, 0, 12, false);//чтобы не опаздывал
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload1", false);//открыть выход из аптеки
			AddQuestRecord("Holl_Gambit", "3-14");
		break;
		
		case "About_Fleetwood_9":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "はい、しかし残念ながらあまり知りません。それに、役に立つかどうかも怪しいです。";
			link.l1 = "吐けよ！フリートウッドに関係あるなら、どんな些細なことでも大事なんだ。";
			link.l1.go = "About_Fleetwood_10";
		break;
		
		case "About_Fleetwood_10":
			dialog.text = "少し前、リチャードは正体不明の島からユダヤ人の難民二人――老人とその娘――を拾い上げ、ウィレムスタッドへ向かわせた。彼らが乗っていた船は海賊に沈められたのだ。 フリートウッドは自分の身を危険にさらしながら、こっそり彼らをキュラソーへ連れてきた。\nそれから数ヶ月が経った。今、彼は忠実なる犬、チャーリー・クニッペルをウィレムスタッドへ送り出している……";
			link.l1 = "ふむ……どう繋がっているんだ？";
			link.l1.go = "About_Fleetwood_11";
		break;
		
		case "About_Fleetwood_11":
			dialog.text = "チャーリーがウィレムスタッドからアビゲイル・シュヌールというユダヤ人の娘をここに連れてくるよう命令を受けたこと を突き止めた。そう、あの島の娘だ。どうやらリチャードは彼女に惚れているらしく、 彼女のために一番の手下を送っているらしい。\nそれだけだ。役に立つかどうかは分からない。";
			link.l1 = "おほほほ！ははは！どうやら我らが独身貴族殿が、あのユダヤ女の狡猾な魅力にやられたようだな。 これは素晴らしい働きだ、ジョン、感謝する！さて、我らの友人キニッペルはいつキュラソーへ発つのだ？\n";
			link.l1.go = "About_Fleetwood_12";
		break;
		
		case "About_Fleetwood_12":
			dialog.text = "彼は昨日出発した。";
			link.l1 = "「それで、どの船だ？」";
			link.l1.go = "About_Fleetwood_13";
		break;
		
		case "About_Fleetwood_13":
			dialog.text = "そう聞かれると思ってたぜ。あいつはコモンウェルスが雇ったブリガンティンに乗ってる――いや、もう面倒だ、『ロイヤル・ネイビー』ってやつさ。船の名前は『ジーカルフ』だ。";
			link.l1 = "「ジーカルフ」？それはイングランドの船にしてはずいぶんオランダ風の名前だな……ああ、なるほど。";
			link.l1.go = "About_Fleetwood_14";
		break;
		
		case "About_Fleetwood_14":
			dialog.text = "あんたは頭の回転が速いな……元の名は「ロイヤル・メアリー」だったが、今回の航海では「ゼーカルフ」と名付けられている。 今はオランダの旗を掲げているんだ。";
			link.l1 = "君の助けは本当に貴重だった、ジョン。\nこれから出発する。すぐ戻るつもりだし、療養中に泊めてもらった二階の部屋をまた使わせてもらうぞ。";
			link.l1.go = "About_Fleetwood_15";
		break;
		
		case "About_Fleetwood_15":
			dialog.text = "何をしているんだ？";
			link.l1 = "戻ったら全部話すよ。幸運を祈ってくれ、ジョン！じゃあな。";
			link.l1.go = "About_Fleetwood_16";
		break;
		
		case "About_Fleetwood_16":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-16");
			pchar.questTemp.HWIC.Self = "HuntKnippel";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("HuntKnippelOver", 0, 0, 10, false);
			pchar.quest.Hunt_Knippel.win_condition.l1 = "location";
			pchar.quest.Hunt_Knippel.win_condition.l1.location = "Curacao";
			pchar.quest.Hunt_Knippel.function = "CreateKnippelShip";
			LocatorReloadEnterDisable("SentJons_town", "houseH1", true);//закрыть хижину Чарли
			AddMapQuestMarkIsland("Curacao", true);
		break;
		
		case "About_Fleetwood_17":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-15");
			pchar.questTemp.HWIC.Self = "end";
			pchar.questTemp.HWIC.Detector = "self_fail";
			CloseQuestHeader("Holl_Gambit");
		break;
		
		case "Abigile":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "本当か？なんでそんなに自信があるんだ？";
			link.l1 = "チャーリーは今ごろ海底で魚の餌になってるからだ。俺は「ジーカルフ号」に乗り込み、 クニッペルを地獄に送ってやった。もちろん、その前にしっかり尋問したぜ……奴は手紙を持っていてな、それを使って勇敢なリチャードの恋人である我らがユダヤ娘アビゲイルに、 クニッペルになりすまして接触できたんだ。";
			link.l1.go = "Abigile_1";
		break;
		
		case "Abigile_1":
			dialog.text = "ふむ……それは賢いな。つまり、君が言いたいのは……";
			link.l1 = "ああ。ユダヤ人の娘をアンティグアに連れてきた。彼女は俺の船に乗っている。 これでフリートウッドとの駆け引きで切り札を手に入れたぜ！あいつは彼女のためなら何でもするだろう…";
			link.l1.go = "Abigile_2";
		break;
		
		case "Abigile_2":
			dialog.text = "本当にそう思うのか？お前が言うほど単純な話じゃないかもしれねえぞ……";
			link.l1 = "ああ、間違いなくそうだよ。手紙から分かったのは、 アビゲイルの父親が金のことでリチャードとの結婚に反対していたってことさ。分かるだろ、 典型的なユダヤ人の義父ってやつだ。それでフリートウッドは、 彼女の父親に持参金として二十万ペソ払うことにしたんだ！\nさて、教えてくれよ、世界中にそんな大金の価値がある娘が何人いると思う？";
			link.l1.go = "Abigile_3";
		break;
		
		case "Abigile_3":
			dialog.text = "へっ！ユダヤ女じゃねえことは確かだな！俺の人生でそんな価値のあるキリスト教の娘には一度も会ったことがねえよ、 間違いなくな。 "+pchar.name+"、お前はずる賢い悪党だな。彼女をどうするつもりだ？";
			link.l1 = "ユダヤ人の娘をここに連れてきて、あなたの部屋に泊めることにする。 リチャードは海に出てまだ戻っていないと彼女に伝えるから、彼女は一週間ほど我々の客人ということになる。 彼女は私のことをチャーリー・クニッペルだと思っているんだ。";
			link.l1.go = "Abigile_4";
		break;
		
		case "Abigile_4":
			dialog.text = "それは面白いな。つまり、あの娘を俺の家に置いておくことにしたのか？ふむ……";
			link.l1 = "ジョン、あの女はユダヤ人だ。オランダ領から連れてこられた無国籍の流れ者だよ。 ここセント・ジョンズでは誰でもないし、誰も彼女のことを知らない。安心しろ、俺たちは好きなようにできるし、 あいつは一言も口にできやしない。金もなければ、友達もいないんだ。それに、どうせ長く客人でいるわけじゃない。 あいつを餌にしてフリートウッドをおびき出すつもりだ。その後は、もう彼女は必要ないさ。";
			link.l1.go = "Abigile_5";
		break;
		
		case "Abigile_5":
			dialog.text = "シャルル、君はちょっと怖くなってきたよ。この娘を利用するつもりじゃないだろうな？それとも、 クニッペルと同じ運命を辿らせる気か？";
			link.l1 = "いや、もちろんそんなことはないさ。俺は「ずる賢い悪党」かもしれねえが、美人の娘――ユダヤ人でもキリスト教徒でも――の敵じゃねえ。ついでに言えば、ブスだって敵じゃねえよ。あの娘が大人しくしてりゃ、 この騒ぎが終わったらウィレムスタッドの親父の元に連れてってやるさ。あのケチな爺さん、 きっと俺の足元にひれ伏して、あの裏切り者のイギリス野郎から娘を救ったことに感謝するだろうぜ。";
			link.l1.go = "Abigile_6";
			// belamour legendary edition -->
			link.l2 = "この茶番にはあいつにも役割がある。芝居が終われば、もうあいつに用はない。";
			link.l2.go = "Abigile_6a";
		break;
		
		case "Abigile_6a":
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Sneak", 60);
			dialog.text = "なるほど、つまり今は俺が彼女の面倒を見るってことか。";
			link.l1 = "無理強いはしねえよ、相棒。お前がどうしても嫌だってんなら、あの娘は俺の船に置いといてもいいぜ。ただし、 安全のために足枷をつけて、船倉のネズミどもと一緒に閉じ込めることになるがな。女が船にいるなんて、 あいつらには珍しいことだからよ。こんな可愛い娘をそんなふうに扱うのは、もったいねえ話だぜ。";
			link.l1.go = "Abigile_7";
		break;
		
		case "Abigile_6":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 60);
			// <-- legendary edition
			dialog.text = "なるほど、つまり今のところ俺が彼女の面倒を見なきゃならないってことか。";
			link.l1 = "無理強いはしねえよ、相棒。お前がどうしても嫌だってんなら、あの娘は俺の船に残してもいいぜ。だがその場合、 安全のために足枷をはめて、船倉のネズミどもと一緒に閉じ込めるしかねえ。うちの連中にとっちゃ、 女が船にいるなんて珍しいことだからな。あんな可愛い娘をそんな風に扱うのは、もったいねえ話だがな。";
			link.l1.go = "Abigile_7";
		break;
		
		case "Abigile_7":
			dialog.text = "承知した。よろしい、彼女をここに連れてきなさい。フリートウッドとの戦いであなたを助けるのが私の務めだ。 彼女をここに連れてきてくれれば、「客間」の準備をしよう。";
			link.l1 = "ありがとう、John。君なら頼りになると分かっていたよ。";
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Self = "AbigileInCabin";
			DoQuestCheckDelay("SetAbigileToCabin", 1.0); // fix 180812
			AddQuestRecord("Holl_Gambit", "3-24");
			//поставим табурет
			sld = ItemsFromID("lcheer");
			sld.shown = true;
			sld.startLocation = "SentJons_HouseF3";
			sld.startLocator = "goto2";
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "Abigile_7_1":
			DelLandQuestMark(npchar);
			dialog.text = "おお！こちらこそ光栄です。これほど重要で…優雅なご婦人をお迎えできて嬉しい限りです。お嬢様、どうぞ二階へお上がりくださいませ。 夕食をご用意しておりますし、お部屋も整えてございます。長旅でお疲れでしょうから、 きっとゆっくりお休みになりたいことでしょう。\n";
			link.l1 = "そうだな。アビゲイルはウィレムスタッドからの長旅できっと疲れているだろう。";
			link.l1.go = "Abigile_8";
		break;
		
		case "Abigile_8":
			DialogExit();
			sld = characterFromId("Abigile");
			sld.dialog.currentnode = "Abigile_kidnapping_11";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_9":
			dialog.text = "もう計画はあるのか？";
			link.l1 = "ああ、そうだ。リチャード宛てにアビゲイルの身代金要求の手紙を書かねえとな。\nどこか無人島――例えばタークスみてえな場所で会う段取りをつけろ。\nもし奴が従わなけりゃ、そうだな……あのユダヤの恋人をバラバラにして送りつけてやるさ。";
			link.l1.go = "Abigile_10";
		break;
		
		case "Abigile_10":
			dialog.text = "「無人島にそんなややこしいことをする必要があるのか？」";
			link.l1 = "中立地帯だ。そっちの方が安全だしな。どうせアビゲイルは連れて行かない。必要なのはフリートウッドだ。 アンティグアなら確実に待ち伏せを仕掛けてくるが、タークスならそんな有利はないはずだ。";
			link.l1.go = "Abigile_11";
		break;
		
		case "Abigile_11":
			dialog.text = "なるほど。それで、その手紙を誰が届けるんだ？とても危険だぞ。";
			link.l1 = "見知らぬ奴だ。酒場で酔っぱらいを選べ、信頼できそうなやつをな。ラム代さえ渡せば、何でも言うことを聞くだろう。 リチャードが怒りに任せてそいつを殺したら、また別のを送ればいい。手紙にはアビの指を一本同封してやる。 それであいつもずっと従順になるさ。";
			link.l1.go = "Abigile_12";
		break;
		
		case "Abigile_12":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "心配するな、ジョン。そんなことにはならないさ。伝令を見つけてくれれば、すぐに手紙を書くよ。紙とインクはあるか？ ";
			link.l1.go = "Abigile_13";
		break;
		
		case "Abigile_13":
			dialog.text = "ああ、知っているよ。それに、ちょうどいい酔っ払いも心当たりがある。ジャック・ハリソンをおすすめするぜ。 あいつは毎晩酒場でラムをあおってるからな。すぐに見つかるはずだ。";
			link.l1 = "よし、ペンとインクを持ってこい。リチャードへの身代金の手紙を書いてやる。";
			link.l1.go = "Abigile_14";
		break;
		
		case "Abigile_14":
			DialogExit();
			StartQuestMovie(true, false, true);
			locCameraFromToPos(0.07, 2.57, -2.46, true, -0.08, -0.38, 1.35);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "MC_writeLetter", -1);
		break;
		
		case "Abigile_15":
			dialog.text = "いつ彼に手紙を渡すつもりだ？\n渡すところを見届ける気か？";
			link.l1 = "もちろんだ。リチャードは馬鹿じゃねえが、危険は冒さねえだろうな。少なくとも、そう願いたいもんだ。 あの娘を傷つけたくはねえが、必要ならやるしかねえ。さて、お前が言ってた酔っ払いを探す時間だな。ジャック…フルネームは何だったっけ？\n";
			link.l1.go = "Abigile_20";
		break;
		
		case "Abigile_20":
			dialog.text = "彼の名前はジャック・ハリソンだ。彼は普段、夕方に酒場へ来る。気をつけろ！";
			link.l1 = "すべてうまくいくさ。俺を待っててくれ。";
			link.l1.go = "Abigile_22";
		break;
		
		case "Abigile_22":
			DialogExit();
			LAi_SetOwnerType(npchar);
			pchar.questTemp.HWIC.Self = "LetterToDrunkardGo";
			AddDialogExitQuestFunction("CreateDrunckardInTavern");
			AddQuestRecord("Holl_Gambit", "3-25");
		break;
		
		case "Abigile_23":
			DelLandQuestMark(npchar);
			dialog.text = "そうは言えませんね。フリートウッドは狡猾で危険な男です。その上、剣術の達人であり、 経験豊富な船乗りでもあります。簡単に獲物になるような相手ではありません。";
			link.l1 = "カリブに来てからは楽な道を選ぶのはやめたんだ。\nさて、ジョン、そろそろ俺は行くよ。\nところで、君が言ってた勇敢なフリートウッドはいい船を持ってるって話、本当か？";
			link.l1.go = "Abigile_24";
		break;
		
		case "Abigile_24":
			dialog.text = "あいつの持ってるブリッグは、俺が今まで見た中で一番だぜ。しかも、俺はいろんな船を見てきたんだ。";
			link.l1 = "それはいいな。俺は立派な船が好きだぜ。さあ、錨を上げる時だ！";
			link.l1.go = "Abigile_26";
		break;
		
		case "Abigile_26":
			DialogExit();
			pchar.questTemp.HWIC.Self = "FleetwoodToIsland";
			pchar.quest.Fleetwood_meetingShore.win_condition.l1 = "location";
			pchar.quest.Fleetwood_meetingShore.win_condition.l1.location = "Shore56";
			pchar.quest.Fleetwood_meetingShore.function = "InTerksShore";
			AddQuestRecord("Holl_Gambit", "3-28");
			AddMapQuestMarkShore("Shore57", false);
		break;
		
		case "Abigile_27":
			int iVal = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
				sld = GetCharacter(iTemp);
				if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_VALCIRIA) iVal = 1;
				}
			}//установили признак наличия Валькирии в эскадре.
			if (iVal != 0)
			{
				dialog.text = "言葉もありません！素晴らしい組み合わせ、見事な発想、そして巧みな実行力！おめでとうございます、 "+pchar.name+"！しかも、あいつのブリッグまで拿捕したんだな！";
				link.l1 = "ありがとう！それで、エルキュールはどこだ？彼に会いたいんだ。前に会ったとき、 君の助けがあれば彼を見つけられるって言ってたんだ。";
				link.l1.go = "Abigile_28";
			}
			else
			{
				dialog.text = "素晴らしい組み合わせ、素晴らしいアイデア、そして見事な実現！おめでとうございます、 "+pchar.name+"!";
				link.l1 = "ありがとう！それで、エルキュールはどこにいるんだ？彼に会いたいんだ。前に会ったとき、 君の助けがあれば彼を見つけられるって言ってたんだよ。";
				link.l1.go = "Abigile_28";
			}
		break;
		
		case "Abigile_28":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SentJons");
			dialog.text = "私は彼を今にも待っているところだ。彼は秘密の通路を通ってここに来るはずだ。\nそれから、アビゲイルにちゃんと説明したほうがいい。リチャードがいないことで彼女が心配し始めているぞ。";
			link.l1 = "わかった、でも彼女を家に帰すべきじゃないか？";
			link.l1.go = "Abigile_29";
		break;
		
		case "Abigile_29":
			dialog.text = "まだだ……まず君と話がしたい。でもその前に、エルキュールが来るのを待て。アビゲイルを慰めてやってくれ。 何か話を作って聞かせてやるんだ。それから地下室に来てくれ。いいな？";
			link.l1 = "あいよ、ジョン。";
			link.l1.go = "Abigile_30";
		break;
		
		case "Abigile_30":
			DialogExit();
			npchar.greeting = "merdok_4";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "SentJons_TownCave", "item", "berglar1", "", -1);
			pchar.questTemp.HWIC.Self = "AbigileLie";
			sld = characterFromId("Abigile");
			LAi_SetCitizenType(sld);
			AddLandQuestMark(sld, "questmarkmain");
			AddQuestRecord("Holl_Gambit", "3-34");
		break;
		
		case "Lucas":
			DelLandQuestMark(npchar);
			dialog.text = "さて、いよいよ腹を割って話す時が来たな。もう気づいているだろうが、俺はただの薬屋じゃねえ。 本当の名はヨハン・ファン・メルデン、つい最近までオランダ西インド会社のエージェントで、 副総裁ルーカス・ローデンブルクの右腕だったんだ。";
			link.l1 = "本当か！それは面白いな……";
			link.l1.go = "Lucas_1";
		break;
		
		case "Lucas_1":
			dialog.text = "今はもう違う。ルーカスはこの世界から足を洗い、オランダへ帰ろうとしている。 だから自分の過去に関わるものや人間をすべて葬り去る必要があるんだ\n俺がまだ生きていられるのは、ルーカスの犯罪に関するすべての情報を記録した自分のアーカイブのおかげだと思う……たとえば「幽霊船」の話もそうだ。実際はただの海賊船で、 無謀で節操のない悪党ヤーコプ・ファン・ベルクが指揮している。ローデンブルクがこいつを雇って、 イギリスの商船を襲わせて沈めていたんだ\nファン・ベルクはアビゲイルとその父親が乗っていたフリュート船を沈めた張本人でもある。 アビゲイルはこのゲームで重要な人物だ。ローデンブルクもフリートウッドと同じく、 彼女の心と手を欲しがっていたから、君が彼女をここに連れてきたときは正直驚いたよ……";
			link.l1 = "ローデンブルク……それがアビゲイルの変わり者の父親が話していた婿殿か！";
			link.l1.go = "Lucas_2";
		break;
		
		case "Lucas_2":
			dialog.text = "ああ、だからこそ彼女にはしばらくここにいてほしいのだ。ローデンブルクとの駆け引きで、 彼女が最後の切り札になるかもしれないが、できればこれ以上利用したくはない。彼女はいい娘だ、苦しんでほしくない。 もし選択を迫られたら、ルーカスは彼女よりも私の書庫を選ぶだろうと思う。\nそこで提案だが、ルーカスとの駆け引きで私の味方になってくれ……奴を排除してほしい、手段は問わない。報酬は十分に用意する。";
			link.l1 = "ふむ……フリートウッドとやるのと比べて、これ以上難しくなるとは思わないな。 ";
			link.l1.go = "Lucas_3";
		break;
		
		case "Lucas_3":
			dialog.text = "いいや、違うぜ。結局のところ、フリートウッドは一匹狼で、独断で動いていたんだ。ローデンブルクは会社の副総裁だ。 あいつはかなりの大物で、キュラソーの総督だけがそれ以上の権力を持っている。 ヤーコプ・ファン・ベルクはローデンブルクの手先で、とても危険な男だ。 ルーカスはウィレムスタッドで会社の衛兵に守られながら尻を据えてやがるし、 あいつらはフリートウッドの部下にも劣らない連中だ。\nこれは簡単にはいかねえな。";
			link.l1 = "ゲームのルールは同じだ――虎を巣穴からおびき出すことさ……もう作戦は考えてある。他にルーカスについて何か知っていることはあるか？";
			link.l1.go = "Lucas_4";
		break;
		
		case "Lucas_4":
			dialog.text = "さて、ほとんど全て話したな。あいつは『美風（メイフェン）』という俊足の船を持っている。 船長はロンウェイという中国人で、ローデンブルクの忠実な部下だ。あいつもまた、敵に回したくない相手だぜ。 ルーカスの手下に素人なんて一人もいねえんだ。 ";
			link.l1 = "最初から俺たちには切り札があった――お前のアーカイブだ。もしあいつがユダヤ女より自分の命を大事にするなら、 アーカイブの情報を守るためなら何でもするはずだ……だが……本当にそのアーカイブは存在するのか、ジョン？ bleuffしてるんじゃねえのか？";
			link.l1.go = "Lucas_5";
		break;
		
		case "Lucas_5":
			dialog.text = "記録庫は実在する。そしてルーカスもそれを知っている。何か考えはまとまったか？";
			link.l1 = "あるさ。ジョン、本当にお前が会社のエージェントなら、何か知っているはずだろう。";
			link.l1.go = "Lucas_6";
		break;
		
		case "Lucas_6":
			dialog.text = "何のことだ？俺に聞いてみろ。";
			link.l1 = "私はカンパニーの船を拿捕する必要があるんだ。できれば護衛のない船――伝令船かそれに近いものがいい。これについて何か知っているか？";
			link.l1.go = "Lucas_7";
		break;
		
		case "Lucas_7":
			dialog.text = "ふむ……そのような情報は持っていない。待てよ！確かに、会社のパケット船が月に一度、 フィリップスブルフとウィレムスタッドの航路を行き来しているはずだ。業務書類を運んでいるんだ。その船は『フープ』 という名のブリガンティンだ。\n今日か明日、フィリップスブルフを出航するぞ。";
			link.l1 = "ああ、それだ！あとはセントクリストファーの岸に向かうだけだ。キュラソーへの航路はちょうどそこを通るんだ。";
			link.l1.go = "Lucas_8";
		break;
		
		case "Lucas_8":
			dialog.text = "「幸運を祈る」 "+pchar.name+"……あなたの計画の詳細については聞きません。あなたの帰りを待っています！";
			link.l1 = "すべてうまくいくさ、ジョン。あのユダヤ人の女をちゃんと世話して、丁重に扱えよ！";
			link.l1.go = "Lucas_9";
		break;
		
		case "Lucas_9":
			DialogExit();
			RemoveItems(PChar, "MC_Letter", 1);
			GiveItem2Character(pchar, "MC_Letter");
			ChangeItemDescribe("MC_Letter", "itmdescr_MC_Letter2");
			AddQuestRecordInfo("LetterToLucas", "1");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "SentJons_HouseF3", "goto", "goto1", "MC_TakeCloves", -1);
			pchar.questTemp.HWIC.Self = "LetterToLucas";
			sld = characterFromId("Tonzag");
			sld.dialog.currentnode = "Tonzag_hired";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			AddQuestRecord("Holl_Gambit", "3-36");
			//установим таймер на генерацию энкаунтера
			pchar.quest.HWIC_Cureer.win_condition.l1 = "Timer";
			pchar.quest.HWIC_Cureer.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.HWIC_Cureer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.HWIC_Cureer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.HWIC_Cureer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.HWIC_Cureer.function = "CreateHWICCureerOnMap";
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("HWICCureerOnMapOver", 0, 0, 16, false);//таймер
		break;
		
		case "Lucas_10":
			dialog.text = "信じられない！私の耳を疑いますわ！どうしてそんなことになったのです？";
			link.l1 = "俺はパケット船を拿捕して、フリートウッドの名代としてルーカスに手紙を送ったんだ。その中で、 セント・ジョンズの薬屋の持ち物だったある文書庫を手に入れたこと、 そしてまもなく奴の悪事の証拠がここからアムステルダムやロンドンにまで知れ渡るだろうと書いた。 奴が俺を追い始めると思ってたが、実際は逆だったんだ。";
			link.l1.go = "Lucas_11";
		break;
		
		case "Lucas_11":
			dialog.text = "";
			link.l1 = "ルーカスはマティアス・ベックを裏切りとイギリス人との取引で告発し、投獄した上で総督の宮殿に居座った。 おそらくブリガンティンの船長も始末したのだろう。それから、メイフェン号の忠実な中国人に命じて、 会社の総監督ピーター・スタイフェサントが乗っている船を沈めさせたんだ！";
			link.l1.go = "Lucas_12";
		break;
		
		case "Lucas_12":
			dialog.text = "ローデンブルクは容赦ない男だ。しかし、俺でさえあそこまでやるとは思わなかった……";
			link.l1 = "俺はメイフェン号を拿捕してロンウェイを尋問した。奴は全部白状したぜ。 スタイフェサントを見つけてローデンブルクの企みを警告し、一緒にウィレムスタッドへ向かった。 スタイフェサントはベックを釈放し、ルーカスを逮捕した。今は牢屋にぶち込まれてる。";
			link.l1.go = "Lucas_13";
		break;
		
		case "Lucas_13":
			dialog.text = "へっ！お前には本物の才能があるな、友よ……会社の海軍で出世するか、連邦共和国に戻って政治家になったほうがいいぜ。総督にだってなれる器だ！それで、 ロンウェイには何をしたんだ？";
			link.l1 = "俺はあいつを逃がしてやった。潔く降参したから、手荒な真似はしなかったぜ。";
			link.l1.go = "Lucas_14";
		break;
		
		case "Lucas_14":
			dialog.text = "それは良かった。ロンウェイは元の上司とは違って、いい奴だ。さて、 "+pchar.name+"、素晴らしい働きだったぞ！報酬の準備をするが、少し時間が必要だ……その間に……";
			link.l1 = "ジョン、正直に言うと、問題があるんだ。ロンウェイに続いてローデンブルクも、 ヤーコブ・ファン・ベルフが俺を狙っているって言ってた。どれほどヤバい状況なんだ？";
			link.l1.go = "Lucas_15";
		break;
		
		case "Lucas_15":
			dialog.text = "ヤーコブ・ファン・ベルク？チャーリー、これは本当に深刻だ。あいつは容赦ない海賊で、腕利きの船乗りにして戦士、 フリートウッドなんて子猫に見えるほどだぜ。プロの狩人だ。ローデンブルクの命令で船を沈めていたのもあいつだ。\n必ずお前を見つけ出すだろうから、しっかり備えておけ。俺も用心しておくとしよう。";
			link.l1 = "どうやってこのファン・ベルクを見つければいいんだ？";
			link.l1.go = "Lucas_16";
		break;
		
		case "Lucas_16":
			dialog.text = "分からない。ルーカスとロンウェイだけが彼の居場所を知っていたんだ。だから、とにかく気をつけて警戒してくれ\nここは閉めるつもりだ。俺に会いたければ秘密の抜け道を通れ。それと、あのユダヤ人の娘も連れて行け。 ここにいさせるのは危険すぎる。";
			link.l1 = "心配するな、ジョン。あいつが現れたら俺が片をつける。アビゲイルはどこだ？";
			link.l1.go = "Lucas_17";
		break;
		
		case "Lucas_17":
			dialog.text = "彼女は教会に行ったよ。かわいそうにな。最近ずっと動揺しているんだ。";
			link.l1 = "ほう……それは嬉しい驚きだな。もしかすると、 彼女もついにキリストこそが長らく民が待ち望んだ救世主だと気づいたのかもしれん。さて、 彼女を父親のもとへ連れ戻す時だな。";
			link.l1.go = "Lucas_18";
		break;
		
		case "Lucas_18":
			dialog.text = "彼女はあなたに会いたがっていた。きっと彼女は家に連れて帰ってほしいと頼むはずだ。";
			link.l1 = "「アビか、ふん？」";
			link.l1.go = "Lucas_19";
		break;
		
		case "Lucas_19":
			dialog.text = "まあ、正直に言えば、俺たちは友達になったんだ。彼女が俺の家に住んでいたことを後悔はしていないし、 ありがたいことに、彼女がここに連れて来られた理由を知ることは決してないだろう。";
			link.l1 = "わかった、ジョン。教会に行ってアビゲイルに会ってくる。その後、ウィレムスタッドへ向かう。";
			link.l1.go = "Lucas_20";
		break;
		
		case "Lucas_20":
			DialogExit();
			sld = characterFromId("Abigile");
			AddLandQuestMark(sld, "questmarkmain");
			ChangeCharacterAddressGroup(sld, "SentJons_church", "goto", "goto1");//Аби - в церковь
			AddQuestRecord("Holl_Gambit", "3-56");
			pchar.questTemp.HWIC.Self = "AbiReturnHome";
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//закрыть аптеку
		break;
		
		case "Final":
			dialog.text = "お前……あいつのタマを潰したのか？ああ、比喩か。まあ、タマがあろうがなかろうが、やったんだな！おめでとう！";
			link.l1 = "あなたに嘘なんてつかないさ、へっ。もう安心していいぞ、ジョン。";
			link.l1.go = "Final_1";
		break;
		
		case "Final_1":
			dialog.text = "やっと終わったな！もうこんな政治的な駆け引きや陰謀ごっこは全部やめた方がいいと思うぜ。さて、 そろそろお前の報酬について話そうか。";
			link.l1 = "それはぜひありがたいですわ。";
			link.l1.go = "Final_2";
		break;
		
		case "Final_2":
			dialog.text = "私はカリブを永遠に去るつもりです。\nあなたが助けてくれたこと、そしてローデンブルクから救い出してくれたことへの感謝のしるしとして、 この家と私の薬局の所有権証書をあなたに譲ります。\n今や全てあなたのものです。鍵を受け取ってください。";
			link.l1 = "それは素晴らしいですね！私はとても嬉しいです。あなたの家はとても快適で、地下室も居心地が良いですね…";
			link.l1.go = "Final_3";
		break;
		
		case "Final_3":
			GiveItem2Character(pchar, "Drugstore_keys");//ключ
			dialog.text = "それから、このささやかな十万ペソとこのマスケット銃もお受け取りください。\nかつては私に忠実に仕えてくれましたが、あなたにもきっと役立つでしょう。";
			link.l1 = "そんな贈り物、俺が断るわけないだろう！";
			link.l1.go = "Final_4";
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", false);//открыть аптеку
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload3", false); // открыть комнату
			pchar.quest.Jino_Door.win_condition.l1 = "locator";
			pchar.quest.Jino_Door.win_condition.l1.location = "SentJons_HouseF3";
			pchar.quest.Jino_Door.win_condition.l1.locator_group = "reload";
			pchar.quest.Jino_Door.win_condition.l1.locator = "reload4";
			pchar.quest.Jino_Door.function = "OpenRoomDoor";//на локатор комнаты Джино
			Achievment_Set("ach_10");
		break;
		
		case "Final_4":
			AddMoneyToCharacter(pchar, 100000);
			GiveItem2Character(pchar, "mushket2");
			dialog.text = "二階の部屋には若い自然哲学者がいる。私の知る限り最高の薬剤師だ。君が数日で回復できたのも、 彼が作ったこの薬のおかげだよ。彼の給金をきちんと払えば、 その知識が必ずや元を取って余りある利益をもたらしてくれるだろう。";
			link.l1 = "私専属の本の虫か？よろしい、俺が面倒を見てやる。";
			link.l1.go = "Final_5";
		break;
		
		case "Final_5":
			dialog.text = "もうお別れを言わなければなりません。これから地下室に行って荷物をまとめます。明日にはここを離れ、 アンティグアから出航します。あなたに出会えて本当に嬉しかったし、敵ではなく味方でいてくれて感謝しています。";
			link.l1 = "私もお会いできて嬉しいです、ジョン。またどこかでお会いするかもしれませんね……";
			link.l1.go = "Final_6";
		break;
		
		case "Final_6":
			dialog.text = "この人生じゃ無理だな、友よ。俺は荷物をまとめるぜ。じゃあな、 "+pchar.name+"!";
			link.l1 = "さようなら、ジョン！幸運を祈るぜ！";
			link.l1.go = "Final_7";
		break;
		
		case "Final_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);
			npchar.lifeday = 0;
			pchar.questTemp.HWIC.Self = "final";
			AddQuestRecord("Holl_Gambit", "3-64");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Detector = "self_win";
		break;
		
		// Страж Истины
		case "guardoftruth":
			dialog.text = "ああ、旦那、そんな馬鹿げた話は聞かないでください。誰もいませんよ。あそこは私の実験室でして、 調合が行われているんです、ええ…";
			link.l1 = "冗談はさておき、ジョン。ジーノ・グヴィネリという名前に心当たりはあるか？";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "ふむ……";
			link.l1 = "あはっ！目を見ればわかる――俺の言った通りだな……あそこに住んでて、そいつのために薬草を用意してるんだろう！";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "旦那、もう一度申し上げますが――ここには誰もいません。";
			link.l1 = "言い訳はやめよう、ジョン。お前の錬金術師には手を出さない——だが、もしサンティアゴのヴィンチェント神父が見つけたら、どうなるか分からないぞ。異端審問官はすでに“ドミニ・カネス”をアンティグアに送り込むつもりらしい……";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "「彼に何の用だ？」";
			link.l1 = "ただ話をするだけだ。彼は私にとってかなり重要な情報を持っている。約束する、異端審問に引き渡したり、 彼に危害を加えたりは決してしない。";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "ジーノは親切な男だ。ヴィンチェンツォ神父が彼について何を言ったとしても信じるな。そして覚えておけ――俺は自分の錬金術師を必ず守るからな。";
			link.l1 = "約束しただろう。それじゃ足りねえのか？";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "では、二階へお上がりください。扉は開いております。そして、約束を守ってくださることを願っております。";
			link.l1 = "ご安心ください、必ずそうします。";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			DialogExit();
			pchar.questTemp.Guardoftruth = "jino1";
			AddQuestRecord("Guardoftruth", "36");
			LocatorReloadEnterDisable(pchar.location, "reload4", false);
		break;
		
		// алхимический набор
		case "alchemy":
			dialog.text = "船長、錬金術の奥義に親しんでみませんか？これはきっとあなたの役に立つことでしょう。";
			link.l1 = "申し訳ありませんが、私の職業は少し違います。私は手に剣の柄を握るのには慣れていますが、 フラスコや試験管を持つことには慣れていません。";
			link.l1.go = "alchemy_exit";
			link.l2 = "「天にも地にも、お前さんの哲学じゃ想像もできねえことがまだまだあるんだぜ。」もちろん、喜んでやらせてもらうよ。 何が必要なんだ？";
			link.l2.go = "alchemy_1";
			npchar.quest.alchemy = true;
		break;
		
		case "alchemy_exit":
			dialog.text = "かしこまりました。私はただ提案しただけでして…";
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "alchemy_1":
			dialog.text = "自分の手で薬草を調合することを学ぶべきだ。しかし、錬金術師の道具がなければうまくいかないぞ。\nこの袋を見てみなさい。これには見習い錬金術師に必要なものがすべて入っている――試験管、フラスコ、蒸留器、ヘラ、ガラス管、バーナー、それに他にもたくさんの道具が入っているんだ…";
			link.l1 = "とても興味深いね！それで俺は何を作れるんだ？";
			link.l1.go = "alchemy_2";
		break;
		
		case "alchemy_2":
			dialog.text = "まあ、鉛を金に変えることはできないが、さまざまなレシピに従って材料を調合すれば、 薬や他の役立つものを手に入れることはできるぜ。";
			link.l1 = "レシピか？";
			link.l1.go = "alchemy_3";
		break;
		
		case "alchemy_3":
			dialog.text = "その通りだ。薬やアイテムを作るには、まずレシピを知らなければならない。レシピは商人から買うこともできるし、 どこかで見つけることもある。一度レシピを学んだら、必要な材料をすべて集めて、 そこに書かれている通りに正確に作業するのだ\n 錬金術の道具を使い、乳鉢と乳棒を探すか買うかし、るつぼも探してみるといい。残念ながら、 余分なものを君にあげることはできない。薬草、酒、薬、鉱石、ゴミ――正しいレシピと道具さえあれば何でも使えるのだ。";
			link.l1 = "とても興味深いな。それで、この道具一式はいくら欲しいんだ？";
			link.l1.go = "alchemy_4";
		break;
		
		case "alchemy_4":
			dialog.text = "二万ペソだ。これはとても優れた装備で、すぐに元が取れるぞ。";
			link.l1 = "俺をバカにしてるのか？ガラス細工入りのハンドバッグがラガー船一隻分の値段だと？いや、遠慮しとくぜ。";
			link.l1.go = "alchemy_exit";
			if (sti(pchar.money) >= 20000)
			{
				link.l2 = "同感だ。自分の手で何かを作ってみるのは面白そうだと思う。";
				link.l2.go = "alchemy_5";
			}
		break;
		
		case "alchemy_5":
			AddMoneyToCharacter(pchar, -20000);
			Log_Info("You've got the alchemist's kit.");
			GiveItem2Character(pchar, "alchemy_tool");
			PlaySound("interface\important_item.wav");
			dialog.text = "この買い物、絶対に後悔しませんよ、私は自信があります。\n必要なときに自分で薬を作ったほうが、薬草屋の屋台を回って一つずつ買い集めるよりも、確実にお得ですからね。\nそれに、必要なものがいつでも全部手に入るとは限りませんし。 ";
			link.l1 = "学ぼう。俺ならできると思うぜ！";
			link.l1.go = "alchemy_6";
		break;
		
		case "alchemy_6":
			DialogExit();
			PlaySound("interface\notebook.wav");
			Log_Info("In order to make your own herbs and amulets you must have the Alchemy skill!");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("あなたは "+GetSexPhrase("泥棒だ、旦那！衛兵、そいつを捕まえろ","泥棒だ、あの娘だ！衛兵、あいつを捕まえろ")+"!!!","見てよこれ！僕が物思いにふけっていた隙に、君は僕の胸を探ろうとしたんだね！泥棒だ！誰か泥棒を捕まえてくれ！！！ ","衛兵！強盗だ！泥棒を捕まえろ！！！");
			link.l1 = "くそっ！";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
