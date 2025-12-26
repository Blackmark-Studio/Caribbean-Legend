void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arTmp;
	int i, n;
	string sTemp, sStr;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "何の用だ？";
			link.l1 = "「何もない。」";
			link.l1.go = "exit";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "AlonsoNaPalube":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_AlonsoNaPalube"))
			{
				pchar.questTemp.LadyBeth_AlonsoNaPalube2 = true;
				dialog.text = "どうなさいますか、船長？やめておいたほうがいいのでは？";
				link.l1 = "その任務のために、さらに志願者を集めることができたか？";
				link.l1.go = "AlonsoNaPalube_StrongGroup";
			}
			else
			{
				pchar.questTemp.LadyBeth_AlonsoNaPalube = true;
				dialog.text = "船長、ちょっと話がある。";
				link.l1 = "「報告しろ、アロンソ。」";
				link.l1.go = "AlonsoNaPalube_2";
			}
			locCameraFromToPos(-10.33, 9.69, -22.16, true, -5.22, 7.19, -21.06);
		break;
		
		case "AlonsoNaPalube_2":
			dialog.text = "乗組員たちはお前がカイマンで何をするつもりか気にしてるぜ。皆、不安がってるんだ。";
			link.l1 = "まだ決めてねえよ。それに、なんで奴らが心配してるんだ、アロンソ？";
			link.l1.go = "AlonsoNaPalube_3";
		break;
		
		case "AlonsoNaPalube_3":
			dialog.text = "この島はブラックウッド船長の縄張りだ。\n船乗りたちの話じゃ、あいつは取り憑かれたように島中を掘り返してるらしい。\n発掘で何十人もの男を潰したってな……\nそして奴の元を離れた連中は、妙な話をするんだ。";
			link.l1 = "どんな話だ？";
			link.l1.go = "AlonsoNaPalube_4";
		break;
		
		case "AlonsoNaPalube_4":
			dialog.text = "ブラックウッドはもう昔の彼じゃねえ。今は征服者の財宝に取り憑かれてやがる。そのためなら何もかも、 誰であろうと犠牲にする覚悟だ。お前が面白そうな話に首を突っ込むのが好きなのも、 ひとりで上陸して罠にかかるのも知ってるぜ……だが、今回はそう簡単には抜け出せねえぞ。";
			link.l1 = "報告と警告、感謝するぜ。もし上陸を決めたら、俺が先陣を切って、精鋭の戦闘員を連れて行くからな。";
			link.l1.go = "AlonsoNaPalube_5";
		break;
		
		case "AlonsoNaPalube_5":
			dialog.text = "それは難しいかもしれませんぜ、船長。拿捕はともかく、上陸して海兵の銃弾や、 ブラックウッドが小アンティル諸島のあらゆる穴から雇ったっていうクズどものサーベルの下をくぐるとなりゃ話は別だ。 \nそれにカイマンには悪い噂もある……いや、そんな仕事に志願する奴はそうそういませんぜ。";
			link.l1 = "なら、使える奴を誰でも使うしかねえな。アロンソ、お前の参加は絶対だぞ。";
			link.l1.go = "AlonsoNaPalube_LiteGroup";
			link.l2 = "俺の考えじゃ、証明できることはもう全部みんなに見せてやったはずだ。\n腕の立つ戦士と射撃手は全員行くんだ。これは命令だぜ。";
			link.l2.go = "AlonsoNaPalube_StrongGroup";
			link.l3 = "ふむ……まあ、少し考えさせてくれ。たぶんこの話はまた後で戻ることになるだろう。";
			link.l3.go = "AlonsoNaPalube_Exit";
		break;
		
		case "AlonsoNaPalube_Exit":
			SetFunctionLocationCondition("LadyBeth_CaimanSea", "Caiman", false);
			EndQuestMovie();
			bQuestDisableMapEnter = false;
			chrDisableReloadToLocation = false;
			if(UnloadLocation(loadedLocation) == true)
			{
				pchar.Ship.Pos.x = 0;
				pchar.Ship.Pos.z = 0;
				pchar.Ship.Ang.y = 0;
				Land_MapLoad();
				pchar.location = "";
			}
		break;
		
		case "AlonsoNaPalube_LiteGroup":
			dialog.text = "ああ、船長！";
			link.l1 = "ブラックウッドの船はどうするんだ？問題にならねえか？";
			link.l1.go = "AlonsoNaPalube_Vpered";
			pchar.questTemp.LadyBeth_LiteGroup = true;
		break;
		
		case "AlonsoNaPalube_StrongGroup":
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 40 || sti(pchar.rank) >= 12)
			{
				dialog.text = "ああ、船長！";
				link.l1 = "ブラックウッドの船はどうするんだ？問題にならねえか？";
				link.l1.go = "AlonsoNaPalube_Vpered";
				pchar.questTemp.LadyBeth_StrongGroup = true;
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) >= 40) Notification_Skill(true, 40, SKILL_LEADERSHIP);
				if (sti(pchar.rank) >= 12) Notification_Level(true, 12);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LadyBeth_AlonsoNaPalube2"))
				{
					dialog.text = "残念ながら、まだです、船長。";
				}
				else
				{
					dialog.text = "俺や士官たちには証明することなんて何もねえし、命令通りにどこへでもついていくぜ。\nだが、普通の水夫たちはそうは思っちゃいねえ。問題が起きるかもしれねえな、船長。";
				}
				link.l1 = "それなら、使える奴で何とかするしかねえな。アロンソ、お前の参加は必須だぞ。";
				link.l1.go = "AlonsoNaPalube_LiteGroup";
				link.l2 = "ふむ……まあ、じっくり考えなきゃならねえな。たぶんこの話は後でまた戻ることになるだろう。";
				link.l2.go = "AlonsoNaPalube_Exit";
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 40) Notification_Skill(false, 40, SKILL_LEADERSHIP);
				if (sti(pchar.rank) < 12) Notification_Level(false, 12);
			}
		break;
		
		case "AlonsoNaPalube_Vpered":
			dialog.text = "スノー船だ。美人で気性が荒いって評判だぜ。あいつのことは心配いらねえよ。たぶん乗組員全員が陸でこき使われてて、 船は海岸の入り江にしっかり隠してあるだろうさ。俺たちが勝ったら、 その船を岸から戦利品としていただこうじゃねえか。\n";
			link.l1 = "野郎どもを集めろ。今日はいい日だ――運は俺たちの味方だぜ。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_AlonsoNaPalube_Vpered");
		break;
		
		// Диалог в таверне с Блеквудом
		case "LadyBeth_DialogInCity": // главное меню
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Fourth"))
			{
				dialog.text = "お会いできて嬉しいです、船長。もう全て話し合ったと思いますが…。";
				link.l1 = "確かに。さらばだ。";
				link.l1.go = "exit";
				NextDiag.TempNode = "LadyBeth_DialogInCity_again";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Third"))
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+", "+npchar.name+"";
				link.l1.go = "LadyBeth_DialogInCity_Third_2";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+"「ブラックウッド船長。」";
				link.l1.go = "LadyBeth_DialogInCity_Second_1";
				break;
			}
			if (startHeroType == 4)
			{
				dialog.text = "...";
				link.l1 = "こんにちは。あなたがブラックウッド船長か？";
				link.l1.go = "LadyBeth_DialogInCity_First_Helena_1";
			}
			else
			{
				dialog.text = "...";
				link.l1 = ""+TimeGreeting()+"。お前がアルバート・ブラックウッド船長で間違いねえか？";
				link.l1.go = "LadyBeth_DialogInCity_First_1";
			}
		break;
		
		case "LadyBeth_DialogInCity_again": // повтор
			dialog.text = "お会いできて嬉しいです、船長。もう全て話し合ったと思います。";
			link.l1 = "確かに。さらばだ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "LadyBeth_DialogInCity_again";
		break;
		
		case "LadyBeth_DialogInCity_First_1": // первый диалог
			dialog.text = "ああ、俺だよ。で、お前は？";
			link.l1 = "Captain "+GetFullName(pchar)+"。俺は『" + PChar.Ship.Name + "「。」";
			link.l1.go = "LadyBeth_DialogInCity_First_2";
		break;
		
		case "LadyBeth_DialogInCity_First_2":
			dialog.text = "船長……カイマンに行ったことがあるか？";
			link.l1 = "通りかかっただけだ。";
			link.l1.go = "LadyBeth_DialogInCity_First_3";
		break;
		
		case "LadyBeth_DialogInCity_First_3":
			dialog.text = "あそこに宝の噂を聞いたことがあるか？";
			link.l1 = "いや、特に何もないぜ。";
			link.l1.go = "LadyBeth_DialogInCity_First_4";
		break;
		
		case "LadyBeth_DialogInCity_First_4":
			dialog.text = "スペイン人の痕跡か？古い武器か？征服者時代のコインか？";
			link.l1 = "そんなものは見つからなかった。";
			link.l1.go = "LadyBeth_DialogInCity_First_5";
		break;
		
		case "LadyBeth_DialogInCity_First_5":
			dialog.text = "地元の伝説か？コルテスの話か？埋葬に関することは何か知らねえか？";
			link.l1 = "申し訳ありません、船長。でもそんな情報は持っていません。それに、もう尋問みたいになってきましたね。";
			link.l1.go = "LadyBeth_DialogInCity_First_6";
		break;
		
		case "LadyBeth_DialogInCity_First_6":
			dialog.text = "申し訳ない……元士官の悪い癖だ。だが……これは俺にとって本当に大事なことなんだ。";
			link.l1 = "「なぜお前はカイマンにそんなにこだわるんだ？」";
			link.l1.go = "LadyBeth_DialogInCity_First_7";
		break;
		
		case "LadyBeth_DialogInCity_First_7":
			dialog.text = "重要じゃねえ。改めて謝るぜ。";
			link.l1 = "承知した。探索の幸運を祈る。";
			link.l1.go = "LadyBeth_DialogInCity_First_8";
		break;
		
		case "LadyBeth_DialogInCity_First_8":
			if (GetHour() >= 23 || GetHour() < 6) sStr = "Good night";
			else sStr = "Wishing you a good day";
			dialog.text = "何か価値のあるものを見つけたら、俺のところに来てくれ。\n他の船長――海を理解する者と語り合うのは楽しいからな。 " + sStr + ".";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "LadyBeth_DialogInCity_First_9";
		break;
		
		case "LadyBeth_DialogInCity_First_9":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_1": // первый диалог с Элен
			dialog.text = "ご本人か。そして……お前がヘレン・マッカーサー船長だな？ヤン・スヴェンソンの弟子ってやつだろ？噂は聞いてるぜ。";
			link.l1 = "よくご存知ですね、ブラックウッド船長。しかし、イギリスの士官が俺のことを知っていても驚きはしませんよ。";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_2";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_2":
			dialog.text = "元士官だな。そして赤服どもはみんな、お前とその…王室からの特別なご趣味について知ってるぜ。アイアンウッドは、臭わねえって話さ。\nそれに、お前の親父ショーン・マッカーサーが子供の頃からお前を海に連れて行き、船長にしたって話は、 艦隊じゃちょっとした伝説になってるぜ。";
			link.l1 = "「この伝説と出会った気分はどうだ？」";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_3";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_3":
			dialog.text = "俺は個人的に感心してるぜ。だが、正直言って、昔の同僚たちの多くはかなり苛立ってるみたいだ。\nだが、船長になるには貴族の血筋や王の任命状だけじゃ足りねえだろ？";
			link.l1 = "その通りだ。知識と経験、そして常に自分の腕前を証明する覚悟が必要なんだ。特に俺の場合はな。";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_4";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_4":
			dialog.text = "その通りだ！海でも人生でも、大事なのは肩書きじゃなくて結果だぜ。初めまして、マッカーサー船長。 いつかまた会えるといいな。遠征から戻ったら、ワインでも一杯どうだ？\n";
			link.l1 = "たぶんね。探索の幸運を祈るぜ、船長。";
			link.l1.go = "LadyBeth_DialogInCity_First_Helena_5_harizma";
			link.l2 = "興味はねえ。でも、探索がうまくいくことを祈ってるぜ、船長。";
			link.l2.go = "LadyBeth_DialogInCity_First_Helena_5_oruzhie";
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_5_harizma":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_DialogInCity_First_Helena_5_oruzhie":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Second = true;
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Second_1": // второй диалог
			dialog.text = "ああ、船長 "+pchar.lastname+"！会えて嬉しいぜ。座りたいか？";
			link.l1 = "喜んで。";
			link.l1.go = "LadyBeth_DialogInCity_Second_2";
		break;
		
		case "LadyBeth_DialogInCity_Second_2":
			dialog.text = "船長……教えてくれ、本物の財宝ってお前にとって何なんだ？";
			link.l1 = "本当の宝は愛だ。そばにいるべき相手がいることさ。\nひとりぼっちほど辛いものはねえぜ。";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_love";
			link.l2 = "金さ、もちろん。他に宝になるものがあるか？";
			link.l2.go = "LadyBeth_DialogInCity_Second_3_sokrovisha";
			link.l3 = "貴重で唯一無二の装備だ。\n良い剣やピストルは金よりも価値があるぜ。";
			link.l3.go = "LadyBeth_DialogInCity_Second_3_oruzhie";
			link.l4 = "知識――一番貴重な宝は頭の中にあるものだ。";
			link.l4.go = "LadyBeth_DialogInCity_Second_3_znania";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love":
			if (startHeroType == 4)
			{
				dialog.text = "愛か？ふむ……海賊の娘からそんな答えが返ってくるとは思わなかったよ。俺は……俺は婚約していたんだ。エリザベスと。バルバドスのプランテーションオーナーの娘さ。だが、あいつの父親がな……俺には金が足りないと決めつけた。俺の愛以外に、彼の娘に何を与えられるっていうんだ？あんたは運が良かったな、 マッカーサー船長。あんたの父親は、持参金よりもあんたの才能を評価してくれたんだからな。";
				link.l1 = "運じゃなくて、本当の愛は金じゃ測れないってことかもしれないわ。私の父はそれを理解していたの。 あなたの婚約者はどう？彼女も父親と同じ考えなのかしら？";
				link.l1.go = "LadyBeth_DialogInCity_Second_3_love_Helena_1";
			}
			else
			{
				dialog.text = "愛か？ああ……もしかしたら、お前の言う通りかもしれねえ。俺は……婚約してたんだ。バルバドスでな。お互いに愛し合ってた、でも……彼女の親父が俺をふさわしくねえって言いやがった。はっ！金が足りねえってさ。だから俺はここにいる――奴らが間違ってたって証明するために財宝を探してるんだ。無駄なことかもしれねえがな？";
				link.l1 = "彼女と直接話せばいいんじゃねえか？あんなプランテーションの地主なんざ、くそくらえだ。";
				link.l1.go = "LadyBeth_DialogInCity_Second_3_love_2";
			}
			AddComplexLandExpToScill(100, 100, 0);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_2":
			dialog.text = "話すか……ああ、たしかに。だが、何を言えばいい？「すまない、まともな人生を与えてやれなかった」ってか？違う。 俺は勝者として戻らなきゃならねえ。さもなきゃ、二度と戻らねえ。";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_Helena_1":
			dialog.text = "エリザベス？いや……彼女は俺を愛してくれている。だが……俺は、彼女を貧困の中で生きさせるわけにはいかなかった。彼女にはもっとふさわしい人生があるべきだ。そして俺は、 彼女にふさわしい男だと証明しなければならないんだ。";
			link.l1 = "「時には誇りが貧しさよりも幸せを妨げることがあるんだぜ、船長。」";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_love_Helena_2";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_love_Helena_2":
			dialog.text = "手ぶらでは戻れないんだ。どうしても無理だ。すまない、仕事が山ほどあるんだ。君と話せて楽しかったよ、MacArthur船長。";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_5";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_sokrovisha":
			dialog.text = "なんてありきたりな答えだ。しかし、反論しにくいな。確かに、ブリストルのスラムで育ち、 残飯を巡って争わなきゃならなかった時代を思えば……金の本当の価値がわかってくる。贅沢じゃねえ。自由だ。あの泥まみれの底辺から、 やっとの思いで這い上がった場所に二度と戻らずに済む力さ。";
			link.l1 = "同感だ。金があれば大抵の問題は解決する。\nそれでも解決しないなら、単に金が足りねえってことさ。";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_sokrovisha_2";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_sokrovisha_2":
			dialog.text = "その通りだ！わかってるじゃねえか。金が幸せを運ぶわけじゃねえが、金がなきゃ確実に不幸になるんだよ。 俺はそれを痛いほど知ってるんだ……";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_oruzhie":
			dialog.text = "面白いな。実用的だ。俺は火縄銃を持ってる……本物だぜ、征服者たちの時代のやつだ。ある神父からの贈り物さ。時々、 見つけた金銀財宝全部より価値があるんじゃねえかって思うこともある。だが……俺の問題はそれじゃ解決しねえんだよ。";
			link.l1 = "良い武器があれば、多くの問題は解決できる。\nそして武器は決して裏切らないぜ。";
			link.l1.go = "LadyBeth_DialogInCity_Second_3_oruzhie_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Second_3_oruzhie_2":
			dialog.text = "それは確かに一理ある。だが、武力だけでは勝てない戦もあるんだ。";
			link.l1 = "...";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
		break;
		
		case "LadyBeth_DialogInCity_Second_3_znania":
			dialog.text = "知識……ああ、わかってるさ。征服者たちや財宝について、できる限りのことは勉強した。 宝探しのためのマニュアルも丸ごと作り上げた。船の銃士隊のために、定期訓練と物質的な報酬制度まで考案したんだ。 どんな船長だって俺のマニュアルを欲しがるだろうさ。\nだが、こんな知識も……結果につながらなければ無意味だ。本当の結果にな。";
			link.l1 = "だが、結果を出すのに役立つのは知識だ。知識がなければ、どんな探索もただの暗闇の中の彷徨に過ぎねえ。";
			link.l1.go = "LadyBeth_DialogInCity_Second_4";
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "LadyBeth_DialogInCity_Second_4":
			if (GetHour() >= 23 || GetHour() < 6) sStr = "Well, it's already late, and I have a lot of work to do";
			else sStr = "Well, I have a lot of work to do";
			dialog.text = "" + sStr + "。話をしてくれてありがとう、船長。実に興味深かった。";
			link.l1 = "こちらこそ、ありがとう。 "+Goodbye(true)+".";
			link.l1.go = "LadyBeth_DialogInCity_Second_5";
		break;
		
		case "LadyBeth_DialogInCity_Second_5":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Third = true;
		break;
		
		case "LadyBeth_DialogInCity_Third_2": // третий диалог
			dialog.text = "「あっ、」 "+pchar.name+"！会えて嬉しいぜ。素晴らしい知らせがあるんだ――ついに俺の問題の解決策を見つけたんだよ。もうすぐ遠征に出発するが、今度こそ本物の財宝を持って帰ってくるぜ！\nところで、ひとつ忠告しておく。カイマンには近づくなよ。今は俺の縄張りだからな。";
			link.l1 = "カイマンはお前のものじゃねえぞ、アルバート。お前には王冠の権利なんてねえんだ。それは海賊行為だぜ。";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_harizma";
			link.l2 = "俺を脅してるのか、Blackwood？";
			link.l2.go = "LadyBeth_DialogInCity_Third_3_oruzhie";
		break;
		
		case "LadyBeth_DialogInCity_Third_3_harizma":
			dialog.text = "王権だと？ブリストルのスラムで暮らしてみりゃよかったんだぜ、 "+pchar.name+"、そうすりゃこの書類がどれほどの価値か分かるはずだ。腹が減ってりゃ、法なんて意味ねえよ。だが……お前の言う通りだ。形式上、俺には島の権利なんてねえ。だが、俺はあそこで何年も探し続けてきたものを見つけたんだ。 それを誰にも奪わせやしねえ。";
			link.l1 = "お前が危険な道を進んでいること、わかっているだろうな。";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_harizma_2";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_DialogInCity_Third_3_harizma_2":
			dialog.text = "俺の道が楽じゃねえことは、最初から分かってたさ。じゃあな、 "+pchar.name+"……また会うこともあるかもしれねえな。";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "LadyBeth_DialogInCity_Third_4";
		break;
		
		case "LadyBeth_DialogInCity_Third_3_oruzhie":
			dialog.text = "脅してる？いや、全然そんなことはないさ。ただ、船長同士の親切な忠告だ。カイマンは危険な場所だぜ……特に俺の邪魔をする奴にはな。";
			link.l1 = "「忠告」覚えておくぜ。カイマンでの幸運を祈る。";
			link.l1.go = "LadyBeth_DialogInCity_Third_3_oruzhie_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_DialogInCity_Third_3_oruzhie_2":
			dialog.text = "健闘を祈るぜ、船長。運なんて必要ないといいがな。じゃあな。";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "LadyBeth_DialogInCity_Third_4";
		break;
		
		case "LadyBeth_DialogInCity_Third_4":
			DialogExit();
			
			NextDiag.CurrentNode = "LadyBeth_DialogInCity_again";
			pchar.questTemp.LadyBeth_DialogInCity_Fourth = true;
		break;
		
		// Ловушка, абордаж в каюте
		case "LadyBeth_abordage":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "お前か？！俺が降伏すると思ってるのか？また貧乏に戻ると思ってるのか？ 二度とスラムで飢え死にするくらいなら死んだ方がマシだ！容赦も、報酬も、勝利もねえ！\nベッドの下に火薬樽がある……全員まとめて海の底だ！";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("LadyBeth_Lovushka");
			}
			else
			{
				dialog.text = "俺に攻撃するとは何者だ！？俺が降伏すると思うのか？いやだ！またスラムで飢えるくらいなら死んだほうがマシだ！ 容赦も報酬も勝利もねえ！ベッドの下に火薬樽がある……全員まとめて海の底行きだ！";
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("LadyBeth_Lovushka");
			}
		break;
		
		// Блеквуд разговаривает с ГГ перед битвой на Каймане
		case "LadyBeth_BlackWood_Boss":
			if (CheckAttribute(pchar, "questTemp.LadyBeth_DialogInCity_Second"))
			{
				dialog.text = "船長！警告したはずだぜ。今度はその好奇心の代償を払ってもらうぞ。";
			}
			else
			{
				dialog.text = "貴様は何者だ、そして俺の縄張りにどうして土足で踏み込んできやがった！？この島は俺のものだ！";
			}
			link.l1 = "見ていようじゃねえか、Blackwood。今日、この世から狂気に取り憑かれた奴が一人減ることになるぜ。";
			link.l1.go = "LadyBeth_BlackWood_Boss_oruzhie_1";
			link.l2 = "穏便に済ませようぜ、Blackwood。俺は立ち去ることもできる。";
			link.l2.go = "LadyBeth_BlackWood_Boss_torgovlya_1";
			link.l3 = "ブラックウッド、お前は分別のある男だろう！お前は士官じゃねえか！お前の陣営には王家の旗が掲げられてるんだ、 頼むぜ！どうにか話し合いで解決できねえのか？";
			link.l3.go = "LadyBeth_BlackWood_Boss_harizma_1";
		break;
		
		case "LadyBeth_BlackWood_Boss_oruzhie_1":
			dialog.text = "「取り憑かれてる？はっ！俺はただ自分の欲しいものが分かってる男だぜ！」";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
			AddComplexSelfExpToScill(50, 50, 50, 50);
		break;
		
		case "LadyBeth_BlackWood_Boss_torgovlya_1":
			dialog.text = "去るだと？お前が見たものの後で？いや、いや、いや！ここで俺が見つけたことは誰にも知られちゃいけねえ。誰にもだ！ ";
			link.l1 = "誰にも言わないと誓うぜ。船長の名誉にかけて誓う。";
			link.l1.go = "LadyBeth_BlackWood_Boss_torgovlya_2";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		break;
		
		case "LadyBeth_BlackWood_Boss_torgovlya_2":
			dialog.text = "この世に名誉なんてねえんだよ、船長。あるのは汚れと貧困、そして軽蔑だけだ。残念だが、ここで死んでもらうぜ。";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
		break;
		
		case "LadyBeth_BlackWood_Boss_harizma_1":
			dialog.text = "考えたんだ。たくさん考えた。そんで気づいた――これが俺の唯一のチャンスだってな。コルテスの黄金を見つけるか、それとも……何もない。わかるか？何もだ！昔の生活には戻らねえ！汚れと貧乏には戻らねえ！ここで死んだほうがマシだ！";
			link.l1 = "...";
			link.l1.go = "LadyBeth_BlackWood_Boss_2";
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		case "LadyBeth_BlackWood_Boss_2":
			dialog.text = "戦闘開始だ！ブルロック、フレーザー、奴らが近づいたらブドウ弾を撃て！ホプキンス、突撃しろ！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_CaimanKino_11");
		break;
		
		// Диалоги с офицерами
		case "LadyBeth_Helena_1": // Элен
			dialog.text = "大丈夫か？";
			link.l1 = "ああ、大丈夫だ。そっちはどうだ？";
			link.l1.go = "LadyBeth_Helena_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Helena_2":
			dialog.text = "生きてるぜ。でも陸での戦いは俺の性に合わねえ。甲板の上ならどんな船でもぶっ壊してやるが、ここは……妙な場所だ。百人の海の狼どもを上陸させて、ツルハシ振らせて、砦を作らせるなんて……俺には無理だな。";
			link.l1 = "ブラックウッドは自分の船員たちを鼓舞する術を知っていた。";
			link.l1.go = "LadyBeth_Helena_3";
		break;
		
		case "LadyBeth_Helena_3":
			dialog.text = "ブルーフィールドで彼のことを聞いたぜ。多くのイギリス人船乗りが彼を敬意をもって語っていた。艦隊で一番の士官、 輝かしい経歴……それが突然、すべてを捨てて宝探しに走ったんだ。";
			link.l1 = "あいつのことをどう思う？";
			link.l1.go = "LadyBeth_Helena_4";
		break;
		
		case "LadyBeth_Helena_4":
			dialog.text = "ブラックウッドの例は、俺たち……いや、あなたが部下たちの前で背負う責任の重さをはっきり示していると思う。どうか、 彼のような船長にはならないでくれ。";
			link.l1 = " やってみるよ、ヘレン。";
			link.l1.go = "LadyBeth_Helena_5";
		break;
		
		case "LadyBeth_Helena_5":
			dialog.text = "ありがとうございます、俺の船長。きっと成功してくれると信じてるぜ。";
			link.l1 = "やるぜ。";
			link.l1.go = "LadyBeth_Helena_6";
		break;
		
		case "LadyBeth_Helena_6":
			dialog.text = "俺たちがやるぜ。";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Helena_7";
		break;
		
		case "LadyBeth_Helena_7":
			DialogExit();
			ReturnOfficer_Helena();
		break;
		
		case "LadyBeth_Mary_1": // Мэри
			dialog.text = "「チャールズ……ここはなんて恐ろしい場所なの。」";
			link.l1 = "メアリー、大丈夫か？まるで本物の兵士みたいにしっかりしてたな。";
			link.l1.go = "LadyBeth_Mary_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Mary_2":
			dialog.text = "いや、全然大丈夫じゃねえよ。見てみろ、この連中を！こいつらは死ぬほど働かされて、飢えに苦しみ、 病気で死んでいった……それで何のためだ？存在するかも分からねえ金のためだぞ。";
			link.l1 = "ブラックウッドはここだと信じていた。";
			link.l1.go = "LadyBeth_Mary_3";
		break;
		
		case "LadyBeth_Mary_3":
			dialog.text = "この赤いコート……まるで俺のと同じだ。イギリスの士官……なあ、急に親父とおふくろのことを思い出しちまったんだ。自分のルーツ……知らなかったことについてもな。もしかして、俺もあいつらの一人なのか？";
			link.l1 = "「その一人か？」";
			link.l1.go = "LadyBeth_Mary_4";
		break;
		
		case "LadyBeth_Mary_4":
			dialog.text = "存在するかどうかも分からないものを求めてさまよう者たちさ。\nそして、その探索の中で自分自身を見失うんだ。\n俺は……この話はまた後でしよう。\nこの忌々しい場所を出てからな。";
			link.l1 = "もちろんだよ、メアリー。";
			link.l1.go = "LadyBeth_Mary_5";
		break;
		
		case "LadyBeth_Mary_5":
			dialog.text = "まずは彼を埋葬しよう、頼むよ？たとえ彼にその価値がなくても。かつての彼のためにさ。";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Mary_6";
		break;
		
		case "LadyBeth_Mary_6":
			DialogExit();
			ReturnOfficer_Mary();
		break;
		
		case "LadyBeth_Tichingitu_1": // Тичингиту
			dialog.text = "船長、ティチンギトゥはここが悪い場所だと見てる。とても悪い場所だ。";
			link.l1 = "どういう意味だ？";
			link.l1.go = "LadyBeth_Tichingitu_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Tichingitu_2":
			dialog.text = "この島は今や呪われているぜ。大地があまりにも多くの血と涙を吸い込んじまった。ここで掘る奴は誰でも、 この呪いを吸い込むことになるんだ。";
			link.l1 = "ブラックウッドが取り憑かれていたと思うのか？";
			link.l1.go = "LadyBeth_Tichingitu_3";
		break;
		
		case "LadyBeth_Tichingitu_3":
			dialog.text = "憑かれてるだけじゃねえ。あいつは……なんて言うか……空っぽの器だ。何かが中に入り込んで、魂を追い出しちまったんだ。俺は前にもこれを見たことがある。 部族のシャーマンが精霊に人間を捧げたときだ。そのシャーマンも同じ目をしてたぜ。";
			link.l1 = "「しかし、何がそこまでの執着を生むんだ？」";
			link.l1.go = "LadyBeth_Tichingitu_4";
		break;
		
		case "LadyBeth_Tichingitu_4":
			dialog.text = "内側が空っぽの男は、他人の考えで簡単に満たされちまう。誰かがそいつの弱点を見つけて利用するんだ。 ティチンギトゥはこの男にちょっと同情しちまうぜ。";
			link.l1 = "「ほとんど？」";
			link.l1.go = "LadyBeth_Tichingitu_5";
		break;
		
		case "LadyBeth_Tichingitu_5":
			dialog.text = "ああ、ほとんどそうだ。どの戦士も自分の選択に責任を持つ。たとえ悪魔が耳元でささやいたとしてもな。";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Tichingitu_6";
		break;
		
		case "LadyBeth_Tichingitu_6":
			DialogExit();
			ReturnOfficer_Tichingitu();
		break;
		
		case "LadyBeth_Irons_1": // Томми
			dialog.text = "くそっ、船長！これを見てくれ！まるで昔の良き時代みてえだな！";
			link.l1 = "陸での戦争がどんなものか、よく知っているだろう。";
			link.l1.go = "LadyBeth_Irons_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Irons_2":
			dialog.text = "ナズビーの戦いを思い出すな。俺たちの騎兵隊がルパートの騎兵とぶつかったんだ。 あいつらも王のために同じ激しさで戦ってたぜ。";
			link.l1 = "ブラックウッドのこと、どう思う？";
			link.l1.go = "LadyBeth_Irons_3";
		break;
		
		case "LadyBeth_Irons_3":
			dialog.text = "このブラックウッドって奴は天才か、完全なイカレ野郎か、その両方だと思うぜ。\n驚いたのはな、奴の部下たちさ。多くが元軍人なんだ。チンピラじゃなくて、本物の兵隊だぜ。\nそいつら全員がこの狂気に付き合ったんだ。フォックスの海兵隊までな。\nははっ！今日の殺戮を喜ぶ奴がここにいるぞ！あいつは裏切った連中を絶対に許さなかったからな。";
			link.l1 = "もしかして金のことか？";
			link.l1.go = "LadyBeth_Irons_4";
		break;
		
		case "LadyBeth_Irons_4":
			dialog.text = "いや、他にも何かある。この男は奴らを支配してたんだ。本物の力を持ってた。それに、 バルバドスの金持ちのお嬢さんと婚約してたって話も聞いたぜ。あれだけの財宝を手に入れても、 結婚しなかったのは不思議だな。まったく、典型的な兵隊野郎だ――戦争の終わり時が分かってなかったんだろう。";
			link.l1 = "ありがとう、Tommy。お前は本当に頭が切れるな。";
			link.l1.go = "LadyBeth_Irons_5";
		break;
		
		case "LadyBeth_Irons_5":
			dialog.text = "「え？」";
			link.l1 = "「何もない。」";
			link.l1.go = "LadyBeth_Irons_6";
		break;
		
		case "LadyBeth_Irons_6":
			DialogExit();
			ReturnOfficer_Irons();
		break;
		
		case "LadyBeth_Knippel_1": // Книппель
			dialog.text = "これを見るのはなんと苦しいことか、船長。俺たちはどこまで落ちちまったんだ！？";
			link.l1 = "俺たちか？";
			link.l1.go = "LadyBeth_Knippel_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Knippel_2":
			dialog.text = "イギリス艦隊だ！見てみろ、この死んだクズどもの山に、赤い軍服の小さな点が転がってやがるぜ！";
			link.l1 = "その「クズ」の中には俺たちの仲間もいるんだ、チャーリー。お前の気持ちは分かるが……";
			link.l1.go = "LadyBeth_Knippel_3";
		break;
		
		case "LadyBeth_Knippel_3":
			dialog.text = "「ふざけんな、旦那！」";
			link.l1 = "お前の気持ちは分かるが、怒りや失望はブラックウッドに向けたほうがいいぜ。お前の大事なイギリス艦隊を裏切って、 ここに連れてきたのはあいつなんだからな。";
			link.l1.go = "LadyBeth_Knippel_4";
			link.l2 = "ああ、そうだな。行くぜ、まだ日は暮れちゃいねえ。";
			link.l2.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_4":
			dialog.text = "奴らはただ指揮官の命令に従っていただけだ！";
			link.l1 = "「お前もフリートウッドの後を追ったようにか？」";
			link.l1.go = "LadyBeth_Knippel_5";
			link.l2 = "ああ、行こうぜ。まだ日は暮れちゃいねえ。";
			link.l2.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_5":
			dialog.text = "「お前なんかについて行くかよ！」";
			link.l1 = "俺はブラックウッドやフリートウッドよりもいい船長になれると信じてるぜ。\nさあ行こう、まだ日は暮れちゃいねえ。";
			link.l1.go = "LadyBeth_Knippel_6";
		break;
		
		case "LadyBeth_Knippel_6":
			dialog.text = "ああ、船長。終わったら――次の戦が終わるまで飲み続けるぜ。";
			link.l1 = "...";
			link.l1.go = "LadyBeth_Knippel_7";
		break;
		
		case "LadyBeth_Knippel_7":
			DialogExit();
			ReturnOfficer_Knippel();
		break;
		
		case "LadyBeth_Alonso_1": // Алонсо
			dialog.text = "「マドレ・デ・ディオス、船長！大丈夫か？」";
			link.l1 = "それはこれから分かることだ。俺たちは何人失った？";
			link.l1.go = "LadyBeth_Alonso_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Alonso_2":
			
			dialog.text = "殺されたのか？この冒険で俺たちは失ったんだ "+sti(pchar.SailorDiedInBattleInfo)+" 野郎ども。お邪魔したくはねえが、船長……だがな、警告はしたぜ！";
			link.l1 = "今日はお前が実力を見せてくれたから、その発言は聞かなかったことにしてやるぜ、Alonso。\nどこでそんなに多くの才能を身につけたんだ？";
			link.l1.go = "LadyBeth_Alonso_3";
		break;
		
		case "LadyBeth_Alonso_3":
			dialog.text = "いつかその話をしてやるよ、船長――もちろん、俺たちが十分長く生き延びられたらの話だがな。";
			link.l1 = "他にもっと役立つ助言はあるか？";
			link.l1.go = "LadyBeth_Alonso_4";
		break;
		
		case "LadyBeth_Alonso_4":
			dialog.text = "もしここに財宝があったなら、とっくに見つかってるはずだぜ。\nだが、島を探して生存者を見つけてから、そいつらをどうするか決めるべきだ。\nそれにブラックウッドの船のことも忘れちゃいけねえ。あの美しいスノーについては、いい噂しか聞かねえからな。\nそんなお宝を逃すのはもったいねえぜ、船長。\nもちろん、これはあくまで船員たちの意見を伝えてるだけだ。";
			link.l1 = "もちろんだ。行くぞ。戦利品が待ってるぜ！";
			link.l1.go = "LadyBeth_Alonso_5";
		break;
		
		case "LadyBeth_Alonso_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		break;
		
		// Диалог с матросом в гроте Каймана
		case "LadyBeth_MatrosyInGrot":
			dialog.text = "撃たないでくれ！降参する！";
			link.l1 = "「お前は誰だ？」";
			link.l1.go = "LadyBeth_MatrosyInGrot_2";
		break;
		
		case "LadyBeth_MatrosyInGrot_2":
			dialog.text = "俺たち……俺たちは「レディ・ベス」号の者だ。ブラックウッド船長の乗組員さ。あの人は……生きてるのか？";
			link.l1 = "いいや。お前の船長は死んだ。";
			link.l1.go = "LadyBeth_MatrosyInGrot_3";
		break;
		
		case "LadyBeth_MatrosyInGrot_3":
			dialog.text = "これで全て終わったんだな……神に感謝するよ。";
			link.l1 = "お前は自分の船長を悼んでいるようには見えねえな。";
			link.l1.go = "LadyBeth_MatrosyInGrot_4";
		break;
		
		case "LadyBeth_MatrosyInGrot_4":
			dialog.text = "お前にはわからねえ。ブラックウッドは偉大な男だった。俺が知る中で最高の船長さ。\nだがここ数か月で……奴は変わっちまった。何かに取り憑かれ、残酷になったんだ。\n存在するかもわからねえ何かを探して、俺たちを昼も夜も働かせやがった。";
			link.l1 = "お前を俺の船の仲間にするぜ。経験豊富な水夫が必要なんだ。";
			link.l1.go = "LadyBeth_MatrosyInGrot_PlusKomanda";
			link.l2 = "敗者に災いあれ、野郎ども。今やお前たちの居場所は俺の船倉だ。運が良けりゃ、 バルバドスのどっかのプランテーションまで生き延びられるかもな。";
			link.l2.go = "LadyBeth_MatrosyInGrot_PlusRaby";
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusKomanda":
			dialog.text = "本当か？お前……お前は俺たちが……こんなことの後で何かおかしくなっちまったんじゃないかって、怖くねえのか？";
			link.l1 = "誰にでもやり直す機会はあるんだ。";
			link.l1.go = "LadyBeth_MatrosyInGrot_PlusKomanda_1";
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusKomanda_1":
			dialog.text = "ありがとうございます、船長。誓います、絶対に後悔させません。俺たちは腕のいい船乗りです。それに……これで悪夢も終わるかもしれません。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Grot_MatrosySdautsya_2");
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) + 30;
		break;
		
		case "LadyBeth_MatrosyInGrot_PlusRaby":
			dialog.text = "ありがとう、ありがとう！少なくとも俺たちは生きていられる。ここから連れ出してくれ、頼む。この島……まるで呪われてるみたいだ。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Grot_MatrosySdautsya_2");
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			SetCharacterGoods(pchar, GOOD_SLAVES, GetCargoGoods(pchar, GOOD_SLAVES)+30);
		break;
		
		case "LadyBeth_MatrosyInGrot_exit":
			DialogExit();
			for (i=1; i<=8; i++)
			{
				sld = CharacterFromID("LadyBeth_MatrosyPryachutsya_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", 5);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
		break;
		
		// Диалог с матросом на Леди Бет
		case "LadyBeth_EnemyMatros_1":
			dialog.text = "なんだと！？よくも“レディ号”を襲ってジェレミーを殺したな！てめえら、このまま生きて帰れると思うなよ、船長が戻ってきたら……";
			link.l1 = "お前の船長は死んだ。先に撃ったのはジェレミーだ、そして俺はお前たちの“レディ号”を血で買った正当な戦利品としていただくぜ。";
			link.l1.go = "LadyBeth_EnemyMatros_2";
		break;
		
		case "LadyBeth_EnemyMatros_2":
			dialog.text = "船長が……死んだだと？嘘つけ、この野郎！お前なんざ、あいつの制服のボタン一つの価値もねえ！";
			link.l1 = "その制服に意味があったとしても、それはとうの昔に死んだブラックウッドのためのものだ。\nどっちを選ぶ？死んだ男のために戦うか、自分の命を守るかだ。";
			link.l1.go = "LadyBeth_EnemyMatros_3";
		break;
		
		case "LadyBeth_EnemyMatros_3":
			if (CharacterIsHere("Helena"))
			{
				StartInstantDialog("Helena", "LadyBeth_EnemyMatros_Helena_1", "Quest\ShipsPack\LadyBeth_dialog.c");
				break;
			}
			if (CharacterIsHere("Knippel"))
			{
				StartInstantDialog("Knippel", "LadyBeth_EnemyMatros_Knippel_1", "Quest\ShipsPack\LadyBeth_dialog.c");
				break;
			}
			if (CharacterIsHere("Irons"))
			{
				StartInstantDialog("Irons", "LadyBeth_EnemyMatros_Irons_1", "Quest\ShipsPack\LadyBeth_dialog.c");
				break;
			}
			dialog.text = "戦わずに船を渡すつもりはねえぞ！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Bitva");
		break;
		
		case "LadyBeth_EnemyMatros_Helena_1":
			dialog.text = "聞けよ、お前ら。自分の船長に忠義を尽くすのは立派なことだ。だが、あいつはもう死んじまった。 生きてるのはお前たちだ。これからどう生きるか、自分で決めなきゃならねえ。 俺たちは新しい人生を始めるチャンスをやってるんだぜ。";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_5";
			CharacterTurnByChr(npchar, CharacterFromID("LadyBeth_CrewOfShip_7"));
		break;
		
		case "LadyBeth_EnemyMatros_Knippel_1":
			dialog.text = "船長、こいつらは敵じゃありません。ただ命令に従っていただけです。多くは元王室の水兵で、 よく訓練され規律もあります。彼らの腕を使わないのはもったいないですよ。\nお前たち、俺も艦隊で長く務めてきた中で何度もお前らと同じ立場になったことがある。そして俺は正しい選択をした。 お前たちもそうしろ。";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_5";
		break;
		
		case "LadyBeth_EnemyMatros_Irons_1":
			dialog.text = "さて、水夫ども！選択は簡単だ――生きたけりゃ、船倉の囚人になるか、俺たちの仲間になって飯と給料をもらうか、どっちかだ。\n……（喉元を指でなぞる）俺なら前者を選ぶぜ！";
			link.l1 = "...";
			link.l1.go = "LadyBeth_EnemyMatros_10";
			CharacterTurnByChr(npchar, CharacterFromID("LadyBeth_CrewOfShip_7"));
		break;
		
		case "LadyBeth_EnemyMatros_5":
			StartInstantDialog("LadyBeth_CrewOfShip_7", "LadyBeth_EnemyMatros_6", "Quest\ShipsPack\LadyBeth_dialog.c");
		break;
		
		case "LadyBeth_EnemyMatros_6":
			dialog.text = "...";
			link.l1 = "お前は俺の船の仲間になるんだ。";
			link.l1.go = "LadyBeth_EnemyMatros_7";
			link.l2 = "負け犬に災いあれ、野郎ども。これからは俺の船倉がお前らの居場所だ。運が良けりゃ、 バルバドスのどっかのプランテーションまで生き延びられるかもな。\n";
			link.l2.go = "LadyBeth_EnemyMatros_9";
		break;
		
		case "LadyBeth_EnemyMatros_7":
			dialog.text = "俺たちを仲間に入れてくれるのか？こんなことの後で？";
			link.l1 = "優秀な船乗りはいつだって貴重だ。\nそれにブラックウッド船長は部下の選び方をよく知っていたぜ。";
			link.l1.go = "LadyBeth_EnemyMatros_8";
		break;
		
		case "LadyBeth_EnemyMatros_8":
			dialog.text = "ありがとうございます、船長。俺たちは絶対に期待を裏切らねえ。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Vnutri_1");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) + 12;
		break;
		
		case "LadyBeth_EnemyMatros_9":
			dialog.text = "まあ……少なくとも、この冒険が終わる道はそれしかなかったんだ。\n許してくれ、ブラックウッド船長。俺たちはあんたを守れなかった。";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Vnutri_1");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			SetCharacterGoods(pchar, GOOD_SLAVES, GetCargoGoods(pchar, GOOD_SLAVES)+12);
		break;
		
		case "LadyBeth_EnemyMatros_10":
			StartInstantDialog("LadyBeth_CrewOfShip_7", "LadyBeth_EnemyMatros_11", "Quest\ShipsPack\LadyBeth_dialog.c");
		break;
		
		case "LadyBeth_EnemyMatros_11":
			dialog.text = "戦わずにこの船は渡さねえぞ！";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_ShipInShore_Bitva");
		break;
		
		// Диалог с Элизабет Бишоп
		case "LadyBeth_Elizabeth_1":
			dialog.text = "...";
			link.l1 = "失礼します。あなたがエリザベスですか？";
			if (pchar.sex == "man") link.l1.go = "LadyBeth_Elizabeth_2";
			if (pchar.sex == "woman") link.l1.go = "LadyBeth_Elizabeth_Woman_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LadyBeth_Elizabeth_2":
			dialog.text = "ああ、俺だよ。で、お前は誰だ？";
			link.l1 = "Captain "+GetFullName(pchar)+"……俺は……アルバート・ブラックウッドを知っていた。";
			link.l1.go = "LadyBeth_Elizabeth_3";
		break;
		
		case "LadyBeth_Elizabeth_3":
			dialog.text = "「私のアルバート？ああ、なんてこと……彼は……彼は無事なの？」";
			link.l1 = "残念だが、違う。彼は戦死した。最後まで戦い抜いたんだ。";
			link.l1.go = "LadyBeth_Elizabeth_4";
		break;
		
		case "LadyBeth_Elizabeth_4":
			dialog.text = "私……そうじゃないかと疑ってたわ。何年も何の音沙汰もなくて……ねえ、私、彼を待ってたの。ずっと長い間待ってたのよ。父はアルベルトは昇進を待つだけだって言ってた。 総督はすでにすべて決めていて、数か月の問題だって。でもアルベルトは……その話をまったく違うふうに受け取ったの。裕福になって、私にふさわしい男になって帰ってくるって言ったわ。 そして彼は出ていったの。ただ……出ていったのよ。";
			link.l1 = "彼は最期の日まであなたのことを思っていた。";
			link.l1.go = "LadyBeth_Elizabeth_5";
		break;
		
		case "LadyBeth_Elizabeth_5":
			dialog.text = "なんて愚かだったんだろう。私は彼の財宝なんて必要なかった。愛していたのは彼自身で、お金じゃない。 彼と一緒に逃げる覚悟もできていた……でも、彼はあまりにも誇り高かった。私は手紙を、どんな言葉でもいいから待っていた……そして届いたのは、この奇妙な手引きだけだった。冷たくて、計算高い書類……私の知っているアルベールとはまるで違う。あの時、私は彼を失ったのだと悟った。";
			link.l1 = "彼の持ち物の中に、これを見つけた。";
			link.l1.go = "LadyBeth_Elizabeth_6";
		break;
		
		case "LadyBeth_Elizabeth_6":
			dialog.text = "俺の家への地図だと？俺があいつの一番の宝だったって？皮肉なもんだな。カリブ中で財宝を探し回って、 あいつにとって本当に大事なものはずっとここにあったんだ……待て。お前に渡すものがある。これはアルベルトの手引き書だ。あいつが一年前に送ってきた。 これがあれば財宝を見つけて俺の元に戻れるって言ってたよ。今はお前の方が役立てられるだろう。";
			link.l1 = "ありがとう、エリザベス。こんな結果になってしまってすまない。";
			link.l1.go = "LadyBeth_Elizabeth_7";
			GiveItem2Character(PChar, "talisman18");
		break;
		
		case "LadyBeth_Elizabeth_7":
			dialog.text = "それで、私、結婚したのです、船長。ビショップ氏と。父がどうしてもと言って。あなたはあの人を知らない……知りたくもないでしょう。毎日、アルベールがもし……戻ってきてくれていたら、私の人生はどうなっていたのかと考えてしまいます。";
			link.l1 = "「そのことも俺が考えてやるぜ。」";
			link.l1.go = "LadyBeth_Elizabeth_8";
		break;
		
		case "LadyBeth_Elizabeth_8":
			dialog.text = "さようなら、船長。\nそれと……どうかご無事で。幽霊なんか追いかけるんじゃないぞ。";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Elizabeth_2");
		break;
		
		case "LadyBeth_Elizabeth_Woman_2":
			dialog.text = "ああ、それが俺だ。";
			link.l1 = " ヘレン・マッカーサー船長。俺は……アルバート・ブラックウッドを知っていた。";
			link.l1.go = "LadyBeth_Elizabeth_Woman_3";
		break;
		
		case "LadyBeth_Elizabeth_Woman_3":
			dialog.text = "俺のアルベルト？ああ、なんてことだ……彼が……で、あんたは誰だ？";
			link.l1 = "ヘレン・マッカーサー船長だと言ったばかりだ。俺は自分の船を指揮している。";
			link.l1.go = "LadyBeth_Elizabeth_Woman_4";
		break;
		
		case "LadyBeth_Elizabeth_Woman_4":
			dialog.text = "船長？女の船長だと？お前……アルベルトと一緒だったのか？どういう意味で……あいつを知ってたんだ？";
			link.l1 = "船長としてだけだ。すまないが、アルベルトは死んだ。俺は彼の最後の戦いを目撃したんだ。";
			link.l1.go = "LadyBeth_Elizabeth_Woman_5";
		break;
		
		case "LadyBeth_Elizabeth_Woman_5":
			dialog.text = "わかった。疑ってすまない。ただ……ブラックウッド船長はいつも女たちの注目を集めていたんだ。ここバルバドスでも。いや、特にここでな。";
			link.l1 = "お前はあいつを愛していたんだ。";
			link.l1.go = "LadyBeth_Elizabeth_Woman_6";
		break;
		
		case "LadyBeth_Elizabeth_Woman_6":
			dialog.text = "心からそう思います。父はアルベルトに、昇進を待つだけでよいと言っていました。数か月の問題だったのです。 しかし彼は、父の言葉を貧しさゆえの拒絶だと受け取ってしまいました。宝を持って帰ると言い残し、去っていきました。 ";
			link.l1 = "男どもとその誇りかよ！";
			link.l1.go = "LadyBeth_Elizabeth_Woman_7";
		break;
		
		case "LadyBeth_Elizabeth_Woman_7":
			dialog.text = "運がいいな、マッカーサー船長。\n自由の身だ。好きな場所へ航海できる。\nプランテーションの主人もいないし、親父に運命を決められることもない。\n夫に自分を所有物扱いされることもないんだ。";
			link.l1 = "自由には大きな代償が伴うんだ。\nそして、それを毎日守らなきゃならねえ。";
			link.l1.go = "LadyBeth_Elizabeth_Woman_8";
		break;
		
		case "LadyBeth_Elizabeth_Woman_8":
			dialog.text = "この件で役立つものがあるかもしれねえ。ほら、持っていけ。これはあいつの財宝探しの手引き書だ。 アルベルトがちょうど一年前くらいに俺に送ってきたんだ。自分の最高傑作だって言ってたよ。 これがあれば金持ちになって俺の元に帰れるってな。だが、ページをめくるごとに、 あいつは俺の知ってるアルベルトじゃなくなっていったんだ。\n";
			link.l1 = "ありがとう。預かっておくよ。";
			link.l1.go = "LadyBeth_Elizabeth_Woman_9";
			GiveItem2Character(PChar, "talisman18");
		break;
		
		case "LadyBeth_Elizabeth_Woman_9":
			dialog.text = "お願いです、船長……ご自分の自由を大切になさってください。私はビショップ大佐と結婚しました。父でさえ恐れる男です。 もし私もあなたのように自由だったら……すべてが違っていたでしょう。";
			link.l1 = "知ってる。";
			link.l1.go = "LadyBeth_Elizabeth_Woman_10";
		break;
		
		case "LadyBeth_Elizabeth_Woman_10":
			dialog.text = "さらばだ、船長。良い風が吹きますように。";
			link.l1 = ""+Goodbye(true)+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LadyBeth_Barbados_Elizabeth_2");
		break;
	}
} 