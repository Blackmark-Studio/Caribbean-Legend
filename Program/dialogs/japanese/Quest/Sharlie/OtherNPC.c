// диалог прочих и малозначимых НПС
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp;
	string attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "何かご用ですか？";
			link.l1 = "いや、今は違う。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// --> матрос на корабле, прибытие в Сен-Пьер
		case "Startsailor":
			dialog.text = "ちくしょう、やっと陸だ！起きろ、旦那……なんて名前だったか……着いたぞ！";
			link.l1 = "あ、ああ！もう朝か？なんだこのクソ暑さと湿気は！？";
			link.l1.go = "Startsailor_1";
			link.l2 = "おや！シャルル・ド・モール！貴族だぞ、知ってるだろう。この暑さでどうやって酒なんか飲めるんだ？ 私は天に誓って水の方がいいですわ。";
			link.l2.go = "Startsailor_1a";
		break;
		
		case "Startsailor_1":
			dialog.text = "慣れてください、旦那。ここじゃこれが唯一の天気です……もっとひどくなることだってありますよ。";
			link.l1 = "これ以上悪くなることがあるか！？俺はリネンのシャツ一枚しか着てねえのに、背中を汗がだくだく流れてるんだぞ！";
			link.l1.go = "Startsailor_2";			
		break;
		
		case "Startsailor_2":
			dialog.text = "見てろよ、はは！もしかしたらハリケーンの季節かもな！急げ、旦那。ロングボートは待っちゃくれねえぞ。 マルティニークまで泳ぎたいわけじゃねえだろ？";
			link.l1 = "ちょっと待ってくれよ。俺の剣はどこだ？ああ、ここにあった……";
			link.l1.go = "Startsailor_3";			
		break;
		
		case "Startsailor_3":
			dialog.text = "もうヨーロッパにはいないんだ……気をつけてくれ、旦那。今は物騒な時代だ。アメリカ諸島会社がマルティニーク島を宗教狂信者か十字軍か、 そんな連中に売り渡したって噂が流れている。俺はまだ特に変わったことには気づいていないが、 少なくとも甲板から岸を見た限りではな。しかし、俺たちがしばらく留守にしていた間に、色々 と変わってしまったかもしれないな。";
			link.l1 = "十字軍だと？馬鹿な！";
			link.l1.go = "Startsailor_4";			
		break;
		
		case "Startsailor_4":
			dialog.text = "馬鹿げた噂かどうかはともかく、噂は広まってるんだ。こっちはもう十分に厄介ごとを抱えてる。 ジャングルの人食いども、熱帯の病、海賊、路地裏の盗賊――スペイン人やイギリス人のことは言うまでもない……\n";
			link.l1 = "ああ、また始まったか……今のところ俺が感じる厄介ごとは、うだるような暑さと蚊だけだぜ……よし、準備はできてる。行こうか？";
			link.l1.go = "Startsailor_5";			
		break;
		
		case "Startsailor_5":
			dialog.text = "甲板に上がってロングボートに乗り込んでください、旦那。カリブへようこそ！";
			link.l1 = "";
			link.l1.go = "Startsailor_6";			
		break;
		
		case "Startsailor_1a":
			dialog.text = "ここじゃ他の天気なんてねえよ、旦那様。むしろ、悪くなる一方さ。";
			link.l1 = "天気は耐えがたいし、この数ヶ月の私の付き合いも同じくらいひどいものだった。\n諸島にはまともな人間がいることを願うよ。";
			link.l1.go = "Startsailor_2a";
			AddCharacterExpToSkill(pchar, "Leadership", 10);
		break;
		
		case "Startsailor_2a":
			dialog.text = "では、やっとあなたが私たちのもとを去ってくれるのは皆にとって喜ばしいことだと思いますよ、旦那。\nボートはもう待っています。嬉しさのあまりズボンから飛び出さないように。\nそれと、お荷物をお忘れなく――船はさらに先へ進みますから、忘れたらもう取り戻せませんよ。";
			link.l1 = "お前の楽しみのために置いていくわけないだろう。\nペソも剣も……どうやら盗まれてはいないようだな。";
			link.l1.go = "Startsailor_3a";			
		break;
		
		case "Startsailor_3a":
			dialog.text = "俺たちはもちろん正直者だが、用心するに越したことはねえ――自分の持ち物には常に気をつけろよ、さもないと誰かに財布をすられちまうぜ。昔のヨーロッパと同じさ。いや、 どこでもそうか。\nだが、ここは故郷とは違う。ここには狂信者どもが根城を作ってるらしい。噂じゃ、 連中がこの島をこっそり丸ごと買い取ったって話だ。\nだから、油断せず、目立たないようにしとけよ。";
			link.l1 = "なんて馬鹿げたことだ！";
			link.l1.go = "Startsailor_4a";			
		break;
		
		case "Startsailor_4a":
			dialog.text = "それが噂だ。わざわざ教えてやって、ここでの滞在を気遣ってやったことに感謝しろよ。さもないと、 お前の繊細なガスコーニュのバラも、この灼熱の太陽の下じゃすぐに枯れちまうぜ。真偽はともかく、気を抜くな――狂信者抜きでも厄介ごとは山ほどあるんだ。路地やジャングルには盗賊、海には海賊、 そして赤い肌の人喰いどもまでいるからな……\n";
			link.l1 = "まあまあ！大丈夫さ。今はちょっと暑いかもしれないけど、俺は故郷でしっかり日差しに鍛えられてるんだ、 ノルマン人なんかとは違ってな。剣で解決できることなら、俺に任せてくれ。でも蚊だけは…あれは本当に拷問だぜ！さて、持ち物は全部揃ってる。船も準備できてるんだな？\n";
			link.l1.go = "Startsailor_5a";			
		break;
		
		case "Startsailor_5a":
			dialog.text = "心待ちにしているよ。自分で来られるだろうな、旦那？顔を上げて、そこから迷子にならないようにな。ああ、 それと諸島へようこそ、へっへっ。";
			link.l1 = "ああ、ありがとう。せめてもの慰めは、ここに長くいるつもりはないってことだ。";
			link.l1.go = "Startsailor_6";
		break;
		
		case "Startsailor_6":
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_StartGameInMartinique");
		break;
		// <-- матрос на корабле, прибытие в Сен-Пьер
		
		// горожанин знает Мишеля
		case "Benuatalker":
			DelLandQuestMark(npchar);
			link.l1 = "「失礼します」 "+GetAddress_FormToNPC(NPChar)+"、ミシェル・ド・モンペールがどこにいるか教えてもらえますか？彼はこの町のどこかにいるはずです。";
            link.l1.go = "Benuatalker_1";
		break;
		
		case "Benuatalker_1":
			dialog.text = "ふむ……ここに来たばかりのようだな、そんな大胆な質問をするとは……忠告しておくが、やめておけ。さもないと面倒なことになるぞ。質問の件だが……修道院長に聞け。教会にいるはずだ。";
			link.l1 = "ありがとう！";
            link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddDialogExitQuest("Sharlie_SetBenua");
			QuestPointerToLoc("FortFrance_town", "reload", "reload7_back");
		break;
		
		// --> арест в резиденции
		case "Sharlie_arest":
			dialog.text = "止まれ！すぐに武器を渡せ、旦那、そして我々について来い！";
			link.l1 = "「これは一体何だ？」";
			link.l1.go = "Sharlie_arest_1";
			if (CheckCharacterItem(PChar, "knife_03")) pchar.Sharlie.KnifeMonpe = true;
		break;
		
		case "Sharlie_arest_1":
			DialogExit();
			AddDialogExitQuestFunction("Sharlie_enterSoldiers_2");
		break;
		// арест в резиденции
		
		// --> офицер базы
		case "Maltie_officer":
			ref location = &Locations[FindLocation(pchar.location)];
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "begin")
			{
				dialog.text = "お会いできて嬉しいです、de Maure様。今日はどんなご用件ですか？";
				link.l1 = TimeGreeting()+"「旦那、私の兄ミシェル・ド・モンペールについてお話ししたいのです。もちろん、これは非公式な話です。 カリブでの彼の勤務について知りたいのですが。」";
				link.l1.go = "spanish";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
			{
				dialog.text = "尋問はどうだった？何か価値のある情報は見つかったか？";
				link.l1 = "ああ、そうさ。だからこのスペイン野郎を俺の船に連れて帰るんだ。こいつは重要な証人で、 さらなる尋問のためにセントクリストファーへ連れて行かねえといけねえんだ。";
				link.l1.go = "spanish_10";
				break;
			}
			if (!CheckAttribute(location, "first_meeting"))
			{
				dialog.text = "ここでのご用件は何です、旦那？";
				link.l1 = "私は兄のミシェル・ド・モンペールに会いに来ました。";
				link.l1.go = "Maltie_officer_1";
				location.first_meeting = true;
			}
			else
			{
				dialog.text = "旦那、ここは軍の駐屯地でございますので、どうかそれにふさわしい振る舞いをお願いいたします。";
				link.l1 = "はい、旦那。もちろんです。";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
			
			if (SandBoxMode)
			{
				dialog.text = "旦那、ここは軍の駐屯地内でございますので、どうかそれにふさわしい振る舞いをお願いいたします。";
				link.l1 = "はい、旦那。もちろんです。";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
		break;
		
		case "Maltie_officer_1":
			DelLandQuestMark(npchar);
			dialog.text = "ミシェル・ド・モンペールは現在、シュヴァリエ・フィリップ・ド・ポワンシーの直々の命令で、我々 のカズマットの一つで監視下に置かれている。\n階下の下層へ向かいなさい。そこには我々が倉庫や牢として使っているカズマットがある。\n道は自分で見つけられると思う。";
			link.l1 = "ありがとう！";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_officer";
			QuestPointerToLoc("FortFrance_Dungeon", "quest", "quest1");
		break;
		// офицер базы
		
		// --> солдаты базы
		case "Maltie_soldier":
			dialog.text = "こんにちは、旦那。何かお手伝いできますか？";
			link.l1 = "ありがとう、兵士。しかし、いや、大丈夫だ。続けてくれ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_soldier";
		break;
		// --> солдаты базы
		
		// --> мальтиец-проводник
		case "Sharlie_maltie":
			dialog.text = "お待たせしました、旦那。さて、あなたはミシェル・ド・モンペをお探しですか？彼の弟さんですか？";
			link.l1 = "はい、その通りです。私は彼の弟シャルルです。すぐに彼に会わなければなりません。ミシェルは困っているのですか？";
			link.l1.go = "Sharlie_maltie_1";			
		break;
		
		case "Sharlie_maltie_1":
			dialog.text = "残念ながら、その通りでございます、旦那。ミシェル様は下のカズマットの一つに閉じ込められております。 新世界におけるフランス植民地の総督、シュヴァリエ・ド・ポワンシー閣下が自ら逮捕命令に署名されました。我々一同、 大変な衝撃を受けました。ご兄弟は男らしい美徳、規律、勇気の模範であり、我が騎士団の誇りでございます！ 最も辛いのは、我々友人が彼を牢に閉じ込め、まるで普通の犯罪者のように見張らねばならぬことです！ できる限り快適に過ごせるよう努めておりますが……牢獄はやはり牢獄でございます。";
			link.l1 = "彼は何の罪で訴えられているんだ？何か犯罪を犯したのか？";
			link.l1.go = "Sharlie_maltie_1_1";			
		break;
		
		case "Sharlie_maltie_1_1":
			dialog.text = "総督府がミシェルを横領の罪で告発したんだ！馬鹿げている！ここにいる全員が、 これは政治的な動機によるものだと確信しているよ。内緒で教えてあげよう。 ミシェルは騎士団のためにいくつかの秘密工作に関わっていたんだ。もしかすると、知りすぎてしまったのかもしれない。 あるいは、もっと悪くすれば、権力者たちを怒らせたのかもな。でも金を盗んだ？そんなこと誰も信じちゃいない。 あれは口実、本当の理由じゃない、卑怯で卑劣な口実さ！まあ、もう十分話したな。 君の兄上は君に会うのを楽しみにしているよ。きっと自分の口からすべて話してくれるだろう。";
			link.l1 = "よし。お前たちの牢獄はどこにあるんだ？";
			link.l1.go = "Sharlie_maltie_1_2";
		break;
		
		case "Sharlie_maltie_1_2":
			dialog.text = "この街の地下武器庫にあるんだ。ついて来い。案内してやる。";
			link.l1 = "...";
			link.l1.go = "Sharlie_maltie_2";
		break;
		
		case "Sharlie_maltie_2":
			DialogExit();
			AddDialogExitQuestFunction("Sharlie_Maltie_DlgExit_1");
		break;
		
		case "Sharlie_maltie_3":
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Maltie_officer"), "questmarkmain");
			dialog.text = "ここだ。我々の作戦拠点、聖ヨハネ騎士団カリブ支部だ。エルサレム、ロドス、マルタの軍事病院騎士団の拠点でもある。 カスマット（地下要塞）はこの下にある。廊下を進み、食堂と礼拝堂を通り過ぎろ。そこに階段があるから、 それを下りれば下層に行ける。牢が並ぶ廊下を探せ。奥の方の牢に君の兄がいるはずだ。\n行きなさい、シャルル。そして神のご加護を。どうかミシェルを助けて！彼は無実だと、ここにいる全員が誓える。";
			link.l1 = "俺がこんなクソみたいな場所に来たのは全部兄貴に会うためだったんだ。せめてこの窮地から助け出せればいいんだがな。 ";
			link.l1.go = "Sharlie_maltie_4";
		break;
		
		case "Sharlie_maltie_4":
			DialogExit();
			AddDialogExitQuestFunction("Sharlie_Maltie_DlgExit_2");
		break;
		
		//belamour cle -->
		case "Sharlie_maltieA":
			dialog.text = "つまり、ミシェル・ド・モンペを探していたのか？それで、お前が彼の弟なのか？";
			link.l1 = "はい、その通りです。私は彼の弟シャルルです。すぐに彼に会う必要があります。彼、 何かトラブルに巻き込まれたんでしょう？";
			link.l1.go = "Sharlie_maltie_1a";			
		break;
		
		case "Sharlie_maltie_1a":
			dialog.text = "残念ながら、その通りでございます、旦那。ミシェルは逮捕され、我々の牢に拘束されております。 フランス植民地の総督、シュヴァリエ・ド・ポアンシー閣下自らが命令を下し、署名なさいました。我々一同、 大変な衝撃を受けました。\nご兄弟は男らしさ、強さ、勇気の象徴であり、我が騎士団の誇りです！最も辛いのは、我々友人が彼の独房に鍵をかけ、 罪人として見張らねばならぬことです！できる限り彼の境遇を和らげようと努めておりますが……牢は牢でございます。";
			link.l1 = "それで、彼は何の罪で告発されているんだ？何か犯罪を犯したのか？";
			link.l1.go = "Sharlie_maltie_1_1a";			
		break;
		
		case "Sharlie_maltie_1_1a":
			dialog.text = "馬鹿げている！全くの馬鹿げた話だ！ミシェルが横領や国庫金の盗難で告発されたなんて、ありえない！我々全員、 これは単なる政治的な駆け引きに過ぎないと確信している。ミシェルは騎士団の秘密任務に関わっていたから、 もしかすると知ってはいけないことまで知ってしまったのかもしれん。\nあるいは他の何かだ。しかし金を盗んだなど、誰も信じていない。ただの口実に過ぎん、本当の理由ではない――しかも実に稚拙で愚かな口実だ！もうこの話はやめよう。君の兄上は君に会えるのを楽しみにしている、 ご本人がすべて話してくれるだろう。";
			link.l1 = "よし。牢屋はどこにある？";
			link.l1.go = "Sharlie_maltie_1_2a";
		break;
		
		case "Sharlie_maltie_1_2a":
			dialog.text = "それはこの街の地下基地にあるんだ。\nついて来い。案内してやるよ。";
			link.l1 = "...";
			link.l1.go = "Sharlie_maltie_2a";
		break;
		
		case "Sharlie_maltie_2a":
			DialogExit();
			AddDialogExitQuestFunction("Sharlie_Maltie_DlgExit_3");
		break;
		//<-- cle
		// мальтиец-проводник
		
		// --> найм матросов
		case "Sharlie_sailor":
			DelLandQuestMark(npchar);
			dialog.text = "そしたら奴は手すりに身を乗り出して、あまりにも大量に吐いたもんだから、 カリブ海そのものが緑色になっちまったんだ！ハハハ！";
			link.l1 = "「アロンソ？」";
			link.l1.go = "Sharlie_sailor_1";
		break;
		
		case "Sharlie_sailor_1":
			dialog.text = "おお！シャルル、ちょうど俺たちの武勇伝を皆に語っていたところだぜ！";
			link.l1 = "気づいたよ。聞いてくれ、アロンソ。俺は……船長になったんだ。";
			link.l1.go = "Sharlie_sailor_2";
		break;
		
		case "Sharlie_sailor_2":
			dialog.text = "もう終わったのか？少なくとも一ヶ月はかかると思ってたぜ、ははっ！";
			link.l1 = "私は本気です！";
			link.l1.go = "Sharlie_sailor_3";
		break;
		
		case "Sharlie_sailor_3":
			dialog.text = "もし自分ひとりだけなら、すぐにでも参加するさ。だが、俺にはユリシーズ号から連れてきた四十人の仲間がいる。 奴らは自分の未来を俺に託してくれたんだ。お前があいつらを裏切らないと確信しなきゃならねえ\n"+
			"どんな船を持っているんだ？";
			link.l1 = "「船は船だ」 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype),"Name")))+"「……なぜ、そんなに重要なのか？」";
			link.l1.go = "Sharlie_sailor_4";
		break;
		
		case "Sharlie_sailor_4":
			dialog.text = "あんたな、ユリシーズ号の後じゃ、バルク船やタルタンなんかに乗りたかねえよ。もうあんたの船は見せてもらったし、 連中も気に入ってるぜ\n"+"さて、金の話だ。前金で4,800ペソ要求するぜ。あとはいつも通り取り分を分ける。不当なことは言ってねえ、安心しな。払えるか？";
			if (sti(Pchar.money) >= 4800)
			{
				link.l1 = "よくやった！これが報酬の金貨だ。";
				link.l1.go = "Sharlie_sailor_5";
			}
			link.l2 = "残念ながら、今はそんなに多くのお金を持っていません。";
			link.l2.go = "Sharlie_sailor_nomoney";
		break;
		
		case "Sharlie_sailor_5":
			if (GetSquadronGoods(pchar, GOOD_FOOD) < 20 || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < 30)
			{
				dialog.text = "船長、船倉に食料はあるか？薬は？ないのか？それじゃ困るぜ。航海に必要な最低限の物を調達してから戻ってきな。\n店に行って必要な物を手に入れてこい。";
				link.l1 = "ふむ。君の言う通りだな。よし、そうしよう。";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				AddMoneyToCharacter(pchar, -4800);
				dialog.text = "バッ！おめでとう……船長！すぐに野郎どもを集めて、あんたの船に向かうぜ。";
				link.l1 = "また冒険を再開できて嬉しいぜ、アロンソ。船を出航の準備にかかれ！";
				link.l1.go = "Sharlie_sailor_6";
			}
		break;
		
		case "Sharlie_sailor_6":
			DialogExit();
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "Fortfrance_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
			SetCrewQuantityOverMax(PChar, 40);
			pchar.Ship.Crew.Morale = 50;
			pchar.Ship.Crew.Exp.Sailors = 50;
			pchar.Ship.Crew.Exp.Cannoners = 50;
			pchar.Ship.Crew.Exp.Soldiers = 50;
			AddQuestRecord("Sharlie", "7");
			pchar.questTemp.Sharlie = "skiper";
			DeleteAttribute(pchar, "GenQuest.CannotWait");//снимаем запрет, если не был снят раньше
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
		break;
		
		case "Sharlie_sailor_nomoney":
			dialog.text = "まあ、金が十分に集まったら戻ってこいよ。俺たちはここ酒場にいるぜ。どうせ他に船なんていねえしな。 俺たちは飲んで女遊びして金を使い果たすだけさ、ハハハ！";
			link.l1 = "できるだけ早く戻るようにするよ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Sharlie_sailor_again";
		break;
		
		case "Sharlie_sailor_again":
			dialog.text = "戻ったのかい、船長？俺や仲間たちを雇う気はできたか？財布が軽くなってきてよ、また潮風を顔で感じたいんだ！";
			if (sti(Pchar.money) < 4800)
			{
				link.l1 = "まだだ、今はまだ準備中なんだ。";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				link.l1 = "ああ。前金を受け取れ。これでお前は俺の配下だ。";
				link.l1.go = "Sharlie_sailor_5";
			}
		break;
		// найм матросов
		
		// наводчик на штурмана
		case "skipertalker":
			DelLandQuestMark(npchar);
			dialog.text = LinkRandPhrase("おう、船長！何の用だ？","こんにちは、旦那。ご用件は何でしょうか？","ごきげんよう。ご用件は何ですか？");
			link.l1 = RandPhraseSimple("お前に聞きたいことがあるんだ。","この植民地についての情報が必要だ。");
			link.l1.go = "skipertalker_1";
			link.l2 = "挨拶だけさ。オルヴォワール！";
			link.l2.go = "exit";
			NextDiag.TempNode = "skipertalker";
		break;
		
		case "skipertalker_1":
			dialog.text = RandPhraseSimple("何だ？","何の用だ？");
			link.l1 = "「聞け、」 "+GetAddress_FormToNPC(NPChar)+"……それでだが……俺は航海士を探している。この町でその仕事にふさわしい者を知っていたら教えてくれないか？";
			link.l1.go = "skipertalker_2";
		break;
		
		case "skipertalker_2":
			dialog.text = "航海士か？ふむ。まあ、一人知ってるが……ただ一つ問題がある――あいつは今、牢屋に入ってるんだ、借金牢にな。可哀想に、 もうかれこれ一ヶ月近くもカスマットに閉じ込められてるんだよ、奴か誰かが借金を払うまでな。";
			link.l1 = "借金者か？ふむ……名前は何だ？";
			link.l1.go = "skipertalker_3";
		break;
		
		case "skipertalker_3":
			dialog.text = "あいつの名前はフォルク・デルックだ。面会したいなら牢屋の司令官に聞いてみな。だが、 あんたが奴の借金を払わない限り、あいつを出してくれるとは思えねえぜ。本人が払う気なんてさらさらねえからな、 ははは！";
			link.l1 = "そうするかもな。情報をありがとう、友よ。";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie = "jailskiper";
			AddQuestRecord("Sharlie", "8");
			LocatorReloadEnterDisable("Fortfrance_town", "reload_jail", false);
			SetFunctionLocationCondition("FortfranceJailOff_AddQuestMark", "fortfrance_prison", false);
		break;
		
		// --> штурман
		case "Folke":
			dialog.text = "「このような光栄にあずかるとは、いったい何のご用でしょう、旦那？」";
			link.l1 = "やあ、Folke。話は簡単だ。俺は船を手に入れたが、航海士がいない。だから必要なんだ。それで、お前の借金を肩代わりしたんだよ…";
			link.l1.go = "Folke_1";
		break;
		
		case "Folke_1":
			dialog.text = "「俺をここから引っ張り出したのは、自分の船の仲間にするためだったってのか？」";
			link.l1 = "その通りだ。君に使った金はすぐに取り戻せると思っているよ。まあ……どうなるか見てみよう。";
			link.l1.go = "Folke_2";
		break;
		
		case "Folke_2":
			dialog.text = "感謝します、旦那。こんな腐った湿っぽい牢屋にはもううんざりだ。もう一度船に戻れるなんて、 これほど嬉しいことはない。ああ、海よ…";
			link.l1 = "理解し合えて嬉しいよ、Folke。もう一つ聞きたいんだが、船を操縦する以外に何か他の技能はあるか？";
			link.l1.go = "Folke_3";
		break;
		
		case "Folke_3":
			dialog.text = "何でも少しずつできますよ、船長。昔はオランダ西インド会社の私掠船で働いていました。 そこで大砲の扱いを覚えたので、必要なら砲術士官としてお仕えできます。ただ、 交易と白兵戦はあまり得意じゃありません。";
			link.l1 = "話してくれてありがとう、さあ俺についてきて船へ行こう。出航の準備をする船員たちを、 その経験豊かな目で見ていてほしいんだ。\nそれが終わったら、できるだけ早くグアドループへ向かいたい。";
			link.l1.go = "Folke_4";
		break;
		
		case "Folke_4":
			dialog.text = "了解だぜ、船長！船室で待ってるからな。\n※航海中にアクションメニューを使えば、船室や他の船内エリアに入れるぞ";
			link.l1 = "ありがとう、Folke。また船で会おう。";
			link.l1.go = "Folke_5";
			Log_Info("You have received amulet 'Merchant's Rosary'");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "obereg_8");
			if(CheckAttribute(pchar,"systeminfo.tutorial.Amulet"))
			{
				DoQuestFunctionDelay("Tutorial_Amulet", 0.1);
			}
		break;
		
		case "Folke_5":
			DialogExit();
			EndQuestMovie();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			AddQuestRecord("Sharlie", "10");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_skiper.win_condition.l1 = "location";
			pchar.quest.Sharlie_skiper.win_condition.l1.location = "My_Cabin_Small";
			pchar.quest.Sharlie_skiper.function = "Sharlie_SkiperTalk";
			//прерывание на засаду пиратов - принудительный квест
			pchar.quest.Sharlie_seabattle.win_condition.l1 = "location";
			pchar.quest.Sharlie_seabattle.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_seabattle.function = "SharlieSeabattle_agent";
			
			pchar.quest.NewGameTip2.win_condition.l1 = "location";
			pchar.quest.NewGameTip2.win_condition.l1.location = "Martinique";
			pchar.quest.NewGameTip2.function = "ShowNewGameTip";
			pchar.quest.NewGameTip2.text = "Your first officer is waiting for you. Use the action menu (ENTER) to go to the cabin.";
		break;
		
		case "Folke_6":
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин 250912
			dialog.text = "いいラガー船ですね、船長！帆装も立派で船体もしっかりしている、なかなかの小型船です。こんな船があれば、 グアドループまで無事に行けるだけじゃなく、望めばカリブ中を巡航することだってできそうですよ。";
			link.l1 = "素晴らしい。少なくとも金を穴の開いたボロ船に捨てずに済んだな……出航前に何か助言はあるか、フォルケ？";
			link.l1.go = "Folke_8";
		break;
		
		case "Folke_7":
			dialog.text = "くそっ、このスループはザルみたいに水漏れしてるぜ、船長。グアドループまでたどり着けるかどうか、際どいところだ。 \nバステールに無事に着きたいなら、すぐにでも造船所で修理しなきゃならねえぞ。";
			link.l1 = "選択肢なんてなかったんだ、これしか売りに出てる船がなかったんだよ！しかも、えらく高い金をふんだくられたぜ。 ご存知の通り、今は修理してる暇もねえ……出航前に何かアドバイスはあるか？";
			link.l1.go = "Folke_8";
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_BALLS) >= 80) && (GetSquadronGoods(pchar, GOOD_GRAPES) >= 80) && (GetSquadronGoods(pchar, GOOD_KNIPPELS) >= 80) && (GetSquadronGoods(pchar, GOOD_BOMBS) >= 80) && (GetSquadronGoods(pchar, GOOD_POWDER) >= 180);
		case "Folke_8":
			if (bOk)
			{
				dialog.text = "弾薬と火薬は十分に備えていますぜ、船長。今のところはこれで大丈夫ですが、補給は早めにお願いしますよ。";
				link.l1 = "まあ、それは言うまでもないだろう。他に意見はあるか？";
				link.l1.go = "Folke_10";
				if (CheckCharacterItem(PChar, "BoxOfBalls"))
				{
					link.l2 = "あっ！思い出させてくれてありがとう。ちょうど弾薬の箱を一箱持ってきているんだ！";
					link.l2.go = "Folke_8_1";
				}
			}
			else
			{
				dialog.text = "弾薬庫に弾が足りません、船長。最低でも砲弾、チェーンショット、爆弾をそれぞれ百発ずつ、ぶどう弾の袋を百袋、 火薬の樽を二百樽は必要です。\n必要な物資を購入してください、船長。大した金額じゃありませんが、海賊やスペイン人に襲われた時、 俺たちの命を救うかもしれませんぜ。";
				link.l1 = "価値ある投資だな。これから商人のところへ行ってくる。";
				link.l1.go = "Folke_9";
			}
		break;
		
		case "Folke_8_1":
			dialog.text = "「……それをどれくらいの間、引きずってきたんだ？」";
			link.l1 = "ほぼ二週間になる。";
			link.l1.go = "Folke_8_2";
			TakeItemFromCharacter(pchar, "BoxOfBalls");
			//AddCharacterGoodsSimple(sld, GOOD_BALLS, 10);
			Achievment_Set("ach_CL_164");
		break;
		
		case "Folke_8_2":
			dialog.text = "「でも、なんでだよ、船長！？」";
			link.l1 = "私はガラクタを集めるのが好きなんだ。何が役に立つか分からないからな。";
			link.l1.go = "Folke_8_3";
		break;
		
		case "Folke_8_3":
			dialog.text = "まあ、お前さんには残念だったな。この弾じゃ俺たちの玩具みたいな銃には絶対使えねえよ。実際、 こんなでかい弾は見たこともねえ。こんなの一発食らったらアデリーヌ号も海の底行きだぜ。";
			link.l1 = "...";
			link.l1.go = "Folke_10";
		break;
		
		case "Folke_9":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_1";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "12");
		break;
		
		case "Folke_goods_1":
			dialog.text = "弾薬の購入は終わりましたか、船長？";
			if (bOk)
			{
				link.l1 = "ああ、あるぜ。他に何か言いたいことはあるか？";
				link.l1.go = "Folke_10";
			}
			else
			{
				link.l1 = "今はまだだ、まだ作業中なんだ。";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_1";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_WEAPON) >= 50);
		case "Folke_10":
			if (bOk)
			{
				dialog.text = "よくやった、乗組員のために十分な武器を買い揃えたな。武器が足りなければ、 斬り込みの際にもっと多くの仲間を失うことになる。神よ、そんな事態から我々をお守りください。 貨物室の在庫はこまめに確認するのを忘れるな\n必要な分より少し多めに武器を持っておくのが賢明だ。 くそったれなネズミどもが木の柄や銃床をかじるのが好きだからな。";
				link.l1 = "承知しました。まだ何か付け加えたいことがあるのですね？";
				link.l1.go = "Folke_11";
			}
			else
			{
				dialog.text = "船内には乗組員全員分の武器が足りていない。武器が不足していれば、斬り込みの際にもっと多くの犠牲者が出るだろう。 神よ、そんな事態から我々をお守りください。私の理解では、あなたの乗組員は四十人いるようだ\n全員分、いや、予備も含めて武器を買い揃えた方がいい。五十セットあれば十分だろう。 必要数より少し多めに持っておくのが賢明だ。くそったれなネズミどもが木製の柄や銃床をかじるのが好きだからな。";
				link.l1 = "そうしよう。すぐ戻る。";
				link.l1.go = "Folke_10_1";
			}
		break;
		
		case "Folke_10_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_2";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "13");
		break;
		
		case "Folke_goods_2":
			dialog.text = "武器の購入は終わりましたか、船長？";
			if (bOk)
			{
				link.l1 = "武器は船倉にある。まだ何か追加したいことがあるのか？";
				link.l1.go = "Folke_11";
			}
			else
			{
				link.l1 = "今はまだだ、まだ作業中なんだ。";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_2";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_FOOD) >= 100) && (GetSquadronGoods(pchar, GOOD_RUM) >= 10);
		case "Folke_11":
			if (bOk)
			{
				dialog.text = "いや、これで十分だと思う。食料も足りているし、乗組員のラムもちゃんと用意してくれたな。賢明だぜ、 勤務の後に冷えたラムを一杯やるほど、あらゆる病に効く薬はねえからな。\n毎日ラムを配る船長は水夫たちに愛され、尊敬されるもんだ。\n「なぜラムがなくなったんだ？」なんて部下に言わせちゃいけねえぜ。";
				link.l1 = "今すぐ出航できるか？";
				link.l1.go = "Folke_12";
			}
			else
			{
				dialog.text = "ああ。食糧とラム酒だ。船に十分な食糧がないのは致命的だぜ。必要だと思うより多めに積んでおけ。 航海がどれだけ長引くか分からねえ――無風や嵐でどんな計画も台無しになる。食糧が尽きりゃ、船員は反乱を起こすか飢え死にするだけさ\nラム酒の備蓄はそこまで重要じゃねえが、必ず多少は積んでおけと強く勧めるぜ。 持ち場を終えた後の冷えたラム一杯ほど、あらゆる不調に効く薬はねえ。船員ってのは、毎日ラムを配る船長を愛し、 敬うもんだ\nだから必要な物資を買ってこい――食糧は最低百箱、ラム酒は十樽だ。船員に「ラムはどこ行った？」なんて言わせるなよ";
				link.l1 = "おっしゃる通りかもしれません。もう一度商人に話をしに行きます。";
				link.l1.go = "Folke_11_1";
			}
		break;
		
		case "Folke_11_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_3";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "14");
		break;
		
		case "Folke_goods_3":
			dialog.text = "俺たちの食料とラムの買い出しは終わったか、船長？";
			if (bOk)
			{
				link.l1 = "はい。もう出航できますか？";
				link.l1.go = "Folke_12";
			}
			else
			{
				link.l1 = "いいえ、まだ取り組んでいるところだ。";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_3";
			}
		break;
		
		case "Folke_12":
			dialog.text = "あいよ、船長。ご希望通り、錨を上げてグアドループへ北上できますぜ。";
			// belamour legendary edition -->
			link.l1 = "よくやったな、Folke。お前がいなけりゃ俺は無理だったぜ。";
			link.l1.go = "Folke_13";
			link.l2 = "よし、仕事に取りかかろう。お前が金に見合う価値があるか見せてもらうぞ。";
			link.l2.go = "Folke_13a";
		break;
		
		case "Folke_13a":
			Npchar.loyality = makeint(Npchar.loyality) - 5;
			ChangeCharacterComplexReputation(pchar,"authority", 5);
			dialog.text = "それなら俺を航海士に任命してくれ、そうすりゃ甲板に立つぜ。";
			link.l1 = "...";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_13":
			Npchar.loyality = makeint(Npchar.loyality) + 5;
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			// <-- legendary edition
			dialog.text = "それなら俺を航海士に任命してくれ、そうすりゃ甲板に立つぜ。";
			link.l1 = "...";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_14":
			DialogExit();
			LAi_SetStayType(npchar);
			LAi_SetImmortal(npchar, false);
			AddQuestRecord("Sharlie", "15");
			pchar.questTemp.Sharlie = "seabattle";//в Ле Франсуа
			DeleteAttribute(pchar, "NoNavyPenalty"); // штрафуем за нехватку навигации
			
			npchar.quest.OfficerPrice = 20;
			npchar.loyality = 30;
			
			// --> копипаста LandEnc_OfficerHired
			AddPassenger(pchar, npchar, false);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			// <--
			
			pchar.questTemp.HelenDrinking.TakeFolke = true;
			
			DoQuestFunctionDelay("Tutorial_Navigator2", 1.0);
			//DoQuestFunctionDelay("Ngt_FolkeEng", 3.0);
			//NewGameTip("Welcome aboard your new officer! Press F4 to assign him as your Navigator.");
			pchar.questTemp.Sharlie.FolkeWait = true;
			LocatorReloadEnterDisable("My_Cabin_Small", "reload1", true);
			NextDiag.CurrentNode = "Folke_wait";
		break;
		
		case "Folke_wait":
			dialog.text = "出航の準備はできてますぜ、船長！";
			link.l1 = "...";
			
			if (!CheckAttribute(npchar, "navigator")) {
				dialog.text = "船長、俺を航海士にしてくれ、さもないとすぐに座礁しちまうぞ。";
				link.l1 = "了解だ、今すぐやるぜ。";
			}
			
			link.l1.go = "exit";
			NextDiag.TempNode = "Folke_wait";
		break;
	
		// штурман

	// --> пират-обманщик
		case "Seabattle_pirate":
			dialog.text = "申し訳ありません。 "+GetFullName(pchar)+"?";
			link.l1 = "その通りです。今回のお礼はどうすればよろしいですか、旦那？";
			link.l1.go = "Seabattle_pirate_1";
		break;
		
		case "Seabattle_pirate_1":
			dialog.text = "自己紹介させていただきます—— "+GetFullName(npchar)+"……セザール・クレイグに頼まれてここへ来たんだ。あんたも知ってるだろう。ル・フランソワの酒場の主人さ。彼の話では、 あんたはグアドループへ出発するところらしい。彼がちょっとした楽な稼ぎ話を持ってきたんだ。";
			link.l1 = "ふむ……面白いな！それで、どうしてセザール・クレイグはそんなに詳しいんだ？";
			link.l1.go = "Seabattle_pirate_2";
		break;
		
		case "Seabattle_pirate_2":
			dialog.text = "簡単なことだぜ、船長。今サン・ピエールにいる船はあんたの船だけだ。耳が二つ、目が一つでもあれば、 あんたが誰でどこへ向かうかなんてすぐに知れ渡るさ。こっちの植民地じゃ、噂はカモメより速く飛ぶんだ。\nそれで、俺たちの提案を聞く気はあるか？";
			link.l1 = "ああ、もちろんだ。稼げる話には反対しねえよ。";
			link.l1.go = "Seabattle_pirate_3";
		break;
		
		case "Seabattle_pirate_3":
			dialog.text = "そうこなくちゃな、相棒！あんた、商売の勘が鋭いな。話はこうだ。 セザールが急ぎでワインをグアドループに届けてほしいんだ。樽二百本、あんたの船の船倉なら余裕だろ。 報酬は一万ペソ、楽な仕事さ――セザールは急いでるし、今この港にいるのはあんたの船だけだ。こんなうまい話、めったにないぜ。\n";
			link.l1 = "くそっ、一万ペソだと？まあ、話はまとまったな！";
			link.l1.go = "Seabattle_pirate_4";
		break;
		
		case "Seabattle_pirate_4":
			dialog.text = "ル・フランソワへ行ってセザールと話せ。あいつが全部手配してくれる。 お前はル・フランソワのすぐ外の湾に錨を下ろすだけでいいんだ。俺をがっかりさせるなよ、 セザールがもしお前を説得できたら千ペソくれるって約束してくれたんだからな…\n";
			link.l1 = "心配しないで、納得したよ。出発の準備ができ次第、すぐにル・フランソワへ直行する。";
			link.l1.go = "Seabattle_pirate_5";
		break;
		
		case "Seabattle_pirate_5":
			dialog.text = "万歳！俺は千枚取りに行ってくるぜ。ありがとな、相棒！";
			link.l1 = "どういたしまして……";
			link.l1.go = "Seabattle_pirate_6";
		break;
		
		case "Seabattle_pirate_6":
			DialogExit();
			AddLandQuestMark(characterFromId("LeFransua_tavernkeeper"), "questmarkmain");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "", -1);
			AddQuestRecord("Sharlie", "11");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.location = "None";
		break;
	// пират-обманщик

	// офицер Гриффондора
		case "griffondor_officer":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;

	// командир абордажной роты по защите Сен-Пьера
		case "rosetti":
			PlaySound("Voice\English\EvilPirates01.wav");
			dialog.text = "船長、斬り込み隊の編成が完了し、準備万端です！ご命令をお待ちしております！";
			link.l1 = "";
			link.l1.go = "rosetti_1";
		break;
		
		case "rosetti_1":
			DialogExit();
			bDisableCharacterMenu = true;//лоченые интерфейсы
			ChangeShowIntarface();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("DefendSP_soldier_0"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Blaze");
			sld.dialog.filename = "MainHero_dialog.c";
			sld.dialog.currentnode = "SP_defend";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rosetti_2":
			PlaySound("interface\abordage_wining.wav");
			dialog.text = "了解だぜ、船長！準備しろ、野郎ども、船長について来い！よし、いち・に・さん！";
			link.l1 = "";
			link.l1.go = "rosetti_3";
		break;
		
		case "rosetti_3":
			DialogExit();
			PlaySound("interface\abordage_wining.wav");
			bDisableCharacterMenu = false;//лоченые интерфейсы
			ChangeShowIntarface();
			for (i=0; i<=12; i++)
			{
				sld = CharacterFromID("DefendSP_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// прерывание на джунгли перед выходом из города
			pchar.quest.DefendSP_jungle1.win_condition.l1 = "location";
			pchar.quest.DefendSP_jungle1.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.DefendSP_jungle1.function = "DefendSP_SpainPatrol";
		break;
		
		case "spain_patrol":
			dialog.text = "くそっ、フランスの援軍だ！隊列を組め！ロレンソ、野営地に行って警報を鳴らせ！死ね、この野郎ども！\n";
			link.l1 = "...";
			link.l1.go = "spain_patrol_1";
		break;
		
		case "spain_patrol_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DefendSP_spapatrol_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "DefendSP_SpaPatrolDie");
				AddDialogExitQuest("MainHeroFightModeOn");
			}
			sld = CharacterFromID("DefendSP_spapatrol_5");
			LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "DefendSP_GateAlarm", -1);
		break;

	// страж истины
		case "spanish":
			dialog.text = "私にはそのような情報を開示する権限がないことを理解していますか？";
			link.l1 = "私の迅速な介入があったからこそ、サン・ピエールはスペイン人に蹂躙されずに済んだのだと理解しているか？\n兄は姿を消し、修道会を捨ててしまった！何か理由があったに違いない。\n私はフィリップ・ド・ポワンシー卿の代理人として、調査する権限がある！";
			link.l1.go = "spanish_1";
		break;
		
		case "spanish_1":
			dialog.text = "わかった、わかったよ、ド・モール旦那。質問には答えてやるから、まずは落ち着け。さあ、何でも聞いてくれ。";
			link.l1 = "ミシェルが監禁される前に何があったんだ？";
			link.l1.go = "spanish_2";
		break;
		
		case "spanish_2":
			dialog.text = "ミシェル・ド・モンペールはトルトゥーガで政権交代を企てるため、海賊男爵たちと交渉していた。";
			link.l1 = "それはもう知っている。他には？";
			link.l1.go = "spanish_3";
		break;
		
		case "spanish_3":
			dialog.text = "彼はまた、スペイン人に対する別の作戦も計画していたんだ。具体的には、貴重な積荷を運ぶスペイン船の拿捕だ。 ミシェルは標的を重コルベット艦『グリフォン・ドール』の砲門の下に誘い込む役目だった。この計画中、 しばらくの間ミシェルの姿をまったく見かけなかった。\nだが計画は狂った。スペインの輸送船は現れず、 ミシェル自身はル・マラン湾の岸に打ち上げられているのを地元の漁師に発見された――半死半生の状態でな。作戦は失敗だったようだ。\n戦争は戦争、物事はうまくいかないものだ。ミシェルが生きていたのは奇跡だったが、ポワンシー騎士は激怒した。 ミシェルが騎士団の金を横領したと非難し、投獄してしまった。もちろん、我々はそんな言いがかりは信じていない。 ミシェルは誠実な男であり、真の騎士団の騎士だ。総督がなぜあそこまで怒ったのかは神のみぞ知る。もしかしたら、 ポワンシー騎士自身が君に説明してくれるかもしれないな？";
			link.l1 = "たぶんね。それだけしか知らないのか？";
			link.l1.go = "spanish_4";
		break;
		
		case "spanish_4":
			dialog.text = "残念ながら、これ以上申し上げることはありません。あなたの兄上の行動の詳細は、 本人とポワンシー騎士だけが知っておりました。\n我々はマルタ聖ヨハネ騎士団の騎士です。命令を遂行するのみです。";
			link.l1 = "シュヴァリエがそんなにミシェルを信頼しているなら、以前にも秘密の計画をうまくやり遂げたことがあるに違いない。\nミシェルが成功させた作戦について、何かご存知ですか？";
			link.l1.go = "spanish_5";
		break;
		
		case "spanish_5":
			dialog.text = "間違いありません。ミシェル・ド・モンペールの今回の失敗は彼にとって初めてのことだったので、 シュヴァリエの反応には私たちも驚きました。つい最近も、ミシェルの綿密な計画のおかげで『グリフィンドール』 が銀を満載したスペインの財宝ガレオン船を拿捕したばかりです。それだけでも、 将来の何十回もの失敗を補って余りあるはずでした。それなのに、あなたの兄上は逮捕されてしまいました。";
			link.l1 = "なるほど。ミシェルがサン・ピエールから逃げた理由に心当たりはありますか？";
			link.l1.go = "spanish_6";
		break;
		
		case "spanish_6":
			dialog.text = "私は、ミシェルとド・ポワンシーの間の人間関係のもつれが彼の逮捕の原因だったのではないかと疑っています。 明らかに、あなたの兄上は釈放後もシュヴァリエが自分を追い詰め続けることを恐れ、予防策を講じたのでしょう。 そしてね、ド・モール旦那——ここにいる誰もが彼のその判断を責めてはいません！\nあの男は騎士団のために勇敢に働いてきたのに、たった一度の失敗で、しかも重傷を負っている最中に、 悪臭漂う牢屋に放り込まれたんです！しかもその失敗だって大したものじゃない、誰も死んでいないし船も沈んでいない！ \nところで、この話は絶対に内密ですし、私は今言ったことをたとえ宣誓の場でも繰り返しませんよ、いいですね、 ド・モール旦那？";
			link.l1 = "はい、旦那。もうこの会話のことはすっかり忘れましたよ。さて、スペインによるサン・ピエール襲撃は、 騎士団がスペインの船を襲ったことが原因だったのでしょうか？ あなたが言っていたあの銀を積んだスペインのガレオン船かもしれませんね。 カスティーリャ人はあなた方の拠点を探し出すのに異常なほど熱心でしたから……\n";
			link.l1.go = "spanish_7";
		break;
		
		case "spanish_7":
			dialog.text = "疑わしいな。カリブにおける騎士団の存在を知る者はごくわずかだし、スペインへの出撃もすべて慎重に計画してきた。 捕虜にしたスペイン将校に聞いてみるといい。今ごろ我々のカスエマートで、熱いカスティーリャ気質を冷ましているさ。 すでに尋問は済ませた。サン・ピエールへの襲撃は、スペインのグランデ、 ラモン・デ・メンドーサ・イ・リバという男が自分の利益とフランス植民地への威嚇のために仕組んだ、 ただの略奪行為だった。それにエスコリアルのご機嫌取りも狙っていたらしい。";
			link.l1 = "このスペイン人と話をしよう。どこに行けば会える？";
			link.l1.go = "spanish_8";
		break;
		
		case "spanish_8":
			dialog.text = "下の階、兄上が拘束されていたのと同じ牢屋です。";
			link.l1 = "道は分かっている。スペイン人を尋問したら戻るつもりだ。追加で聞きたいことが出てくるかもしれない。";
			link.l1.go = "spanish_9";
		break;
		
		case "spanish_9":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "2");
			pchar.questTemp.Guardoftruth = "prisoner";
			sld = characterFromId("spa_baseprisoner");
			LAi_CharacterEnableDialog(sld);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "spanish_10":
			dialog.text = "ほう、これは驚いたな！あの捕虜を解放できない理由はわかるだろ？ あの悪党はサン・ピエール襲撃の手引きをしたんだぜ！";
			link.l1 = "「役人、この者は重要な証人だ。サン・ピエールへの襲撃は、ただの略奪目的の襲撃ではなかった。 ドン・ラモン・メンドーサは他の何かを探していた。我々は決定的な動機を突き止める必要がある。\nそれで、このスペイン人を私に引き渡してくれるのか、それともポワンシー殿に許可を求めねばならないのか？」";
			link.l1.go = "spanish_11";
		break;
		
		case "spanish_11":
			dialog.text = "全能の神にかけて……よし、連れて行け。どうせこいつはそのうちサン・ピエール広場で、他の海賊どもと同じように首を吊るつもりだった……今やお前の問題だ。絶対に法の裁きから逃がすなよ！";
			link.l1 = "間違いない。私がこのスペイン人の件はプアンシー殿の前で責任を持とう。 この捕虜を縛って町の桟橋にある私のロングボートまで運べ。";
			link.l1.go = "spanish_12";
		break;
		
		case "spanish_12":
			dialog.text = "「承知しました、船長。」";
			link.l1 = "もう一つ聞きたいことがある、役人殿。ミゲル・ディチョソという名前に心当たりはあるか？";
			link.l1.go = "spanish_13";
		break;
		
		case "spanish_13":
			dialog.text = "いいえ、聞いたことがないな。どうしてそんなことを聞くんだ？";
			link.l1 = "本当にそうか？その名前の人物には、ここ駐屯地でも、総督の宮殿でも、 サン・ピエールのどこでも会ったことがないんだな？\n";
			link.l1.go = "spanish_14";
		break;
		
		case "spanish_14":
			dialog.text = "いいや、会ったことはない。俺の故郷じゃ、スペイン野郎なんて大して評価されちゃいねえんだ。";
			link.l1 = "よし。まあ、それも当然だな。簡単すぎるってことはなかったか……ありがとう、士官！とても助かったぜ。";
			link.l1.go = "spanish_15";
		break;
		
		case "spanish_15":
			dialog.text = "どういたしまして……さて、ド・モール旦那、あなたの兄上は今どこにいると思いますか？";
			link.l1 = "私自身もその問いの答えを知りたいと思っている。いずれにせよ、必ず突き止めてみせる……遅かれ早かれ。では、さようなら！";
			link.l1.go = "spanish_16";
		break;
		
		case "spanish_16":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "3");
			pchar.questTemp.Guardoftruth = "toship";
			sld = characterFromId("spa_baseprisoner");
			sld.dialog.currentnode = "spa_prisoner_28";
			LAi_CharacterEnableDialog(sld);
		break;
		
	// монах-посланник от Винсенто
		case "monk_vinsento":
			dialog.text = TimeGreeting()+"！お前が船長か "+GetFullName(pchar)+"?";
			link.l1 = "ああ、私です。何かご用でしょうか？";
			link.l1.go = "monk_vinsento_1";
		break;
		
		case "monk_vinsento_1":
			dialog.text = "ごきげんよう、船長。ヴィンセンテ神父に頼まれて参りました。あなたにお渡しする物がございます……";
			link.l1 = "ヴィンチェント神父？私はもうあの閣下のためには働いていない。\nあいつがディエゴ・デ・モントーヤの忠臣、アロンソ・デ・マルドナードを差し向けて俺を殺そうとした後ではな。\n神父様にこう伝えてくれ――失敗だったとな。";
			link.l1.go = "monk_vinsento_2";
		break;
		
		case "monk_vinsento_2":
			dialog.text = "待ってください、船長。ヴィンチェント神父はあなたがそう反応することを予想して、私に警告してくれました。 閣下はあなたに害を与えるつもりはないと、私が保証します。どうか、この手紙をお読みください。本当に、 とても大事なものです。";
			link.l1 = "ヴィンチェント神父は私に悪意がないって？ふむ。じゃあ、 あんたに俺とドン・デ・マルドナードのことも何も話してないんじゃないか？あんたの言うことを信じる理由なんて、 俺にはないぜ。";
			link.l1.go = "monk_vinsento_3";
		break;
		
		case "monk_vinsento_3":
			dialog.text = "この手紙を受け取ってくれ、船長。読んで、自分自身で決断してほしい。 全キリスト教世界の運命が君の手にかかっていることを忘れないでくれ。軽く考えてはならん。神のご加護があり、 君の歩む道が正しきものであるよう祈っている！";
			link.l1 = "わかった、その手紙を渡してくれ。";
			link.l1.go = "monk_vinsento_4";
		break;
		
		case "monk_vinsento_4":
			GiveItem2Character(pchar, "specialletter"); 
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_last";
			dialog.text = "どうぞ。あなたが正しい決断を下されることを祈ります。パックス・ヴォビスクム。";
			link.l1 = "...";
			link.l1.go = "monk_vinsento_5";
		break;
		
		case "monk_vinsento_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			ReOpenQuestHeader("Sharlie"); // patch-8
			AddQuestRecord("Sharlie", "40");
			CloseQuestHeader("Ksochitam");
		break;
		
	// падре Адриан
		case "adrian":
			dialog.text = "ごきげんよう、息子よ。主があなたと共にあらんことを。";
			link.l1 = "「あなたにも平安を、アドリアン神父。総督閣下が、あなたが私にお守りと薬を用意できるとおっしゃっていました。」";
			link.l1.go = "adrian_1";
		break;
		
		case "adrian_1":
			dialog.text = "はい、もちろんです。あなたのために特別な荷をサンティアゴから受け取りました。 ここに祝福されたお守りと治癒の薬があります。さらに極めつけとして、 戦いで無敵になれる珍しい唯一無二のオメトチトリのチンキもございます。これはすべてあなたのため、息子よ。 受け取りなさい、そして主の恵みを知りなさい。";
			link.l1 = "ありがとうございます！";
			link.l1.go = "adrian_2";
		break;
		
		case "adrian_2":
			for(i=2; i<=10; i++)
			{
				if (i == 4 || i == 5 || i == 8 || i == 9) continue;
				TakeNItems(pchar, "amulet_"+i, 2);
			}
			TakeNItems(pchar, "potion2", 20);
			TakeNItems(pchar, "potion4", 10);
			TakeNItems(pchar, "potion7", 3);
			TakeNItems(pchar, "berserker_potion", 3);
			dialog.text = "もし治療用の薬草がもっと必要なら、毎日それぞれ小瓶に入れて用意できます。必要なだけご用意いたします。";
			link.l1 = "感謝します、Adrian神父。そのことは心に留めておきます。";
			link.l1.go = "exit";
			link.l2 = "素晴らしい。今すぐ必要なんだ。";
			link.l2.go = "potion";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "adrian_3":
			dialog.text = "神のご加護とお守りがありますように、息子よ。何をご所望かな？";
			link.l1 = "回復薬をいくつか購入したいのですが。";
			link.l1.go = "potion";
			link.l2 = "今は特に用事はないよ、これから旅の準備をしているんだ。ちょっと挨拶がてら、 元気にしてるか様子を見に寄っただけさ。";
			link.l2.go = "exit";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "potion":
			dialog.text = "もちろんだ、息子よ。どんな薬が必要なんだ？";
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = "「ただの簡単な薬だ。」";
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = "健康をもたらす霊薬だ。";
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = "解毒剤だ。";
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = "薬草の混合物。";
				link.l4.go = "potion4";
			}
			link.l5 = "ご迷惑をおかけしてすみません、神父様。考えを改めました。";
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = "治療用のエッセンスかい？材料代として、90ペソいただくよ、坊や。もちろん材料費だよ。";
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = "「ありがとうございます、お父様。」";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "残念ながら、お金がないんだ……また後で来るよ。";
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = "「健康に効く霊薬かい？五百ペソだよ、坊や。」";
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = "「ありがとうございます、お父様。」";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "残念ながら、お金がないんだ……また後で来るよ。";
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = "「解毒剤かい？200ペソだよ、坊や。」";
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = "「ありがとうございます、お父様。」";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "残念ながら、お金がないんだ……また後で来るよ。";
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = "薬草の調合かい？900ペソだよ、坊や。";
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = "「ありがとうございます、お父様。」";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "残念ながら、お金がないんだ……また後で来るよ。";
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = "「『わたしはあなたを癒し、あなたの傷を治す。主の言葉である。』これがあなたの薬です。ドミヌス・ヴォビスクム！」 ";
			link.l1 = "ありがとうございます、Adrian神父。";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
			NextDiag.TempNode = "adrian_3";
		break;
		
	// посланец Дичозо
		case "Dichoso_agent":
			dialog.text = "Captain "+GetFullName(pchar)+"?";
			link.l1 = "ああ、俺だ。何の用だ？";
			link.l1.go = "Dichoso_agent_1";
		break;
		
		case "Dichoso_agent_1":
			dialog.text = "ミゲル・ディチョソ船長からあなたへの伝言です。あなたは彼をご存知だそうですよ。";
			link.l1 = "ああ、彼のことは聞いたことがある。実際にお会いしたことは一度もないが。";
			link.l1.go = "Dichoso_agent_2";
		break;
		
		case "Dichoso_agent_2":
			dialog.text = "ディチョソ船長はその状況を変えたいそうだ。あなたと直接会って話したいと言っている。\nスペイン領本土の奥地にある失われたインディオの都市タイアサルへの遠征について、あなたに提案があるらしい。\nあなたの経験と彼の知識を組み合わせれば、きっと満足のいく結果が得られると彼は言っていた。";
			link.l1 = "「それが彼の正確な言葉だったのか？」";
			link.l1.go = "Dichoso_agent_3";
		break;
		
		case "Dichoso_agent_3":
			dialog.text = "その通りだ。ディチョソ船長がセント・クリストファーでお前を待っている。 カプスターヴィル墓地の大きな地下墓所で待っているから、余計な目や耳を避けるためだ。";
			link.l1 = "ふむ……";
			link.l1.go = "Dichoso_agent_4";
		break;
		
		case "Dichoso_agent_4":
			dialog.text = "ディチョソはお前がためらうだろうと俺に警告していた。交渉の間は、 どんな決断をしようともお前に危害は加えないと保証するように言われている。さらに、あの島で見つけたものは、 タイアサルで見つけるものに比べればほんの前菜に過ぎないとも伝えてくれと言っていた。";
			link.l1 = "そうか……それは実に興味深いな。だが、なぜディチョーソ船長本人が私に会いに来ない？なぜ第三者を寄越したんだ？";
			link.l1.go = "Dichoso_agent_5";
		break;
		
		case "Dichoso_agent_5":
			dialog.text = "ドン・ディチョーソは最初にイスラ・テソロでお前を探し、それからここに来て、 今はセント・クリストファーへ向かった。そこでお前を見つけられると期待しているんだろう。 お前はフィリップ・ド・ポワンシー本人の士官なんだろ？もしお前がブルーウェルドに来た場合、 ここで待つように言われていたんだ。";
			link.l1 = "それなら全て納得だな。\nよし、分かった。時間を無駄にせず、カプスターヴィルへ向かうとしよう。";
			link.l1.go = "Dichoso_agent_6";
		break;
		
		case "Dichoso_agent_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "Tieyasal_PrepareDichosoTrap", -1);
		break;
		
	// агент Дичозо
		case "Dichoso_crypt_agent":
			dialog.text = "ようやく会えたな、船長 "+GetFullName(pchar)+"...";
			if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) 
			{
				link.l1 = "ミゲル・ディチョソはどこだ？言い逃れは許さねえぞ。奴の正体は知ってるし、お前も分かってるはずだ。";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "目の前にいるのが、ミゲル・ディチョソ本人ってわけか？";
				link.l1.go = "Dichoso_crypt_agent_1";
			}
		break;
		
		case "Dichoso_crypt_agent_1":
			dialog.text = "察しがいいな、船長。俺たちは長い間、お互いを追いかけてきたじゃねえか？";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
			{
				link.l1 = "お前が嘘をついてるのは顔を見ればすぐわかるぜ、相棒。お前はディチョーソじゃねえ。俺は『サンタ・キテリア』 の船長の日誌を読んだし、やつの風貌についても聞き込みしたんだ。お前は全然似ちゃいねえ。 顔に騎兵の剣でできた傷すらねえじゃねえか。おいおい、せめて道化芝居でも傷を描くくらいの努力はするだろうによ！\n";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "その通りです。私の理解では、我々は失われた都市タイアサルについて話し合うためにここに来たのですね？";
				link.l1.go = "Dichoso_crypt_agent_7";
			}
		break;
		
		case "Dichoso_crypt_agent_2":
			dialog.text = "はっ！これ以上茶番を続ける意味はねえな。ミゲルが、お前がずる賢い野郎だって警告してたぜ…";
			link.l1 = "ミゲル・ディチョソはどこだ？";
			link.l1.go = "Dichoso_crypt_agent_3";
		break;
		
		case "Dichoso_crypt_agent_3":
			dialog.text = "彼はここにおりません。私が代理としてあなたにお会いし、お話しする許可を受けております。";
			link.l1 = "小物と話す気はない。俺が会いに来たのは王様だ。奴はどこだ！？";
			link.l1.go = "Dichoso_crypt_agent_4";
		break;
		
		case "Dichoso_crypt_agent_4":
			dialog.text = "あまり愉快な話し相手じゃないな、船長。冷静さを失っているぞ。";
			link.l1 = "もう茶番はたくさんだ、分かったよ。また待ち伏せか。お前ら、たまには新しい手でも考えたらどうだ。";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
		case "Dichoso_crypt_agent_5":
			dialog.text = "ははっ、またしても正解だ！俺の手下どもが、カタコンベへ続く扉のすぐ向こうでお前を待ってるぜ。\nそれだけじゃねえ、墓石の後ろにはマスケット銃兵も隠れてて、いつでも撃てるようにしてある。逃げ道はねえぞ。\nだから、いくらこの手口が繰り返しでも、お前はまんまと引っかかったってわけだ！テヤサルを見たいって欲望が、 分別を上回っちまったんだな！";
			link.l1 = "喧嘩をするにはいい場所を選んだな、クズ野郎。お前もその盗賊仲間も、ここなら埋めるのに遠くまで行かずに済むぜ。";
			link.l1.go = "Dichoso_crypt_agent_6";
		break;
		
		case "Dichoso_crypt_agent_6":
			dialog.text = "ははっ！お前の機知、気に入ったぜ！ミゲルとそっくりだ！好きなだけほざけよ、どっちも同じ穴のムジナじゃねえか……あいつの命令通りにしてやるよ――できるだけ早く、苦しまずに地獄へ送ってやる。\n武器を取れ、野郎ども！";
			link.l1 = "お前より腕の立つ奴らも挑んできたぜ。地獄の悪魔によろしく伝えな、ろくでなし！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_StartCryptBattle");
		break;
		
		case "Dichoso_crypt_agent_7":
			dialog.text = "本当に街に行きたいのか？気持ちはわかるぜ、船長。でも、あまりいい考えじゃねえと思うな。";
			link.l1 = "「じゃあ、俺たちは何の話をしにここに来たんだ？」";
			link.l1.go = "Dichoso_crypt_agent_8";
		break;
		
		case "Dichoso_crypt_agent_8":
			dialog.text = "長々とロマンチックな会話をしたいわけじゃない。\nお前がここにいる、それだけで十分だ。";
			link.l1 = "もう茶番はたくさんだ、わかったよ。また待ち伏せかよ。お前ら、たまには新しい手でも考えたらどうだ。";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
	// командир абордажников
		case "newcastle_officer":
			dialog.text = "ご命令をお待ちしています、船長！";
			link.l1 = "俺たちはジャングルを抜けてキャップスターヴィルの墓地へ向かう。\n着いたら、墓地の中には入るな。門のすぐ外で射撃位置につき、俺が中に入ったらよく耳を澄ませていろ。\nもし戦いの音が聞こえたら、すぐに突入しろ。";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_0":
			dialog.text = "ご命令をお待ちしています、船長！";
			link.l1 = "俺たちはジャングルを抜けてキャップスターヴィルの墓地へ向かう。\n着いたら、墓地の中には入るな。道沿いに射撃位置を取って、墓地を包囲しろ。俺が中に入る時の合図をよく聞いておけ。 \nこの計画、どうにも待ち伏せの臭いがする。敵を見つけたら、すぐに攻撃しろよ。";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_1":
			dialog.text = "あいよ、船長！";
			link.l1 = "よし。進め！";
			link.l1.go = "newcastle_officer_2";
		break;
		
		case "newcastle_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Charles_exittown")].DisableEncounters = true; //энкаутеры закрыть
			locations[FindLocation("Charles_CaveEntrance")].DisableEncounters = true; //энкаутеры закрыть
			for(i=2; i<=4; i++)
			{
				locations[FindLocation("Charles_Jungle_0"+i)].DisableEncounters = true; //энкаутеры закрыть
			}
			LocatorReloadEnterDisable("Shore42", "boat", true);
			for(i=1; i<=iTotalTemp; i++)
			{
				sld = characterFromID("Tieyasal_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// на локацию перед кладбищем
			pchar.quest.Tieyasal_newcastle.win_condition.l1 = "location";
			pchar.quest.Tieyasal_newcastle.win_condition.l1.location = "Charles_exittown";
			pchar.quest.Tieyasal_newcastle.function = "Tieyasal_NewcastleGoJungle";
			// на крипту
			pchar.quest.Tieyasal_graveyard.win_condition.l1 = "location";
			pchar.quest.Tieyasal_graveyard.win_condition.l1.location = "Charles_CryptBig2";
			pchar.quest.Tieyasal_graveyard.function = "Tieyasal_InGraveyardCrypt";
		break;

case "Europe":
			PlaySound("Voice\English\military01.wav");
			dialog.text = "ホバート船長！我々の密偵の情報によると、この屋敷に反乱者が潜んでいるそうだ。\nお前の指揮下には竜騎兵が五人いる。建物をくまなく捜索し、中に隠れている者は全員捕らえろ！\nこのクズどもに情けは無用だ。王の名のもとに行動しているのだからな！";
			link.l1 = "「はい、旦那！」";
			link.l1.go = "Europe_1";
		break;
		
		case "Europe_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Europe_SharlieFinal_1", 5);
		break;
		
		//Индеец по квесту "Знакомство с индейцами"
		case "ZsI_ListKakao":
			dialog.text = "ちっ！海の息子め！";
			link.l1 = "えっ…何だ？俺に話しかけてるのか？";
			link.l1.go = "ZsI_ListKakao_1";
			sld = characterFromId("Tichingitu");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "ZsI_ListKakao_1":
			dialog.text = "そうか。俺はココア・リーフだ。海の子よ、お前に用がある。";
			link.l1 = "ココアがどんなものかも、お前がなんでその名前なのかも知らねえよ。だがまあ、いいさ。用件をさっさと言え。";
			link.l1.go = "ZsI_ListKakao_2";
		break;
		
		case "ZsI_ListKakao_2":
			dialog.text = "ちっ！町へ行け。ピストルを二丁と火薬と弾丸を十発ずつ二組買ってこい。それを俺のところに持って来い。 褒美をやるぞ。海の息子も喜ぶだろう。";
			link.l1 = "ピストル二丁と弾二十発？それだけか？じゃあ、自分で買えばいいじゃねえか？";
			link.l1.go = "ZsI_ListKakao_3";
		break;
		
		case "ZsI_ListKakao_3":
			dialog.text = "わかんねえのか、色白野郎？誰が俺に火縄銃なんか売るってんだよ！？";
			if (CheckAttribute(pchar, "questTemp.ZsI_Cannibals"))		//Sinistra Только если проходил квест "Каннибалы"
			{
				link.l1 = "そういえば、マルティニークでお前らみたいなのに会ったことがある……人食いどもだ。女一人と男二人をさらって、男の一人を焼いて食いやがった。もしあいつらのどっちかが銃を持ってたら、 今こうして話してることもなかっただろうな。\n";
				link.l1.go = "ZsI_ListKakao_3_1";
			}
			else
			{
				link.l1 = "「それで、どうして火器が必要なんだ、コカリーフ？誰かを殺すつもりか？」";
				link.l1.go = "ZsI_ListKakao_3_2";
			}
		break;
		
		case "ZsI_ListKakao_3_1":
			dialog.text = "グーオー！ココアリーフは山賊じゃない、俺の戦いはお前たち部族の戦士だけだ。白い顔の奴らが俺たちの土地に来て、 俺たちを奴隷にする。ココアリーフ自身も戦う。奴隷を取る。それが良いとも悪いとも言えねえ。そういうものだ。 インディアンも白人も違いはねえ。違いを生むのは火薬の武器だけだ。\n";
			link.l1 = "「それで、どうして火器が必要なんだ、コカリーフ？誰かを殺すつもりか？」";
			link.l1.go = "ZsI_ListKakao_3_2";
		break;
		
		case "ZsI_ListKakao_3_2":
			dialog.text = "戦うためだ。しかし、対等な条件でな。白人どもは火器を持っているが、インディアンにはない。不公平だろう。 インディアンにとって火器を持つことは、白人どもの不当な扱いや屈辱、侮辱から身を守る手段なんだ。";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_4";
		break;
		
		case "ZsI_ListKakao_4":
			StartInstantDialog("Tichingitu", "ZsI_ListKakao_5", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_ListKakao_5":
			dialog.text = "了解だ、船長。白い顔の連中は俺たちを見下してやがる。";
			link.l1 = "気づいているさ。ヨーロッパじゃ、インディオたちに真の信仰を教えるとか、 みんなで仲良くプランテーションで働いてるなんて説教してるが…";
			link.l1.go = "ZsI_ListKakao_7";
		break;
		
		case "ZsI_ListKakao_7":
			dialog.text = "ティチンギトゥは船長の言葉はわからなくても、コカの葉の意味はわかる。彼は復讐を求めている。";
			link.l1 = "そうみたいだな……お前も、最近俺たちを捕まえた連中に復讐したくねえのか？";
			link.l1.go = "ZsI_ListKakao_8";
		break;
		
		case "ZsI_ListKakao_8":
			dialog.text = "たぶんそうかもしれない。だが、ティチンギトゥはそんな手段には出ない。今、ティチンギトゥはお前のそばにいる。 そしてティチンギトゥは自分の頭で考える。血が流れすぎることになる。白人の血も、インディアンの血も。 苦しみが多すぎる。それは正しくない。";
			link.l1 = "ああ、すでに状況は悪いし、ココアリーフに銃を渡せばさらに悪化する……だが、あいつの言い分にも一理ある。それに、俺はもうすぐ船員たちに給料を払わなきゃならねえんだ。";
			link.l1.go = "ZsI_ListKakao_9";
		break;
		
		case "ZsI_ListKakao_9":
			dialog.text = "自分の頭で考えろよ、船長。";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_10";
		break;
		
		case "ZsI_ListKakao_10":
			StartInstantDialog("ListKakao", "ZsI_ListKakao_11", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_ListKakao_11":
			dialog.text = "海の息子はよくしゃべるな。口ひげを生やした女みてえだぜ。";
			link.l1 = "誰だ？説明してくれ、ココアリーフ。俺も白人だぜ？それなのにお前は白人と戦うための武器を俺に頼んでる。 矛盾してるんじゃねえか？なぜ俺に近づくんだ？";
			link.l1.go = "ZsI_ListKakao_12";
		break;
		
		case "ZsI_ListKakao_12":
			dialog.text = "お前とあの奇妙な服を着たインディアンの会話を聞いてたぜ。お前は他の白人どもとは違うな。 ティチンギトゥのことも分かってるし、コカの葉のこともきっと分かってるだろう。";
			link.l1 = "ああ……武器の代わりに何を差し出すつもりだ、ココアリーフ？";
			link.l1.go = "ZsI_ListKakao_13";
		break;
		
		case "ZsI_ListKakao_13":
			dialog.text = "神々の涙さ。お前たちはそれを真珠と呼ぶ。たくさんの真珠だ。";
			link.l1 = "俺は決めたぜ、ココアリーフ。ここで待ってろ、武器商人のところへ行ってくる。必要な物を買って戻るからな。";
			link.l1.go = "ZsI_ListKakao_Soglasen_5";
			if (sti(pchar.items.pistol1) >= 2 && sti(pchar.items.GunPowder) >= 20 && sti(pchar.items.bullet) >= 20)
			{
				link.l2 = "俺はもう決めたぜ、ココアリーフ。お前が欲しいものはもう持ってる。ほら、受け取れ。";
				link.l2.go = "ZsI_ListKakao_Soglasen_2";
			}
			link.l3 = "俺の決断はもう下したぜ、ココアリーフ。余計な面倒はごめんだ。俺から火器は手に入らねえ。さっさと行きな。";
			link.l3.go = "ZsI_ListKakao_Otkaz";
			npchar.LifeDay = 1;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		
		case "ZsI_ListKakao_Otkaz":
			dialog.text = "ちっ！";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_Otkaz_2";
		break;
		
		case "ZsI_ListKakao_Otkaz_2":
			DialogExit();
			
			ChangeIndianRelation(-3.0);
			ChangeCharacterComplexReputation(pchar, "authority", -1);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "ZsI_Mir", -1);
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 1.0, 1.0);
			npchar.lifeday = 0;
			PChar.quest.ZsI_Draka.win_condition.l1 = "NPC_Death";
			PChar.quest.ZsI_Draka.win_condition.l1.character = "ListKakao";
			PChar.quest.ZsI_Draka.win_condition = "ZsI_Draka";
			PChar.quest.ZsI_Mir.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ZsI_Mir.win_condition.l1.location = PChar.location;
			PChar.quest.ZsI_Mir.win_condition = "ZsI_Mir";
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			sld = characterFromId("Tichingitu");
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			sld.Dialog.CurrentNode = "Tichingitu_officer";
			LaunchTutorial("Fighter", 1);
		break;
		
		case "ZsI_ListKakao_Soglasen_2":
			dialog.text = "おっと！海の息子がマスケット銃を持ってるのか？マスケット銃の代償は高くつくぜ！";
			link.l1 = "いいや、だが俺の船の大砲ならどうだ？今すぐ立ち去れ、ココアリーフ。見つかって捕まる前にな。";
			link.l1.go = "ZsI_ListKakao_Soglasen_3";
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			ChangeIndianRelation(3.0);
			AddItems(pchar, "jewelry53", 180);
			Log_Info("You have received 180 small pearls");
			PlaySound("Interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
			if (sti(pchar.items.pistol1) >= 2 && sti(pchar.items.GunPowder) >= 20 && sti(pchar.items.bullet) >= 20)
			{
				RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
				RemoveItems(PChar, "pistol1", 2);
				RemoveItems(PChar, "GunPowder", 20);
				RemoveItems(PChar, "bullet", 20);
			}
		break;
		
		case "ZsI_ListKakao_Soglasen_3":
			dialog.text = "いい取引だな！海の息子よ、もしセルバに入るなら火器を持っていけ。インディオに会ったら、取引を持ちかけろ。";
			link.l1 = "覚えておくよ。さらばだ、ココアリーフ。";
			link.l1.go = "ZsI_ListKakao_Soglasen_4";
		break;
		
		case "ZsI_ListKakao_Soglasen_4":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			ReturnOfficer_Tichingitu();
			LaunchTutorial("Fighter", 1);
		break;
		
		case "ZsI_ListKakao_Soglasen_5":
			dialog.text = "ココアリーフ号は待っている。";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_Soglasen_6";
		break;
		
		case "ZsI_ListKakao_Soglasen_6":
			DoQuestReloadToLocation("BasTer_town", "reload", "gate_back", "ZsI_TPvGorod");
		break;

		case "ZsI_officer":
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				dialog.text = "バッ、ここは土人どもの集まりかよ！\nまた牢屋に戻りてえのか、この野郎？\n何してるんだ、旦那？";
			}
			else
			{
				dialog.text = "止まれ！ここで何をしている、旦那？";
			}
			link.l1 = "";
			link.l1.go = "ZsI_officer_2";
			sld = CharacterFromID("ListKakao");
			LAi_CharacterEnableDialog(sld);
			EndBattleLandInterface();
		break;
		
		case "ZsI_officer_2":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ListKakao"));
			dialog.text = "おい、クズども、この立派な市民を待ってたのか？";
			link.l1 = "";
			link.l1.go = "ZsI_officer_3";
		break;
		
		case "ZsI_officer_3":
			DialogExit();
			StartInstantDialog("ListKakao", "ZsI_officer_4", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_officer_4":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ZsI_Patrul_off"));
			dialog.text = "白い顔の者は皆同じに見える。だが、こいつは見たことがない。お前、戦士よ、好きにするがいい。もう飽きてきた。 ココアリーフは森の精霊と向き合う覚悟ができている。";
			link.l1 = "";
			link.l1.go = "ZsI_officer_5";
		break;
		
		case "ZsI_officer_5":
			DialogExit();
			StartInstantDialog("ZsI_Patrul_off", "ZsI_officer_6", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_officer_6":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ListKakao"));
			dialog.text = "お前を待っているのは地獄だ、森の精霊じゃねえ。";
			link.l1 = "";
			link.l1.go = "ZsI_officer_7";
		break;
		
		case "ZsI_officer_7":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			dialog.text = "船長、下がってよい。俺の邪魔をするな。街を守るのは重大な任務だ。";
			link.l1 = "なるほど……しかし、このインディアンはどうするんだ？";
			link.l1.go = "ZsI_officer_8";
		break;
		
		case "ZsI_officer_8":
			dialog.text = "インディアンに何の興味があるんだ、旦那？まあ……そうか、あんたはヨーロッパから来たばかりだもんな\nパリはどうだ？まだ街のネズミを踏み潰してるのか、それとも聖餐式に招くようになったのか？ こっちはネズミの代わりに原住民がいるんだ。バッカニアと取り引きしたり、伐採者を襲ったり、人間を食ったりする、 まったく\n三日前、誰か頭のいい奴がこいつらに火縄銃を売りやがった。どうなったと思う？あの野郎ども、 俺の友人であり戦友が率いる哨戒隊の兵士を全員殺しやがった。裏切り者の植民者は見つけて、 見せしめに太陽の下に吊るしてやったさ。インディアンに武器を渡すなんて！それは裏切りだ！フランスへの反逆だ！ あの色付きの猿は、いろんな事件で顔なじみになってきたから、前から追ってたんだ\nまあ、今度こそ素早く当然の最期を迎えるだろう。先に進んでいいぞ、船長。あんたには関係ないことに首を突っ込むな。 この戦争の当事者じゃない……まだな……それとも、違うか！？";
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l1 = "（信用できる）お分かりいただけますか、役人殿……私はシャルル・ド・モール船長、モスクワ人ファディの客人です。このインディアンには我々なりの関心がありましてね……お互いの職務には干渉しないことにしましょう。よろしいですね、中尉殿？\n";
				link.l1.go = "ZsI_officer_Mir";
			}
			link.l2 = "新参者への態度、現地人への態度……植民者、現地人……まだ私にはよく分かりませんが、今この瞬間だけは、中尉、比較すればあなたの方が分が悪いようですね……戦闘開始！";
			link.l2.go = "ZsI_officer_Draka";
			link.l3 = "おっしゃる通りだ、中尉。俺は違う。じゃあな。";
			link.l3.go = "ZsI_officerKIll";
			StartBattleLandInterface();
		break;
		
		case "ZsI_officer_Mir":
			dialog.text = "「ゴホン！了解しました、船長。ファデイ様によろしくお伝えください。隊員たち、巡回を再開せよ！」";
			link.l1 = "";
			link.l1.go = "ZsI_officer_Mir_2";
		break;
		
		case "ZsI_officer_Mir_2":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_SetImmortal(sld, true);
			LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetActorType(sld);
				sld.lifeday = 0;
				LAi_SetImmortal(sld, true);
				LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
			}
			sld = CharacterFromID("ListKakao");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "ZsI_MirFinal";
			LAi_SetActorType(sld);
			LAi_SetActorType(pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Fortune", 30);
		break;
		
		case "ZsI_MirFinal":
			dialog.text = "「おっと！」";
			link.l1 = "ああ、まあ、俺も上手くいくとは思わなかったぜ。ほらよ、ココアリーフ、品物だ。";
			link.l1.go = "ZsI_MirFinal_2";
		break;
		
		case "ZsI_MirFinal_2":
			dialog.text = "海の息子はよくしゃべるな。インディアンを救うなんて、並大抵のことじゃねえ！でっけえ報酬が待ってるぜ！";
			link.l1 = "なんてこった、こりゃあ大漁だぜ……それに穴の空いた石と、何かのお守りまであるじゃねえか。";
			link.l1.go = "ZsI_MirFinal_3";
			AddItems(pchar, "jewelry53", 180);
			AddItems(pchar, "cannabis1", 3);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "talisman11");
			Log_Info("You have received 180 small pearls");
			Log_info("You have received Amulet 'Cascavella'}");
			Log_info("You have received Ward 'Adder stone'");
			Log_info("You have received 3 Datura herbs");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_MirFinal_3":
			dialog.text = "海の息子はマスケット銃を持ってるのか？マスケット銃には高い金を払えよ！";
			link.l1 = "いや、だが俺の船の大砲じゃダメか？今すぐ立ち去れ、ココアリーフ。見つかって捕まる前にな。";
			link.l1.go = "ZsI_MirFinal_4";
		break;
		
		case "ZsI_MirFinal_4":
			dialog.text = "いい取引だな！海の息子よ、もしセルバに入るなら火器を持っていけ。インディオに会ったら、取引を持ちかけろ。";
			link.l1 = "覚えておくよ。じゃあな、ココアリーフ。";
			link.l1.go = "ZsI_MirFinal_5";
		break;
		
		case "ZsI_MirFinal_5":
			DialogExit();
			
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], false);
			LAi_SetPlayerType(pchar);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "ZsI_officer_Draka":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], false);
			LAi_SetFightMode(pchar, true);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeCharacterComplexReputation(pchar, "authority", -2);	
			ChangeIndianRelation(5.0);
			ChangeCharacterNationReputation(pchar, FRANCE, -10);
			sld = CharacterFromID("ListKakao");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetImmortal(sld, false);
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "ZsI_officer_Draka_3");
		break;
		
		case "ZsI_Final":
			ChangeIndianRelation(5.0);
			dialog.text = "おっと！まずい選択だな、海の息子よ。どうしてそんなことをしたんだ？";
			link.l1 = "うっ……五分前までは正しいと思ってたのに……今はもう自信がない……結局、俺は仲間を殺しちまったんだ。これからどうすればいいんだ？もしバレたらどうなる？くそっ！くそっ！";
			link.l1.go = "ZsI_Final_2";
		break;
		
		case "ZsI_Final_2":
			dialog.text = "今から襲撃があるぞ。兵隊どもが皆殺しにする。二つの巡回隊は許しちゃくれねえ。ココアリーフは逃げるしかねえ。 お前はどうだ、海の子よ……なぜだ。結局ココアリーフは死ぬ運命だ。精霊たちがそう望んでいるのさ。";
			link.l1 = "「ああ…俺たちの取引はまだ有効か？」";
			link.l1.go = "ZsI_Final_3";
		break;
		
		case "ZsI_Final_3":
			dialog.text = "悪い選択だな、海の息子よ。しかし、感謝する。大きな褒美だ。";
			link.l1 = "思ったほど大きくはないな……";
			link.l1.go = "ZsI_Final_4";
			AddItems(pchar, "jewelry53", 180);
			AddItems(pchar, "cannabis1", 3);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "talisman11");
			Log_Info("You have received 180 small pearls");
			Log_info("You have received Amulet 'Cascavella'}");
			Log_info("You have received Ward 'Adder stone'");
			Log_info("You have received 3 Datura herbs");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_Final_4":
			dialog.text = "海の息子よ、もし生き延びてその後セルバへ行くなら、火器を持っていけ。\nインディオに出会ったら、取引を持ちかけろ。";
			link.l1 = "今後のために覚えておくよ。じゃあな、ココアリーフ。";
			link.l1.go = "ZsI_Final_5";
		break;
		
		case "ZsI_Final_5":
			DialogExit();
			
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			LAi_SetImmortal(npchar, true);
			npchar.lifeday = 0;
		break;
		
		case "ZsI_officerKIll":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("ListKakao"));
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("ZsI_officerKIll_1", 0.1);
			DoQuestCheckDelay("ZsI_officerKIll_2", 1.3);
			AddItems(pchar, "pistol1", 2);
			AddItems(pchar, "GunPowder", 20);
			AddItems(pchar, "bullet", 20);
		break;
		
		//Торговец Барбье по квесту "Деньги на деревьях"
		case "MOT_Barbie":
			dialog.text = "ごきげんよう、シャルル・ド・モール船長。私の名はシャルル・バルビエです。少しお時間をいただけますか？";
			link.l1 = "ド・モール船長……そう、私のことです！どうぞ、お話を続けてください、バルビエ旦那。";
			link.l1.go = "MOT_Barbie_2";
		break;
		
		case "MOT_Barbie_2":
			dialog.text = "同業者に会えるのはいつだって嬉しいものです、しかも同じ名前を持つ方ならなおさら！提案がございます、船長。実は、 サン・ピエールまで護衛をお願いしたいのですが……";
			link.l1 = "サン・ピエールなら知ってるさ！だが、そこまでならたった二日の航海じゃねえか！それに正直に言うと、 護衛役なんてまだまだ新米なんだ。俺がこの船の指揮を執るようになったのは、たった一週間前なんだよ。";
			link.l1.go = "MOT_Barbie_3";
		break;
		
		case "MOT_Barbie_3":
			dialog.text = "ご誠実に感謝します、船長。シャルル、無礼をお許しください、しかしまさに私が必要としているのはあなたなのです。";
			link.l1 = "ふむ……つい最近も似たような提案があったな。それがル・フランソワ近くでの海賊の待ち伏せにつながったんだ。";
			link.l1.go = "MOT_Barbie_4";
		break;
		
		case "MOT_Barbie_4":
			dialog.text = "その事件のことは聞いている、だからこそあなたを探し出したのだ\nまず、私はかなり貴重な積み荷を運んでいるので、常に獲物を狙う連中がいる。しかし、 ル・フランソワ近くで最近あなたがあの海賊どもを打ち負かしたことで、あそこの悪党どもも手を出しにくくなるだろう\nそれから、ファディ・モスコバイトと親しいというのも大きな信頼の証だ";
			link.l1 = "説得力のあるご意見ですな、旦那。で、このご恩に対する報酬は何をお考えですか？";
			link.l1.go = "MOT_Barbie_5";
		break;
		
		case "MOT_Barbie_5":
			dialog.text = "恩義じゃなくて、船長、これはお互いに得する取引だぜ！俺をサン・ピエールまで迅速に護衛してくれたら、 四十枚の金貨を払うぞ。\n";
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l1 = "（信用できる）私が向かうのは反対方向ですので、旦那、前払いをお願いしたいのですが。";
				link.l1.go = "MOT_Barbie_Torg";
			}
			link.l2 = "悪くない提案だな――どうせそっちに向かうところだ。乗ったぜ！";
			link.l2.go = "MOT_Barbie_Soglasen";
			link.l3 = "貴重な積み荷ですって？残念ですが、旦那、今はもう冒険は十分でございます。";
			link.l3.go = "MOT_Barbie_Otkaz";
		break;
		
		case "MOT_Barbie_Torg":
			dialog.text = "こんなに真面目な若者の頼みは断りづらいな、船長。はい、四十ドゥブロンだ。\nさあ、すぐに出航するか？時は金なりだぜ。";
			link.l1 = "長居はいたしません、旦那。まもなく出航いたします。";
			link.l1.go = "MOT_Barbie_Escadra";
			
			AddItems(pchar, "gold_dublon", 40);
			Log_info("You've received 40 doubloons");
			PlaySound("Interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
		break;
		
		case "MOT_Barbie_Soglasen":
			dialog.text = "素晴らしい！すぐに出発の準備をするぞ！";
			link.l3 = "";
			link.l3.go = "MOT_Barbie_Escadra";
		break;
		
		case "MOT_Barbie_Otkaz":
			dialog.text = "承知しました、船長。お邪魔はしません。では、ごきげんよう。";
			link.l3 = "";
			link.l3.go = "MOT_Barbie_Otkaz_2";
		break;
		
		case "MOT_Barbie_Otkaz_2":
			DialogExit();
			
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload6_back", "none", "", "", "", -1);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "MOT_Barbie_Escadra":
			DialogExit();
			
			SetQuestHeader("MoneyOnTrees");
			AddQuestRecord("MoneyOnTrees", "1");
			
			FantomMakeCoolSailor(npchar, SHIP_BARKENTINE, "Charles", CANNON_TYPE_CANNON_LBS3, 40, 33, 20);
			npchar.Ship.Mode = "trade";
			SetCharacterRemovable(npchar, false);
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.CompanionEnemyEnable = true;
			SetCrewQuantity(npchar, 35);
			SetCharacterGoods(npchar, GOOD_ROPES, 30);
			LAi_SetImmortal(npchar, false);
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			SetTimerCondition("MOT_ZadanieProvaleno", 0, 0, 14, false);
			PChar.quest.MOT_Zahvatili.win_condition.l1 = "NPC_Death";
			PChar.quest.MOT_Zahvatili.win_condition.l1.character = "SharlieBarbie";
			PChar.quest.MOT_Zahvatili.win_condition = "MOT_Zahvatili";
			PChar.quest.MOT_Dostavili.win_condition.l1 = "location";
			PChar.quest.MOT_Dostavili.win_condition.l1.location = "FortFrance_town";
			PChar.quest.MOT_Dostavili.win_condition = "MOT_Dostavili";
		break;
		
		case "MOT_Barbie_101":
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				dialog.text = "模範的な護衛をありがとうございます、船長。何事もなくて安心しました。";
				link.l1 = "お取引できて光栄です、旦那。さて、失礼しますが、これからやるべきことがたくさんございますので。";
			}
			else
			{	
				dialog.text = "模範的な護衛をしていただき、ありがとうございます、船長。何事もなく済んで嬉しく思います。こちらが全額の報酬、 四十ドゥブロンです。";
				link.l1 = "お取引できて光栄です、旦那。さて、失礼しますが、これからやるべきことがたくさんありますので。";
				AddItems(pchar, "gold_dublon", 40);
				Log_info("You've received 40 doubloons");
				PlaySound("Interface\important_item.wav");
			}
			link.l1.go = "MOT_Barbie_102";
		break;
		
		case "MOT_Barbie_102":
			dialog.text = "シャルル……";
			link.l1 = "「どうしたの、シャルル？何か悩みでもあるの？何か問題でも？」";
			link.l1.go = "MOT_Barbie_103";
			RemoveCharacterCompanion(pchar, npchar);
			npchar.lifeday = 0;
		break;
		
		case "MOT_Barbie_103":
			dialog.text = "さて、君は頼りになる人物だし、ファディとも知り合いだろう…見てくれ、商売ってのは危険なものじゃないか？";
			link.l1 = "そう言うなら。";
			link.l1.go = "MOT_Barbie_104";
		break;
		
		case "MOT_Barbie_104":
			dialog.text = "グアドループで……まあ、あの連中からロープをまとめて安く手に入れたんだ。すぐにサン・ピエールで売りさばいて、 その金でウィレムスタッドで転売用のコーヒーを買うつもりだった。悪くない計画に思えただろう。";
			link.l1 = "あなたの誠実さを疑っているわけではありません、旦那。しかし、どうにも胡散臭く聞こえますね。 あなたは自分の積み荷をまるで金のように語りますが、私の船にもこのロープが積まれていて、値段は二束三文です。";
			link.l1.go = "MOT_Barbie_106";
		break;
		
		case "MOT_Barbie_106":
			dialog.text = "シャルル、この縄は最高級品で、上質な麻から作られ、モスクワのツァーリの工場で織られたものだ。 これは戦略的な用途に使われ、軍艦の索具に用いられている。イングランドはモスクワとの交易路を独占し、 このような縄の自由な取引を禁じている。他国もまた、 ヨーロッパの自国造船所のために入手可能な全ての供給を確保しようと激しく争っているのだ。";
			link.l1 = "これが密輸ってやつか？";
			link.l1.go = "MOT_Barbie_107";
		break;
		
		case "MOT_Barbie_107":
			dialog.text = "ああ。残念ながら、去年サンティアゴの密輸業者と揉め事を起こしてしまったんだ。もうほとんど忘れかけていたが、 あいつらは仲間同士の繋がりが強くて、根に持つ連中だ。\n忠告しておくぜ――やつらを怒らせたり、取引を反故にしたりするのはやめておけ。後で取り返しがつかなくなるぞ。";
			link.l1 = "ありがとうございますが、密輸には興味ありません。";
			link.l1.go = "MOT_Barbie_108";
		break;
		
		case "MOT_Barbie_108":
			dialog.text = "残念だな！正直な商売でもそれなりの利益は出るが、大きな財は築けねえよ。\nとはいえ、俺がこんな危なっかしい話を持ちかけたのには訳がある。俺からロープの積荷を買わねえか？ 地元の密輸業者どもは酒場によく来るし、この荷には飛びつくだろうぜ。\n考えてみな！今日は大海原に出なくても、かなりの儲けが手に入るってわけだ。";
			link.l1 = "その貨物はいくらで売るつもりだ？";
			link.l1.go = "MOT_Barbie_109";
		break;
		
		case "MOT_Barbie_109":
			dialog.text = "一万ペソだ。控えめな額だが、縄を密輸業者に転売すればかなりの利益になるぜ。";
			if (sti(pchar.Money) >= 10000)
			{
				link.l1 = "こんな機会を逃したら、一生自分を許せないだろう。銀貨を受け取って、品物をすぐに俺の船に届けてくれ。";
				link.l1.go = "MOT_Barbie_ContraSoglasen";
			}
			if (sti(pchar.Money) >= 7000)
			{
				link.l2 = "これは危険な取引だ、友よ。お互い歩み寄ろうじゃないか？君のロープは七千で受け取ろう。";
				link.l2.go = "MOT_Barbie_ContraTorg";
			}
			link.l3 = "それはかなりの大金ですな、旦那。ご事情には同情いたしますが、そのような危険はお受けできません。";
			link.l3.go = "MOT_Barbie_ContraOtkaz";
		break;
		
		case "MOT_Barbie_ContraSoglasen":
			dialog.text = "感謝するぞ、シャルル！おかげで破産せずに済んだ！品物はすぐに、そして細心の注意を払って発送しよう\n同じ商人として一つ助言をさせてくれ。腕のいい会計士を雇ったら、 サン・ピエールでコーヒーを仕入れてウィレムスタッドで売るといい。 現地の資本家たちは植民地産の品に高値をつけて買い、ヨーロッパに輸出して大きな利益を得ているのだ。 商売繁盛を祈っているぞ、友よ！";
			link.l1 = "「ごきげんよう、旦那。」";
			link.l1.go = "MOT_Barbie_ContraSoglasen_2";
			AddCharacterGoodsSimple(pchar, GOOD_ROPES, 30);
			AddMoneyToCharacter(pchar, -10000);
			Log_info("You've received 30 ropes");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "MOT_Barbie_ContraSoglasen_2":
			DialogExit();
			
			AddQuestRecord("MoneyOnTrees", "5");
			CloseQuestHeader("MoneyOnTrees");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			
			sld = CharacterFromID("SharlieBarbie");
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "MOT_Barbie_ContraTorg":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 25)
			{
				Notification_Skill(true, 25, SKILL_COMMERCE);
				dialog.text = "感謝します、シャルル！あなたのおかげで私は破産を免れました！商品は迅速かつ細心の注意を払って発送いたします\n同じ商人として一つ助言をさせてください。腕の良い会計士を雇ったら、サン＝ ピエールでコーヒーを仕入れてウィレムスタッドで売るといいですよ。地元の資本家たちは植民地産の品に高値をつけ、 ヨーロッパへ輸出して大きな利益を得ています。ご商売のご成功を祈っています、友よ！";
				link.l1 = "「ごきげんよう、旦那。」";
				link.l1.go = "MOT_Barbie_ContraSoglasen_2";
				AddCharacterGoodsSimple(pchar, GOOD_ROPES, 30);
				AddMoneyToCharacter(pchar, -7000);
				Log_info("You've received 30 ropes");
				PlaySound("Interface\important_item.wav");
			}
			else
			{
				Notification_Skill(false, 25, SKILL_COMMERCE);
				dialog.text = "できません、船長。私の品物は重要で、相応の扱いが必要です。ほとんどの自由船長は戦略物資の取引を恐れています。 残念ですが、ここで値引き交渉はできません。";
				if (sti(pchar.Money) >= 10000)
				{
					link.l1 = "こんな機会を逃したら、一生自分を許せないだろう。銀貨を受け取って、品物をすぐに俺の船へ届けてくれ。";
					link.l1.go = "MOT_Barbie_ContraSoglasen";
				}
				link.l2 = "それはかなりの大金ですな、旦那。ご事情はお察ししますが、そのような危険は引き受けられません。";
				link.l2.go = "MOT_Barbie_ContraOtkaz";
			}
		break;
		
		case "MOT_Barbie_ContraOtkaz":
			dialog.text = "残念だ！さようなら、船長。";
			link.l1 = "";
			link.l1.go = "MOT_Barbie_ContraOtkaz_2";
		break;
		
		case "MOT_Barbie_ContraOtkaz_2":
			DialogExit();
			
			AddQuestRecord("MoneyOnTrees", "4");
			CloseQuestHeader("MoneyOnTrees");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			
			sld = CharacterFromID("SharlieBarbie");
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		//Миниквест "Делюк"
		//Матрос Алонсо
		case "Del_Alonso":
			dialog.text = "問題ですぜ、船長。";
			link.l1 = "どうだ？";
			link.l1.go = "Del_Alonso_2";
		break;
		
		case "Del_Alonso_2":
			dialog.text = "うちの航海士が逮捕されて、地元の牢屋に連れて行かれたんだ。借金の問題らしいぜ。";
			link.l1 = "またかよ！？";
			link.l1.go = "Del_Alonso_3";
		break;
		
		case "Del_Alonso_3":
			dialog.text = "「いたずら好きな野郎ですよ、船長。」";
			link.l1 = "なんてひどいタイミングだ！航海士がいなけりゃ、ここから動けないじゃねえか。あいつをまた保釈しなきゃならねえ！ 司令官と話してくるか…";
			link.l1.go = "Del_Alonso_4";
		break;
		
		case "Del_Alonso_4":
			dialog.text = "「発言してもよろしいですか、船長？」";
			link.l1 = "どうぞ。";
			link.l1.go = "Del_Alonso_5";
		break;
		
		case "Del_Alonso_5":
			dialog.text = "「なぜこんな面倒なことをするんだ？あいつみたいな男は船に災いしかもたらさねえぜ。」";
			link.l1 = "選択肢があるのか？他に航海士なんてほとんどいないから、俺の選択肢はかなり限られているんだ。";
			link.l1.go = "Del_Alonso_6";
		break;
		
		case "Del_Alonso_6":
			dialog.text = "確かに、一流の航海士はなかなか見つからないが、今は達人じゃなくても腕の立つ者で十分だ。\nこの一週間で状況が変わったのは分かってるだろう？もう無理に人集めをする必要はねえ。\nあんたがあの海賊を倒したことや、持ってるコネの噂が広まってる。\n乗組員もあんたの味方だぜ、船長。俺たちはあんたが好きなんだ。";
			link.l1 = "安心したよ、アロンソ。で、乗組員たちはデリュックのことをどう思っている？";
			link.l1.go = "Del_Alonso_7";
		break;
		
		case "Del_Alonso_7":
			dialog.text = "覚えが早いな、船長。\n乗組員たちは、あいつは有能な士官で俺たちにも公平に接してくれるが、 わざわざ関わるほどの価値はねえって言ってるぜ。\nでかい商船がちょうど士官たちを解雇したらしい――酒場を探してみたらどうだ？\nきっと適任がいるはずだ。\nそれとデリュクのことは忘れな、みんなの間じゃそういう話だぜ。";
			link.l1 = "助言ありがとう、アロンソ。君なら頼りになると分かっていたよ。俺がこれを片付けている間、船に戻って見張りを頼む。 ";
			link.l1.go = "Del_Alonso_8";
		break;
		
		case "Del_Alonso_8":
			dialog.text = "「アイアイサー！」";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Del_Alonso_DlgExit");
		break;
		
		//Делюк
		case "Del_Folke_1":
			DelLandQuestMark(npchar);
			dialog.text = "「キャプ…」";
			link.l1 = "聞きたいことは山ほどあるが、一つだけ聞かせてくれ。 どうしてこの間ずっと俺と一緒にいて航海術を教えてくれていたのに、新たな借金を作ることができたんだ！？";
			link.l1.go = "Del_Folke_2";
		break;
		
		case "Del_Folke_2":
			dialog.text = "正直に言うと恥ずかしいんですが、船長、俺はあんたの船に乗る前から色んな貸主から借金してたんだ。 こっそり身を隠して、あんたの船で働きながら全部返すつもりだった。でも、 サン・ピエールである女に関わったのが間違いでな、船を離れた途端、彼女の目の前で兵士に捕まっちまったんだ。 マルティニークでは新しい借金は作ってない、最後の分はあんたが払ってくれたからな、誓うぜ！";
			link.l1 = "お前は間抜けだ、デリュク、それにおかげで俺はサン・ピエールの笑い者になっちまったじゃねえか！";
			link.l1.go = "Del_Folke_3a";
			link.l2 = "感心したぜ、Folke。逸話をありがとう。";
			link.l2.go = "Del_Folke_3b";
		break;
		
		case "Del_Folke_3a":
			AddComplexSelfExpToScill(10, 10, 10, 10);
			dialog.text = "どうするんだ、船長？また俺を助けてくれるのか？新しい航海士を見つけるのは簡単じゃねえんだぜ……";
			link.l1 = "今はここにいてくれ。私が決断する。もう一度銀行家を訪ねるかもしれない。";
			link.l1.go = "Del_Folke_4";
		break;
		
		case "Del_Folke_3b":
			AddCharacterExpToSkill(pchar, "Sailing", 10);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 10);//торговля
			dialog.text = "どうするんだ、船長？また俺を助けてくれるのか？新しい航海士を見つけるのは簡単じゃねえぞ……\n";
			link.l1 = "今はここにいろ。私が決める。もう一度銀行家のところへ行くかもしれん。";
			link.l1.go = "Del_Folke_4";
		break;
		
		case "Del_Folke_4":
			dialog.text = "行くあてもないんだよな……";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Del_Folke_DlgExit_1");
		break;
		
		case "Del_Folke_10":
			dialog.text = "船長、ありがとうございます。あなたが俺の借金を清算してくれたが、今度は俺の命まで救ってくれた恩ができちまった。 本当に感謝してるぜ！断言するが、この世のどこを探しても、俺ほど忠実な男はいないぜ！";
			link.l1 = "借りは借りで返すしかないこともあるんだろうな。\nさあ、仕事に戻ろうぜ、フォルケ。海にはまだまだやることが山ほどあるんだ。";
			link.l1.go = "Del_Folke_11a";
			link.l2 = "忘れるなよ、Deluc。次は撃つからな。";
			link.l2.go = "Del_Folke_11b";
			Del_Ohrannik();
		break;
		
		case "Del_Folke_11a":
			AddCharacterExpToSkill(pchar, "Sailing", 10);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 10);//торговля
			dialog.text = "了解だぜ、船長！";
			link.l1 = "...";
			link.l1.go = "Del_Folke_12";
		break;
		
		case "Del_Folke_11b":
			AddComplexSelfExpToScill(10, 10, 10, 10);
			dialog.text = "了解だぜ、船長！";
			link.l1 = "...";
			link.l1.go = "Del_Folke_12";
		break;
		
		case "Del_Folke_12":
			DialogExit();
			AddDialogExitQuestFunction("Del_Folke_DlgExit_2");
		break;
		
		//Штурман из таверны. Стандартный диалог, но с некоторыми изменениями (обучение найма для новичков)
		case "Del_shturman":
			dialog.text = "「士官が必要ですか、船長？」";
    		Link.l1 = "士官か？で、お前は何が得意なんだ？";
    		Link.l1.go = "Del_Node_2";
			Link.l2 = "いや、俺は全部揃ってるぜ。";
			Link.l2.go = "Exit";
			NextDiag.TempNode = "Del_OnceAgain";
		break;		
		case "Del_Node_2":
			dialog.text = "俺はこの海域で一番の航海士だぜ。薬の知識もちょっとはあるんだ。それに、あんたのために一肌脱いで、 部下として仕える用意もできてるぜ。";
			Link.l1 = "「それで、いくら欲しいんだ？」";
			Link.l1.go = "Del_price";
			Link.l2 = "「それで、お前はどんな専門家なんだ？」";
			Link.l2.go = "Del_ShowParam_exit";
			Link.l3 = "あいにく、すでに航海士がいるんだ。";
			Link.l3.go = "Exit";
		break;		
		case "Del_price":
			dialog.text = "4,000ペソで合意できると思います。";
			Link.l1 = "それはちょっとやりすぎじゃねえか？";
			Link.l1.go = "Del_trade";
			Link.l2 = "同意する。お前もこれで乗組員の一員だ。";
			Link.l2.go = "Del_hire";
			Link.l3 = "お前なんかにこの金はもったいねえな。";
			Link.l3.go = "exit";
		break;	
		case "Del_ShowParam_exit":
			NextDiag.TempNode = "Del_OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;		
		case "Del_OnceAgain":
			NextDiag.TempNode = "Del_OnceAgain";
			dialog.text = "考えが変わったのかい、船長？新しい航海士を雇うのも悪くないと思ったのか？";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "そんなところだ。いくら欲しいんだ？";
                Link.l1.go = "Del_price";
			}
			Link.l2 = "「お前には何ができるんだ？」";
			Link.l2.go = "Del_ShowParam_exit";
			// boal <--
			Link.l3 = "揃いが全部ある。じゃあな。";
			Link.l3.go = "exit";
		break;		
		case "Del_trade":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 25)
			{
				dialog.text = "よし…まあ、2500ペソで手を打ってやってもいいかな。どうだ？";
				Link.l1 = "それでいい。お前は仲間入りだ。";
				Link.l1.go = "Del_hire";
				pchar.questTemp.Del_SniziliTsenu = true;
			}
			else
			{
				dialog.text = "申し訳ありません、船長。でも私は自分が要求した分だけの価値があります。それが高すぎるなら、 他の人を探してください。";
				Link.l1 = "わかった、同意する。連れて行ってやる。";
				Link.l1.go = "Del_hire";				
				Link.l2 = "それをするつもりだ。では、さらば。";
				Link.l2.go = "exit";
			}
		break;		
		case "Del_hire":
			if (CheckAttribute(pchar, "questTemp.Del_SniziliTsenu"))
			{
				if (sti(pchar.Money) >= 2500)
				{
					AddMoneyToCharacter(pchar, -2500);
					NextDiag.TempNode = "OnboardSoon";
					dialog.text = "ありがとうございます、船長。あなたの選択を後悔することはありません。";
					Link.l1 = "そうだといいんだけどな。";
					Link.l1.go = "Del_Exit_hire";
					DeleteAttribute(pchar, "questTemp.Del_SniziliTsenu");
				}
				else
				{
					dialog.text = "お金が足りないようだな、船長！悪いが、ツケでは仕事しねえんだ。";
					Link.l1 = "「ああ、くそっ！」";
					Link.l1.go = "Exit";								
				}
			}
			else
			{
				if (sti(pchar.Money) >= 4000)
				{
					AddMoneyToCharacter(pchar, -4000);
					NextDiag.TempNode = "Del_OnboardSoon";
					dialog.text = "ありがとうございます、船長。あなたの選択を後悔することはありません。";
					Link.l1 = "そうだといいんだけどな。";
					Link.l1.go = "Del_Exit_hire";
				}
				else
				{
					dialog.text = "お金が足りないようだな、船長！悪いが、俺はツケでは働かねえんだ。";
					Link.l1 = "「ああ、くそっ！」";
					Link.l1.go = "Exit";								
				}
			}
		break;
		case "Del_OnboardSoon":			
			NextDiag.TempNode = "Del_OnboardSoon";
			dialog.text = "飲み物を飲み終えたらすぐに船へ行くぜ、船長。\n心配すんな、ちゃんと時間通りに行くからよ。";
			Link.l1 = "よし。遅れたら甲板掃除をやらせるからな！";
			Link.l1.go = "Exit";											
		break;
		case "Del_exit_hire":
			DialogExit();
			AddDialogExitQuestFunction("Del_shturman_DlgExit");
		break;
		
		//Квест "Травля крысы"
		//Капитан корабля Хейтер
		case "TK_Kapitan":
			dialog.text = "わかった、わかった！降参だ、くそっ！";
			link.l1 = "今やお前は俺の捕虜だが、すぐにサン・ピエールで絞首台に立つことになるぜ。";
			link.l1.go = "TK_Kapitan_1";
			PChar.quest.TK_Potopil.over = "yes";
		break;
		
		case "TK_Kapitan_1":
			dialog.text = "これで終わりか……どうして俺の居場所がわかったんだ？";
			link.l1 = "総督が直々に状況を説明してくれた。";
			link.l1.go = "TK_Kapitan_2";
		break;
		
		case "TK_Kapitan_2":
			dialog.text = "なんて野郎だ！俺の計画を嗅ぎつけて、他の船乗りどもへの見せしめに、自分のアジトの目の前で堂々 と俺をハメやがったんだな！";
			link.l1 = "閣下への侮辱をもう一度でもすれば、サン・ピエールへの旅路はあっという間で忘れられないものになるぞ。";
			link.l1.go = "TK_Kapitan_3";
		break;
		
		case "TK_Kapitan_3":
			dialog.text = "え？旦那のことを言ってるんじゃねえよ、相棒。俺が言ってるのは「善人ジャック」のことさ\nくそっ、噂は本当だったのか！バルバゾンの野郎、俺が脅威になりそうだと気づいて、 俺を州総督に引き渡しやがったんだ。自分の邪魔にならねえようにな。だからあんたは俺の居場所をピタリと掴んで、 しかも俺が油断してるとこを捕まえたってわけだ、はは！";
			link.l1 = "お前は妄想してるな。マルティニーク総督が海賊の頭目なんかと取引するわけがねえだろう！";
			link.l1.go = "TK_Kapitan_4";
		break;
		
		case "TK_Kapitan_4":
			dialog.text = "ああ、そうだな。直接じゃないかもしれねえが、バルバゾンと取引したんじゃねえかと思うぜ。 あいつにとっちゃ都合がいいだろう？危険な海賊は絞首刑、報告書も見栄えがいいし、「軍事作戦の費用」 も正当化できる。俺も軍務経験があるんだぜ？だからあそこの仕組みはよく知ってる。\nお前はどうだ？駐屯部隊に所属してるのか？";
			link.l1 = "私は祖国に仕えている。この話はこれで終わりだ。牢屋へようこそ。";
			link.l1.go = "TK_Kapitan_5";
		break;
		
		case "TK_Kapitan_5":
			dialog.text = "待てよ、相棒。俺はカスティーリャ人じゃねえし、今日はフランスの商船を襲うために海に出てたわけじゃねえんだ。 俺にも信念ってもんがあるんだよ、くそっ！取引しようじゃねえか？";
			link.l1 = "無駄口を叩くな、海賊。牢屋にぶち込め。";
			link.l1.go = "TK_Kapitan_7_1";
			link.l2 = "縄にかかるのを避けようとしてるのか？";
			link.l2.go = "TK_Kapitan_6";
		break;
		
		case "TK_Kapitan_6":
			dialog.text = "ここで確かな手がかりを掴んでたんだ。俺を逃がしてくれりゃ、お前にも分け前をやるぜ。 俺の命なんざ銀貨二千枚程度の価値しかねえが、それ以上の儲けを約束する――しかも無税だ。";
			if (CheckAttribute(pchar, "questTemp.MOT_SharlyBad"))
			{
				link.l1 = "魅力的な提案だな……だが、海賊稼業は俺の得意分野じゃないんだ。";
				link.l1.go = "TK_Kapitan_7";
			}
			else
			{
				link.l1 = "俺は海賊じゃねえ！";
				link.l1.go = "TK_Kapitan_7";
			}
		break;
		
		case "TK_Kapitan_7":
			dialog.text = "お前次第だぜ、相棒。運に身を任せるのか、信念だけの無一文の船長になるのか。\n本当に金と自由が欲しいなら、何でも少しは手を出さなきゃな。\nチャンスは逃すなよ。";
			link.l1 = "あなたは本当に口がうまいんだな……";
			link.l1.go = "TK_Kapitan_8";
			link.l2 = "ゴホン……まあ、君をサン・ピエールまで連れて行こう。そうするのが正しい気がするからな。";
			link.l2.go = "TK_Kapitan_7_1";
		break;
		
		case "TK_Kapitan_7_1":
			dialog.text = "「だったらくたばっちまえ！」";
			link.l1 = "...";
			link.l1.go = "TK_Kapitan_Plen";
		break;
		
		case "TK_Kapitan_8":
			dialog.text = "それで、取引成立か？";
			link.l1 = "ああ。お前の頭が誰か教えれば、自由にしてやる。";
			link.l1.go = "TK_Kapitan_9";
		break;
		
		case "TK_Kapitan_9":
			dialog.text = "ヘンリー号っていうバーク船に、頭の切れるイギリス野郎が乗ってるんだ。そいつは今、 フランスのプランテーションからウィレムスタッドまで商品を運んで、 がっぽり儲ける小さな交易航海を終えようとしてる。もうすぐマルティニークを出てキュラソーへ向かうらしい。 楽な仕事さ――護衛もなし、防備を犠牲にしてまで積荷は金目の物ばかり。のんびりしすぎてるから、噂も広まってるぜ。俺からの助言？ 酒場で遠慮なんかするなよ。地元の連中に一杯おごれば、すぐに秘密を漏らしてくれるさ。";
			link.l1 = "「なぜ護衛がいないんだ？」";
			link.l1.go = "TK_Kapitan_10";
		break;
		
		case "TK_Kapitan_10":
			dialog.text = "イギリス人がキュラソーで静かに商売するには他にどうすればいい？\nイングランドとオランダは戦争中だし、交易許可証を取るのも面倒だし高くつくんだ。";
			link.l1 = "しかし、フランスとイングランドの間に戦争はない。中立船を攻撃したらどうなるんだ？";
			link.l1.go = "TK_Kapitan_11";
		break;
		
		case "TK_Kapitan_11":
			dialog.text = "お前が目立たなければ問題ねえさ。船員どもは近くの港でお前の武勇伝を自慢げに吹聴するだろうが、 イギリスやオランダの船ばかり襲わねえ限り大丈夫だ。フランスの旗を掲げてヘンリー号に近づけ。 砲門にブドウ弾を込めて、距離を詰めて、黒旗を翻し、数発ぶっ放してから乗り込めばいい。簡単だろ、相棒。";
			link.l1 = "それはどうかな。約束通りお前を解放してやる。俺に後悔させるような真似はするなよ。";
			link.l1.go = "TK_Kapitan_12";
		break;
		
		case "TK_Kapitan_12":
			dialog.text = "俺はやらねえ。狩りを楽しめよ、相棒。";
			link.l1 = "...";
			link.l1.go = "TK_Kapitan_Otpustil";
		break;
		
		case "TK_Kapitan_Plen":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			sld.DontRansackCaptain = true;
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = GetCharacter(NPC_GenerateCharacter("TK_Heiter2", "mercen_8", "man", "man", sti(PChar.rank), PIRATE, -1, false, "pirate"));
			sld.name = "Daniel";
			sld.lastname = "Montbars";
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto7");
			LAi_SetGroundSitType(sld);
			LAi_CharacterDisableDialog(sld);
			DoQuestCheckDelay("TK_KapitanSidit_1", 0.8);
		break;
		
		case "TK_Kapitan_Otpustil":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			sld.ShipEnemyDisable  = true;
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetCitizenType(sld);
			sld.lifeday = 0;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			pchar.questTemp.TK_Otpustil = true;
			AddQuestRecord("TravlyaKrys", "4");
			
			SetTimerCondition("TK_GenrihSpawn", 0, 0, 1, false);	
		break;
		
		//Диего и Гийом за столиком по квесту "Встреча с Диего"
		case "VsD_DiegoAndErnat":
			dialog.text = "……お前の賭博の問題は俺が何とかしてやる。\nおい！しっかりしろ、野郎！さっさと気を引き締めるか、俺がぶん殴って目を覚まさせてやるぞ。";
			link.l1 = "";
			link.l1.go = "VsD_DiegoAndErnat_2";
			sld = CharacterFromID("GiumDyubua");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "VsD_DiegoAndErnat_2":
			DialogExit();
			StartInstantDialogNoType("GiumDyubua", "VsD_DiegoAndErnat_3", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "VsD_DiegoAndErnat_3":
			dialog.text = "旦那、申し訳ありませんが、少々お邪魔になっています。";
			link.l1 = "ええ、もちろんです。どうぞ良い一日を、お諸君。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("VsD_DiegoInTaverna_3");
		break;
		
		//Гийом Дюбуа по квесту "Встреча с Диего"
		case "VsD_GiumDyubua":
			dialog.text = "「ド・モール船長！待って！」";
			link.l1 = "はい、少尉？";
			link.l1.go = "VsD_GiumDyubua_2";
			DelLandQuestMark(npchar);
		break;
		
		case "VsD_GiumDyubua_2":
			dialog.text = "あなたについていくのがやっとでした。少し…問題が起きました、船長。なんてこった！";
			link.l1 = "一息ついて落ち着いてください。";
			link.l1.go = "VsD_GiumDyubua_3";
		break;
		
		case "VsD_GiumDyubua_3":
			dialog.text = "そうそう。聞けよ、大砲を積み終わった後、まだ船倉に空きはあるか？";
			link.l1 = "俺はまだこれに慣れてないから、はっきりとは言えないけど、多分あるはずだと思うぜ。";
			link.l1.go = "VsD_GiumDyubua_4";
		break;
		
		case "VsD_GiumDyubua_4":
			dialog.text = "素晴らしい！司令部はポルトベロでの作戦をあらゆる手段で支援したがっていて、 戦闘艦への火薬二百樽の追加納入を命じたんだ。大した量じゃないように思えるかもしれないが、 数回の追加斉射が戦いの流れを変えることもあるぞ！";
			link.l1 = "承知しました、中尉。私の役目を果たす準備はできています。火薬を詰めてください――まったく気にしませんよ。";
			link.l1.go = "VsD_GiumDyubua_5";
		break;
		
		case "VsD_GiumDyubua_5":
			dialog.text = "ありがとうございます、船長。すぐに積み込み班に知らせます。幸い、彼らはまだ作業を終えていませんので "+PChar.Ship.Name+"まだだ。任務、頑張ってくれよ！";
			link.l1 = "ありがとう、ただ今のところはかなり混乱していたけどな。では、リュテナン、さようなら。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("VsD_GoToCity");
		break;
		
		//Фульк или Алонсо по квесту "Встреча с Диего"
		case "VsD_FolkeAlonso":
			dialog.text = "「イエス様、船長！ご無事で本当に良かったです！」";
			link.l1 = "何が起きたんだ！？俺の船に何があった！？";
			link.l1.go = "VsD_FolkeAlonso_2";
		break;
		
		case "VsD_FolkeAlonso_2":
			dialog.text = "わかりません、船長！最近知り合った土地の女性に別れを告げていただけで……くそっ！ユジェニー！";
			link.l1 = "「彼女は死んだ」 "+npchar.name+"…申し訳ありませんが、今は集中して、乗組員に被害が出ていないか確認しなければなりません。";
			link.l1.go = "VsD_FolkeAlonso_3";
		break;
		
		case "VsD_FolkeAlonso_3":
			dialog.text = "俺たち、ほとんど面識もなかったのに……ああっ！くそっ！報告します、船長：爆発が起きた時、ほとんどの乗組員は運よく上陸していました。次の大航海の前に、 みんな上陸休暇を楽しんでいたんです。でも、船の見張りは……生存者はいないと思います。見てくださいよ！ここ、桟橋にまで破片が飛んできて、けが人や死者が出てるんです！ 俺たち二人が無事なのは奇跡ですよ。";
			link.l1 = "船はどうしたんだ？無事なのか！？";
			link.l1.go = "VsD_FolkeAlonso_4";
		break;
		
		case "VsD_FolkeAlonso_4":
			dialog.text = "彼女が！？申し訳ありません、船長。はっきりとは言えませんが、爆発は下ではなく上甲板で起こったようです。 火の手は見当たりませんし、大きな被害は免れたようです。";
			link.l1 = "...";
			link.l1.go = "VsD_FolkeAlonso_5";
			
			VsD_AfterVzriv_1();
		break;
		
		case "VsD_FolkeAlonso_5":
			DialogExit();
			AddDialogExitQuestFunction("VsD_AfterVzriv_2");
		break;
		
		case "VsD_Komendant":
			dialog.text = "一体全体どうなってやがるんだ、船長！？";
			link.l1 = "「同じことを聞いているんだ、カーネル！」";
			link.l1.go = "VsD_Komendant_1";
			VsD_AfterVzriv_3();
		break;
		
		case "VsD_Komendant_1":
			dialog.text = "気をつけろ、ド・モール！お前は海軍からこの任務を引き受け、 王冠の所有物であり戦略的にも重要な重砲を受け取ったんだぞ！ この大砲が作戦全体にとってどれほど重要か分かっているのか！？お前の怠慢のせいで、 ほぼ四百人とフランスの軍艦が危険にさらされたんだ！ここでお前は反逆罪で裁かれることになるぞ！\n";
			link.l1 = "落ち着いてください、大佐！奇跡的に私の船は無事だったようですし、あなたの大事な積み荷もほとんど無傷ですよ……ほとんど、ですが。";
			link.l1.go = "VsD_Komendant_2";
		break;
		
		case "VsD_Komendant_2":
			dialog.text = "「ほとんどって、どういう意味だ！？」";
			link.l1 = "最後の瞬間にお前の副官の一人が積み込んだ火薬二百樽が無事だったとは保証できねえ。 あれは本来最後に積むはずだったし、たぶん爆発したのもあれだろう。";
			link.l1.go = "VsD_Komendant_3";
		break;
		
		case "VsD_Komendant_3":
			dialog.text = "何だこれは、シャルル？どの副官のことだ？火薬って何の話だ？そんな命令、私は出していないぞ！";
			link.l1 = "この副官はお前たちの守備隊の者だったに違いない。名前は聞かなかったが、作戦のことは把握している様子だった。";
			link.l1.go = "VsD_Komendant_4";
		break;
		
		case "VsD_Komendant_4":
			dialog.text = "ああ、くそっ！カスティーリャ人も汚い手を使う気らしいな……この厄介な事態は俺が何とかする、船長。だが、お前にはまだやるべき仕事が残ってるぜ。 自分の船がちゃんと航海できるか、本当に確信してるのか？";
			link.l1 = "浮かんではいるが、大規模な修理が確実に必要だな。";
			link.l1.go = "VsD_Komendant_5";
			SetMusic("classic_fra_music_day");
		break;
		
		case "VsD_Komendant_5":
			dialog.text = "そんな暇はないぞ、船長。すぐに出航して任務を果たせ。これ以上遅らせるには危険が大きすぎる。";
			link.l1 = "頼むから、せめて一日くらいくれないのか？地元の造船所なら必要な修理もできるはずだ！\nそれに俺の船員たちはどうなる！？きっと負傷者も出てるはずだぞ！";
			link.l1.go = "VsD_Komendant_6";
			VsD_AfterVzriv_4();
		break;
		
		case "VsD_Komendant_6":
			dialog.text = "お気付きでなければ申し上げますが、造船所が炎上しております。\nそれが故意によるものか、爆発の余波かはまだ調査中です。\n負傷者には必ず治療を施しますし、亡くなった方々の埋葬費用は王室が負担いたします。";
			link.l1 = "本気か？それがあんたの精一杯か？";
			link.l1.go = "VsD_Komendant_7";
			VsD_AfterVzriv_5();
		break;
		
		case "VsD_Komendant_7":
			dialog.text = "船長、フランスはあなたの助けを緊急に必要としています。\n板材は私が用意しますし、うまく立ち回ればジャマイカに着く頃にはあなたの船はほぼ完全に修理されているはずです。";
			link.l1 = "失礼ですが、どの板のことですか？それに、なぜジャマイカなんです？";
			link.l1.go = "VsD_Komendant_8";
			VsD_AfterVzriv_6();
		break;
		
		case "VsD_Komendant_8":
			dialog.text = "お前の乗組員は、板材という主要な修理資材を使って海上で応急修理ができるぜ。\nそれに、ジャマイカはポルトベロへ向かう航路のひとつの近くにある。\n時間を無駄にしなければ、そこで修理を終えて、乗組員も十分に補充できるはずだ。";
			link.l1 = "承知しました。それではすぐに出航します、カーネル。";
			link.l1.go = "VsD_Komendant_9";
			
			VsD_AfterVzriv_7();
		break;
		
		case "VsD_Komendant_9":
			DialogExit();
			AddDialogExitQuestFunction("VsD_AfterVzriv_8");
		break;
		
		case "VsD_Tsyganka":
			dialog.text = "「どうしてそんなに急ぐの、あなた？」";
			link.l1 = "ダーリン、今はこんなことに構っていられないの。\n状況が見えてないの？";
			link.l1.go = "VsD_Tsyganka_1";
		break;
		
		case "VsD_Tsyganka_1":
			dialog.text = "ああ、今の困難も深刻だが、あなたの手を見れば、さらに大きな災いが近づいているのが分かる。";
			link.l1 = "私の手を見なくても誰にだって分かるさ。しかも、手袋をしてるんだぜ。まあいい、付き合ってやるよ。で、 最近の災難回避の値段はいくらだ？";
			link.l1.go = "VsD_Tsyganka_2";
		break;
		
		case "VsD_Tsyganka_2":
			dialog.text = "俺にそんな力はないよ、イケメンさん。たとえあったとしても、払えるもんじゃないさ。だけど、 船のことでなら手を貸せるぜ……あの娘（船）はひどい有様だよ、坊や。";
			link.l1 = "お前らジプシー連中が大工仕事に野心を持ってるなんて聞いたことねえな。";
			link.l1.go = "VsD_Tsyganka_3";
			
			VsD_Final_1();
		break;
		
		case "VsD_Tsyganka_3":
			dialog.text = "あなた、ご自分が大工でもないくせに。板だけで船が直ると思ってるの？名人の大工がいなきゃ、 板なんて重荷になるだけよ……";
			link.l1 = "それとも？";
			link.l1.go = "VsD_Tsyganka_4";
		break;
		
		case "VsD_Tsyganka_4":
			dialog.text = "地元の人々に崇められている強力なお守りがあるんだ。木材はその意志に従い、 木工に不慣れな者でも身につければ腕が上がるってわけさ。たった千ペソであんたのものだよ、旦那。";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "よろしい、取引成立だ。俺にはできるだけ多くの助けが必要なんだ。";
				link.l1.go = "VsD_Tsyganka_Da";
			}
			link.l2 = "お前の魔術に付き合ってる暇はない。平和に行け、魔女よ、そして余計なことはするな。";
			link.l2.go = "VsD_Tsyganka_Net";
			npchar.lifeday = 0;
		break;
		
		case "VsD_Tsyganka_Net":
			DialogExit();
			AddDialogExitQuestFunction("VsD_Tsyganka_Net");
		break;
		
		case "VsD_Tsyganka_Da":
			DialogExit();
			AddDialogExitQuestFunction("VsD_Tsyganka_Da");
			Log_info("You have received Amulet 'Teredo'");
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"聞けよ、お前。俺はこの街の法を守る市民だ。強盗みたいに刃物をむき出しで歩き回るのはやめてもらおうか。","旦那、お願いです、法律は明白です：市壁内で抜き身の武器を持ち歩くことは許されておりません。");
			link.l1 = LinkRandPhrase("よし。","「いいだろう。」","お望みのままに……");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (npchar.id == "GigoloMan") NextDiag.TempNode = "GigoloMan";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
