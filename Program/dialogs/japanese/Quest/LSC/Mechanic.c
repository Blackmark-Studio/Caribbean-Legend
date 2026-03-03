// Хенрик Ведекер. Он же Механик.
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "ごきげんよう、旦那。お見かけするのは初めてですね。新しく来られた方ですか？ この台船にいらっしゃるのは初めてですか？";
				link.l1 = TimeGreeting()+"。私の名前は "+GetFullName(pchar)+"……俺はここに来たばかりで、ちょっと見て回ったり、人と知り合いになろうとしてるんだ……";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				if (pchar.questTemp.LSC == "platinum_wait")
				{
					dialog.text = "「聞いてくれ、」 "+pchar.name+"「お前がちょっかいを出し続けるなら、修理がいつまで経っても終わらねえぞ。」";
					link.l1 = "ああ、ああ、それは覚えているよ。迷惑をかけてすまなかったな！";
					link.l1.go = "exit";
					break;
				}
				// возвращение блудного скафандра
				if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
				{
					dialog.text = "あっ！見てみろよ！あの世から溺死者が戻ってきやがった！さて、どうやってそんな芸当をやってのけたんだ？ お前のために葬式までやって、お前が知らねえうちに墓まで用意してやったんだぜ……";
					link.l1 = "残念だが、俺はまだ死ぬつもりはねえよ。仕掛けは単純さ――ククルカンの偶像の底にちょっと触れただけで、ドミニカに転送されちまったんだ、しかもカリブ族の村のど真ん中に……";
					link.l1.go = "return";
					break;
				}
				
				dialog.text = "「ああ、」 "+GetFullName(pchar)+"! "+TimeGreeting()+"!";
				// квестовые ветки
				if(pchar.questTemp.LSC == "mechanic")
				{
					link.l4 = "ヘンリク、君にビジネスの提案があるんだ。とても重要な話だぜ。オーレ・クリスチャンセンから君のことを聞いた。 あいつは“ホワイトボーイ”とも呼ばれているんだ。";
					link.l4.go = "mechanic_1";
				}
				if(pchar.questTemp.LSC == "platinum" && GetCharacterItem(pchar, "jewelry10") >= 11)
				{
					link.l4 = "ヘンリック、お前に十分な「銀貨」を持ってきたぜ。頼まれた通りだ：お前の分一つに、さらに十枚余分に。ほら、 受け取れ。";
					link.l4.go = "mechanic_15";
				}
				if(pchar.questTemp.LSC == "underwater_check")
				{
					link.l4 = "また俺だ、ヘンリック。スーツの調子はどうだ？修理できたか？";
					link.l4.go = "mechanic_20";
				}
				if(pchar.questTemp.LSC == "platinum_add_wait" && GetCharacterItem(pchar, "jewelry10") >= sti(pchar.questTemp.LSC.PtAddQty))
				{
					link.l4 = "頼まれた金属は十分にある。持っていけ。";
					link.l4.go = "mechanic_23";
				}
				if(pchar.questTemp.LSC == "underwater_prepare")
				{
					link.l4 = "ごきげんよう、ヘンリック。で、潜水用のスーツはもう準備できてるか？";
					link.l4.go = "immersion";
				}
				if(pchar.questTemp.LSC == "underwater_natan" && CheckAttribute(pchar, "questTemp.LSC.NatanTalk"))
				{
					link.l4 = "もう終わった、問題は片付けたし、潜る準備もできている。\nいつ始める？";
					link.l4.go = "immersion_1";
				}
				if(CheckAttribute(pchar, "questTemp.LSC.UW_ready"))
				{
					link.l5 = "やあ、ヘンリック。で、潜水用のスーツはもう準備できたか？";
					link.l5.go = "immersion_next";
				}
				if(CheckAttribute(pchar, "questTemp.LSC.UW_end") && CheckCharacterItem(pchar, "underwater"))
				{
					link.l5 = "あなたの服を返したいんだ。";
					link.l5.go = "immersion_next_2";
				}
				// квестовые ветки				
				link.l1 = LinkRandPhrase("何か面白い話でもあるのかい？","島で何か新しいことが起きたかい？","最近の噂話を教えてくれないか？");
				link.l1.go = "rumours_LSC";
				link.l3 = "ただ、あんたの調子がどうか知りたかっただけだ。";
				link.l3.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "そして俺はヘンリック・ヴェデッカーだ。\nだが、ここの連中には大抵「機械屋」と呼ばれている。それが実に的を射た呼び名なんだよ。";
			if(pchar.questTemp.LSC == "mechanic")
			{
				link.l1 = "お前がヘンリク・ヴェデッカーか？会えて嬉しいぜ！探してたんだ。";
				link.l1.go = "mechanic";
			}
			else
			{
				link.l1 = "お前は何でも屋ってやつだろ？";
				link.l1.go = "meeting_1";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting_1":
			dialog.text = "ああ、そうだよ、ナーヴァルたちは本当に俺の腕を評価してくれてるんだ。 俺の道具があれば外輪の沈没船からたくさんの貴重品を引き上げられるから、 ドドソン提督から食料を買うことができるのさ\n実のところ、俺は科学と探検に情熱を注いでる。だから、もし君と十分な時間を過ごせなかったとしても許してくれ――実験にほとんどの時間を取られてしまうんだ。";
			link.l1 = "なるほど。理由もなくお邪魔するつもりはありません、ヴェデッカー旦那、ご安心ください。 お会いできて本当に嬉しいです！";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "mechanic":
			dialog.text = "そうだったのか？それで、なぜだ？";
			link.l1 = "オーレ・クリスチャンセンがあんたのことを話してたぜ。あいつは「ホワイトボーイ」とも呼ばれてるんだ。";
			link.l1.go = "mechanic_1";
		break;
		
		case "mechanic_1":
			dialog.text = "ああ、あの面白いやつか！ああ、知ってるさ。で、そいつが何て言ってたんだ？";
			link.l1 = "次の質問が馬鹿みたいに聞こえたらすまないが……それでも聞かせてくれ。オーレが、 お前なら水中に潜って海底まで行く方法を教えてくれるかもしれないって言ってたんだ。 もしそれが彼の妄想だったとしても、どうか笑わないでくれよ。";
			link.l1.go = "mechanic_2";
		break;
		
		case "mechanic_2":
			dialog.text = "本当だよ。俺も何度か自分で海底まで潜ったことがあるんだ。でも今はもう潜らない。 最近は浅瀬に巨大なカニがうようよしていて、見ての通り、俺にはあいつらと戦う力はない。俺は科学者だ、 あんな化け物と戦えるわけがないさ。\nそれに、他にも二人、ナーワル族の男がいて、昔は潜ってたけど、結局やめちまった――外輪の船の船倉を漁る方が、巨大カニがうじゃうじゃいる場所に潜るよりよっぽど安全だったからな。\n今じゃ俺の装備もほとんど使われなくなった。ここ数ヶ月はスーツが壊れてて、一度も潜ってないんだ……";
			link.l1 = "本当に海底まで潜れる装備を持ってるのか？俺の聞き間違いじゃねえよな？";
			link.l1.go = "mechanic_3";
		break;
		
		case "mechanic_3":
			dialog.text = "耳がいいな、若者よ。このスーツは俺が自分で発明し、作り上げたものだ。分厚くて十分に水に浸した完全防水の帆布、 金属部品、そして俺とユルゲンが彼の鍛冶場で鍛えた鋼鉄のヘルメットでできている\nさらに、カニから身を守るためと重さを増すために、金属製の胸当てや膝当て、胸部パーツ、ブーツで補強してある\n特別なタンクには加圧空気が詰めてあり、生命維持と水中でしばらく過ごすことができる。このスーツは唯一無二で、 俺はかなり自慢しているんだ。";
			link.l1 = "それは素晴らしい。しかし、その服が傷んでいることは言ったか？";
			link.l1.go = "mechanic_4";
		break;
		
		case "mechanic_4":
			dialog.text = "残念ながら、それは本当だ。スーツのいくつかの部分は、柔軟性と追加の防護のために金属板でつながれていたが、 海水がそれらに悪影響を及ぼした。長年の使用で板は錆びつき、防水性を失ってしまったんだ。\n損傷に気づいて誰も死なずに済んだのは幸運だったよ。乾いたスーツでさえ、少し塩分と水分が残っていて、 すでに悪影響を及ぼしていたんだ。";
			link.l1 = "そうだな……でも、スーツは修理できるだろう！古くて錆びた部品を新しいものに取り替えれば……そうじゃないか？";
			link.l1.go = "mechanic_5";
		break;
		
		case "mechanic_5":
			dialog.text = "何のためだ？一年後にまた交換するためか？この作業がどれほど大変か知っているのか？ 可動式の継ぎ目で服を組み立てて、防水にするんだぞ？休みなしでやっても最低一週間はかかるんだ。";
			link.l1 = "それが理由で、自分の発明を捨てる気になったのか？";
			link.l1.go = "mechanic_6";
		break;
		
		case "mechanic_6":
			dialog.text = "いや、もちろん違う。考えがあるんだ。水や塩でも壊れない金属で継ぎ目を作る必要がある。 そのために使える金属が何か、俺は知ってるんだ…";
			link.l1 = "「それで、何が問題なんだ？」";
			link.l1.go = "mechanic_7";
		break;
		
		case "mechanic_7":
			dialog.text = "問題は、この金属が非常に珍しいことだ。俺が持っているのはたった一つだけで、とても足りねえ。あと十個、 いや十五個は必要なんだ。";
			link.l1 = "「それで……お前が言ってるその金属って何だ？」";
			link.l1.go = "mechanic_8";
		break;
		
		case "mechanic_8":
			dialog.text = "ああ、これは独特な金属だよ、多くの者に過小評価されているがな。耐久性が高く、柔軟性もあり、 しかもまったく腐食しない――水も塩も傷をつけられねえ\nもしかしたら、あんたもこの金属を見たことがあるかもしれねえ。白くて銀に見えるから、スペイン人は「銀」 と呼んだんだ。ははっ！銀なんかより百倍も優れてるぜ！金よりも上だ！いつかみんなもそのことに気づくだろうが、 まだその時じゃねえな。";
			link.l1 = "なあ、どうして他の金属を使わねえんだ？その板を作るのに金を使ったらどうだ？金が錆びたりダメになるなんて話、 聞いたことねえぞ。";
			link.l1.go = "mechanic_9";
		break;
		
		case "mechanic_9":
			dialog.text = "お前は柔軟で生き生きとした頭を持っているな、若者よ。それを知れて嬉しいぜ。だが残念ながら、 お前の提案はうまくいかねえ。金のことは真っ先に俺も考えたが、 金は柔らかすぎてスーツの各部を繋げるには向いてねえんだ\nああ、残念だが、プラチナだけが唯一の材料だ。どれだけ年月がかかろうと、俺はそれだけで部品を作るつもりだよ。 でもな、この島でその金属のかけらを見たことがある。見た目が似てるから、よく銀と混ぜられてるんだ。";
			link.l1 = "ふむ。その……「銀」とやらを十分に見つける手伝いをしたら、俺にもその装備を貸してくれて、水中に潜らせてくれるのか？";
			link.l1.go = "mechanic_10";
		break;
		
		case "mechanic_10":
			dialog.text = "聞くまでもねえさ！もちろんやるぜ。カニがいるからあそこには潜らねえって前に言っただろ、 他の奴らも誰も行きたがっちゃいねえんだよ。";
			link.l1 = "それなら、その金属片を見せてくれ。俺が何を探せばいいのか分かるようにな。";
			link.l1.go = "mechanic_11";
		break;
		
		case "mechanic_11":
			dialog.text = "それを探しに行くのか？素晴らしい。ほら、これを見本として持っていけ。銀鉱石やナゲットの中から探してみろ。 見つけるのは簡単じゃないが、お前ならできるさ。銀には小さな黒い斑点があるが、 俺たちの金属は透明で銀よりずっと硬い。一番簡単な見分け方は、銀貨で引っかいてみることだ。 もし銀貨のほうが傷ついたら、それが探しているものだぞ。";
			link.l1 = "わかった。すぐに探しに行くぜ。どこを探せばいいか、何かアドバイスはあるか？";
			link.l1.go = "mechanic_12";
		break;
		
		case "mechanic_12":
			GiveItem2Character(pchar, "jewelry10");
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a platinum ingot");
			dialog.text = "残念だが、俺は知らねえ。もし場所が分かってたら、自分で探しに行ってるさ。\nだが、ひとつ助言はできるぜ。リヴァドスの船を探してみな。俺はあそこには行かねえから、 あいつらが持ってる可能性は高いぜ。";
			link.l1 = "考えてみるよ、ヘンリック。運が味方してくれるといいんだがな。";
			link.l1.go = "mechanic_13";
		break;
		
		case "mechanic_13":
			dialog.text = "あと十個集めろ。それがこの装備を修理するための最低限だ。幸運を祈る！";
			link.l1 = "ありがとうございます。さらばだ、メカニック！";
			link.l1.go = "mechanic_14";
		break;
		
		case "mechanic_14":
			DialogExit();
			pchar.questTemp.LSC = "platinum";
			AddQuestRecord("LSC", "7");
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) >= 65 || rand(2) == 1) pchar.questTemp.LSC.PtAddQty = 0;
			else pchar.questTemp.LSC.PtAddQty = rand(4);
		break;
		
		case "mechanic_15":
			RemoveItems(pchar, "jewelry10", 11);
			dialog.text = "ほうほう、見せてみろ……素晴らしい！よくやったな、若造！難しかったか？";
			link.l1 = "あんまり……";
			link.l1.go = "mechanic_16";
		break;
		
		case "mechanic_16":
			dialog.text = "さて、これで修理を始められるな。時間は無駄にしねえ、明日から取り掛かるぜ。お前、 本当に潜るのが待ちきれねえんだろ？";
			link.l1 = "確かに。俺は本当に水中を探検してみたいんだ。";
			link.l1.go = "mechanic_17";
		break;
		
		case "mechanic_17":
			dialog.text = "それはとても良いことだ、なぜならお前に頼みたいことがあるんだ、潜水の準備ができたときにな。だが、 その話は後にしよう。五日後にまた来てくれ、修理が終わっているといいんだが。";
			link.l1 = "いいだろう。幸運を祈るぜ！";
			link.l1.go = "mechanic_18";
		break;
		
		case "mechanic_18":
			dialog.text = "運も確かに必要だが、この装甲の修理には主に腕前が問われるぜ。\nそれに、お前が持ってきた金属で板を作るために、ユルゲンと一緒に炉のそばで一日過ごさなきゃならねえ。";
			link.l1 = "それじゃあ邪魔しねえよ。五日後にまた会おう。じゃあな！";
			link.l1.go = "mechanic_19";
		break;
		
		case "mechanic_19":
			DialogExit();
			pchar.questTemp.LSC = "platinum_wait";
			AddQuestRecord("LSC", "8");
			SetFunctionTimerCondition("LSC_PrepareUnderwater_Check", 0, 0, 5, false); // таймер
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "mechanic_20":
			if (sti(pchar.questTemp.LSC.PtAddQty) == 0)
			{
				dialog.text = "ああ。ユルゲンと俺で大した仕事をやったぜ、お前が持ってきた部品の量も十分だった。装備は修理済みで、 もう準備万端だ。あとはいくつかテストをするだけだが、問題ないはずだ。明日の午前10時に来い――タンクに空気を入れておくから、好きなように使えるぞ。";
				link.l1 = "素晴らしい！楽しみにしているよ。じゃあ、また明日だな、Henrik！";
				link.l1.go = "mechanic_24";
				DeleteAttribute(pchar, "questTemp.LSC.PtAddQty");
				AddCharacterExpToSkill(pchar, "Fortune", 100);
			}
			else
			{
				dialog.text = "残念だけど、 "+pchar.name+"……やはり予想通り、金属が足りない。俺には必要だ "+FindRussianQtyString(sti(pchar.questTemp.LSC.PtAddQty))+" 修理を終えるには、もっと部品が必要だ。またお前に助けを頼まなきゃならねえ。";
				link.l1 = "ほう、こんな展開になるとは思わなかったぜ。まあいい、足りねえ金塊を探してみるとするか。";
				link.l1.go = "mechanic_21";
			}
		break;
		
		case "mechanic_21":
			dialog.text = "お前を待ってるぜ。この額で十分だと保証する。奴らを連れて来てくれれば、一日で仕事を終わらせてやる。";
			link.l1 = "そうだといいな……またな！";
			link.l1.go = "mechanic_22";
		break;
		
		case "mechanic_22":
			DialogExit();
			pchar.questTemp.LSC = "platinum_add_wait";
			AddQuestRecord("LSC", "9");
			AddQuestUserData("LSC", "sQty", FindRussianQtyString(sti(pchar.questTemp.LSC.PtAddQty)));
		break;
		
		case "mechanic_23":
			RemoveItems(pchar, "jewelry10", sti(pchar.questTemp.LSC.PtAddQty));
			dialog.text = "素晴らしい！これで装備は元通りになる。あとはいくつかテストを行うだけだが、問題ないはずだ。明日の午前10時に来てくれ——タンクに空気を入れておくから、好きなことができるぞ。";
			link.l1 = "素晴らしい！楽しみにしているよ。じゃあ、また明日だな、Henrik！";
			link.l1.go = "mechanic_24";
		break;
		
		case "mechanic_24":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.LSC.PtAddQty"))
			{
				iTemp = 2;
				sTemp = "the day after tomorrow";
				DeleteAttribute(pchar, "pchar.questTemp.LSC.PtAddQty");
			}
			else
			{
				iTemp = 1;
				sTemp = "tomorrow";
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.NatanTalk")) string sText = "But I have to find Nathaniel Hawk first before I dive."; //не было разговора с Натаном
			else sText = "";
			AddQuestRecord("LSC", "10");
			AddQuestUserData("LSC", "sText1", sTemp);
			AddQuestUserData("LSC", "sText2", sText);
			pchar.quest.LSC_prepunderwater.win_condition.l1 = "Timer";
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.hour  = 10;
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.day   = GetAddingDataDay(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.win_condition.l1.date.year  = GetAddingDataYear(0, 0, iTemp);
			pchar.quest.LSC_prepunderwater.function = "LSC_PrepareUnderwater";
			pchar.questTemp.LSC = "wait";
		break;
		
		case "immersion":
			dialog.text = "はい、装備は準備できていて空気も入っている。潜っていいぞ。";
			if (!CheckAttribute(pchar, "questTemp.LSC.NatanTalk")) // не было разговора с Натаном
			{
				link.l1 = "よし。しかし今は潜れないんだ。俺の……友人、ナサニエル・ホークに関する問題を解決しなきゃならない。あいつが見つからないんだ。 スーツは少し待ってくれないか？";
				link.l1.go = "natan";
			}
			else
			{
				link.l1 = "素晴らしい！いつ始めるんだ？今か？";
				link.l1.go = "immersion_1";
			}
		break;
		
		case "natan":
			dialog.text = "ああ、別に急がなくてもいいさ。友達を一年間も探し続けるつもりか？";
			link.l1 = "ああ、約束するよ。もしかしたら今日中に彼を見つけるかもしれない。彼との用事が済んだらすぐに君のところへ寄るよ。 ";
			link.l1.go = "natan_1";
		break;
		
		case "natan_1":
			dialog.text = "はい、どうぞ。潜る準備ができたら来てくれ。";
			link.l1 = "ありがとう！";
			link.l1.go = "exit";
			pchar.questTemp.LSC = "underwater_natan";
		break;
		
		case "immersion_1":
			dialog.text = "今すぐでもいいぜ。ただし、まず少し説明しておく。お前は「フェニックス」台から潜るんだ。 サン・ガブリエル号の船尾から行けるぞ。そこに昇降機があって、海底まで降りてまた戻って来られる。 それが唯一の帰還方法だ\nだから、水中で昇降機の場所をしっかり覚えて迷うなよ。スーツのタンクには二十分分の空気が入ってる。 時間をちゃんと見てないと窒息するぞ\n昇降機からあまり離れるな。戻る時間がなくなるし、もしこの浅瀬から出たら神様でも助けられねえ――ヒラメみたいにぺちゃんこになるぞ\n気をつけて、カニにも注意しろ。近づきすぎると襲ってくる。無理はするな。群れ全部を倒すなんて無理だし、 あそこじゃ素早く逃げることもできねえからな。";
			link.l1 = "カニは俺がやる。あとは任せとけ。あんまり深く潜るな、巻き上げ機から離れすぎるな、時間も忘れるなよ。 いつ潜っていいんだ？";
			link.l1.go = "immersion_2";
		break;
		
		case "immersion_2":
			dialog.text = "いつでもいいが、朝7時から夜9時までだけだぜ。暗くなったら何も見えなくなるからな。";
			link.l1 = "了解だ。";
			link.l1.go = "immersion_4";
		break;
		
		case "immersion_4":
			dialog.text = "そういうことだ。台のそばの部屋から潜水服を持っていけ。潜った後は脱いで、俺のところに持ってきてくれ。 俺がまた空気を入れてやる。ただし、一日に一度以上は潜るな。たとえ20分でも、潜って圧縮空気を吸うのは体に悪いからな。";
			link.l1 = "じゃあ、一日に一度以上は潜らねえことにするぜ。";
			link.l1.go = "immersion_5";
		break;
		
		case "immersion_5":
			dialog.text = "わかってくれて嬉しいよ。さあ行け、幸運を祈るぜ！";
			link.l1 = "ありがとう！";
			link.l1.go = "immersion_6";
		break;
		
		case "immersion_6":
			DialogExit();
			pchar.questTemp.LSC = "first_immersion"; // флаг на первое погружение
			pchar.questTemp.LSC.immersion = "true"; // погружение возможно
			pchar.quest.LSC_takeUnderwater.win_condition.l1 = "locator";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.location = "FenixPlatform";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator_group = "item";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator = "armor";
			pchar.quest.LSC_takeUnderwater.function = "LSC_takeUnderwater"; // выдача костюма
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1 = "locator";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.location = "Underwater";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.locator_group = "quest";
			pchar.quest.LSC_UnderwaterDolly.win_condition.l1.locator = "dolly";
			pchar.quest.LSC_UnderwaterDolly.function = "LSC_FindUnderwaterDolly"; // нашли статую
			NextDiag.CurrentNode = "after_first_immersion"; // нода после первого погружения
			AddQuestRecord("LSC", "11");
			QuestPointerToLoc("UnderWater", "quest", "dolly");
		break;
		
		case "after_first_immersion":
			if (CheckAttribute(pchar, "questTemp.LSC.immersion"))
			{
				dialog.text = "それで、なぜまだここにいるんだ？あの服が君を待ってるぜ。";
				link.l1 = "ああ、ああ。今向かっているところだ。";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "それで、最初の潜水はどうだった？";
				if (CheckAttribute(pchar, "questTemp.LSC.FindDolly"))
				{
					link.l1 = "実に素晴らしい、そして私は結果に満足している。沈没したガレオン船で石の偶像を見つけたんだ。以前、 リヴァドスがその偶像に生贄を捧げていたと聞いた。ヘンリク、これについてもっと詳しく知っている者を知らないか？\n";
					link.l1.go = "af_immersion_1";
				}
				else
				{
					link.l1 = "いいだろう。俺がやったんだ！実に面白かったぜ、ちょっとスリルもあったけどな。";
					link.l1.go = "af_immersion_2";
				}
			}
			NextDiag.TempNode = "after_first_immersion";
		break;
		
		case "af_immersion_1":
			dialog.text = "私たちの歴史に興味があるのか？アントニオ・ベタンコートのところへ行くといい。彼はこの正義の島で生まれたんだ。 今はフルート船プルートに住んでいる。もし彼が何も知らないなら、誰も知らないさ。";
			link.l1 = "素晴らしい！必ず彼に会いに行くよ。";
			link.l1.go = "af_immersion_2";
			pchar.questTemp.LSC.Betancur = "true";
			AddQuestRecord("LSC", "14");
		break;
		
		case "af_immersion_2":
			dialog.text = "ここにスーツを置いていけ。明日でも他の日でもまた来い、俺が空気を入れてやる。";
			if (CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "もちろん。はい、あなたの服だ。ありがとう！";
				link.l1.go = "af_immersion_3";
			}
			else
			{
				link.l1 = "かしこまりました。すぐにお持ちします！";
				link.l1.go = "af_immersion_wait";
			}
		break;
		
		case "af_immersion_wait":
			dialog.text = "さて、俺の装備を持ってきてくれたのか？";
			if (CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "もちろん。こちらがあなたの服だ。ありがとう！";
				link.l1.go = "af_immersion_3";
			}
			else
			{
				link.l1 = "すぐにやるぜ！";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "af_immersion_wait";
		break;
		
		case "af_immersion_3":
			DialogExit();
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
			NextDiag.CurrentNode = "First time";
			// даем старт мини-квестам с крабикусами
			sld = characterFromId("Carpentero");
			if(!CheckAttribute(sld, "quest.crab")) sld.quest.crab = "begin";
			if (GetCharacterIndex("LSC_Jacklin") != -1)
			{
				sld = characterFromId("LSC_Jacklin");
				sld.quest.crab = "true";
			}
		break;
		
		// блок погружений, за искл. первого
		case "immersion_next":
			if (CheckAttribute(npchar, "quest.guarantee")) // требует залог
			{
				dialog.text = "はい、もちろんだ。スーツはちゃんとテストして空気も入れてあるぜ。誓約書は持ってきたか？五十万ペソだろう？";
				if (sti(pchar.money) >= 500000)
				{
					link.l1 = "ああ、もちろんだ。ほら、持っていけ。";
					link.l1.go = "immersion_next_pay";
				}
				else
				{
					link.l1 = "おっと！忘れてたぜ。すぐに持ってくるよ……";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "はい、もちろんです。スーツは試験済みで、空気も充填されています。いつも通り『フェニックス』 プラットフォームを確認してください。";
				link.l1 = "じゃあ、俺が潜るぜ。ありがとう！";
				link.l1.go = "immersion_next_1";
			}
		break;
		
		case "immersion_next_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.UW_ready"); 
			LocatorReloadEnterDisable("LostShipsCity_town", "reload72", false); //открываем вход в Феникс
			pchar.questTemp.LSC.immersion = "true"; // погружение возможно
			pchar.quest.LSC_takeUnderwater.win_condition.l1 = "locator";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.location = "FenixPlatform";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator_group = "item";
			pchar.quest.LSC_takeUnderwater.win_condition.l1.locator = "armor";
			pchar.quest.LSC_takeUnderwater.function = "LSC_takeUnderwater"; // выдача костюма
		break;
		
		case "immersion_next_2":
			dialog.text = "わかった。明日か後でまた来い。俺は衣装の準備をするからな。";
			link.l1 = "ありがとう、整備士！";
			link.l1.go = "immersion_next_3";
		break;
		
		case "immersion_next_3":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.LSC.UW_end"); 
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			if (CheckAttribute(npchar, "quest.guarantee")) AddMoneyToCharacter(pchar, 500000); // возврат залога
			LocatorReloadEnterDisable("SanGabrielMechanic", "reload3", false);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
		break;
		
		case "immersion_next_pay":
			AddMoneyToCharacter(pchar, -500000);
			dialog.text = "スーツを返却したら金は返す。公平な取引だろう。";
			link.l1 = "ありがとう、メカニック！これから潜るぜ。";
			link.l1.go = "immersion_next_1";
		break;
		// блок погружений
		
	//--------------------------------------вернулся на Остров---------------------------------------------
		case "return":
			dialog.text = "ちょっと待ってくれ！何の像だって？あ、ああ、わかったぜ。沈没船『サン・ヘロニモ』 にあるあの偶像のことを言ってるんだな？じゃあ、リヴァドスの噂は本当だったのか？";
			link.l1 = "その通りだ！それに、噂話なんてないさ。群島にはあと二つ、触れた者を互いに転送する偶像があるって俺は知ってる。 輪になってな。";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "なるほど、なるほど。君を信じるしかないが、君の話は非科学的な戯言だな。テレポートや像だと…ははっ！そんなもの、誰が考えつくんだ？どうやってそんな仕組みが成り立つんだよ？";
			link.l1 = "俺を信じて、ここで理屈を探そうとするな。嘘は言ってねえ。";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "いいだろう。ただし、お前のその転移でスーツを失くしてはいないだろうな？";
			if(CheckCharacterItem(pchar, "underwater"))
			{
				link.l1 = "ああ、してないさ。いわばカリブ族から俺を救ってくれたんだ。ほら、これだ。";
				link.l1.go = "return_4";
			}
			else
			{
				link.l1 = "ああ、そうだな、持ってなかったよ。ある意味、カリブ族から俺を救ってくれたんだ。だが、今は持ってねえんだ。";
				link.l1.go = "return_3";
			}
		break;
		
		case "return_3":
			dialog.text = "だから早く持ってこい、この野郎！俺のところにそれを持ってくるまで話はしねえ、わかったか？";
			link.l1 = "落ち着け、メカニック。ちゃんと返すからな！";
			link.l1.go = "exit";
			NextDiag.TempNode = "return_underwater";
		break;
		
		case "return_underwater":
			if(CheckCharacterItem(pchar, "underwater"))
			{
				dialog.text = "おお、本当に俺の服を持ってきてくれたのか！ありがとう、ちょっと心配し始めてたんだ。";
				link.l1 = "心配する必要はなかったんだ。返すと約束しただろう。";
				link.l1.go = "return_4";
			}
			else
			{
				dialog.text = "俺の服を持ってくるまで、ここに来るんじゃねえぞ。";
				link.l1 = "「わかった、わかった。」";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "return_underwater";
		break;
		
		case "return_4":
			DeleteAttribute(pchar, "questTemp.LSC.UW_end"); 
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			RemoveItems(pchar, "underwater", 1);
			SetFunctionTimerCondition("LSC_ReadyUnderwater", 0, 0, 1, false);
			dialog.text = "よくやった。新しいものを作ろうかと考え始めていたが、それには少なくとも一年はかかる……。君が見事な判断をして、私の持ち物を無傷で返してくれたことを嬉しく思う。お礼に贈り物まであげよう。";
			link.l1 = "本気か？";
			link.l1.go = "return_5";
		break;
		
		case "return_5":
			dialog.text = "もちろんだよ！お前は俺のスーツを修理するのを手伝ってくれたし、最初のチャンスで捨てたりもしなかった。 ずっと大事にしてくれて、ついにこうして返してくれたんだな。\nとにかく、これは上等な工具箱だ。使い方を覚えておけよ。これがあれば、いろんな役立つものが作れるぜ。";
			link.l1 = "さすが機械屋だな！やっぱり工具箱か！ありがとう、ヘンリック、感激だ……俺にはもったいない贈り物だよ。";
			link.l1.go = "return_6";
		break;
		
		case "return_6":
			GiveItem2Character(pchar, "mechanic_tool");
			Log_Info("You have received a toolbox");
			PlaySound("interface\important_item.wav");
			dialog.text = "お前が何に値し、何に値しなかったかは俺の方がよく知ってる。受け取れ！役に立つはずだ。だが、 例の偶像で勝手にどこかへ飛ぶ癖があるから、もう一度その服を渡すのは、五十万ペソを誓約してからだぞ。";
			link.l1 = "おったまげたぜ！まあ、わかったよ……用心ってわけだな……";
			link.l1.go = "return_7";
		break;
		
		case "return_7":
			dialog.text = "もちろんさ。だが、もしお前がいつかそれを持って逃げたら？そのときは金が俺の補償になるってわけだ。";
			link.l1 = "わかったよ、ヘンリック。俺も同意するぜ。正直なところ、 もう二度とお前がそれを渡してくれるとは思ってなかったんだ。";
			link.l1.go = "return_8";
		break;
		
		case "return_8":
			dialog.text = "無理だな。五十万賭ければ全部お前のものだぜ。";
			link.l1 = "取引成立だ！いつも通り潜りに行っていいか？明日からでいいのか？";
			link.l1.go = "return_9";
		break;
		
		case "return_9":
			dialog.text = "その通りだ。";
			link.l1 = "ありがとう！またな、Henrik！";
			link.l1.go = "return_10";
		break;
		
		case "return_10":
			DialogExit();
			AddQuestRecord("LSC", "26");
			npchar.quest.return_isl = "true";
			npchar.quest.guarantee = "true"; // залог за скафандр
			NextDiag.CurrentNode = "First time";
		break;
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("そこで何してやがる、ああ？泥棒め！","見てくれよ！俺がちょっと物思いにふけってたら、あんたはすぐに俺の箱を調べる気になったんだな！","俺の宝箱を調べるつもりか？ただじゃ済まねえぞ！");
			link.l1 = "くそっ！";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "「何だと？！俺の宝箱を調べるつもりか？そうはさせねえぞ！」";
			link.l1 = "馬鹿な娘め……";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//замечание по обнажённому оружию
		case "LSCNotBlade":
			dialog.text = LinkRandPhrase("聞けよ、武器はしまってくれ。見てると落ち着かねえんだ。","ここでは刃物を振り回すのは許されていないんだ。しまってくれ。","聞けよ、剣を振り回して中世の騎士みたいな真似はやめろ。\nしまっとけ、そんなのはお前に似合わねえ…");
			link.l1 = LinkRandPhrase("「いいだろう。」","ああ、いいぜ。","おっしゃる通りだな……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar,"聞いてくれ、俺はこの町の住人だ。剣を納めてくれないか。","聞いてくれ、俺はこの街の住人だ。だから剣を納めてくれ。");
				link.l1 = LinkRandPhrase("「いいだろう。」","ああ、いいぜ。","おっしゃる通りだな……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar,"気をつけろよ、相棒、武器を持ってうろついてると。俺がビビっちまうかもしれねえぞ……","人が武器を抜いたまま俺の前を歩くのは好きじゃねえ……怖いんだよ……");
				link.l1 = RandPhraseSimple("了解だ。","俺が持っていくぜ。");
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
// <-- специальные реакции
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
