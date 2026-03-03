// колдун ривадос - Чимисет
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
			link.l1 = "いや、やっぱりいい。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//-------------------------------------в тюрьме на Тартарусе-----------------------------
		// вариант R
		case "KillChad":
			dialog.text = "待って、止まってくれ！頼む、ひどい間違いを犯す前に、俺の話を聞いてくれ。";
			link.l1 = "聞いてるぜ…";
			link.l1.go = "KillChad_1";
			LAi_RemoveCheckMinHP(npchar); //убираем проверяльщик, если ещё есть
		break;
		
		case "KillChad_1":
			dialog.text = "俺を殺せって言われたんだろ？上でチャドと話してるのを聞いたぜ。お前を責める気はねえ――あいつはお前に選択肢を与えなかったからな――だがな、俺が死んだらチャドがすぐにお前を解放してくれるなんて思うのは間違いだぜ。";
			link.l1 = "ふむ……それで、なぜ彼はそうしないんだ？俺が知ってるのは、あんたを殺さなきゃ俺の未来は真っ暗ってことだけだ。";
			link.l1.go = "KillChad_2";
		break;
		
		case "KillChad_2":
			dialog.text = "俺を殺したら、お前の未来なんてなくなるぜ。聞けよ、ナーヴァルとチャドは俺に消えてほしいと思ってるが、 自分じゃ怖くて手を下せねえ――俺を殺した奴は永遠に呪われるからな。だから、誰かにやらせようとしてるんだ。\nチャドはお前がリヴァドスじゃねえって知ってる。お前を利用してるのさ。俺を殺したら、今度はお前が同じ目に遭う。 お前の死体を使ってシャークを騙すつもりだ。";
			link.l1 = "「シャーク！？シャーク・ドドソン？あいつがここにいるのか？頼むから教えてくれ、リヴァドスって一体何者なんだ？」 ";
			link.l1.go = "KillChad_3";
		break;
		
		case "KillChad_3":
			dialog.text = "嘘じゃなかったんだな……本当にここは初めてか……ふむ……だが今は説明してる場合じゃねえ！逃げなきゃならねえ。策があるんだ、聞いてくれるか？";
			link.l1 = "いいや。なあ、魔法使い、俺はさっき不思議なポータルをくぐり抜けて生き延びたばかりだ。 だからお前の呪いなんか怖くねえよ。悪いが――できるだけ痛くしないようにするぜ。";
			link.l1.go = "KillChad_fightfail";
			link.l2 = "わかった、話を聞こう。お前の計画は何だ？";
			link.l2.go = "KillChad_4";
		break;
		
		case "KillChad_fightfail":
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "afraid", "", -1);
			LAi_SetImmortal(npchar, false);
			pchar.quest.LSC_fightfail.win_condition.l1 = "NPC_Death";
			pchar.quest.LSC_fightfail.win_condition.l1.character = "Chimiset";
			pchar.quest.LSC_fightfail.function = "LSC_Fightfail_Final";
		break;
		
		case "KillChad_4":
			dialog.text = "あそこに宝箱がある。中にはそこそこの武器と薬が入っている。鍵はかかっているが、 古くて壊れかけているからバールを見つけてこじ開けろ。\n宝箱の中身は全部持っていけ、自分を武装して階段へ向かえ。あそこは防御に適した場所だ。 奴らは一度に一人ずつしか攻めてこれねえ――ただし、マスケット兵には気をつけろよ。\n剣の腕が立つことを願ってるぜ。俺はもう年で戦いの助けにはなれねえ。もし全員倒して生き残れたら、リバドス――俺の一族の加護を約束するぜ。";
			link.l1 = "よし……俺のためにも神に祈ってくれ。この戦いは楽じゃねえぞ。上にいる連中は甘くなさそうだ。";
			link.l1.go = "KillChad_5";
		break;
		
		case "KillChad_5":
			DialogExit();
			pchar.quest.LSC_fightfail.over = "yes"; //снять прерывание
			LAi_SetImmortal(npchar, true);
			ref location = &Locations[FindLocation(pchar.location)];
			location.private1.key = "crowbar";
			location.private1.key.delItem = true;
			NextDiag.CurrentNode = "KillChad_6";
		break;
		
		case "KillChad_6":
			dialog.text = "時間を無駄にするな！早く錠をこじ開けろ！";
			link.l1 = "ああ、ああ、やってるよ！";
			link.l1.go = "exit";
			NextDiag.TempNode = "KillChad_6";
		break;
		
		case "Chad_die":
			dialog.text = "よくやった！お前は本当に達人の戦士だな。命の恩人だ、よそ者。教えてくれ、お前の名は何だ？";
			link.l1 = ""+pchar.name+". "+GetFullName(pchar)+"。で、あんたの名前は？";
			link.l1.go = "Chad_die_1";
		break;
		
		case "Chad_die_1":
			dialog.text = "私はチミセット、リヴァドスのシャーマンであり、我らの首長ブラック・エディの相談役だ。\nあなたが私を解放し、命を救ってくれたことをエディもきっと喜ぶだろう。\nあなたは私、ブラック・エディ、そしてリヴァドス全員の友人だ。\nこれからはいつでもプロテクター号の歓迎される客人となるだろう…";
			link.l1 = "待てよ……チミセット、まだ分かってないかもしれないが、俺がここに来てからほんの数時間しか経ってないんだ！\nここがどこなのか、あんたたちリヴァドスって何者なのか、それからシャーク・ドッドソンがどこにいるのか、 説明してくれないか？";
			link.l1.go = "Chad_die_2";
		break;
		
		case "Chad_die_2":
			dialog.text = "ここは「見捨てられた船の街」と呼ばれているが、その名は皮肉だ。街と呼ぶには程遠い場所さ。\nこの場所は、何百もの沈没船が集まってできた島だ。中心部の難破船が我々の住居になっている。島の住人は、 島を取り巻く嵐や潮流で難破し、生き残った者たちだ。\n俺たちリヴァドスは、長い間共に暮らしてきた自由黒人の一族だ。ここには他に三つの集団がいる。アフリカから我々 の祖先を連れてきた男たちの子孫であるナーワル一族、シャーク・ドッドソン率いる海賊たち、 そして自分たちだけで暮らす一般人たちだ。\nシャークは島の長と見なされているが、自分では「提督」と名乗っている。彼はごく最近やって来て、 暴力で権力を奪った。島の食料庫であるサン・アウグスティン号を占拠し、 今では俺たちが自分の食料をシャークの言い値で買い戻さなきゃならなくなった。お前とチャドの会話を聞いた限り、 もう海賊の倉庫に行ったようだな。\nチャド・キャッパーはシャークの甲板長であり、牢屋番でもあった。レイトン・デクスターというシャークの副長と共に、 彼らとその海賊たちは、俺たちリヴァドス、ナーワル一族と並ぶ島の三大勢力の一つを成しているんだ。";
			link.l1 = "「なぜチャド・カッパーは俺にお前を殺させたかったんだ？」";
			link.l1.go = "Chad_die_3";
		break;
		
		case "Chad_die_3":
			dialog.text = "チャドはリヴァドスの宿敵であるナーヴァルと取引をしたんだ。奴らの助けを借りて、 シャークを殺してその座を奪うつもりだった。\nナーヴァルは提督に恨みを抱いている。自分たちのリーダー、アラン・ミルロウを殺されたからだ。 奴らはシャークの仕業だと思い込んでいるが、それは間違いだ。アランを殺したのはチャドだ――この目で見た俺だけが証人だ。\nだからこそチャドは俺を殺したがったが、自分の手は汚すのを恐れていた。海賊は戦いでは恐れ知らずだが、 大きな魔法には一目置く。だからお前を利用しようとしたんだ。\nチャドとナーヴァルはシャークを殺し、その罪をリヴァドスに着せるつもりだった。";
			link.l1 = "「なぜお前を責めるんだ？」";
			link.l1.go = "Chad_die_4";
		break;
		
		case "Chad_die_4":
			dialog.text = ""+pchar.name+"、後で話そう。急がなきゃいけない、シャークの海賊どもが現れる前にな。チャドの死体を調べて鍵を取れ。 それからあいつの机も見てみろ、重要な書類があるかもしれねえ。\nシャーク・ドドソンのところへ行け。やつは島の北端にある大型船サン・アウグスティンにいる。 あの船からプルートー号へ渡るロープ橋がかかってる。チャドが裏切りを企んでいたこと、すべての黒幕はナーワル族で、 俺たちリヴァドスは無関係だと伝えてくれ。\nプロテクター号で会えたら、知りたいことは何でも喜んで話すぜ。さあ、行こう！";
			link.l1 = "わかった、チミセット。後で…プロテクターで会おう。行くぞ！";
			link.l1.go = "Chad_die_5";
		break;
		
		case "Chad_die_5":
			dialog.text = "最後にもう一つだけ言っておくぜ。俺たちの船、プロテクター号も含めて、よそ者は立ち入り禁止だ。 入るにはリヴァドスの一員か、合言葉を知ってなきゃならねえ。教えてやりてえが、合言葉は毎週変わるし、 俺はここに長くいすぎて今の合言葉を知らねえんだ。\nまずはサン・アウグスティンに行け。お前が誰か、俺が仲間に伝えておく。その間にシャークと話せ。 俺たちはお前を待ってるぜ。シャークと話すまではプロテクター号に近づくんじゃねえぞ！";
			link.l1 = "わかった。サン・オーガスティンへ向かうよ。すぐに会おう！";
			link.l1.go = "Chad_die_6";
		break;
		
		case "Chad_die_6":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.LSC_LetterChad.win_condition.l1 = "item";
			pchar.quest.LSC_LetterChad.win_condition.l1.item = "letter_chad";
			pchar.quest.LSC_LetterChad.function = "LSC_LetterChad_Find";
			sld = characterFromId("SharkMush_17");
			sld.lifeday = 0;
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("SharkSold_1"+(i+3));
				sld.lifeday = 0;
			}
			AddSimpleRumourCityTip("They say that you are a friend of clan Rivados. Interesting... congratulations.", "LostShipsCity", 5, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that you saved the Rivados wizard Chimiset from Tartarus. Now, you are a welcome guest on their ships.", "LostShipsCity", 5, 1, "LSC", "");
			AddSimpleRumourCityTip("So, it was you who set Chimiset free! Interesting. Now you are a friend of Rivados but an enemy of Narwhals. I'm not sure whether to congratulate or pity you...", "LostShipsCity", 5, 1, "LSC", "");
		break;
		
		// вариант N
		case "prisoner":
			dialog.text = "俺に何の用だ、よそ者？";
			link.l1 = "「お前の名前はチミセットだろ？」";
			link.l1.go = "prisoner_1";
		break;
		
		case "prisoner_1":
			dialog.text = "ああ、そうだ。俺に何か用か？";
			link.l1 = "そうだ。俺は提督、シャーク・ドドソンから来た。お前を解放する命令を持ってきたが、条件が一つある――俺の質問に答えてもらうぞ。";
			link.l1.go = "prisoner_2";
		break;
		
		case "prisoner_2":
			dialog.text = "ドドソンが俺を解放することにしたのか？それは嬉しい知らせだ――いや、もし罠じゃなければな。";
			link.l1 = "これは企みじゃねえ、だがあんたの助けが必要なんだ。チミセット、教えてくれ。この島に、昼は石で、 真夜中になると金になるインディアンの偶像があるって本当か？俺のことを狂ってるとは思わないでくれ…";
			link.l1.go = "Friend_2";
		break;
		
		case "prisoner_3":
			dialog.text = "他に質問はあるか？";
			link.l1 = "ああ。「ホワイトボーイ」と呼ばれる男を知っているか？";
			link.l1.go = "prisoner_4";
		break;
		
		case "prisoner_4":
			dialog.text = "ホワイトボーイ？ああ、知ってるぜ。あれはオーレ・クリスチャンセンだ。今じゃ大人になって、 もう少年には見えねえが、頭の中はまだ子供のままだよ。";
			link.l1 = "そうかい？で、そいつはどこにいるんだ？";
			link.l1.go = "prisoner_5";
		break;
		
		case "prisoner_5":
			dialog.text = "彼はよくアクセル・ヨーストの店やカルペンテロの酒場、あるいはただ通りを歩いているところで見かけるだろう。\n色白で白髪、飾り気のない雰囲気の男だ。\nきっとすぐにわかるはずだ。";
			link.l1 = "素晴らしい！もう一つ質問だ。ここでナサニエル・ホークという男に会ったことはあるか？少し前にここへ現れたはずで、 重い病気にかかっているかもしれないんだ。";
			link.l1.go = "prisoner_6";
		break;
		
		case "prisoner_6":
			dialog.text = "その名前の男は知らねえな。リバドスの船には絶対いねえし、共用エリアでも見かけたことはねえよ。\nただ、ナーワルの領域については分からねえ。リバドスはあそこには行かねえからな。";
			link.l1 = "なるほど。まあ、手伝ってくれてありがとう、Chimiset！";
			link.l1.go = "prisoner_7";
		break;
		
		case "prisoner_7":
			dialog.text = "「それでシャークは今、俺を自由にしてくれるのか？」";
			link.l1 = "ああ。もう他に聞くことはない。チャド・カッパーがあんたを解放するだろう。さて、俺は行かなくちゃな…";
			link.l1.go = "prisoner_8";
		break;
		
		case "prisoner_8":
			dialog.text = "止まれ！戻ってこい。";
			link.l1 = "ああ？まだ何か思いついたのか？";
			link.l1.go = "prisoner_9";
		break;
		
		case "prisoner_9":
			dialog.text = "いや……（声を潜めて）あんたはカッパーの手下じゃねえな。あいつを信用するなよ。奴は人殺しだ。\nつい最近、アラン・ミルローを丸腰のまま、冷酷に殺したんだ。あいつはナーワル族の長だった。俺の牢から見てたんだ。 チャドはただ入ってきて、あいつを刺した。\n提督の部下の中にも、やつを暗殺しようと企んでる連中がいるって噂も聞いた。シャークに伝えてくれ――それと、俺とシャークが直接会った時に、もっと話すと伝えてくれ。";
			link.l1 = "ふむ。わかった、ドドソンに伝えておくよ。またな！";
			link.l1.go = "prisoner_10";
		break;
		
		case "prisoner_10":
			DialogExit();
			sld = characterFromId("Capper");
			sld.quest.chimiset_talk = "true"; // разговор с Чимисетом состоялся
			if (!CheckAttribute(npchar, "quest.capper_talk")) chrDisableReloadToLocation = true;//закрыть локацию
			else chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance_10"; // ноду Акуле
			LSC_SetWhiteBoy(); // поставим белого мальчика
			NextDiag.CurrentNode = "prisoner_11";
			AddQuestRecord("SharkHunt", "20");
		break;
		
		case "prisoner_11":
			dialog.text = "シャークのところへ行って、俺が話したことを全部伝えてくれ。早くこの檻から出してもらえるといいんだがな……";
			link.l1 = "俺は今向かってるぜ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "prisoner_11";
		break;
		
		//------------------------беседа на Протекторе, если был старт через Тартарус-----------------
		case "Friend":
			dialog.text = "やっと来たな、友よ！もう一度助けてくれて、そしてカッパーではなく俺を信じてくれて感謝するぜ。\nこのお守りを努力への礼として受け取ってくれ。きっと役に立つはずだ。";
			link.l1 = "ありがとう！まさかそんなことになるとは思わなかった……";
			link.l1.go = "Friend_1";
		break;
		
		case "Friend_1":
			GiveItem2Character(pchar, "indian_1");
			GiveItem2Character(pchar, "indian_11");
			GiveItem2Character(pchar, "amulet_1");
			PlaySound("interface\important_item.wav");
			dialog.text = "さて、これで話ができるな。俺に聞きたいことがあるんだろう？";
			link.l1 = "そうだ。お前の助けが必要だ。チミセット、俺のことを狂ってるとは思わないでくれ……だが、この島に、昼は石で、真夜中になると金に変わるインディアンの偶像があるって話は本当か？";
			link.l1.go = "Friend_2";
		break;
		
		// нода пересечения
		case "Friend_2":
			dialog.text = "お前が狂っているとは思わねえ。あのような偶像は確かにあったんだ。\nだがな、朝日の光を浴びると黄金に変わり、それ以外の時間はただの石のままだ……\n何度も邪悪なナーヴァルどもをその偶像のもとへ連れていったが、そいつは一人残らず喰らい尽くした。だが、 もうそんなことはない。";
			link.l1 = "もう……つまり、あの偶像はもう無いってことか？";
			link.l1.go = "Friend_3";
		break;
		
		case "Friend_3":
			dialog.text = "偶像はサン・ヘロニモ号に積まれていたんだ。その船は数年前に沈没して、偶像も一緒に海の底さ。";
			link.l1 = "くそっ！あの像を使ってこの島を出るつもりだったのに……それで、その船はどこにあったんだ？";
			link.l1.go = "Friend_4";
		break;
		
		case "Friend_4":
			dialog.text = "ナーワルの領地からそう遠くない、フェニックス号の難破船の近くだ。晴れた日には、 サン・ヘロニモ号が海底に沈んでいるのが見えるぞ。\n";
			link.l1 = "あっ！じゃあ、浅瀬にあるのか？それなら泳いで行けるな――";
			link.l1.go = "Friend_5";
		break;
		
		case "Friend_5":
			dialog.text = "無理だぜ、旦那。まず、あそこは深すぎる。それに、巨大なカニがたくさんいるんだ。 サン・ヘロニモにたどり着く前にバラバラにされちまうぞ。";
			link.l1 = "うう…仕方ねえ、ちょっと考えさせてもらうぜ。少なくとも像が存在して、どこにあるかは分かったからな。";
			if (CheckAttribute(npchar, "quest.chimiset_die")) link.l1.go = "prisoner_3";
			else
			{	
				if (CheckAttribute(pchar, "questTemp.LSC.Mary")) link.l1.go = "freedom_1";
				else link.l1.go = "Friend_6";
			}
			AddQuestRecord("LSC", "4");
		break;
		// нода пересечения
		
		case "Friend_6":
			dialog.text = "まだ質問があるようだな。聞いてくれ、友よ。";
			link.l1 = "シャーク・ドドソンにチャドの仲間を探してくれと頼まれたんだ。チャドの箱の中で手紙を見つけた。 何やら射撃の名手とライフルについて書いてある。どうやら遠くからシャークを暗殺しようとしているみたいだ。 どう思う、チミセット？";
			link.l1.go = "Friend_7";
		break;
		
		case "Friend_7":
			dialog.text = "提督を撃つつもりなのか？ふむ、ちょっと考えさせてくれ……問題はな、提督はほとんど自分の屋敷から出てこねえし、たまに出る時も海賊どもが六人は護衛についてるんだ。\nだがな……夜遅くになると、提督は船尾ギャラリーをぶらぶら歩くのが癖なんだよ。\n提督の屋敷を狙える場所は二つある。サンタ・フロレンティナ号の船首と、フューリー号のマストだ。だがな、 俺の知る限り、そんな狙撃ができる奴はいねえ。\n本当に鷲の目を持ったやつで、しかも極上のライフルが必要だ。そんな銃を手に入れられる奴がいないか、 島中で聞いてみるといいぜ。";
			link.l1 = "手紙には……シュトゥッツェンという銃のことが書かれていたんだ。そんな銃を持っている奴を見たことがあるか？";
			link.l1.go = "Friend_8";
		break;
		
		case "Friend_8":
			dialog.text = "いいや。そんな武器のことは聞いたこともないな。みんなに聞いてみな、 もしかしたら俺たちの知らないことを知ってる奴がいるかもしれねえ。";
			link.l1 = "わかった。貴重な情報をありがとう。ああ、最後にもう一つだけ……「ホワイトボーイ」という名の人物を知っているか？\n";
			link.l1.go = "Friend_9";
		break;
		
		case "Friend_9":
			dialog.text = "ホワイトボーイ？ああ、それはオーレ・クリスチャンセンのあだ名さ。今じゃもう大人で、見た目は少年じゃねえが、 頭の中はまだ子供のままだぜ。";
			link.l1 = "つまり、あいつは間抜けなのか？どこにいるか教えてくれないか？";
			link.l1.go = "Friend_10";
		break;
		
		case "Friend_10":
			dialog.text = "彼はよくアクセル・ヨーストの店やカーペンテロの酒場、あるいは通りを歩いているところで見かけるだろう。\n肌が青白く、白髪で、飾り気のない雰囲気だ。\nきっとすぐにわかるはずだ。";
			link.l1 = "素晴らしい。ありがとう、Chimiset、君は本当に大きな助けになったよ！";
			link.l1.go = "Friend_11";
		break;
		
		case "Friend_11":
			dialog.text = "リバドスの友人にはいつでも力を貸すぜ。何か他に聞きたいことがあれば、また俺のところに来な。";
			link.l1 = "今はここまでにしておく。もう行かなくちゃ。じゃあな！";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary")) link.l1.go = "freedom_2";
			else link.l1.go = "Friend_12";
		break;
		
		case "Friend_12":
			DialogExit();
			NextDiag.CurrentNode = "Chimiset_wait";
			LSC_SetWhiteBoy(); // ставим Белого Мальчика в магазин
			pchar.questTemp.Saga.SharkHunt = "search_mush_1"; // флаг на магазин - поиск мушкета
			AddQuestRecord("SharkHunt", "11");
		break;
		
		case "freedom":
			dialog.text = "そして、ここにいるのが、俺の自由と命の恩人だ。 カッパーという殺人鬼から俺を救い出すために兄弟たちを助けてくれて、ありがとう。\nこのお守りを、あなたの尽力への礼として受け取ってくれ。きっと役に立つはずだ。";
			link.l1 = "ありがとう！まさかこんなことになるとは……";
			link.l1.go = "Friend_1";
		break;
		
		case "freedom_1":
			dialog.text = "本日、他に俺にできることはあるかい？";
			link.l1 = "教えてくれ、チミセット。「ホワイトボーイ」って呼ばれてる奴を知ってるか？";
			link.l1.go = "Friend_9";
		break;
		
		case "freedom_2":
			DialogExit();
			NextDiag.CurrentNode = "Chimiset_wait";
			LSC_SetWhiteBoy(); // ставим Белого Мальчика в магазин
		break;
		
		//--> информационный блок
		case "Chimiset_wait": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "おお！友よ "+pchar.name+"！お前が溺れたって聞いてたぜ！どうやらロアたちがお前を気に入ったみたいだな…";
				link.l1 = "私は元気に生きているよ、チミセット。心配してくれてありがとう。君のロアについては、 確かにその通りかもしれないな――ククルカンを旅したとき、彼らが俺を守ってくれたのは間違いないからな…";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "どうしてここへ来たんだ、友よ？";
			/*if (!CheckAttribute(npchar, "quest.story"))
			{
				link.l1 = "ナーヴァルの頭領がどうやって死んだのか教えてくれ。見ていたのはお前だけだ。";
				link.l1.go = "story";
			}*/
			if (!CheckAttribute(npchar, "quest.crab"))
			{
				link.l2 = "サン・ヘロニモの下の方にカニがいるって言ってたな。それは何なんだ？";
				link.l2.go = "crab";
			}
			link.l9 = "何でもないさ、チミセット。ただ会いたかったんだ、友よ。";
			link.l9.go = "exit";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		
		case "story":
			dialog.text = "俺が見たまま、すべて書き記すぜ。";
			link.l1 = "ありがとうございます。";
			link.l1.go = "exit";
			npchar.quest.story = "true";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		
		case "crab":
			dialog.text = "奴らがどこから来たのか、なぜあんなに巨大になったのか、誰にも分からない。実のところ、 俺たちはあの化け物についてほとんど何も知らねえんだ。\n難破船の間の浅瀬に群れでいることもあるが、ほとんどは海底を徘徊して、魚や俺たちが捨てたゴミなんかを食っている。 \nあいつらは厄介者だぜ。ハサミで手足を切り落としやがるし、顎にはバラクーダの体内にある毒に似た危険な毒がある。 治療しなければ、カニに噛まれたら命はない。幸い、その毒はどんな普通の解毒薬や混合薬でも打ち消せる。\n昔、ここにはカニ狩りの名人がいた――勇敢な男で、自ら海底に潜ってカニを仕留めていた。あいつはよくカニの肉を持ち帰ってくれて、 それはうまい料理になったもんだ。毒も持ってきてくれて、俺の薬の重要な材料になった。\nあいつが天に召されたのは本当に残念だ――みんなに愛され、そして羨ましがられていたからな。";
			link.l1 = "「どうやって死んだんだ？」";
			link.l1.go = "crab_1";
		break;
		
		case "crab_1":
			dialog.text = "自分が狩っていたカニに食われちまったんだ。警告しておくぜ、あいつらには気をつけろよ。";
			link.l1 = "やるよ。";
			link.l1.go = "exit";
			npchar.quest.crab = "true";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		//<-- информационный блок
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
