// Addon-2016 Jason, французские миниквесты (ФМК) Сент-Кристофер
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "明らかなバグだ。開発者たちに伝えてくれ。";
			link.l1 = "ああ、そうするよ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "seafox":
			DelMapQuestMarkCity("Charles");
			LAi_SetImmortal(npchar, false);
			DelLandQuestMark(npchar);
			LAi_RemoveLoginTime(npchar);
			PlaySound("Voice\English\LE\SeaFox\SeaFox_01.wav");
			dialog.text = TimeGreeting()+"「船長。 (敬礼) 自己紹介させていただきます―中尉 "+GetFullName(npchar)+"、セントジョンズに駐屯しているアンティグア海兵連隊所属だ。頼みがあるんだ。";
			link.l1 = "ごきげんよう、グレトン中尉。私の名は "+GetFullName(pchar)+"「……どんな頼みごとだ？」";
			link.l1.go = "seafox_1";
		break;
		
		case "seafox_1":
			dialog.text = "状況を簡単に説明させてくれ。俺と部下四人はセントジョンズからシント・マールテンへ航海していたんだが、 嵐に遭ってしまった。悪天候は長くは続かなかったが、それでも古い船に浸水が起きるには十分だった。進路を変えて、 修理のためにここに立ち寄らざるを得なかったんだ。それで、俺たちにはない時間を食っている。\n急いでシント・マールテン、特にグランケース・ビーチへ行かねばならない。手を貸してくれ、船長。 そうすれば必ず礼はする。二日間の航海でたっぷり報酬を出すぜ！";
			link.l1 = "気前のいい報酬じゃなきゃ困るぜ、中尉。イギリス海兵をこっそりオランダの島に潜り込ませろってんならな。";
			link.l1.go = "seafox_2";
		break;
		
		case "seafox_2":
			dialog.text = ""+UpperFirst(GetAddress_Form(PChar))+"、これはお前には関係ねえことだ。危険はねえよ。湾に俺たちを降ろしてくれりゃ、それで終わりだ。どうだ、 話はまとまったか？";
			link.l1 = "よし、乗ったぜ。ここからそんなに遠くねえしな。で、報酬の話を聞かせてくれ。";
			link.l1.go = "seafox_3";
			link.l2 = "申し訳ないが、俺は別の方向に急ぎの用事があって、できればオランダ人を怒らせたくないんだ。";
			link.l2.go = "seafox_exit";
		break;
		
		case "seafox_exit":
			dialog.text = "おっしゃる通りです、船長。じゃあ、引き続き探してみるぜ。さらばだ、そしてご武運を！";
			link.l1 = "さらばだ、中尉。";
			link.l1.go = "seafox_exit_1";
		break;
		
		case "seafox_exit_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			npchar.lifeday = 0;
		break;
		
		case "seafox_3":
			GiveItem2Character(pchar, "purse2"); 
			Log_Info("You have received a purse of doubloons");
			dialog.text = "一万枚のエイトだ。前金を渡すぜ。";
			link.l1 = "よし。部下を乗船させろ、時間を無駄にするな。";
			link.l1.go = "seafox_4";
		break;
		
		case "seafox_4":
			dialog.text = "了解だぜ、船長！";
			link.l1 = "...";
			link.l1.go = "seafox_5";
		break;
		
		case "seafox_5":
			DialogExit();
			AddQuestRecord("FMQ_Nevis", "1");
			pchar.questTemp.FMQN = "begin";
			
			chrDisableReloadToLocation = false;
			sld = CharacterFromID("FMQN_seafox_1");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", "", "", "", "", 10.0); // англичане на борт
			sld.location = "None";
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.FMQN_sailing.win_condition.l1 = "location";
			pchar.quest.FMQN_sailing.win_condition.l1.location = "Shore40";
			pchar.quest.FMQN_sailing.win_condition.l2 = "Ship_location";
			pchar.quest.FMQN_sailing.win_condition.l2.location = "Shore40";
			pchar.quest.FMQN_sailing.function = "FMQN_ArriveMaarten";
			if(bImCasual)
			{
				NewGameTip(StringFromKey("FMQ_69"));
			}
			else SetFunctionTimerCondition("FMQN_SailingLate", 0, 0, 10, false);
			for(i = 0; i < MAX_LOCATIONS; i++)
			{	
				sld = &Locations[i];
				if (CheckAttribute(sld, "islandId") && sld.islandId == "SentMartin")
				{
					sld.DisableEncounters = true;	
				}
			}
			sld = &Locations[FindLocation("Shore40")];
			sld.QuestlockWeather = "23 Hour";
			AddMapQuestMarkShore("Shore40", true);
		break;
		
		case "seafox_6":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "順調な航海をありがとうございます、船長！本当に申し訳ないのですが、今この場ではお支払いできません……この辺りに我々のラガー船がいるはずだったのですが、ご覧の通りいません。もう一度だけお力をお借りしたいのです。 この湾で二、三日待っていただけませんか？我々は周囲を調べに行かねばなりません。戻ってきたら、 アンティグアまで連れて行ってください。フォックス大佐がきっとたっぷりと報酬をお渡しします。";
			link.l1 = "ふむ……これは俺たちが約束した内容とはちょっと違うじゃねえか……";
			link.l1.go = "seafox_7";
		break;
		
		case "seafox_7":
			dialog.text = "どうかご立腹なさらないでください、船長。あなたのお気持ちはよく分かりますが、残念ながら、 今は全くお金がありません。ですが、必ずや両方の航海とここで待っていてくださったことへの報酬、 そしてフォックス大佐ご本人からの感謝もお約束します！";
			link.l1 = "お前を見捨てるわけにはいかねえな……よし、グレトン中尉。三日間だけ待ってやるが、それ以上は無理だぜ。";
			link.l1.go = "seafox_8";
		break;
		
		case "seafox_8":
			dialog.text = "ありがとうございます。 "+GetAddress_Form(NPChar)+"！俺たちは内陸に向かうぜ。72時間以内に必ず戻る、絶対に一分も遅れねえ。";
			link.l1 = "ご武運を、少尉。捕まるんじゃねえぞ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglishmanGo");
		break;
		
		case "seafox_9":
			DelLandQuestMark(npchar);
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "なんて偶然の出会いだ！グラン・ケース・ビーチで俺たちを待ってると思ってたぜ、船長 "+pchar.lastname+"!";
			link.l1 = "やあ、中尉、驚いたのはお互い様だな。まさかお前がオランダ兵みたいな格好をしてるとは思わなかったぜ。";
			link.l1.go = "seafox_10";
		break;
		
		case "seafox_10":
			dialog.text = "それは俺たちの変装だ……なんでお前がここにいるんだ、 "+GetAddress_Form(NPChar)+"?";
			link.l1 = "それは危険な変装だぜ、相棒。スパイは裁判抜きで即刻処刑されるもんだ。\nそれと処刑ついでに言っとくが、自分の首が惜しいなら、ちゃんと話を聞いた方がいいぜ。";
			link.l1.go = "seafox_11";
		break;
		
		case "seafox_11":
			dialog.text = "俺は全神経をお前に向けてるぜ。";
			link.l1 = "俺はフィリップスバーグまで航海して、あんたが上陸した後に地元の連中と話をしたぜ。 オランダ人どもはあんたのことを嗅ぎつけてる。捕まったイギリスの高官たちを救出する任務のこともバレてるぞ。";
			link.l1.go = "seafox_12";
		break;
		
		case "seafox_12":
			dialog.text = "ちくしょう！一体どうやってこいつのことがバレたんだ！？";
			link.l1 = "捕らえられたイギリス士官の一人だ。自由と引き換えに、救出作戦について知っていることをすべてオランダ側に話した。 フィリップスブルフの街全体が、お前と部下たちが市内に入ろうとするのを待ち構えている。\nさらに悪いことに、オランダのコルベット艦がシント・マールテン周辺の海域を巡回している。\nこれは罠だ、中尉。";
			link.l1.go = "seafox_13";
		break;
		
		case "seafox_13":
			dialog.text = RandSwear()+"あの不名誉な悪党め！誰がその裏切り者か突き止めて、議会の前で告発してやるぞ！";
			link.l1 = "それは後回しだ、グレトン旦那。今夜グランドケースビーチに戻って、奴らに捕まる前に俺の船へ帰ってこい。";
			link.l1.go = "seafox_14";
		break;
		
		case "seafox_14":
			dialog.text = "「オランダの牢獄にイギリス紳士を置き去りにするだと？俺は死んだ方がマシだ、旦那。 フォックス大佐を決して裏切らねえ。」";
			link.l1 = "ふん、オランダ人に捕まったら、絞首刑か銃殺刑か選ばせてくれると思うか？";
			link.l1.go = "seafox_15";
		break;
		
		case "seafox_15":
			dialog.text = "ここからただで出航できるなんて思うなよ、ド・モール船長。俺たち二人とも首までどっぷり浸かってるんだぜ。";
			link.l1 = "くそっ、たぶんお前の言う通りだ。あのコルベット艦は、俺たちが錨を上げた瞬間に襲いかかってくるだろうな……";
			link.l1.go = "seafox_16";
		break;
		
		case "seafox_16":
			dialog.text = "オランダ野郎どもは俺たちが来るのを知ってるかもしれねえが、どうやって来るかまでは知らねえ。 変装の準備はもう済んでる――この制服を見てみろよ。いい出来だろ？もし計画が裏切られてなきゃ、そのまま地元の牢屋に行って、 不意打ちで中の連中を皆殺しにできたんだがな。だが、今じゃあいつらが待ち伏せしてるのは間違いねえ。だから、 ここは臨機応変にいくぜ。船長、フィリップスブルグの教会に行って、フィリッペ・ヤコブセンって名の説教師を探せ。 あいつは朝六時から十時までそこにいるはずだ。フィリッペは内通者の一人だ。こいつを合言葉として伝えろ――『捕虜の水夫たちはいつ告白した？』とな。その後、状況を説明して、フォックス大佐の名のもとに協力を要求しろ。 それから、あいつの返事を俺のところに持ってきてくれ。簡単だし、お前に危険はねえよ。";
			link.l1 = "オランダのカルヴァン派教会で告解について聞くなんて、かなり危ねえ話だぜ、中尉。 牧師は俺をカトリックだって理由で吊るそうとするだろうな。\nよし、その制服について教えてくれ……これ、オランダの巡回兵から奪ったのか？";
			link.l1.go = "seafox_17";
		break;
		
		case "seafox_17":
			dialog.text = "「はい、旦那。」";
			link.l1 = "「で、今そいつらはどこにいるんだ？」";
			link.l1.go = "seafox_18";
		break;
		
		case "seafox_18":
			dialog.text = "この洞窟からそう遠くない茂みで人質にされている。";
			link.l1 = "了解だ。奴らを安全にしておけ、俺は町へ行ってくる。ここで待ってろ、目立つなよ――オランダ野郎どももお前を探して海だけじゃなくジャングルまでうろついてるからな。";
			link.l1.go = "seafox_19";
		break;
		
		case "seafox_19":
			dialog.text = "教会のネズミみたいに静かにしてるぜ、船長。急いでくれ！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ToChurch");
		break;
		
		case "seafox_20":
			PlaySound("Voice\English\soldier_common_4.wav");
			DelLandQuestMark(npchar);
			dialog.text = "戻ったのか？船長、ここで何してるんだ？町へ行け、俺たちの隠れ家が目立っちまうだろう！";
			link.l1 = "町から戻ったぜ。お前らイギリス人は一体どんな遊びをしてやがるんだ？";
			link.l1.go = "seafox_21";
		break;
		
		case "seafox_21":
			dialog.text = "「なんだって？」";
			link.l1 = "教会に行ってきたぜ。でかい建物で、質素で立派だ。あのオランダの偶像破壊者どもが好みそうな感じだな。\nなあ、少尉、わかるか？フィリッペ・ヤコブセンって名前の説教師なんていなかったぜ。";
			link.l1.go = "seafox_22";
		break;
		
		case "seafox_22":
			dialog.text = "そんなはずない、あいつは毎朝そこに来てるんだ――";
			link.l1 = "黙って俺の話を聞け！そのヤコブセンとかいう奴が本当に存在するとしても、教会になんか来やしねえ！ 誰も見たことがねえんだよ！朝も夜もな！くそったれ！なんで俺がこんな仕事を引き受けちまったんだ！？ アホでクソガキの新米中尉に率いられてよ――";
			link.l1.go = "seafox_23";
		break;
		
		case "seafox_23":
			dialog.text = "旦那、今の侮辱には納得できません。ここを出たら、我々は慣習に従って決闘することになるぞ―";
			link.l1 = ""+RandSwear()+"";
			link.l1.go = "seafox_24";
		break;
		
		case "seafox_24":
			PlaySound("Ambient\Jail\chain.wav");
			PlaySound("Ambient\Land\door_001.wav");
			dialog.text = "黙れ、てめえら全員！！！…今、何か聞こえたぞ。";
			link.l1 = "";
			link.l1.go = "seafox_25";
		break;
		
		case "seafox_25":
			if (pchar.sex == "man") {PlaySound("VOICE\English\LE\SeaFox\SeaFox_04.wav");}
			dialog.text = "なんてこった、誰かが外にいるぞ！\nお前だ！お前がオランダ野郎をここに連れてきやがったな、このろくでなしめ！";
			link.l1 = ""+RandSwear()+"!!!";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleFight");
		break;
		
		case "seafox_26":
			DelLandQuestMark(npchar);
			pchar.quest.FMQN_fail1.over = "yes";
			PlaySound("Voice\English\LE\SeaFox\SeaFox_02.wav");
			dialog.text = "会えて嬉しいぜ、旦那。何か新しい話はあるか？";
			link.l1 = "お前の仲間には会ったぜ。今晩、あいつが“香り付き”のワインを監獄の守備隊に届けることになってる。ジプシーから手に入れた薬が入っててな、命に別状はねえが、 死んだように眠るだろう。今夜中に中へ入って、捕まった旦那方を助け出すんだな。\nそれと、このワインの手配に二十五ドゥブロンかかったからな。報告書にちゃんと書いといてくれよ。";
			link.l1.go = "seafox_27";
		break;
		
		case "seafox_27":
			dialog.text = "金のことは気にするな。船長、今回の作戦に加わってもらい、監獄まで案内してほしいんだ。 フィリップスバーグには前に行ったことがあるだろうから、俺たちより街のことを知ってるはずだ。 中まで一緒に入る必要はねえ、脱獄は俺たちでやる。扉まで連れていってくれ。\n";
			link.l1 = "ちくしょう、グレットンさん、この仕事はどんどん面白くなってきやがるな。\n報酬もそれに見合って増えてくれりゃいいんだがな。";
			link.l1.go = "seafox_28";
		break;
		
		case "seafox_28":
			dialog.text = "間違いなくそうです、船長。俺たちを助けてくれたこと、絶対に後悔させませんぜ。 あんたの船はグラン・ケース・ビーチにあるのか？";
			if (pchar.location.from_sea == "Shore40")
			{
				link.l1 = "ああ。";
				link.l1.go = "seafox_29";
			}
			else
			{
				link.l1 = "いやだ。";
				link.l1.go = "seafox_29x";
			}
		break;
		
		case "seafox_29":
			dialog.text = "よし。じゃあ、準備して夜十一時までに町の門で俺たちと合流しろ。";
			link.l1 = "そこで会おう。";
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_29x":
			dialog.text = "必ず彼女をそこに移してくれ。俺たちはジャングルを通って仲間を脱出させなきゃならねえんだ。 港やシンプソン湾からの出航は砦のせいで不可能だ。全て準備して、夜十一時までに町の門で合流しよう。\n";
			link.l1 = "そこで会おう。";
			link.l1.go = "seafox_30";
		break;
		
		case "seafox_30":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuestFunction("FMQN_EnglandPrepare");
		break;
		
		case "seafox_31":
			PlaySound("Voice\English\Gr_hovernor01.wav");
			dialog.text = "準備はいいか、船長？";
			link.l1 = "「ああ。」";
			link.l1.go = "seafox_32";
		break;
		
		case "seafox_32":
			dialog.text = "じゃあ、行くぞ。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_EnglandReload");
		break;
		
		case "seafox_33":
			dialog.text = "しっ…船長！終わったぜ、さっさとここからずらかろう！..";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToJungle");
		break;
		
		case "seafox_34":
			dialog.text = "どうやってやり遂げたのか自分でも分からねえが、やったぜ！旦那、あんたの助けがなけりゃ絶対に無理だった。\nさて、ここからは比較的簡単な仕事だ――生きて無事にシント・マールテンを脱出しねえとな。\nグランド・ケース・ビーチへ行こうぜ！";
			link.l1 = "行くぞ！";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_EnglandRunToShore");
		break;
		
		case "seafox_35":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_05.wav");
			dialog.text = "Captain "+pchar.lastname+"... "+GetAddress_Form(NPChar)+"、ご協力ありがとうございます！お願いです、どうかすぐに港を離れず、私がフォックス大佐に報告する間、 もう一日ここに滞在してください。明日、大佐の執務室がある総督邸にお訪ねください。";
			link.l1 = "よろしい、グレトン中尉。俺に見合うだけの価値を示してくれよ。お前の騒動のせいで、 オランダ人との評判を回復するのにかなり時間がかかりそうだぜ。";
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_35x":
			PlaySound("Voice\English\LE\SeaFox\SeaFox_05.wav");
			dialog.text = "ご協力ありがとうございます、船長！あなたは "+GetSexPhrase("本物の英雄のように振る舞った","とても勇敢な若い女性だ")+", "+GetAddress_Form(NPChar)+"！グレトン中尉が生き残れなかったのは悲劇だ。本物の紳士であり、イングランドの息子として亡くなったんだ。 フォックス大佐に報告する間、もう一日ここに滞在させてほしい。明日、大佐の執務室を訪ねてくれ。総督宮殿にあるぞ。 ";
			link.l1 = "よし。ちゃんと割に合うようにしてくれよ。お前のせいでオランダ人との評判を回復するのに時間がかかるんだからな。";
			link.l1.go = "seafox_36";
		break;
		
		case "seafox_36":
			dialog.text = "「心配するな、」 "+GetAddress_Form(NPChar)+"。報告書にはできる限り最高の評価を書きます。（敬礼）お会いできて光栄でした、 "+GetAddress_Form(NPChar)+"!";
			link.l1 = "...";
			link.l1.go = "seafox_37";
		break;
		
		case "seafox_37":
			DialogExit();
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "none", "", "", "", -1);
			pchar.quest.FMQN_eng_reward.win_condition.l1 = "Timer";
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_eng_reward.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_eng_reward.function = "FMQN_EnglandReward";
			AddQuestRecord("FMQ_Nevis", "28");
		break;
		
		case "soldier":
			PlaySound("Voice\English\soldier_common_2.wav");
			dialog.text = "Captain "+GetFullName(pchar)+"?";
			link.l1 = "ふむ……ああ、俺に何か用か？";
			link.l1.go = "soldier_1";
		break;
		
		case "soldier_1":
			dialog.text = "港役所からあなたの船の最近の到着について連絡があった。フィリップスバーグ総督、 マルティン・トーマス閣下があなたにお会いしたいそうだ。";
			link.l1 = "何のためだ？俺は逮捕されたのか？";
			link.l1.go = "soldier_2";
		break;
		
		case "soldier_2":
			AddLandQuestMark(characterFromId("Marigo_Mayor"), "questmarkmain");
			dialog.text = "「いやいや、」 "+GetAddress_Form(NPChar)+" 船長、あんたは逮捕されてるわけじゃねえ。総督の命令で、新しく着いた船長はみんな総督の宮殿に招かれて、 コーヒーでも飲みながら顔合わせをすることになってるんだ。ついてきな！";
			link.l1 = "断れねえ申し出みてえだな。案内してくれ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_ReloadToGovernor");
		break;
		
		case "hol_officer":
			PlaySound("Voice\English\hol_gov_complete.wav");
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+"「おい、どこであのイギリス兵を見たか案内しろ。」";
			link.l1 = "奴らはジャングルの洞窟に隠れてやがる、まるでただの野盗みてえにな。";
			link.l1.go = "hol_officer_1";
		break;
		
		case "hol_officer_1":
			dialog.text = "先導してくれ、俺たちはついていくぜ！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleMarch");
		break;
		
		case "hol_officer_2":
			PlaySound("Voice\English\hol_gov_quest.wav");
			dialog.text = "待ってくれ、船長！あんたが言ってたスパイたちに会ったのは、あそこの洞窟の入口付近だったのか？";
			link.l1 = "ああ。奴らが俺に話しかけた後、中に入っていくのをちらっと見たぜ。";
			link.l1.go = "hol_officer_3";
		break;
		
		case "hol_officer_3":
			dialog.text = "たぶん、まだあそこにいるはずだ。一気に突っ込んだら、奴らは洞窟の中に逃げ込むだろう。そうなったら、 引きずり出すのは悪夢だぜ……ここは頭を使おう。船長、お前が一人で行って奴らの気を引いてくれ。俺と部下たちは、 角を曲がったところの干上がった井戸まで移動する。あれは洞窟の中に直接つながってるんだ。あの野郎どもは、 俺たちが背後から来るなんて思いもしねえだろう\nお前は中に入って、もしスパイどもがまだいたら、くだらねえ質問でもして時間を稼げ。 奴らの注意を完全に引きつけたら――できるだけ下品に罵れ。お前は船乗りだ、自然にできるだろう。それが合図だ。俺の部下二人が正面入口を見張って、 奴らの逃げ道を塞ぐ。これで奴らを捕まえられる。";
			link.l1 = "あんたの計画は俺の命にとっちゃやけに危なそうだぜ。俺の考えじゃ、まず最初に殺されるのは俺だろうな。";
			link.l1.go = "hol_officer_4";
		break;
		
		case "hol_officer_4":
			dialog.text = "心配するな、船長。敵の襲撃隊を見つけたら、できるだけ大声で叫ぶのがあんたの役目だ。もし攻撃されたら、 とにかく逃げながら叫び続けろ。俺の部下たちは鍛えられてるから安心しな、 あんたが傷つく前にスパイどもを片付けてくれるさ。";
			link.l1 = "そうしてもらわないとな。俺はこれから中に入るぜ。";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattlePosition");
		break;
		
		case "hol_officer_5":
			PlaySound("Voice\English\hol_gov_common.wav");
			dialog.text = "あいつらは手強い野郎どもだったな……やるじゃねえか、船長、イギリス野郎どもは片付いたぜ。破壊工作員も始末したし、司令官と総督も喜ぶだろうよ。";
			link.l1 = "のんびりしてたな、旦那……";
			link.l1.go = "hol_officer_6";
		break;
		
		case "hol_officer_6":
			dialog.text = "ロープのせいだ、先にバケツがついてて、ものすごい音を立てやがったんだ。 俺たちは気をつけなきゃならなかったんだぜ。";
			link.l1 = "ああ…ロープのことか。どうでもいいぜ。お前の行方不明になってた巡回兵のひとりが、あそこの茂みに縛られてる。 まだ生きてるはずだ。";
			link.l1.go = "hol_officer_7";
		break;
		
		case "hol_officer_7":
			dialog.text = "俺があいつらの面倒を見ておく。お前は町に行って休んでこい。明日、総督のところに顔を出せばいいさ。その頃には、 俺が書いたお前の手柄を褒め称える報告書が届いてるはずだぜ。";
			link.l1 = "そうするぜ。ご武運を、旦那。";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQN_HollandBattleRest");
		break;
		
		case "monk":
			DelLandQuestMark(npchar);
			DelLandQuestMarkToPhantom();
			if (GetCharacterIndex("marigojailoff") != -1)
			{
				DelLandQuestMark(characterFromId("marigojailoff"));
			}
			pchar.questTemp.FMQN = "way_eng_2";
			dialog.text = "「どうしたんだ、息子よ？」";
			link.l1 = "やあ神父さん、ちょっと気になるんだが、捕虜の水夫たちはいつ告解したんだ？";
			link.l1.go = "monk_1";
		break;
		
		case "monk_1":
			dialog.text = "昨日の夕方だ、息子よ……（小声で）計画が裏切られたことは知っているな？";
			link.l1 = "そうでなければ、俺はここに立っていないさ。カスパー・グラットン中尉とその部下たちは今、ジャングルにいる。 全員オランダ兵の格好をしてるが、看守どもが奴らを待ち構えてるから、追加の助けが必要なんだ。";
			link.l1.go = "monk_2";
		break;
		
		case "monk_2":
			dialog.text = "（大声で）奴の英国国教徒の魂が地獄に堕ちないよう、毎日祈っていたんだ！\n（小声で）策はあるが、必要な物を揃えるには金のドゥブロン金貨が二ダース要るんだ。";
			link.l1 = "高くつく計画だな。金は何に使うんだ？";
			link.l1.go = "monk_3";
		break;
		
		case "monk_3":
			dialog.text = "牢番なんて退屈な仕事さ。士気を保つために、責任者は毎晩夕食に合わせてワインを注文するんだ。そのワインは、 俺が出入りできる倉庫から運ばれてくる。町には俺に借りがあるジプシー女がいてな、あいつが眠り薬を作ってくれる。 あとは良いワインを何本か買って、その薬を混ぜて、倉庫のボトルとすり替えればいい。それで金が必要なんだ。";
			if (PCharDublonsTotal() >= 24)
			{
				link.l1 = "ドブロン金貨は持ってる。受け取れ。";
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = "俺の船に戻って、少し持ってきてやるぜ。";
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_wait":
			DialogExit();
			npchar.dialog.currentnode = "monk_repeat";
		break;
		
		case "monk_repeat":
			dialog.text = "ああ、息子よ、例の「寄付金」は持ってきたか？";
			if (PCharDublonsTotal() >= 24)
			{
				link.l1 = "「ああ、ここだ。」";
				link.l1.go = "monk_4";
			}
			else
			{
				link.l1 = "そのうち手に入れてやるさ……";
				link.l1.go = "monk_wait";
			}
		break;
		
		case "monk_4":
			RemoveDublonsFromPCharTotal(24);
			dialog.text = "素晴らしい。明日も同じ時間に私のところへ来てくれ——結果を伝えるぞ。";
			link.l1 = "「よし…」";
			link.l1.go = "monk_5";
		break;
		
		case "monk_5":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("FMQ_Nevis", "18");
			pchar.quest.FMQN_monk.win_condition.l1 = "Timer";
			pchar.quest.FMQN_monk.win_condition.l1.date.hour  = 6.0;
			pchar.quest.FMQN_monk.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_monk.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_monk.function = "FMQN_EnglandMonkPlan";
			pchar.quest.FMQN_fail.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail.win_condition.l1.date.hour  = 11.0;
			pchar.quest.FMQN_fail.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.FMQN_fail.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.FMQN_fail.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_3";
		break;
		
		case "monk_6":
			DelLandQuestMark(npchar);
			pchar.quest.FMQN_fail.over = "yes";
			dialog.text = "「やあ、息子よ。」";
			link.l1 = "あんたもだよ、神父。何か新しい話はあるか？";
			link.l1.go = "monk_6x";
		break;
		
		case "monk_6x":
			dialog.text = "ああ、終わったぜ。ワインには“味付け”をしておいたから、今夜は衛兵どもに特別なご馳走だ。あいつらは夜九時に夕食を取るから、 真夜中には全員眠ってるはずだ。これが仕事をやる唯一のチャンスだ、二度目はねえぞ。気をつけろよ、 オランダ人の変装だけに頼りきるのは危険だぜ。";
			link.l1 = "了解だ。無駄にしてる暇はねえ。じゃあな。";
			link.l1.go = "monk_7";
		break;
		
		case "monk_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("FMQ_Nevis", "20");
			sld = CharacterFromID("FMQN_seafox_1");
			sld.dialog.currentnode = "seafox_26";
			LAi_CharacterEnableDialog(sld);
			sld.talker = 9;
			AddLandQuestMark(sld, "questmarkmain");
			pchar.quest.FMQN_fail1.win_condition.l1 = "Timer";
			pchar.quest.FMQN_fail1.win_condition.l1.date.hour  = 20.0;
			pchar.quest.FMQN_fail1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.FMQN_fail1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.FMQN_fail1.function = "FMQN_EnglandFail";
			pchar.questTemp.FMQN = "way_eng_4";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
