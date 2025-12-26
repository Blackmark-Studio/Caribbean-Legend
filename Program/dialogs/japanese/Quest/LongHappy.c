// диалоги персонажей по квесту Долго и счастливо
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp;
	
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
		
		// вестовой капитан в порту
		case "cureer":
			dialog.text = "モール旦那、なんて幸運だ！俺は何ヶ月もあんたを探してたんだぜ！";
			link.l1 = "お嬢さん、あたしは偽の地図や怪しい情報、自家製のラム酒なんて買わないわよ、ありがとう！それとも、 あなたは賞金稼ぎかしら？で、今のあたしの首はいくらの値がついてるの？";
			link.l1.go = "cureer_1";
		break;
		
		case "cureer_1":
			dialog.text = "ああ、旦那、私は…私はガラクタなんて扱ってませんし、人殺しもしません――剣に手をかけないでください、必要ありません、危害を加えるつもりはないんです！\nもっとありふれた話なんです――私は急使船の船長です。郵便を届けています。そしてあなたには、大事な手紙をお持ちしました！";
			link.l1 = "手紙だと？誰が差出人か、聞いてもいいか？";
			link.l1.go = "cureer_2";
		break;
		
		case "cureer_2":
			dialog.text = "修道院長がこれを私に渡して、「必ずド・モール船長に直接、手渡ししてくれ」と頼まれたんだ。 もう君を見つけるのは無理だと諦めて、サン・ピエールの港役所に預けて帰ろうとしていたところだったが、 なんて幸運だ――君がここにいるとは！";
			link.l1 = "ああ、ここにいるぞ、待ってたんだ―手紙をよこせ。";
			link.l1.go = "cureer_3";
		break;
		
		case "cureer_3":
			dialog.text = "一つ問題がある……院長は配達料は受取人が払うと言っていたんだ。だからお前は九千二百ペソの借りがあるぞ。";
			link.l1 = "そんな大金なら、俺の部屋まで朝のコーヒーと一緒に大海原で届けてくれてもよかったんじゃねえか！手紙なんざ、 お前が持ってりゃいいさ。";
			link.l1.go = "cureer_6";
			if (sti(pchar.money) >= 9200)
			{
				link.l2 = "「なんで俺は郵便配達なんかに転職しなかったんだ！？海賊よりよっぽど儲かるじゃねえか！ほらよ、銀貨だ、旦那。 封筒を渡しな。」";
				link.l2.go = "cureer_4";
			}
		break;
		
		case "cureer_4":
			AddMoneyToCharacter(pchar, -9200);
			dialog.text = "取引できてよかったぜ！ブノワ院長がよろしくとのことだ！さらばだ、ド・モール旦那！";
			link.l1 = "";
			link.l1.go = "cureer_5";
		break;
		
		case "cureer_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			LongHappy_RecibeLetter();
		break;
		
		case "cureer_6":
			dialog.text = "承知しました。封筒は港の事務所に置いておきます。ただし、値段には影響しますのでご注意を。それから、 ブノワ修道院長があなたによろしくとのことです。";
			link.l1 = "ベノワ院長からの手紙だと？最初からそう言ってくれればよかったのに！きっと大事なものに違いねえ！";
			link.l1.go = "cureer_7";
		break;
		
		case "cureer_7":
			dialog.text = "だから港長から受け取ってくれ。前もって借金するのを忘れるなよ。さようなら、ド・モール船長。";
			link.l1 = "お前より誠実な海賊を何人も知ってるぜ。幸運を祈るよ、俺の大事な人よ。";
			link.l1.go = "cureer_8";
		break;
		
		case "cureer_8":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);
			pchar.questTemp.LongHappy = "portman";
		break;
		
		// испанский офицер в Сантьяго
		case "spa_officer":
			dialog.text = "神父様、今日はいつもより早いですね。どうぞ、お付きの方がお待ちです。\nそして、ド・モーレ旦那――ヴィンチェント神父があなたが街にいることを知り、ぜひ夕食をご一緒にと誘っておられます。";
			link.l1 = "申し訳ないが、異端審問官殿には一人で食事してもらうことになる。これで食欲が失せなければいいがな。 それにブノワ院長も同席しない。俺が誰かは知っているだろうから、忠告しておくぜ――おとなしく通してくれ、そしてパロッティ神父によろしく伝えてくれ。";
			link.l1.go = "spa_officer_1";
		break;
		
		case "spa_officer_1":
			if(sti(pchar.reputation.nobility) > 80 || sti(pchar.reputation.nobility) < 20) // провести учёт чести и известности
			{
				Notification_Reputation(true, 81, "low");
				dialog.text = "ああ、あなたのことはよく聞いている。もしあなたが強情を張っても、この街を血の海にしないようにと、 はっきり指示されているんだ。通っていいぞ。\nだがヴィンチェント神父は……不満に思うだろうな。そのことを覚えておけ。";
				link.l1 = "分別ある行動でしたな、旦那。なんとか生き延びますが、宗教裁判官殿の失望には心が痛みます。 どうぞ良い夜をお過ごしください！";
				link.l1.go = "spa_officer_2";
			}
			else
			{
				Notification_Reputation(false, 81, "low");
				Notification_Reputation(false, 19, "high");
				dialog.text = "ああ、あなたのことは聞いている……面白い噂もたくさんな。だがな、こういう招待を断るのは身のためにならねえぜ、旦那。それに、 ヴィンチェント神父の客人を誘拐するのも同じくらい危険だ。捕まえろ！";
				link.l1 = "皆、それぞれの選択をした。こんなことになってしまい、残念だ。武器を取れ、旦那！";
				link.l1.go = "spa_officer_3";
			}
		break;
		
		case "spa_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("LH_escort_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload3_back", "none", "", "", "", 15.0);
			}
			ChangeCharacterComplexReputation(pchar, "authority", 3);
			pchar.quest.longhappy_santiago2.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago2.win_condition.l1.location = "Cuba1";
			pchar.quest.longhappy_santiago2.function = "LongHappy_SantiagoSail";
			pchar.quest.longhappy_santiago3.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago3.win_condition.l1.location = "Cuba2";
			pchar.quest.longhappy_santiago3.function = "LongHappy_SantiagoSail";
		break;
		
		case "spa_officer_3":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = characterFromId("LH_escort_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				LAi_group_Attack(sld, Pchar);
			}
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			LAi_SetFightMode(pchar, true);
			ChangeCharacterNationReputation(pchar, SPAIN, -20);
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			pchar.quest.longhappy_santiago2.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago2.win_condition.l1.location = "Cuba1";
			pchar.quest.longhappy_santiago2.function = "LongHappy_SantiagoSail";
			pchar.quest.longhappy_santiago3.win_condition.l1 = "location";
			pchar.quest.longhappy_santiago3.win_condition.l1.location = "Cuba2";
			pchar.quest.longhappy_santiago3.function = "LongHappy_SantiagoSail";
		break;
		
		case "Guests_block":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;
		
		// Ян Свенсон патер
		case "Svenson":
			dialog.text = "チャールズ、おめでとう！お前のことは前から好きだったし、ヘレンは俺にとって娘みたいなもんだ。だから二人のこと、 本当に嬉しいぜ。くそっ……教会で涙を流すなんて、俺の夢だったんだ。俺も年を取ったってことか？\n";
			link.l1 = "大丈夫だよ、ヤン。祭壇で泣きそうになったんだ。たぶん香のせいかな？";
			link.l1.go = "Svenson_1";
		break;
		
		case "Svenson_1":
			dialog.text = "そうか、樟脳か、くそっ。どうりで目がしみるし鼻がむずむずするわけだ！よし、シャープタウンで話そうぜ、 グラディスを抱きしめて他のみんなのところへ行くんだ。あいつらの顔ときたら、 まるでウェストファリア条約でも結ぶみてえじゃねえか。";
			link.l1 = "来てくれてありがとう、Jan。会えて嬉しいよ、それにヘレンにとっても大きな意味があるんだ。";
			link.l1.go = "Guests_block";
		break;
		
		// Ян Свенсон на Исла Тесоро
		case "Svenson_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "やっと来たな、チャールズ！俺のコルベットはお前よりほぼ一日も早く着いたぜ――ちょっと自慢できることだな。";
			link.l1 = "どういたしまして、ヤン。でもグラディスと奥さんはどこにいるんだ？";
			link.l1.go = "Svenson_3";
		break;
		
		case "Svenson_3":
			dialog.text = "グラディスは商船でブルーヴェルドに帰したんだ――あの子はこんな華やかな宴会には賛成しないからね。ジョアンナは来られなかった――ああ、マルティニークで君に話す時間がなかったよ！想像してごらん――この歳になって、正式な父親になるんだ、どうだい？急げば、君の子と私の子はほとんど同じ年になるぞ、ははは！";
			link.l1 = "ヤン、おめでとう、いい知らせだな！それを祝って一杯やろうぜ！";
			link.l1.go = "Svenson_4";
		break;
		
		case "Svenson_4":
			dialog.text = "もちろんだ！だがまずは、お前と奥さんに乾杯だ！おい、そこの連中、静かにしろ！！！ この老いぼれ森の悪魔がスピーチをするぞ！\nゴホン…さて、親愛なるムッシュとマダム・ド・モール…ちくしょう！こんなふうには話せねえ！シャルル、ヘレン――お前たち二人は、俺にとっちゃ我が子同然だ。この部屋にいる誰一人として、 お前たちの結婚を喜ばない者はいねえだろう！だから皆で飲もうぜ、兄弟たちよ、忠実なる友の幸せに、 彼らの帆に順風を、そしてお互いへの想いと同じくらい強い運命の女神の愛に！！！乾杯！";
			link.l1 = "乾杯！ありがとう、ヤン……おい、このラム酒はいつもよりずっと強いな……ナサンは何を混ぜたんだ？";
			link.l1.go = "Svenson_5";
		break;
		
		case "Svenson_5":
			dialog.text = "俺にはさっぱり分からねえが、なんとなく正しい気がするぜ。ホークの親父は酒のことなら大体詳しいからな。さあ、 他の連中のところへ行けよ。俺は腹を空かせた百人分の酒を用意しなきゃならねえんだ。\n";
			link.l1 = "森の悪魔が酒を注いでいる――なんて光景だ！宴の準備を仕切ってくれてありがとう。ひと回りしたら必ず戻るよ――もしかしたら他にも助けが必要な奴がいるかもしれないからな。";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_6":
			DialogExit();
			npchar.dialog.currentnode = "Svenson_6_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Svenson_6_1":
			dialog.text = "「大丈夫か、チャールズ？」";
			link.l1 = "完璧だぜ、Jan！";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_7":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "やっと来たな！マルティニークではどうだった？自分の人生が永遠に変わったと感じてるか？";
			link.l1 = "もっと前に変わったんだ、ヤン。でも、すべて驚くほど上手くいったぜ。ヨハンナはどこに……\n";
			link.l1.go = "Svenson_8";
		break;
		
		case "Svenson_8":
			dialog.text = "ヘレンか？あの娘は俺たちのやってることを知るやいなやすぐに出航して、地平線の彼方へ向かったぜ。 お前にいろいろと温かい祝福の言葉を送ってきたが……それでも、お前はあの娘の心を傷つけた、本当にそうだ。だが、心配はいらねえ、若さゆえのことさ。";
			link.l1 = "まあ、心が求めるものは仕方ねえよ、わかるだろ。";
			link.l1.go = "Svenson_9";
		break;
		
		case "Svenson_9":
			dialog.text = "ああ、そうだよ。まあ、ヨハンナは来られなかったんだ、想像してみろよ――この歳になって俺が正式な父親になるんだぜ、どうだ？ほら、急げば俺たちの子どもはほとんど同い年になるぞ、ははは！ \n";
			link.l1 = "ヤン、おめでとう、いい知らせじゃねえか！これは祝杯をあげるしかねえな！";
			link.l1.go = "Svenson_10";
		break;
		
		case "Svenson_10":
			dialog.text = "もちろんだ！だがまずは、お前とその奥方に乾杯だ！おい、そこの奴ら、静かにしろ！！！ この老いぼれ森の悪魔が一席ぶつぞ！\nチャールズとメアリー、今やブレザレン全員がお前たちのために杯を掲げている！真の友の幸せは、 どんな海の狼の魂も喜ばせるものさ――スペインの金貨の輝きにも負けねえくらいにな、ははは！良い航海を、そして家族の旅路に順風が吹くよう祈ってるぜ！！ ！乾杯！";
			link.l1 = "乾杯！ありがとう、ヤン…おい、このラムはいつもよりずっと強いぞ…ナサンは何を混ぜたんだ？";
			link.l1.go = "Svenson_11";
		break;
		
		case "Svenson_11":
			dialog.text = "俺には分からねえが、なんだか正しい気がするぜ。ホークの親父は酒にかけちゃあ大したもんだ。さあ、 他の連中のところへ行けよ。俺はこれから百人分はある飲みたがりどもに酒を作らなきゃならねえんだ。";
			link.l1 = "この酒場は絶対に名前を変えるべきだな――「森の悪魔本人がここでカウンターの後ろに立っていた！」ってな！\nありがとう、ヤン。みんなと話し終えたら必ず戻ってくるぜ――もしかしたら誰か助けを必要としてるかもしれねえしな。";
			link.l1.go = "Svenson_6";
		break;
		
		case "Svenson_12":
			dialog.text = "調子はどうだ、チャールズ？結婚式はどうなってる？";
			link.l1 = "とても心温まる話だな、ヤン。みんなをここに連れてこられて嬉しいぜ。 ホークのラム酒の樽も底が見え始めてきたみたいじゃねえか？";
			link.l1.go = "Svenson_13";
		break;
		
		case "Svenson_13":
			dialog.text = "ああ、そうだよ！さあ、持ってきたものを開ける時間だな。\nそれともう一つ――最初に手伝ってくれた連中は奥の部屋で酔っぱらいすぎちまったみたいだ。\nまだしっかりしてるのはお前だけだぜ、花婿さん――シェリー酒の箱を持ってきてくれないか？";
			link.l1 = "ああ、行き先を教えてくれよ。途中でしらふの奴が何人か見つかれば手伝わせるぜ。もっとも、 俺の連中はほとんどもうベロベロに酔っ払ってるだろうがな。";
			link.l1.go = "Svenson_14";
		break;
		
		case "Svenson_14":
			dialog.text = "ワインは造船所の地下貯蔵庫に保管されていたんだ、覚えてるか？ホークが「奥の通路に置いとけ、 祝日まで取っておくためにな」と言ってたぜ。\nそれに、あそこは温度も湿度も完璧だからワインセラーに最適だとも言ってた。まあ、あいつは本当に気取った野郎だよ。 ";
			link.l1 = "ヤン、あいつは正しい決断をしたな。俺は行くぜ、だがその前に教えてくれ――俺の妻を見たか？";
			link.l1.go = "Svenson_15";
		break;
		
		case "Svenson_15":
			dialog.text = "彼女とダニーはどこかへ行ったよ。女同士で話させてやれ、チャールズ。俺たちは本当の宴を始めるぞ。 俺が料理を片付けてる間に地下貯蔵庫へ行ってくれ。\nこのままだと、羊のあばら肉じゃなくて炭を食う羽目になりそうな匂いがするからな！";
			link.l1 = "よし、肉を助けてこい。俺はワインを取ってくるぜ。";
			link.l1.go = "Svenson_16";
		break;
		
		case "Svenson_16":
			DialogExit();
			npchar.dialog.currentnode = "Svenson_6_1";
			LongHappy_IslaTesoroToVineGo();
		break;
		
		case "Svenson_17":
			dialog.text = "「チャールズ、ネイサン、どうしたんだ、酔っぱらって喧嘩でも始めたのか！？」";
			link.l1 = "いや、ヤン、俺たちは地下牢で武装したカッターどもと一緒に戦ったんだ。そいつらは片付けたが、 あいつらは偵察隊にすぎねえ――本隊がすぐ後ろにいるんだ！";
			link.l1.go = "Svenson_18";
		break;
		
		case "Svenson_18":
			dialog.text = "隊？何の話だ！？マーカス、こっちに来い！チャールズ、おい、全部話してくれ。";
			link.l1 = "言った通りだぜ：造船所の地下牢に何人かの野郎どもがいる。しかも武装してやがる。ナサンと俺で戦って、 奇跡的に全員倒したんだ。だが、まだ増援が来るらしい――一人が助けを呼びに行ったのを聞いた。それと、ジャックって名の奴のことを誰かが口にしてたぜ。";
			link.l1.go = "Svenson_19";
		break;
		
		case "Svenson_19":
			DialogExit();
			sld = characterFromId("Terrax");
			sld.dialog.currentnode = "Terrax_7";
			ChangeCharacterAddressGroup(sld, "Pirates_tavern", "tables", "stay8");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Svenson_20":
			dialog.text = "あいつらの顔は覚えてる……こいつと、あのドアのそばに転がってるクソ野郎もだ。ジャック・ザ・カインドマンの手下どもさ。 名前までは覚えてねえが、間違いねえ。";
			link.l1 = "つまり、これはバルバゾンのせいってことか？あいつ、正気じゃねえのか！？";
			link.l1.go = "Svenson_21";
		break;
		
		case "Svenson_21":
			dialog.text = "俺にはわからねえが、どうやらキンドマンがこの機会を利用して、 兄弟団のバロンたちの間で大規模な入れ替えを仕組んだようだ。";
			link.l1 = "この場合は、奴が自分で現れることを願うぜ――あいつの体に二、三発穴を開ける夢をずっと見てたんだ。野郎、俺の結婚式を台無しにしやがって、 考えただけで腹が立つ！\nさあ、行くぞ、街へ！客人どもにはきっちりと歓迎してやろうぜ！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernReload");
		break;
		
		case "Svenson_22":
			dialog.text = "そして、ここに我らが疲れ切った英雄が登場だ！ははっ、チャールズ、すごかったぜ！ジャック、あの野郎め！見ろよ、 全部仕組みやがって――もう少しで成功するところだったじゃねえか！";
			link.l1 = "ああ、ジャックマンの件が片付いた時に、あの野郎も殺しておくべきだったかもしれねえな。\nだが、もう終わったことだ。バルバゾンは死んだ。";
			link.l1.go = "Svenson_23";
		break;
		
		case "Svenson_23":
			if (CheckAttribute(pchar, "questTemp.LongHappy.SvensonsShipSink")) dialog.text = "まあ、全然終わっちゃいねえさ――俺たちの人生はまだ続くんだ！だが、正直もうボロボロだぜ。燃え盛る船から海に飛び込んで、 サメに気をつけながら一時間も泳いで岸までたどり着くには、俺は歳を取りすぎたよ。 まだラム酒が残ってりゃいいんだがな…";
			else dialog.text = "まあ、全然終わっちゃいねえさ――俺たちの人生はまだまだ続くぜ！くそっ、十歳は若返った気分だ！あんな激しい戦いは久しぶりだったな！ 混乱の最中にラムやワインの在庫が盗まれてなきゃいいが――ちゃんと祝杯をあげねえとな！\n";
			link.l1 = "ああ、俺も飲みたいが、その前に屋敷を確認しなきゃならねえんだ。お前に伝わってるかどうかは知らねえが……";
			link.l1.go = "Svenson_24";
		break;
		
		case "Svenson_24":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				dialog.text = "お前のインディアンの友達のことか？ああ、聞いたぜ、どうしてそんなことになったんだ？";
				link.l1 = "奴が飛び出して、俺の妻とダニエルをあの野郎の撃った弾から守ったんだ。\n行こう、歩きながら説明するぜ。";
			}
			else
			{
				dialog.text = "ナサンのことか？ああ、聞いたよ、でもどうしてそんなことになったのか分からなかったんだよな？";
				link.l1 = "あいつは、どこかの野郎が撃った弾から俺たちの女房たちを守るために飛び込んだんだ。\n行こう、道中で話すぜ。";
			}
			link.l1.go = "Svenson_25";
		break;
		
		case "Svenson_25":
			DialogExit();
			DoQuestReloadToLocation("Pirates_townhall", "goto", "goto4", "LongHappy_DannyInResidence");
		break;
		
		case "Svenson_26":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				dialog.text = "しっかりしろ、チャールズ。お前の仲間たちのこと、本当に気の毒に思うぜ。今日は多くの善き男たちが倒れた。 その一人ひとりのために、バルバゾンの地獄のボイラーにはもっと油が注がれるだろう。";
				link.l1 = "意味がわからねえ……くそっ！つらいぜ、ヤン……仲間を失うのはこれが初めてじゃねえが、どうしても慣れねえ。もうこれ以上やっていけるかわからねえよ。";
				link.l1.go = "Svenson_28";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
				{
					dialog.text = "あの静かな医者のことか？すまない、チャールズ、本当に。彼はいい男だった。";
					link.l1 = "ああ、ヤン、俺もだ。だが、科学の世界は俺よりもはるかに大きなものを失ったと思う。彼は天才だった……他の連中と同じく洗練されていたが……くそ……";
					link.l1.go = "Svenson_27";
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim")) sTemp = "your Indian guy";
					else sTemp = "Nathan";
					dialog.text = "さて、これで終わったようだな。今日は多くの腕利きが逝っちまった。その一人一人のために、 地獄じゃバルバゾンのボイラーにもっと油が注がれるってわけだが\n "+sTemp+" 大丈夫だ、それが一番大事なんだ。";
					link.l1 = "「その通りだ、ヤン、おかげで肩の荷が下りたよ。他の男爵たちはどうだ？みんな無事か？」";
					link.l1.go = "Svenson_32";
				}
			}
		break;
		
		case "Svenson_27":
			dialog.text = "ジャック・バルバゾンの最後の汚点だ。お前の言う通り、もしもっと早く奴を殺していれば、 すべてが違っていたかもしれねえ。";
			link.l1 = "しかし、過去を悔やんでも仕方がないだろう？過去は変えられないんだ。\n他の男爵たちはどうしている？みんな生き残ったのか？";
			link.l1.go = "Svenson_32";
		break;
		
		case "Svenson_28":
			dialog.text = "誰もこんなことには慣れやしねえ。俺たちの仲間に乾杯しようぜ？テーブルの上に瓶を見つけたんだ、 この騒ぎの中で奇跡的に無事だったんだよ。";
			link.l1 = "注げ、俺は……くそっ……くそったれが千回も！";
			link.l1.go = "Svenson_29";
		break;
		
		case "Svenson_29":
			dialog.text = "彼らについて教えてくれ。この医者は頭が切れそうだったな。とても賢く話していたぜ。";
			link.l1 = "彼はやった。しかし、残念ながら、科学の世界は私一人以上のものを失ってしまったのだ。彼は天才だった……他の連中と同じく洗練されていた。奇跡の達人だったのさ！";
			link.l1.go = "Svenson_30";
		break;
		
		case "Svenson_30":
			dialog.text = "インディアンの男のことか？どこで見つけたんだ？";
			link.l1 = "グアドループの牢屋から到着してすぐに奴を助け出したんだ。本当におかしくて間抜けな話さ。そうして、 奴は俺と一緒にいることになった。自由はやったが、奴は自分で俺のそばに残る道を選んだ――俺が命を救ったから、一生かけて恩を返すつもりだったんだろう。無口で変な格好をしていたが、 どんな騎士よりも忠実だったし、特技もあった――どんな距離でも空中のコインをマスケットで撃ち抜けたんだ。";
			link.l1.go = "Svenson_31";
		break;
		
		case "Svenson_31":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "まあ、あいつはお前に借金を返したんだ、俺に言えることはないぜ。助かったな "+sld.name+" そしてあの野郎からダニエルを救った。こんな勇敢な戦士には、これがふさわしい結末だと思うぜ。";
			link.l1 = "そうだな、ヤン。倒れた者たちの冥福を祈って飲もう……彼らが安らかに眠れるように。他の男爵たちはどうしている？みんな無事か？";
			link.l1.go = "Svenson_32";
		break;
		
		case "Svenson_32":
			dialog.text = "今夜は大きな代償を払った。この虐殺から同志たちがいつ立ち直れるのか、俺にも分からねえ。 カインドマンは攻撃の時と場所を完璧に選びやがった。あと少しで全てが終わるところだったが、 奴の目論見はほとんど成功しかけたんだ。だが、俺たちは失ったものが思ったより少なくて済んだ。";
			link.l1 = "";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) link.l1.go = "Svenson_33";
			else link.l1.go = "Svenson_35";
		break;
		
		case "Svenson_33":
			dialog.text = "シャークは医務室にいるぜ。奴の船は二十四ポンド砲の一斉射撃を食らったんだ。海に投げ出されて、 肋骨を何本か折っちまったし、海水も飲んじまったが、まだ生きてる。数日もすりゃ、元通り元気になるさ。";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.LongHappy.BigMarry")) link.l1.go = "Svenson_34"; // был Венсан
			else link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_34":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive")) dialog.text = "ベルナールはかすり傷を二、三受けただけだ――岸を守り、地下墓地を掃討していたんだ。今は港にいて、負傷者のための病院や、 不運にも亡くなった者たちの葬儀を手配している。";
			else dialog.text = "ベルナールは運が悪かった。カタコンベからの襲撃の後、家々を片付けていた時に、 倉庫であの野郎どもと鉢合わせしちまったんだ。頭に弾を食らってな…。残念だ、あいつはいい船長だったのによ…。\nタイレックスがこれを知ったら激怒するぜ。";
			link.l1 = "";
			link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_35":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Vensan_alive")) dialog.text = "ベルナールはかすり傷を二、三受けただけだ――岸を守り、地下墓地を掃討していたんだ。\n今は港にいて、負傷者のための病院や、不運にも亡くなった者たちの葬儀を手配している。";
			else dialog.text = "バーナードは運が悪かった。カタコンベからの襲撃の後、家々を片付けていた時に、 倉庫であの野郎どもと鉢合わせしちまったんだ。頭に弾丸を食らってな……残念だ、いい船長だったのによ……タイレックスがこれを知ったら激怒するぜ。";
			link.l1 = "";
			link.l1.go = "Svenson_36"; // на завершение
		break;
		
		case "Svenson_36":
			dialog.text = "ホークのことだろう。ダニーは少なくとも一ヶ月はあいつを島から出させねえってさ、間違いねえよ。 あいつは一つのことしか頭になかったんだ……まあ、いいけどな。";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "Svenson_37";
			else link.l1.go = "Svenson_38";
		break;
		
		case "Svenson_37":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Free"))
			{
				dialog.text = "マーカスは相変わらず頑固者だ。上陸するや否や、こんな汚れを許した見張りどもをすぐさま叩きのめし始めた。 今でも町の秩序回復を指揮している。まさに鉄の男だ、間違いねえ。";
				link.l1 = "鉄のほうがまだ柔らかいぜ。うちの男爵様は、科学じゃまだ知られてねえ金属でできてるんだろうな、ははっ！";
			}
			else
			{
				pchar.questTemp.LongHappy.Terrax.Lost = "true";
				dialog.text = "マーカスの状況だけはまだはっきりしない。彼の船は拿捕されたが、 生存者たちは彼が海に飛び込むことに成功したと証言している。すでに湾内を捜索するためにロングボートを出した。 うちの男爵がそう簡単に諦めるような軟な奴じゃないことを祈るぜ。";
				link.l1 = "それはまずいが、まだ彼を悼むには早すぎる。マーカスはそんな簡単に俺たちを見捨てるような奴じゃねえ。 捜索の結果を待とうぜ。";
			}
			link.l1.go = "Svenson_39";
		break;
		
		case "Svenson_38":
			if (CheckAttribute(pchar, "questTemp.LongHappy.TerraxShipSink"))
			{
				dialog.text = "マーカスは自分の船が沈められた後、泳いで岸までたどり着いたんだ。\nまあ、知ってるだろうが、タイレックスはそんな些細なことで溺れ死ぬような奴じゃねえ。\n今は町のどこかにいるはずさ。きっと、こんな汚れを見逃した衛兵どもを震え上がらせてるだろうよ。\nまったく、鉄の男だぜ。";
				link.l1 = "鉄なら沈むだろう。どうやら我らの男爵は、まだ科学で知られていない素材でできているらしいな、はは！";
			}
			else
			{
				dialog.text = "マーカスは相変わらず頼もしいぜ。上陸するやいなや、この汚れを見逃した見張りどもをすぐに叩きのめし始めたんだ。 今でも町の秩序回復を指揮してる。まさに鉄の男だな、間違いねえ。";
				link.l1 = "鉄のほうがまだ柔らかいぜ。うちの男爵は科学でもまだ知られてねえ金属でできてるんだろうな、ははっ！";
			}
			link.l1.go = "Svenson_39";
		break;
		
		case "Svenson_39":
			dialog.text = "以上だ。まあ、もっとひどいことになってたかもしれねえ。チャールズ、お前の結婚式でさえ…荒っぽかったじゃねえか。大事なのは、お前たち二人が生きてるってことだ。最後に一つだけ忠告だ…愛し合え…そして、そのための戦いを絶対に諦めるんじゃねえぞ！";
			link.l1 = "ありがとう、ヤン。みんなもありがとう……正直に言うと、最初は祝宴から始まったことを忘れていたよ。";
			link.l1.go = "Svenson_40";
		break;
		
		case "Svenson_40":
			dialog.text = "それでは、ここで念のためにもう一度言っておく。";
			link.l1 = "ああ、あれは……すごい宴だったな。";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum")) link.l1.go = "Svenson_41";
			else link.l1.go = "Svenson_43";
		break;
		
		case "Svenson_41":
			dialog.text = "ああ、そうだ、確かにそうだった、ちょっと待てよ。何か思い出した――お前のそばにはいつもインディアンの男がいたよな？常に一緒にいて、誰かに狙われてるみたいに周囲を警戒してた。 変わった格好で、大勢の中でもすごく目立ってたぜ。";
			link.l1 = "ああ、ティチンギトゥ、奴はこの騒ぎの最初に姿を消したんだ。正直、俺も心配になってきたぜ。何か知ってるか？";
			link.l1.go = "Svenson_42";
		break;
		
		case "Svenson_42":
			pchar.questTemp.LongHappy.Tichingitu_Wife = "true";
			dialog.text = "そうらしいな。うちの酒場の旦那が大騒ぎしてたぜ、姪っ子がさらわれたってよ、襲撃の前だったらしい。なんでも、 インディアンみたいな奴と一緒にいるのを見たって話で、 そのインディアンが姪っ子を肩に担いで町の東の浜辺を歩いてたそうだ。Kindmanの手下どもにインディアンはいなかったと思うが、その話を聞いてお前の連れを思い出したから、黙ってたんだ。 あいつが面倒になる前に探しに行ったほうがいいぜ。なにしろ、酒場の旦那は先に見つけたら殺すって息巻いてるからな。 いい奴だが、姪っ子のためなら誰の首でも引きちぎりかねねえ。";
			link.l1 = "ああ、その手の奴はわかってる、心配すんな。それと、ありがとうな、ヤン。すぐに探しに行くぜ。";
			link.l1.go = "Svenson_43";
		break;
		
		case "Svenson_43":
			dialog.text = "まあ、だいたいこんな感じだ……悪いな、俺は演説とか苦手なんだよ。\nそれに今夜はみんなをすっかり消耗させちまったから、なおさらだ。\nせめて一日は休まねえとな――それから今後どうするか決めようぜ。";
			link.l1 = "そうだな、Jan。俺は行くべきだ、頭を冷やさないといけねえ。";
			link.l1.go = "Svenson_44";
		break;
		
		case "Svenson_44":
			DialogExit();
			DoQuestReloadToLocation("Pirates_town", "reload", "reload3", "LongHappy_WifeInTown");
		break;
		
		case "Svenson_45":
			dialog.text = "いい感じだな、チャールズ。よく眠れたか？";
			link.l1 = "ああ、町外れに居心地のいい家をもらったんだ。昨日のあの狂気じみた出来事も、 夢だったんじゃないかと思ったくらいさ。\nそれなのに、ヤン、お前ひどい顔をしてるじゃないか。他に何があったんだ？";
			link.l1.go = "Svenson_46";
		break;
		
		case "Svenson_46":
			dialog.text = "ああ、いや、なんでもないんだ。まだ一睡もしてなくてな。わかるだろ…ここで起きたことの後始末で街を片付けるのは大変な仕事なんだよ。";
			link.l1 = "ダニーとネイサンは元気か？みんなどこにいるんだ？";
			link.l1.go = "Svenson_47";
		break;
		
		case "Svenson_47":
			dialog.text = "休んでいる。邪魔するなよ、ダニーが今日は銃を持って寝てるってみんなに警告したからな……ドッドソンは海に出て、島を守るために新しい船を探しに行った。他の連中は島の北で亡くなった者たちを埋葬している。 ";
			link.l1 = "";
			link.l1.go = "Svenson_48";
		break;
		
		case "Svenson_48":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner") && !CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Free")) dialog.text = "マーカスはまだ見つかっていないが、俺たちで何とかするから心配するな。お前は皆のために十分やってくれたんだ、 だから気に病むな。タイラックスはいずれ戻ってくる――必ず見つけ出すさ。";
			else dialog.text = "マーカスはここで用を済ませて、誰かのラガー船でイスパニョーラへ急いで行ったぜ。 バルバゾンの死後に起きた問題を解決しなきゃならねえらしい。旦那と奥さんによろしく、そして幸運を祈ってるそうだ。 ";
			link.l1 = "";
			link.l1.go = "Svenson_49";
		break;
		
		case "Svenson_49":
			dialog.text = "ふむ、我ら兄弟団はこの打撃にも耐え抜いた。すぐに、以前よりもさらに強く立ち上がるだろう。 カインドマンとジャックマンは長い間、我らの団結を蝕んできたが、今や奴らはいない――俺の心は確信している、これからカリブを何度も震え上がらせてやるとな。法も王も味方ではない者たちにとって、 黄金時代がやって来る。俺の言葉を覚えておけ。";
			link.l1 = "それは素敵だな。もう旧世界には耐えられそうにないよ。ここへ来たとき、まさか海の自由や、荒々 しい夕焼けや朝焼けの色に恋するなんて思ってもみなかった。世界一の女と出会い……命を預けられる仲間たちに巡り会えるなんて、夢にも思わなかったよ。\n";
			link.l1.go = "Svenson_50";
		break;
		
		case "Svenson_50":
			dialog.text = "まあ、航路は知ってるだろう、自分で決めな。俺たちの家には、いつでも歓迎するぜ。";
			link.l1 = "ありがとう、Jan。俺には本当に大事なことなんだ。";
			if (CheckAttribute(pchar, "questTemp.Mtraxx")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete") link.l1.go = "Svenson_51";
				else link.l1.go = "Svenson_54";
			}		
			else link.l1.go = "Svenson_54";
		break;
		
		case "Svenson_51":
			pchar.questTemp.LongHappy.Baron = "true";
			dialog.text = "だが、その前に大事なことが残っている。シャルル、お前が寝ている間に、俺たちは集まって話し合ったんだ\nバルバゾンが死んだ今、兄弟団には新しいバロンが必要だ。ここにいる俺たちの大多数が賛成し、全会一致で決まった。 おめでとう――お前がル・フランソワの新しいバロンだ。だが待て……分かってる、お前は世慣れた男だし、この素晴らしい場所の管理に時間を割く暇はないだろう。 だから信頼できる者をそこに据えておいた。お前は好きにしていい。ただ覚えておけ――これからは兄弟団でお前の発言にも重みがあるんだぜ。";
			link.l1 = "ヤン、俺は…俺は言葉も出ねえ…こんな大きな名誉、どうしたらいいか…";
			link.l1.go = "Svenson_52";
		break;
		
		case "Svenson_52":
			dialog.text = "さあ行け！お前はあの時タイレックスとの件で見事に実力を示したし、 シャープの遺産を巡る一件でも大活躍だったじゃねえか。お前はまさに神様からの祝福だ。 お前にとっては何も変わらねえ――計画通りにやればいい。お前がいない間は、お前の部下がすべての仕事を仕切るぜ。\n有望な奴が一人いる、ジャン・ダヴィッドって言ってな、バッカニアの一員だ。フランス野郎で、正直者だし、 頭も切れる。お前と同じで、その頭をちゃんと使えるんだ。ただ、そいつを見つけるのに少し時間がかかりそうだ――どうやらスペイン人に捕まったらしいが、心配いらねえ、何とかするさ。あいつが仕事に慣れたらすぐに、 お前の取り分を送るように手配しておくぜ。";
			link.l1 = "まさかこんな展開になるとは思わなかったぜ。まあ、お前がもう決めたんなら、仕方ねえな。 海賊男爵シャルル・ド・モール！";
			link.l1.go = "Svenson_53";
		break;
		
		case "Svenson_53":
			dialog.text = "バロン万歳！その名にふさわしいのはあんただぜ。誇りを持って名乗りな。忘れるなよ――どんなに立派な制服を着ていようと、今やあんたも俺たちの仲間だ。ここ、この胸の奥には、 本物の海賊の心がしっかりと息づいてるんだからな。";
			link.l1 = "俺にはわからねえ、もしかしたらお前は大げさに言ってるのかもな……だが、お前の信頼に応えるためにできることは全部やるぜ。";
			link.l1.go = "Svenson_54";
		break;
		
		case "Svenson_54":
			dialog.text = "これからどうするつもりだ？ヨーロッパに戻るのか、父親のもとへ帰って、妻を紹介するのか？";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") || CheckAttribute(pchar, "questTemp.LongHappy.Jino_died"))
			{
				link.l1 = "ああ、だがまずは誰かに別れを告げなきゃならねえ……言いたいことは分かるだろう。";
				link.l1.go = "Svenson_56";
			}
			else	
			{
				link.l1 = "まだそんなに早くはないさ。もう一度この諸島を航海するぜ、最後にこの自由の空気を思いきり吸いたいんだ。";
				link.l1.go = "Svenson_55";
			}
		break;
		
		case "Svenson_55":
			dialog.text = "まあ、お前は船を手に入れたんだ、好きな時に帰港できるぜ。";
			link.l1 = "そうだといいな。ありがとう、ヤン、みんなにも感謝するぜ。またな、俺の古い友よ！ ホークスとシャークにもよろしく伝えてくれ！";
			link.l1.go = "Svenson_58";
		break;
		
		case "Svenson_56":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_died") && CheckAttribute(pchar, "questTemp.LongHappy.Jino_died")) sTemp = "They deserve";
			else sTemp = "He deserve";
			dialog.text = "ああ、つらいが、やらなきゃならねえんだ。海へ行くか？";
			link.l1 = "いや、俺はアンティグアへ航海する。 "+sTemp+" しばらくの間、我々の家となった場所で安らかに眠るために。";
			link.l1.go = "Svenson_57";
		break;
		
		case "Svenson_57":
			dialog.text = "俺からもよろしく伝えてくれよ。\nそれに、心配すんな――これからは俺たちだけでやれるさ。\nきっと全部うまくいくぜ。";
			link.l1 = "ありがとう、ヤン。またすぐ会おうぜ、古い友よ！ホークスとシャークにもよろしく伝えてくれ！\n…さて、アンティグアに決まりだな。";
			link.l1.go = "Svenson_58";
		break;
		
		case "Svenson_58":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "LongHappy_IslaMarryComplete", 10.0);
		break;
		
		case "Svenson_":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "Svenson_";
		break;
		
		// Глэдис
		case "Gladis":
			dialog.text = "若者よ、今日でお前はさらに私の中で大きくなったぞ。ヘレンのためにこれほど尽くしてくれて、 感謝の言葉も足りぬほどだ。どうかこれからも彼女のことを頼む。もし彼女の父親が生きていてこの様子を見ていたら、 どれほど喜んだことか……ああ、すまない。";
			link.l1 = "大丈夫だよ、グラディス。今日はヘレンを支えるために諸島を渡って来てくれたんだな。俺もヘレンも、 ジャンと一緒に来てくれて本当に感謝してるぜ、ありがとう。";
			link.l1.go = "Guests_block";
		break;
		
		// Форже - патер Мэри
		case "forge":
			dialog.text = "ド・モール旦那、馴れ馴れしくて申し訳ありませんが、あえてこう言わせてください――シャルル、友よ、心から嬉しく思います！君や花嫁のために俺にできることがあれば、何でも言ってくれ！";
			link.l1 = "ありがとうございます、バロン。私は本当に幸せですわ。それから、父が持参金として望んでいた葡萄園の件ですが、 きっとお返しできると思いますの――幸いにも、新世界での生活で私の財政状況はかなり良くなりましたから。";
			link.l1.go = "forge_1";
		break;
		
		case "forge_1":
			dialog.text = "そうだな、チャールズ、お前なら欲しいものは何でも手に入るだろう。失礼するが、 父親代表として私も一役買わせてもらおう――今日は財務大臣である親友に手紙を書くつもりだ。お前の選んだ女性には貴族の称号を授け、そうだな、 ガスコーニュにある借金で没収された領地の中から良いものを見つけて、遡って彼女に与えることにしよう。 これで誰もモンペール騎士が身分の低い妻を迎えたなどとは言えなくなるぞ！";
			link.l1 = "そんな噂話には興味ないと思うが、ありがとう、バロン。だが、それでも君はやめておくべきだ。";
			link.l1.go = "forge_2";
		break;
		
		case "forge_2":
			dialog.text = "もちろんそうすべきだ！さあ、チャールズ、他の客にも気を配ってきなさい。\nそしてもう一度、心からお祝い申し上げる！";
			link.l1 = "妻と私はあなたに感謝します。では、バロン。";
			link.l1.go = "Guests_block";
		break;
		
		// Форже - патер ГГ
		case "forge_3":
			dialog.text = "モール旦那、馴れ馴れしくて申し訳ありませんが、あえてこう言わせていただきます――シャルル、友よ、心から嬉しく思います！君や花嫁のために私にできることがあれば、何でも言ってくれ！";
			link.l1 = "ありがとうございます、男爵様。でも、もう十分にお世話になりました。ご招待に応じていただいただけで、 私たちには十分です。";
			link.l1.go = "forge_4";
		break;
		
		case "forge_4":
			dialog.text = "どうして返事をしないなんてことがある、シャルル！だが聞いてくれ――お前と美しい花嫁にふさわしい贈り物をしたいが、金や剣で手に入らないものなんて思いつかないんだ。だから、 パリの財務大臣である友人に手紙を書くことにする。お前がヨーロッパに着く頃には、王室勅令に署名して 「ド・モンペール」の名を「バロン・ド・モンペール」の爵位に昇格させる手はずを整えておく！いや、何も言うな、 これくらいは俺にさせてくれ。";
			link.l1 = "何と言えばいいのか分かりません、バロン…。父はきっと大喜びします。本当にありがとうございます。";
			link.l1.go = "Guests_block";
		break;
		
		// Форже гость
		case "forge_5":
			dialog.text = "チャールズ、どうか、心からお祝い申し上げます！あなたの選んだお相手は本当に素晴らしい方ですね！今日、 植民地の流行はまさに新たな方向へと強烈な一撃を受けたと思います。あなたの独創性にはいつも感心させられます！ あなたと美しい伴侶が末永く幸せに暮らせますように！";
			link.l1 = "ありがとうございます、男爵様。ご訪問いただき光栄でございます。";
			link.l1.go = "forge_6";
		break;
		
		case "forge_6":
			dialog.text = "どうして離れていられるんだ、相棒？俺たちは一緒にいろんなことを乗り越えてきたし、 お前を友と呼べることを誇りに思ってるぜ、チャールズ。覚えておけ――何があっても俺の家の扉はいつでもお前のために開いてるからな。";
			link.l1 = "バロン、ド・モンペール家の扉はいつでもあなたに開かれております。";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси патер Мэри
		case "puancie":
			dialog.text = "シャルル、友よ、今日はとても大切な日だ、そして君が私を招いてくれたことを心から嬉しく思う。 君と私は長く険しい道のりを歩んできた、そしてマドモワゼル…いや、どうか許してほしい―マドム・ド・モールの代理の父となることは、私にとって光栄の極みだ。本当にそう思っている。心から、 君の幸せを願っている！それから、君がヨーロッパへ行く時はぜひ知らせてほしい―君の選んだ方の代理の父として、君のお父上に必要な結婚祝いの品をすべて送らせてもらうよ。信じてくれ、 誰もモンペール騎士の花嫁が貧しいとか、ふさわしくないなどとは言わせないさ！";
			link.l1 = "お伺いしてもよろしいでしょうか、シュヴァリエ。 モンペール家の領地から北へ数マイルのところに良い葡萄畑がございます。それはラ・ブリーニュ家の所有でして、私も…";
			link.l1.go = "puancie_1";
		break;
		
		case "puancie_1":
			dialog.text = "もう一言も言うな、友よ、もう一言もだ！すぐにリヨンの代理人に手紙を書く――お前が到着する頃には、これらの葡萄園はお前の選んだ者に譲渡されているだろう。";
			link.l1 = "ありがとうございます、シュヴァリエ。おっしゃる通り……我々の「友情」は本当にいろいろありました。しかし、あなたが今日この日を共にしてくれて本当に嬉しいです。 また会いましょう、重ねて感謝します！";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси патер ГГ
		case "puancie_2":
			dialog.text = "チャールズ、友よ、今日はとても大切な日だな。君がこの日に招いてくれて本当に嬉しいよ。 俺たちは長くて険しい道のりを歩んできたが、今日こうして君の結婚式の証人になれるのは俺にとって光栄だ。 心から幸せを祈っている！それから、ヨーロッパに行く時は知らせてくれ――君の父上にふさわしい結婚祝いを贈るからな。";
			link.l1 = "その必要はありません、シュヴァリエ。私の招待に応じてくださり、ありがとうございます。";
			link.l1.go = "puancie_3";
		break;
		
		case "puancie_3":
			Log_Info("You have got gems");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry2", 50);
			TakeNItems(pchar, "jewelry3", 50);
			TakeNItems(pchar, "jewelry4", 50);
			dialog.text = "言った通り、私にとって光栄なことです！だが待ってくれ、友よ、この機会に君に贈り物をしたいんだ――きっと君にも、君の選んだ人にも喜んでもらえるはずだ。ニューギアナの鉱山から採れた美しい宝石だ――上等な枠に飾れば、モール夫人は王宮の晩餐会でもひときわ輝くことだろう！もちろん、彼女がドレスを着てくれるなら……";
			link.l1 = "ああ、本当にお気遣いなく、シュヴァリエ。改めてありがとうございます。";
			link.l1.go = "Guests_block";
		break;
		
		// Пуанси гость
		case "puancie_4":
			dialog.text = "チャールズ、俺の友よ、おめでとう！俺たちは長くて険しい道のりを歩んできたが、 今日ここにいられることを心から嬉しく思うぜ。主も見ておられる――お前はその幸せにふさわしい！その幸せを大切にし、守ってくれ――これからの長い年月が幸せで満ちるよう祈っているぞ！";
			link.l1 = "ありがとうございます、シュヴァリエ。妻も私もとても感謝しております。";
			link.l1.go = "Guests_block";
		break;
		
		// Фадей патер
		case "fadey":
			dialog.text = "チャールズ、なんて盛大な宴だ、それにこんなにたくさんの偉い方々が集まっている！心からお前の幸せと健康、 そして喜びをもたらす子供たちを願うぜ！俺たちの言葉で言うなら――「ゴルコ」だ！\n";
			link.l1 = "ありがとう、Fadey、来てくれるなんて光栄だ。";
			link.l1.go = "fadey_1";
		break;
		
		case "fadey_1":
			dialog.text = "でも、なんでこんなに人が集まってるのか、よく分からねえな。まるで結婚式じゃなくて、 でっけえ商談でもしてるみてえだし、俺の好みにはビールもウォッカもまだ足りねえ……ははっ！まあ、冗談だよ、チャールズ。どうした、真っ青じゃねえか？抱きしめてくれよ、新婚の船長さん！";
			link.l1 = "なんてこった…ファディー、お前は熊みてえに強いじゃねえか！";
			if (CheckAttribute(pchar, "questTemp.Persian"))
			{
				if (pchar.questTemp.Persian == "time" || pchar.questTemp.Persian == "end") link.l1.go = "fadey_2";
				else link.l1.go = "Guests_block";
			}
			else link.l1.go = "Guests_block";
		break;
		
		case "fadey_2":
			GiveItem2Character(pchar, "blade_22");
			GiveItem2Character(pchar, "blade_23");
			GiveItem2Character(pchar, "blade_24");
			Log_Info("You got three Persian sabres");
			PlaySound("interface\important_item.wav");
			dialog.text = "待ってくれ、チャールズ、まだ行くな――客人が贈り物なしで結婚式に出席するのはよくないだろう。\nさあ、これを受け取ってくれ。君がこれらの剣を全部探そうとしたのは知っているし、 その中には明らかに気に入ったものもあっただろう。\nだから受け取ってくれ――家の屋敷に飾って、ファディ・モスコヴィットのことを優しい言葉で思い出してくれよ！";
			link.l1 = "これは本当に素晴らしい贈り物だ！ありがとう、Fadey。確かに見事な武器だし、必ずde Monper家の屋敷にふさわしい場所を与えると約束するよ！";
			link.l1.go = "Guests_block";
		break;
		
		// Фадей гость
		case "fadey_3":
			dialog.text = "チャールズ、なんて盛大な祝いだ、しかもこんなに偉い人たちが集まってる！心から幸せと健康を、 そして喜びをもたらす子どもたちに恵まれることを願ってるぜ！俺たちの言葉で言うと――「ゴルコ！」だ！さあ、抱きしめさせてくれよ、新婚の船長！";
			link.l1 = "うわぁ、驚いたぜ……ファディ、お前は熊みたいに力持ちだな！";
			link.l1.go = "Guests_block";
		break;
		
		// Проспер Трубаль
		case "Prosper":
			dialog.text = "チャールズ、これは見逃せなかったよ。心から君と君の選んだ人にお祝いを言う！幸せになってくれ！\n実はな、数か月前に娘をいい男に嫁がせたんだ。二人は愛し合ってる。でも正直なところ、 相手が君じゃなかったのは少し残念だったよ……まあ、いいか……何を言ってるんだ俺は――とにかくおめでとう！末永く幸せに暮らしてくれよ！";
			link.l1 = "ありがとう、Prosper、来てくれて嬉しいよ。";
			link.l1.go = "Guests_block";
		break;
		
		// Тичингиту
		case "Tichingitu":
			dialog.text = "おめでとう、船長！奇妙な儀式だが、美しいものだった――ティチンギトゥも気に入ったようだぜ。だがな、本来なら船長は女をさらって、その親族に身代金を送ればいいんだよ。";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "まあ、ある意味ではそうしたんだが、これはただの形式にすぎないさ。ありがとう、友よ！";
			else link.l1 = "まあ、ある意味ではそうだが、これはただの形式にすぎないんだ。ありがとう、友よ！ シャープタウンでまたゆっくり話そう――あそこならもっと堅苦しくなく、本当の楽しみが待ってるぜ、約束する！";
			link.l1.go = "Tichingitu_1";
		break;
		
		case "Tichingitu_1":
			dialog.text = "また火の酒か？ティチンギトゥはあまり好きじゃねえんだ。祝いの乗り込みでもした方がマシだろう、 せめて焚き火の周りで踊るとかよ？";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) link.l1 = "できれば終わる前に焚き火の周りで踊るような羽目にはなりたくねえし、白兵戦も避けたいもんだ。まあ、我慢しろよ――もう少しだ、そしたら真っ直ぐ酒場へ行くぜ。";
			else link.l1 = "終わる前に焚き火の周りで踊る羽目になりそうで怖いんだ、できれば白兵戦は避けたい。まあいい、我慢しろ――もう少しだ、すぐにシャープタウンへ出航するぞ。";
			link.l1.go = "Guests_block";
		break;
		
		case "Tichingitu_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "船長、おめでとうございます！またお祝いですね。ティチンギトゥは前回より今回の宴の方が楽しんでいるぜ。 船長は友を選ぶ目があるな――ここには誠実さが多く、偽善やカツラは少ないからな。";
			link.l1 = "ありがとう、友よ！ただし火酒は飲むなよ――ここのはとんでもなく強いからな。";
			link.l1.go = "Tichingitu_4";
			link.l2 = "ありがとう、友よ！一杯やるか？お前は酒が苦手なのは知ってるが、今日は試してみたらどうだ！";
			link.l2.go = "Tichingitu_3";
		break;
		
		case "Tichingitu_3":
			pchar.questTemp.LongHappy.Tichingitu_Rum = "true";
			dialog.text = "ティチンギトゥは火酒は好きじゃねえが、船長がどうしてもってんなら、今日はいいぜ。あんたの幸せと、 あんたの女に乾杯だ！";
			link.l1 = "「そしてお前にもだ、ティチンギトゥ！お前の友情と忠誠に乾杯だ！」";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_4":
			DialogExit();
			npchar.dialog.currentnode = "Tichingitu_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				sld = characterFromId("Mary");
				sld.dialog.currentnode = "LongHappy_57";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Tichingitu_4_1":
			dialog.text = "いい宴だな、船長。";
			link.l1 = "満足してくれて嬉しいよ。";
			link.l1.go = "Tichingitu_4";
		break;
		
		case "Tichingitu_5":
			dialog.text = "船長、星を見に出てきたのか？今夜はとても美しい夜になりそうだ。ティチンギトゥは海の上の夜が大好きなんだ。 とても穏やかだからな。";
			link.l1 = "まだ元気そうで何よりだぜ、相棒！ナサニエルと俺はお前の助けが必要なんだ――酒場の連中が酒を切らしててな、造船所の下にある在庫から酒の箱を何箱か運ばなきゃならねえんだ。";
			link.l1.go = "Tichingitu_6";
		break;
		
		case "Tichingitu_6":
			dialog.text = "先導してくれ、船長。ティチンギトゥはいつも通りお前についていくぜ。";
			link.l1 = "よし、行くぜ！";
			link.l1.go = "Tichingitu_7";
		break;
		
		case "Tichingitu_7":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
		break;
		
		case "Tichingitu_8":
			dialog.text = "船長、人がいるぞ、しかも武装してやがる。ティチンギトゥが奴らの武器の音を聞いてるが、 どんどん大きくなってきてるぜ。気に入らねえな。隠れよう。";
			link.l1 = "さあ、相棒――ここはシャープタウンだぜ、ここじゃトイレに行く時ですらピストルを持っていくんだ。おい、ネイサン……ちくしょう！一本なくなっちまった。こんな調子じゃ全部の瓶を割っちまうぞ！しっかり立て、この野郎！ははは！";
			link.l1.go = "Tichingitu_9";
		break;
		
		case "Tichingitu_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LongHappy_SetBandosInDungeon();
		break;
		
		case "Tichingitu_10":
			dialog.text = "船長……あんた……ティチンギトゥの頭が嵐の中のマストみてえにグルグル回ってるぜ。何があったんだ？";
			link.l1 = "俺も同じことを聞こうと思ってたんだぜ！この間ずっとどこにいたんだ！？";
			link.l1.go = "Tichingitu_11";
		break;
		
		case "Tichingitu_11":
			dialog.text = "ティチンギトゥはこの娘の叫び声で一時間前に目を覚ましたんだ。ほとんど裸で浜辺を走り回って、 誘拐犯や野蛮人がどうのこうのと叫んでいた……だが、ここには俺たち以外誰もいないんだよ。\n水はあるか？またあの火の酒じゃないだろうな、ティチンギトゥはもう嫌いなんだぜ？";
			link.l1 = "どこかに水筒があったはずだ、戦いで失くしてなけりゃ……ほら、これだ。どうやってこんなことをやったんだ？彼女の叔父である地元の酒場の主人が、 姪をさらったインディアンを探していてな、羽飾りをつけた頭ごと八つ裂きにしてやると息巻いてるぜ。 誰のことを言ってると思う？";
			link.l1.go = "Tichingitu_12";
		break;
		
		case "Tichingitu_12":
			dialog.text = "ティチンギトゥは思い出した。彼女は森の悪魔が酒場で結婚式を手伝っていたんだ。俺たちは一緒に火酒を飲んだ、 ティチンギトゥはもっと欲しがっていた。それから、この女……とても綺麗で……船長、思い出したかもしれない！ティチンギトゥは彼女と結婚したかった……カヌーを作って彼女を連れて行きたかったんだ……慈悲深き精霊よ！とても悪い奴らが火酒を持ってきた。もしかしたら悪魔か邪悪な精霊かもしれない！ ティチンギトゥはもう二度と……";
			link.l1 = "彼女を連れて行く？カヌーを作るだと？！あはは、お前はロマンチストだな、相棒……はは……はははははは、ああ、笑いが止まらねえ……止まらねえよ！";
			link.l1.go = "Tichingitu_13";
		break;
		
		case "Tichingitu_13":
			dialog.text = "船長、ティチンギトゥがあの女をさらったのは本当だが、俺たち、いや…今すぐ結婚しなくてもいいんじゃねえか？あいつは…オウムみてえにうるさいし…あんまり美人でもねえんだよ。";
			link.l1 = "ああ、友よ、一晩中遊び明かした女たちは朝になるとみじめなもんだぜ。心配すんな、 英雄好きのお前のために何か考えてやるよ。さあ、シャープタウンに戻らなきゃならねえ、 お前は休暇の乗り込みを逃したんだぞ…";
			link.l1.go = "Tichingitu_14";
		break;
		
		case "Tichingitu_14":
			dialog.text = "拿捕か？船長はさっき戦いのことを言っていたな。ティチンギトゥの命令にもまだ思考が従わねえ。町で何があったんだ？ ";
			link.l1 = "陸でも海でも本物の戦いだったぜ。大砲は一晩中鳴り響いてたと思う、たぶんサンホセにまで聞こえたんじゃねえか。 だが、お前は別の「戦い」で忙しかったんだろ、まあいいさ、分かってる……さあ、行きながら全部話してやるよ。\n";
			link.l1.go = "Tichingitu_15";
		break;
		
		case "Tichingitu_15":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			sld = characterFromId("LH_waitress");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.longhappy_shoregirl1.win_condition.l1 = "location";
			pchar.quest.longhappy_shoregirl1.win_condition.l1.location = "Pirates_town";
			pchar.quest.longhappy_shoregirl1.function = "LongHappy_ReturnShoreGirl";
		break;
		
		case "Tichingitu_16":
			dialog.text = "ありがとうございます、船長…。ティチンギトゥは決して……";
			link.l1 = "ああ、「遠い草原の暴れ馬」よ、お前はもうこれ以上飲むべきじゃねえぜ。さっさと寝ちまいな。 俺ももう疲れ果てて倒れそうなんだ。";
			link.l1.go = "Tichingitu_17";
		break;
		
		case "Tichingitu_17":
			DialogExit();
			npchar.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			LAi_SetImmortal(npchar, false);
			npchar.OfficerWantToGo.DontGo = true;
			npchar.CompanionDisable = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			LAi_SetOfficerType(npchar);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			npchar.dialog.currentnode = "Tichingitu_officer";
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.dialog.currentnode = "LongHappy_55";
			ChangeCharacterAddressGroup(sld, "Pirates_town", "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Tichingitu_18":
			dialog.text = "船長、改めておめでとう！ティチンギトゥは前回よりもこの祝いを楽しんでいるぞ。船長は友を選ぶ目があるな――ここには誠実さが多く、偽善とカツラは少ない。";
			link.l1 = "それから、もっとたくさんの火酒だ。ところで、俺と一杯やらねえか？お前が好きじゃねえのは知ってるが、 今日は特別な日だぜ！";
			link.l1.go = "Tichingitu_19";
		break;
		
		case "Tichingitu_19":
			dialog.text = "ティチンギトゥは火酒が好きじゃねえが、船長がどうしてもってんなら、今日は付き合うぜ。あんたの幸せと、 あんたの女に乾杯だ！二人が同じ道を歩み、太陽と月がいつもその道を照らしますように。";
			link.l1 = "ありがとう、友よ。乾杯だ、ティチンギトゥ！俺たちの友情に！";
			link.l1.go = "Tichingitu_4";
		break;
		
		// губернаторы
		// Сен Пьер
		case "FortFrance_Mayor":
			if (pchar.questTemp.GoldenGirl == "end")
			{
				dialog.text = "素晴らしい…お祝いだな、チャールズ。本当に嬉しいよ。だけど、やっぱりお前のことはよく分からないな…手の中にかけがえのないバラを持ちながら、それを…野の花と取り替えるなんて。でも、心は自分の望むものを求めるものだ…幸せになれよ、友よ。末永く幸せに暮らせますように！";
				link.l1 = "あなたが手にしている花で一番美しいのは、その花へのあなたの想いです。\nそれがなければ、ただ色あせていく肉の塊にすぎません。\nお越しいただき光栄です、公爵様。";
				link.l1.go = "FortFrance_Mayor_1";
			}
			else
			{
				dialog.text = "素晴らしい日だな、友よ、そして素晴らしい出来事だ！心からお祝いを申し上げる！俺は三度も結婚したが、 そのたびに初めてのように震えたものさ、ああ、若き日よ…";
				link.l1 = "旦那、あなたはまだ老け込むには早いですよ、落ち込まないでください。来てくれてありがとう、ジャック！";
				link.l1.go = "Guests_block";
			}
		break;
		
		case "FortFrance_Mayor_1":
			dialog.text = "待ってくれ、チャールズ。誤解しないでくれ、俺は心から本当に嬉しいんだ！それから……はい、これを受け取ってくれ。我々の共通の……友人が、今日君に渡すようにと特別に頼んできたんだ。";
			link.l1 = "誰からのものか心当たりがある。ありがとう、またすぐ会おう。";
			link.l1.go = "Guests_block";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "2-1");
					else AddQuestRecordInfo("Letter_Marquesa", "1-1");
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "4-1");
					else AddQuestRecordInfo("Letter_Marquesa", "3-1");
				}
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.GoldenGirl.Julianna_Prisoner"))
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "2");
					else AddQuestRecordInfo("Letter_Marquesa", "1");
				}
				else
				{
					if (CheckAttribute(pchar, "questTemp.GoldenGirl.JulianaSex")) AddQuestRecordInfo("Letter_Marquesa", "4");
					else AddQuestRecordInfo("Letter_Marquesa", "3");
				}
			}
		break;
		
		// Бас Тер
		case "BasTer_Mayor":
			dialog.text = "素晴らしい式だな、シャルル。心からお祝い申し上げる！私自身とバステールの市民全員を代表して、君と…魅力的な奥様にお祝いを贈るよ。なんて素敵な夫婦なんだ！末永くお幸せに！";
			link.l1 = "ありがとうございます、閣下。お気に召していただけて嬉しいです。";
			link.l1.go = "Guests_block";
		break;
		
		// Порт Принс
		case "PortPax_Mayor":
			dialog.text = "なんと素晴らしいおもてなしだ、ド・モール旦那、本当に素晴らしい！それに花嫁も…この衣装でとても独創的だ。\n我が町の住民一同を代表して、心よりお祝い申し上げます！末永くお幸せに！";
			link.l1 = "「ありがとうございます、閣下。」";
			link.l1.go = "Guests_block";
		break;
		
		// Тортуга
		case "Tortuga_Mayor":
			dialog.text = "とても魅力的でしたわ――あなたと花嫁、ド・モール旦那、お二人とも本当に特別でした！ですが、あなたは並外れた方ですわ。 末永く幸せな結婚生活をお祈りします。どうかいつまでもお幸せに！";
			link.l1 = "「本当に感謝しております、閣下。」";
			link.l1.go = "Guests_block";
		break;
		
		// д'Ойли
		case "PortRoyal_Mayor":
			PlaySound("Voice\English\LE\Doily\Edvard_Doily_03.wav");
			dialog.text = "お前さんの結婚のためなら、カリブを横断する価値があったぜ！\n全てのイギリス植民地の住民を代表して、おめでとう、船長！\nお前さんと花嫁――いや、もう奥さんだな――は本当に素晴らしい夫婦だぜ！";
			link.l1 = "ご訪問とご親切なお言葉、ありがとうございます、カーネル！";
			link.l1.go = "Guests_block";
		break;
		
		// Исла Тесоро
		// Тиракс
		case "Terrax":
			if (CheckAttribute(pchar, "questTemp.Mtraxx")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
				{
					dialog.text = "「それで、この結婚した伊達男が俺の海賊の浜辺で何してやがるんだ、あぁ！？教えろよ、旦那、俺の古い友人――あの荒くれ海賊チャーリー・プリンスをどうしたんだ？」";
					link.l1 = "チャーリー・プリンスは死んだんだ、覚えてるだろ、マーカス……ハハハ、こっちに来いよ、この海の悪魔め！会えて嬉しいぜ！みんな元気にしてるか、もう全員集まったのか？";
					link.l1.go = "Terrax_1_1";
				}
				else // 28-03-20
				{
					dialog.text = "「で、こんな結婚した伊達男が俺の海賊浜で何してやがるんだ、ああ！？教えてくれよ、旦那、俺の古い友達――あの厳しいシャルル・ド・モール船長をどうしたんだ？」";
					link.l1 = "ああ、マーカス、俺も会えて嬉しいぜ！みんな元気にしてるか、全員集まったのか？";
					link.l1.go = "Terrax_1";
				}
			}
			else
			{
				dialog.text = "「で、こんな結婚した伊達男が俺の海賊の浜辺で何してやがるんだ、ああ！？教えろよ、旦那、俺の古い友人――あの厳しいシャルル・ド・モール船長に何をしたんだ？」";
				link.l1 = "ああ、マーカス、俺も会えて嬉しいぜ！みんな元気にやってるか、全員集まったのか？";
				link.l1.go = "Terrax_1";
			}
		break;
		
		case "Terrax_1":
			dialog.text = "ああ、森の悪魔は昨日到着したばかりで、すぐに指図を始めたんだ――だから客人たちも来て、祝宴の準備は万端さ。お前の船がサンゴ礁の近くで目撃されて、 野郎どもは我慢できずに酒場へ飛び込んでいった。たぶん、もうホークの樽を開けちまっただろうな。急げよ、 まだ一緒に一杯やれるかもしれねえ――ネイサンは、あれは特別なラムだって自慢してたぜ！";
			link.l1 = "これぞ俺たち流だぜ――船からそのまま宴会に突入だ！俺の相棒を待って、すぐに後を追うからな、マーカス！";
			link.l1.go = "Terrax_2";
		break;
		
		case "Terrax_1_1":
			dialog.text = "ああ、森の悪魔は昨日ちょうど到着して、すぐに指図を始めた――だから客人たちも来ていて、祝宴の準備は万端だ。お前の船が岩礁の近くで目撃されて、 野郎どもは我慢できずに酒場へ駆け込んで、たぶんもうホークの樽を開けちまっただろうな。急げよ、 まだ一杯やれるチャンスがあるかもしれねえ――ネイサンは、あれは特別なラムだって自慢してたぜ！";
			link.l1 = "これが俺たち流さ――船からそのまま宴会だ！俺の相棒を待って、すぐ後を追うぜ、マーカス！";
			link.l1.go = "Terrax_2";
		break;
		
		case "Terrax_2":
			DialogExit();
			DoQuestReloadToLocation("Pirates_tavern", "reload", "reload1", "LongHappy_IslaTesoroTavern");
		break;
		
		case "Terrax_3":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "シャルル・ド・モールと結婚した――まだ慣れないわ……最初はスヴェンソン、今度はあなた――次は誰かしら？マーロウ牧師？それとも親切者ジャック？";
			link.l1 = "ホークスのことを忘れたのか。\nそれに、お前はどうなんだ、マーカス？一匹狼のままでいるのに飽きてねえのか？";
			link.l1.go = "Terrax_4";
		break;
		
		case "Terrax_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				dialog.text = "ダニーとネイサンは昔からの問題だ――俺はもう諦めてるが、正直お前には驚かされたぜ！だがな、森の悪魔の弟子は見事な女だ――本当に、口も銃も達者で、どんな嵐にも耐えられる。これ以上ふさわしい女はそうそう見つからねえだろう。 お前は幸運な奴だ、船長――彼女を大事にしろよ！";
			}
			else
			{
				dialog.text = "ダニーとネイサンは昔からのことだ――もう俺は慣れっこさ、だがあんたには正直驚かされたぜ！もっとも、聞いた話じゃ、 あんたのメアリーは剣のことをよく知っていて、しかも使いこなせるらしいな――感服するぜ！まさに戦友ってやつだ。ひとつ秘密を教えてやろう、あんな女のためなら、 俺だって独り身の信条を考え直すかもしれねえ。あんたは幸運な男だぜ、船長――彼女を大事にしなよ！";
			}
			link.l1 = "わかってるさ、あの娘はまさに奇跡だ。そして俺はまた幸せで天にも昇る気分だよ――まるで初めて出会ったあの日のようにな！";
			link.l1.go = "Terrax_5";
		break;
		
		case "Terrax_5":
			dialog.text = "さて、乾杯だ！…愛に！…だが俺たちをこの敷居を越えて地平線の彼方へ駆り立てる愛じゃねえ！…この敷居で俺たちを待っている愛にだ！地の果てや黄金の山からでも俺たちを引き戻す愛に！その愛と共に生きて、 幸せになろうぜ！";
			link.l1 = "素晴らしい乾杯だったぜ、Marcus、ありがとう！";
			link.l1.go = "Terrax_6";
		break;
		
		case "Terrax_6_1":
			dialog.text = "乾杯だ、お前の結婚に、相棒！";
			link.l1 = "ありがとう、Marcus...";
			link.l1.go = "Terrax_6";
		break;
		
		case "Terrax_6":
			DialogExit();
			npchar.dialog.currentnode = "Terrax_6_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Terrax_7":
			dialog.text = "ジャックか？これは間違いなくまずいな……";
			link.l1 = "マーカス、どう思うんだ…";
			link.l1.go = "Terrax_8";
		break;
		
		case "Terrax_8":
			dialog.text = "時間がない！奴らが扉の向こうにいるぞ！みんな、武器を取れ！";
			link.l1 = "さあ、行くぜ！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernFight");
		break;
		
		case "Terrax_9":
			dialog.text = "こんなに宴で楽しんだのはいつ以来か思い出せねえぜ！まだ終わっちゃいねえ！聞こえるか？外で誰かが撃ってやがる！ 奴らの血で通りを染めてやろうじゃねえか！";
			link.l1 = "待て！あいつらは一体何者だ！？それに一体何をしやがるつもりなんだ！？";
			link.l1.go = "Terrax_10";
		break;
		
		case "Terrax_10":
			DialogExit();
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "Svenson_20";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		// Натаниэль Хоук
		case "Nathaniel":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "結婚したド・モール船長、これほど心から乾杯したくなる理由に出会うことは滅多にないぜ。グラスを掲げろ――これはただのキャベツ酒じゃねえ。東インドの紅茶が染み込んでて、本物のペルシャの香辛料で味付けされてるんだ！\n";
			link.l1 = "「どうして喉が焼けるように熱いのか不思議に思ってたんだ、まるで溶けた鉛でも飲んだみたいにな。さて、ネイサン、 乾杯だ…」";
			link.l1.go = "Nathaniel_1";
		break;
		
		case "Nathaniel_1":
			dialog.text = "待て、まずは乾杯だ！おい、旦那方、ジョッキを掲げろ！ 今日は我らの友人であり仲間のシャルル・ド・モールが家庭という航路に旅立つ日だ。俺たちから心よりお悔や…おい、ダニー、銃を下ろせって！もちろん、おめでとう！これからは同じ船の帆なんだから、どんな嵐も乗り越えて、 一番豊かな岸まで導いてくれよ！\n";
			link.l1 = "心から感謝します、ネイサン。あなたとダニエルは私たちの手本です。";
			link.l1.go = "Nathaniel_2";
		break;
		
		case "Nathaniel_2":
			dialog.text = "それは嬉しい知らせだ。俺と妻は世界一の夫婦ってわけじゃねえが、一緒にいて幸せだし、 あんたは俺たちのために本当にいろいろしてくれた。だから俺に言わせりゃ、あんたはもう家族の一員だぜ。 必要なときはいつでも力になる。幸せになってくれ、そして一杯やってくれよ！";
			link.l1 = "じゃあ飲もうぜ！おお…このラム酒は聖なる異端審問官の武器庫にでも入れておくべきだな。くそっ！喉から胃まで焼けるようだ…うぐっ！ふうっ！…気に入ったぜ！";
			link.l1.go = "Nathaniel_3";
		break;
		
		case "Nathaniel_3":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_3_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Nathaniel_3_1":
			dialog.text = "お前は二十年前のダニーと俺によく似てるぜ！";
			link.l1 = "もう一杯くれ、ネイサン！";
			link.l1.go = "Nathaniel_3";
		break;
		
		case "Nathaniel_4":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "「なんだと！？ヤンがワインを取りに地下貯蔵庫へお前を行かせたのか？ちょっと散歩しようぜ、手伝ってやるし、 新鮮な空気も吸えて悪くねえだろ。」\n";
			link.l1 = "「でも、ダニーとどこにいるんだ」 "+sld.name+"「ヤンが、あいつらは話をしに行ったって言ってたぜ。」";
			link.l1.go = "Nathaniel_5";
		break;
		
		case "Nathaniel_5":
			dialog.text = "ああ、ダニーも知ってるさ、どんなに腕の立つ女がいても、 運のいい旦那たちが心から羽を伸ばせる時間なんてないってな。だから、彼女たちは受けた賛辞を全部聞き流して、 男たちに楽しませるために屋敷へ向かったんだ。";
			link.l1 = "よし、それじゃあ行くぜ！ジョッキを二、三杯は飲んだが、くそっ、今こそ本気で酔っぱらう時だな！";
			link.l1.go = "Nathaniel_6";
		break;
		
		case "Nathaniel_6":
			DialogExit();
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			bDisableFastReload = true;//закрыть переход
			pchar.quest.longhappy_isla_vine.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_vine.win_condition.l1.location = "Pirates_town";
			pchar.quest.longhappy_isla_vine.function = "LongHappy_IslaTesoroToAlexus";
		break;
		
		case "Nathaniel_7":
			PlaySound("ambient\jail\jail_door2.wav");
			dialog.text = "さあ、これが宝箱だ。持てるだけ持って、さっさと戻るぞ、あの頑固ジジイにここを閉じ込められる前にな。";
			link.l1 = "大げさだぜ、ネイサン。あいつはそこまで悪くねえ……待て、今の音、聞こえたか？";
			link.l1.go = "Nathaniel_8";
		break;
		
		case "Nathaniel_8":
			PlaySound("ambient\jail\jail_door2.wav");
			dialog.text = "ヤンがたぶん仲間をもっと見つけて、俺たちを助けるために送り込んだんだろう。くそっ！";
			link.l1 = "さあ、縁起を担いで瓶を割るんだ。もう一本取って、行こうぜ。";
			link.l1.go = "Nathaniel_9";
		break;
		
		case "Nathaniel_9":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);//запретить драться
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Rum") && GetCharacterIndex("Tichingitu") != -1)
			{
				sld = characterFromId("Tichingitu");
				sld.dialog.currentnode = "Tichingitu_8";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else LongHappy_SetBandosInDungeon();
		break;
		
		case "Nathaniel_10":
			dialog.text = "一体何が起きてやがるんだ、こいつらは何者だ？チャールズ、お前は何か分かるのか？";
			link.l1 = "俺にはわからねえ、ナサン。でも一人が助けを呼びに走ったし、さらに足音が聞こえる気がする。 酒場に戻らなきゃならねえ！";
			link.l1.go = "Nathaniel_11";
		break;
		
		case "Nathaniel_11":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			pchar.quest.longhappy_totavern.win_condition.l1 = "location";
			pchar.quest.longhappy_totavern.win_condition.l1.location = "Pirates_tavern";
			pchar.quest.longhappy_totavern.function = "LongHappy_TavernAlarm";
		break;
		
		case "Nathaniel_12":
			LongHappy_TownRepose();
			dialog.text = "こいつらは叩き伏せたが、海から砲声が響いてるのが聞こえるか？ 戦闘に備えてるのはマーカスのフリゲートとヤンのコルベット、二つの乗組員だけだ。 俺やダニーたちは部下を上陸させた――何せ結婚式だからな――だからセンチュリオンは使えねえ。お前の船はどうだ？どうするか、早く決めねえといけねえぞ！";
			link.l1 = "乗組員の半分は上陸させたが、残りは酔っていないといいんだがな。\nだがまずは、妻を探して無事かどうか確かめねえとな。";
			link.l1.go = "Nathaniel_13";
		break;
		
		case "Nathaniel_13":
			dialog.text = "ああ、ダニーも見当たらないな。じゃあ、こうしよう――タイレックスとスヴェンソンはすでに港へ急いでいて、ボートで自分の船に向かうはずだ。 俺たちは奥方たちのために邸宅へ向かう、残りは岸で防衛を整えてくれ。お前の船の乗組員を集めるために、 何人か士官を送ってくれないか？手助けがあれば助かるぜ。";
			link.l1 = "よし、みんな、動くぞ！一秒でも無駄にできねえ！";
			link.l1.go = "Nathaniel_14";
		break;
		
		case "Nathaniel_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Pirates_town", "reload3_back", false);
		break;
		
		case "Nathaniel_15":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "急げ、上の階へ！ダニーと "+sld.name+" 必ずそこにいるはずだ！もしあの野郎どもが奴らを傷つけてたら……";
			link.l1 = "考えるんじゃねえ！上へ行くぞ！さあ、行くぜ！";
			link.l1.go = "Nathaniel_16";
		break;
		
		case "Nathaniel_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Pirates_townhall", "reload1_back", true);
			pchar.quest.longhappy_isla_bedroom.win_condition.l1 = "location";
			pchar.quest.longhappy_isla_bedroom.win_condition.l1.location = "Location_reserve_04";
			pchar.quest.longhappy_isla_bedroom.function = "LongHappy_IslaTesoroBedroom";
		break;
		
		case "Nathaniel_17":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "くそっ！お前の仲間は、あの野郎が女たちを撃たないように銃にまっすぐ突っ込んでいったんだ！";
			link.l1 = "奴は弾を食らった……待て、ネイサン……息してるぞ！まだ生きてる！くそっ、ジーノが必要だ！ "+sld.name+"「ねえ、あなた、元気？」";
			link.l1.go = "Nathaniel_18";
		break;
		
		case "Nathaniel_18":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_19";
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_7_1";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Nathaniel_18":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "大丈夫だ、チャールズ！俺が彼女の縄を解く。港で銃声が聞こえる――お前とネイサンはすぐに向かえ、さもないとバルバゾンが俺たちの船を全部沈めちまうぞ。\n時間を無駄にするな！";
			link.l1 = "俺がジーノを見つけてここに連れてくる、奴が助けてくれる…きっとそうだ！ "+sld.name+"「ねえ、ここにいて、彼のことを頼むぞ、二人とも。」";
			link.l1.go = "Nathaniel_19";
		break;
		
		case "Nathaniel_19":
			dialog.text = "チャールズ、急げ！どう決めるにせよ、今は時間が金にも勝る価値があるんだ！ジャックの船が岸に突破したら、 すべてが水の泡だぞ！\n";
			link.l1 = "ああ、知ってるぜ。血塗れの野郎め！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_OutOfBedroom");
		break;
		
		case "Nathaniel_20":
			dialog.text = "急げ、話してる暇はねえぞ！";
			link.l1 = "";
			link.l1.go = "Nathaniel_20_1";
		break;
		
		case "Nathaniel_20_1":
			DialogExit();
			npchar.dialog.currentnode = "Nathaniel_20";
		break;
		
		case "Nathaniel_21":
			dialog.text = "くそっ！許してくれ、チャールズ。俺たちは上の階に閉じ込められてたんだ、あの野郎どもが十人もいてよ……間に合わなかったのは残念だが、見たところお前は見事に切り抜けたみたいだな。";
			link.l1 = "楽だったとは言えねえが、くそっ、あの“親切な男”をぶっ殺すのは最高に愉快だったぜ！上陸の時間だ、ネイサン。俺たちの仲間がそこで待ってるぞ！\n";
			link.l1.go = "Nathaniel_22";
		break;
		
		case "Nathaniel_22":
			dialog.text = "ああ、君のインディアンの少年のところに行かないとな。ここを片付けてからシャープタウンへ向かおう。";
			link.l1 = "あんたの言う通りだ、俺はすぐ後ろにいるぜ。";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Terrax.Prisoner")) link.l1.go = "Nathaniel_23";
			else link.l1.go = "Nathaniel_25";
		break;
		
		case "Nathaniel_23":
			dialog.text = "ところで、マーカスを見つけたぜ！貨物室で縛られて気を失ってたんだ。";
			link.l1 = "生きてるのか？";
			link.l1.go = "Nathaniel_24";
		break;
		
		case "Nathaniel_24":
			dialog.text = "あいつはひどい状態だが、大丈夫だ。タイレックスは鋼よりもタフな野郎だから心配いらねえよ。 もうお前の船に移されて、サーベルを要求してきたぜ。";
			link.l1 = "やっといい知らせだな！よし、ここを片付けて戻ろうぜ。";
			link.l1.go = "Nathaniel_25";
		break;
		
		case "Nathaniel_25":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LongHappy_BarbExit", -1);
		break;
		
		// Даниэль Хоук
		case "Danielle":
			dialog.text = "やあ、チャールズ。ちょっと顔を見せてごらん――また一段と男前になったじゃないか、文句のつけようがないよ！十年前のネイサンみたいだ！さあ、中に入りなさい、 玄関先で立ってないで、みんなあんたを待ってたんだから！";
			link.l1 = "ありがとう、Dannie、会えて本当に嬉しいよ！あとで君とNathanのところに行くから、その時に話そう！";
			link.l1.go = "Danielle_1";
		break;
		
		case "Danielle_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "tables", "stay1", "LongHappy_DannyNorm", -1); 
		break;
		
		case "Danielle_2":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "チャールズ、座ってちょうだい——ナサンと私はあなたのことを本当に嬉しく思っているわ！マーカスとヤン、 それに私の夫があなたのために何か用意してくれたの——でも贈り物は後のお楽しみよ。まずはお祝いの言葉と幸せを願わせてね！あなたの愛しい人は本当に素晴らしい方だわ！ ねえ、まさかマルティニークで彼女に白いドレスを着せることに成功したんじゃないでしょうね？";
			link.l1 = "ありがとう、ダニー。ああ、ドレスの件は本当に面白いことになったよ――きっと俺たちの結婚は上流社会でたくさんのスキャンダラスな噂を呼んだだろうな。みんな礼儀正しく目をそらして、 何事もなかったふりをしていたよ。礼節ってやつさ――でも俺は噂なんて気にしない。彼女を愛してる、それが一番大事なんだ。";
			link.l1.go = "Danielle_3";
		break;
		
		case "Danielle_3":
			dialog.text = "まったくその通りだぜ！俺もな、剣とピストル二丁を帯に差して祭壇まで歩いたもんさ。 だがあれはポートロイヤルでのこと、まだあそこが立派な植民地になる前だった。あの頃は本当に楽しかったぜ、 ルヴァスールのトルトゥーガよりもな。誰も驚きゃしなかった……ええ。\nまあ、俺ばっかりしゃべっちまったな――さあ、客たちのところを回ってこいよ、みんなお前を待ってるんだ。ちょっと抱きしめさせてくれ！";
			link.l1 = "ああダニー、どうしてお前の頼みを断れるってんだ、ははっ！俺も女房も、 お前たちに会えてどれほど嬉しいか想像もつかねえよ！";
			link.l1.go = "Danielle_4";
		break;
		
		case "Danielle_4":
			DialogExit();
			npchar.dialog.currentnode = "Danielle_4_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Danielle_4_1":
			dialog.text = "チャールズ、君たちは素敵なカップルだな！";
			link.l1 = "ありがとう、Dannie…";
			link.l1.go = "Danielle_4";
		break;
		
		case "Danielle_5":
			dialog.text = "チャールズ、彼の言う通りだ……お前に選択肢はない。タイレックスや他の連中に手を下すなら、慈悲深きジャックの情けなんて信じちゃいない。 何をすべきか、分かっているだろう。";
			link.l1 = "";
			link.l1.go = "Danielle_6";
		break;
		
		case "Danielle_5_1":
			dialog.text = "あいつの言うことなんか聞くな！キングマンがそんな狂気じみたことを決めたなら、誰も容赦しねえぞ！";
			link.l1 = "";
			link.l1.go = "Danielle_6_1";
		break;
		
		case "Danielle_6":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.Dialog.currentnode = "LongHappy_39";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_6_1":
			DialogExit();
			sld = characterFromId("LH_Dussak");
			sld.dialog.currentnode = "Dussak_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_7_1":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "大丈夫だ、チャールズ！俺が彼女の縄を解く。港で大砲の音が聞こえる、あんたとネイサンはすぐに行くんだ、 さもないとバルバゾンに俺たちの船を樽の中のアヒルみたいに沈められちまうぞ。時間を無駄にしちゃいけねえ！\n";
			link.l1 = "俺がジーノを見つけてここに連れてくるぜ、あいつなら助けてくれる…いや、助けなきゃならねえ、くそっ！ "+sld.name+"「ねえ、ここにいてティチンギトゥの面倒を見ていて。」";
			link.l1.go = "Danielle_8_1";
		break;
		
		case "Danielle_7":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "ネイサン、やめろ！！";
			link.l1 = "彼はその瞬間を逃さず、ダニー、お前を守るために大砲へ駆け寄ったんだ… "+sld.name+"「ねえ、あなた、元気？」";
			link.l1.go = "Danielle_8";
		break;
		
		case "Danielle_8":
			DialogExit();
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			sld.Dialog.currentnode = "LongHappy_41";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_8_1":
			DialogExit();
			sld = characterFromId("Nathaniel");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Danielle_9":
			dialog.text = "ああ、チャールズ、彼は生きてるぞ！心臓はかすかに動いてるが、まだ生きてる！どうするんだ！？";
			link.l1 = "すぐにジーノが必要だ！俺が探してここに連れてくる、あいつなら助けてくれる…いや、助けなきゃならねえ！";
			link.l1.go = "Danielle_10";
		break;
		
		case "Danielle_10":
			dialog.text = "シャルル、時間がないわ！ジャックの船が岸に突破したら、すべてが無駄になるのよ！\n私の夫は……やるべきことをやったわ。今度はあなたの番よ。私は彼のそばに残るわ。\nあなたたち二人でジーノを探しに行って！";
			link.l1 = "ああ、知ってるぜ。あのクソ野郎、絶対に報いを受けさせてやる！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_OutOfBedroom");
		break;
		
		case "Danielle_11":
			dialog.text = "やっと来たな！みんな無事か？";
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim"))
			{
				link.l1 = "大丈夫だ、ダニー、心配するな。ジャックは死んだし、奴の船も海の底だ。ティチンギトゥはどうしてる？";
				link.l1.go = "Danielle_17";
			}
			else
			{
				link.l1 = "大丈夫だ、ダニー、心配するな。ジャックは死んだし、奴の船は海の底だ。ネイサンはどうしてる？";
				link.l1.go = "Danielle_12";
			}
		break;
		
		case "Danielle_12":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
			{
				dialog.text = "大丈夫だ！あんたのイタリア人医者は天才だぜ！ネイサンは二階で寝てるが、ジーノによれば何の心配もいらねえ。 ベッドで一、二週間、赤ワイン、それと……ええと、ジーノの言葉を借りれば「彼に好意的なご婦人の訪問」だとよ、ふふ……まあ、全体的に問題なしだ、また助けてくれたな、チャールズ、どうやって礼を言えばいいんだ？";
				link.l1 = "ナサニエルが私の妻とあなたを救ってくれたんだ。この恩は一生忘れないよ。彼が回復していると聞いて、 どれほど嬉しいか想像もつかないだろう。彼には休ませてやってくれ、あとでまた様子を見に来るよ。";
				link.l1.go = "Danielle_13";
			}
			else
			{
				dialog.text = "大丈夫だ、弾は貫通しただけだし、「センチュリオン」から来たうちの外科医もすぐ近くにいたんだ。 あの騒ぎから隠れてたんだよ。だからネイサンは助かるさ、二、三週間寝てれば問題ねえ！";
				link.l1 = "ダニー、あいつは俺の妻とお前を銃弾から守ってくれたんだ。この恩は一生忘れねえよ。あいつが回復してるって聞いて、 どれだけ嬉しいかお前には想像もつかないだろう。今は休ませてやってくれ、あとでまた様子を見に来るからな。";
				link.l1.go = "Danielle_14";
			}
		break;
		
		case "Danielle_13":
			dialog.text = "もちろんです！でも、もう行かなくてはなりません、夫のところへ行かないと……あなたの友人をお借りしてもよろしいですか？ネイサンが回復したら、私が直接アンティグアまで連れて行きます。 センチュリオン号は奇跡的に生き残りましたが、新しい乗組員を集める必要があるだけです。";
			link.l1 = "わかった、ダニー、ジーノとネイサンによろしく伝えてくれ。俺はもう行くぜ。";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_14":
			dialog.text = "もちろんだ、チャールズ、でも……悪い知らせがある。あんたの結婚式にいたあのイタリア人、グイネイリのことだが……酒場の一室で遺体が見つかったんだ。俺は……すまない、チャールズ。";
			link.l1 = "何だと！？ジーノ！？いやだ！どうして！？";
			link.l1.go = "Danielle_15";
		break;
		
		case "Danielle_15":
			dialog.text = "俺にはわからねえが、多分あの地下墓地を通って町を襲った野郎どもの一人だろうな。どうやら、 あそこに隠れて逃げる機会をうかがってたらしくて、そいつを見つけたんだ……";
			link.l1 = "ちくしょう！いや、信じられねえ……";
			link.l1.go = "Danielle_16";
		break;
		
		case "Danielle_16":
			pchar.questTemp.LongHappy.Jino_died = "true";
			dialog.text = "すまない、チャールズ。ひどい虐殺だったんだ、彼は戦う者じゃなかった……もしご希望なら、遺体をあなたの船に送るので、故郷に連れて帰ってきちんと埋葬してやってくれ。本当に申し訳ない……";
			link.l1 = "ありがとう、ダニー。遺体を船に運ぶよう命令を出してくれ。俺はもう行かなくちゃ……少し考える時間が必要なんだ。それと、ネイサンによろしく伝えてくれ。";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_17":
			if (CheckAttribute(pchar, "questTemp.LongHappy.Jino_alive"))
			{
				dialog.text = "大丈夫だ！お前のイタリア人医者は天才だぜ！上の部屋で寝てるし、ジーノが世話してる。医者が 「一週間か二週間もすれば元気になる」って言ってたぞ。";
				link.l1 = "素晴らしい知らせだ！でも、まだ彼に会いに行けないのか？";
				link.l1.go = "Danielle_18";
			}
			else
			{
				dialog.text = "すまない、チャールズ。センチュリオン号の船医を見つけたが、何もできなかった……お前の友は数時間前に亡くなったんだ。";
				link.l1 = "ティチンギトゥ！？いやだ！信じられねえ！！！";
				link.l1.go = "Danielle_19";
			}
		break;
		
		case "Danielle_18":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "いや、イタリア人は彼を邪魔するなときつく禁じたんだ。休ませてやれってな。 それにジーノもいろいろ心配した後なんだから休むべきだろう。俺も言ったんだ "+sld.name+" すべてがうまくいくとわかったとき、俺たちは散歩に出かけようとしたんだ\nそれからもう一つ……お前の友達が、俺を銃弾からかばってくれたんだ。どう感謝すればいいかわからない。 これからは彼も俺たちの家族の一員だと伝えてくれ。そしてお前は――また俺たちを救ってくれたな、チャールズ！";
			link.l1 = "終わりよければすべてよしだ、ダニー。ナサンのところへ行け、あいつはお前を待ってたぜ。俺はここでちょっと休んで、 自分の\n "+sld.name+".";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_19":
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer")) sld = characterFromId("Helena");
			else sld = characterFromId("Mary");
			dialog.text = "すまねえ、俺はできることは全部やったんだが、そして "+sld.name+"、俺たちもだ。あいつは俺たちをその弾から守ってくれたんだ。そのことは絶対に忘れない、信じてくれよ。";
			link.l1 = "…昔、彼は私のためなら死ぬと言っていた…まさか自分の命を私たち全員のために捧げることになるとは思っていなかったのでしょう…そして今や彼は英雄、私は彼をそれ以外のものとしては決して記憶しません…どこに\n "+sld.name+"「……彼女は無事か？」";
			link.l1.go = "Danielle_20";
		break;
		
		case "Danielle_20":
			dialog.text = "そうとは言えねえな……いや、体は大丈夫だ。だが……わかるだろ……彼女は気分転換に散歩に出たって言ってた。たぶんお前が停泊してるのを見かけて、すぐ戻ってくるさ。";
			link.l1 = "呪われろ、ジャック・バルバゾン……あいつはもっと早く殺しておくべきだったぜ！";
			link.l1.go = "Danielle_21";
		break;
		
		case "Danielle_21":
			dialog.text = "待て……まだ終わりじゃねえ。あのイタリア野郎、グイネイリだろ？あの物静かな若者さ。奴は……遺体が酒場で見つかったんだ……詳しくは知らねえが、多分、カタコンベを抜けて町を襲ったあのクソ野郎どもの仕業だろう。どうやら、 あいつらはそこで身を潜めて、逃げる機会をうかがっていたらしいんだが、グイネイリを見つけちまったんだ……\n";
			link.l1 = "「ジーノまでか！？今日は本当に泣きっ面に蜂だな……」";
			link.l1.go = "Danielle_22";
		break;
		
		case "Danielle_22":
			pchar.questTemp.LongHappy.Tichingitu_died = "true";
			dialog.text = "すまない、チャールズ……もしご希望なら、ご遺体をあなたの船に送り、部下たちを故郷へ連れて帰り、しかるべき形で埋葬いたします。 本当に申し訳ありません……";
			link.l1 = "ありがとう、ダニー。やってくれ……俺は行く……考えなきゃ……";
			link.l1.go = "Danielle_23";
		break;
		
		case "Danielle_23":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
			sld = characterFromId("Svenson");
			sld.dialog.currentnode = "Svenson_26";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		// Додсон
		case "Dodson":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "シャルル、お前の結婚でどれだけ多くの娘たちの心を傷つけたか想像できるか？\nそうさ、諸島中の女の子の半分はお前の結婚を嘆いたに違いねえ、はは！";
			link.l1 = "どうしようもねえな――俺は一人だけ欲しかったんだが、手に入れちまった。でも女たちが落ち込むにはまだ早いぜ、 だってまだお前がいるからな、スティーブン。";
			link.l1.go = "Dodson_1";
		break;
		
		case "Dodson_1":
			dialog.text = "その通りだぜ！ここを片付けたら、すぐにあいつらを始末してやる、くそっ！さあ、チャールズ、 あんたの幸運と家庭に乾杯しようぜ。\nまあ、いわゆる末永くお幸せにな！";
			link.l1 = "ありがとう、友よ！";
			link.l1.go = "Dodson_2";
		break;
		
		case "Dodson_2":
			DialogExit();
			npchar.dialog.currentnode = "Dodson_2_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Dodson_2_1":
			dialog.text = "「幸せな家庭生活に、乾杯だ、ははっ！」";
			link.l1 = "乾杯！";
			link.l1.go = "Dodson_2";
		break;
		
		// Венсан
		case "Vensan":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "チャールズ、お前の結婚でどれだけ多くの娘たちの心を傷つけたか想像できるか？\nそうさ、諸島中の女の子の半分はお前の結婚を嘆いたに違いないぜ、はは！";
			link.l1 = "俺にできることは――一人だけでよかったんだが、手に入れちまった。\nだが、女たちが落ち込むのはまだ早いぜ、だってまだお前がいるからな、ベルナール。";
			link.l1.go = "Vensan_1";
		break;
		
		case "Vensan_1":
			dialog.text = "そうだぜ！ここを片付けたら、すぐにあいつらを始末してやる、くそっ！さあ、チャールズ、 運と家庭に乾杯しようじゃねえか。\nってことで、末永くお幸せにな！";
			link.l1 = "めでたしめでたし！";
			link.l1.go = "Vensan_2";
		break;
		
		case "Vensan_2":
			DialogExit();
			npchar.dialog.currentnode = "Vensan_2_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Vensan_2_1":
			dialog.text = "幸せな家庭生活のために、ははっ！";
			link.l1 = "「最高の乾杯だ！」";
			link.l1.go = "Vensan_2";
		break;
		
		case "Vensan_3":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "はは、チャールズ、お前もついに結婚してつまらねえ男になっちまったか、昔のナサンみてえにな！女遊びも何もかも、 もう過去の話だな？立派な家庭持ちってわけか！";
			link.l1 = "待ってろ、バーナード！俺の女房は、家の廃墟の窓の下で退屈して座ってるような奴じゃねえ！変わるのは、 ここからキュラソーまでの娼婦どもの財布の膨らみだけだぜ！";
			link.l1.go = "Vensan_4";
		break;
		
		case "Vensan_4":
			dialog.text = "大した損じゃねえよ、俺はそう思うぜ！ニッケルの袋より金貨一枚の方がマシだ。飲もうぜ！お前と奥さんに乾杯だ！ 金はしっかり守って、幸せになれよ！";
			link.l1 = "ありがとう、Bernard。おお、これは本当に強いラム酒だな。ふう！";
			link.l1.go = "Vensan_5";
		break;
		
		case "Vensan_5":
			DialogExit();
			npchar.dialog.currentnode = "Vensan_5_1";
			if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Vensan_5_1":
			dialog.text = "「お前の花嫁に――いや、もう奥さんだな！」";
			link.l1 = "ありがとう！";
			link.l1.go = "Vensan_5";
		break;
		
		case "Vensan_6":
			dialog.text = "ちょうどいい時に来てくれたな、チャールズ、ありがとう！";
			link.l1 = "ここで何を楽しんでるんだ？もう港で船に積み込みしてると思ってたぜ。";
			link.l1.go = "Vensan_7";
		break;
		
		case "Vensan_7":
			dialog.text = "マーカスは俺を岸で防衛の指揮に残していったんだ。人手が足りねえし、港の連中は火薬が必要だ。 ちょっと寄って樽を二つほど持っていこうと思ったら……そこにこいつらのチンピラが現れやがった。はっ、隠れてたんだろうな、多分嵐が過ぎるのを待つか、 誰かを襲うつもりだったんだろう。しかも俺はまだホークのラムで酔いが残ってるし、 お前がいなきゃ今ごろ生きてたかどうかも分からねえよ。";
			link.l1 = "いつでも歓迎だ。よし、バーナード、お前は町の警備を頼むぜ。俺は行くとする。気をつけろよ！";
			link.l1.go = "Vensan_8";
		break;
		
		case "Vensan_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			pchar.questTemp.LongHappy.Vensan_alive = "true";
		break;

		// Джино
		case "Jino":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "船長、このめでたい日に心からお祝い申し上げます。あなたと最愛の方が幸せで、お互いを大切にされますように！";
			link.l1 = "ありがとう、ジーノ。来てくれて嬉しいよ！この土地の……雰囲気が気にならなければいいんだが？";
			link.l1.go = "Jino_1";
		break;
		
		case "Jino_1":
			dialog.text = "これは……とても勉強になる旅だわ。正直に言うと、アンティグアを長い間出たことがなかったし、 この社会ではなかなか居心地が良いとは言えないの。でも、あなたはいつも人の気持ちを理解するのが上手だったから、 私はあなたを信じて落ち着いていようと思うわ。";
			link.l1 = "もっと強い酒でも飲んだらどうだ？くつろいで誰かと話してみろよ？";
			link.l1.go = "Jino_2";
		break;
		
		case "Jino_2":
			dialog.text = "ありがとうございます、船長、もう水で薄めたワインは十分です。アルコールは肝臓、 そして場合によっては心臓にもあまり良くないと警告しておきます。\n会話についてですが、あちらの旦那とチリク・サナンゴの治癒効果について話そうとしました。 これはマナカとも呼ばれています。メインの先住民たちはこれを…";
			link.l1 = "当ててみようか――あの旦那は議論に耐えられなかったんだろう？ジーノ、頼むから今日だけでいい、 あそこのカウンターでヤンが注いでるラムを試してみてくれ。その材料を全部当てられたら、 あそこにいるネイサン・ホークもきっと感心するぜ。きっと彼も君と一緒に飲みたがるし、 カウンターのスヴェンソンも同じだ。二人とも教養ある人間を尊敬してるからな。";
			link.l1.go = "Jino_3";
		break;
		
		case "Jino_3":
			DialogExit();
			npchar.dialog.currentnode = "Jino_3_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (CheckAttribute(pchar, "questTemp.LongHappy.HambitOfficer"))
				{
					sld = characterFromId(pchar.questTemp.LongHappy.HambitOfficer);
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Baker") != -1)
					{
						sld = characterFromId("Baker");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						if (GetCharacterIndex("Tichingitu") != -1)
						{
							sld = characterFromId("Tichingitu");
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", -1, 0);
						}
						else
						{
							sld = characterFromId("Mary");
							sld.dialog.currentnode = "LongHappy_57";
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", -1, 0);
						}
					}
				}
			}
			else if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
		break;
		
		case "Jino_3_1":
			dialog.text = "お前の健康に、そしてお前の魅力的な奥方の健康にも乾杯だ！";
			link.l1 = "ありがとう、友よ！";
			link.l1.go = "Jino_3";
		break;
		
		case "Jino_4":
			dialog.text = "船長、あなただったんですね、神に感謝します！あの仮面の連中、俺は奴らを見てここに隠れたんだ、 そしたら奴らがドアを壊そうとしたんだ…";
			link.l1 = "大丈夫だ、ジーノ、もう誰もお前を傷つけやしない。\nお前を見つけられて本当に運が良かった、俺はお前の助けが必要なんだ。\n友人が怪我をしている――撃たれて、大量に血を失ってる。\n急がなきゃならねえ！";
			link.l1.go = "Jino_5";
		break;
		
		case "Jino_5":
			dialog.text = "撃たれて…血が…でも大丈夫だ、船長。ここに来る途中で、万一に備えて医療用の箱と道具一式を持ってきたんだ。 そいつのところまで案内してくれ、何とかできるか見てみるぜ。\nそれと…あの仮面の連中、もしかしたらどこか別の場所に隠れてるかもしれねえな？";
			link.l1 = "きっとあれが最後だったはずだ。ジーノ、港で戦闘が起きてるから、俺はすぐに行かなくちゃならねえ。 お前は自分で総督邸まで行くんだ、すぐ近くだからな。角を曲がったところの大きな屋敷だ――見逃すことはねえよ。怖がるな、通りには俺たちの仲間がたくさんいるし、急いでくれ、頼むぞ！";
			link.l1.go = "Jino_6";
		break;
		
		case "Jino_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 7.0);
			LocatorReloadEnterDisable("Pirates_tavern", "reload1_back", false);
			pchar.questTemp.LongHappy.Jino_alive = "true";
			AddQuestRecord("LongHappy", "18");
			if (CheckAttribute(pchar, "questTemp.LongHappy.Tichingitu_Victim")) sld = characterFromId("Tichingitu");
			else sld = characterFromId("Nathaniel");
			sTemp = sld.name;
			AddQuestUserData("LongHappy", "sName1", sTemp);
		break;
		
		case "Jino_7":
			dialog.text = "船長、このめでたい日に心からあなたとあなたの愛しい方にお祝いを申し上げます！\nどうかお幸せに、お互いを大切にしてください。";
			link.l1 = "ありがとう、ジーノ。来てくれて嬉しいよ！道中は順調だったか？";
			link.l1.go = "Jino_8";
		break;
		
		case "Jino_8":
			dialog.text = "すべて順調です、船長、ご心配ありがとうございます。正直に申しますと、私は長い間アンティグアを離れておらず、 上流階級の中では……あまり居心地が良くありません。しかし、今回来た理由では仕方ありませんでした。ところで、 式のサービスは素晴らしかったです、お二人とも本当におめでとうございます！花嫁のその装い、とても魅力的ですね――これが新しい流行でしょうか？どうやら私は世間から遅れてしまったようですが、気に入りました、本当に。";
			link.l1 = "ファッションか……まあ、ある意味そうだな。いや、もうすぐそうなるだろう。よし、楽しんでこい、ジーノ。 もし貴族どもの話し相手が退屈になったら港に来い。\n船員全員が酒場にいるぜ。みんなお前に会えるのを楽しみにしてるぞ。";
			link.l1.go = "Guests_block";
		break;
		
		case "Jino_9":
			dialog.text = "船長、改めておめでとうございます。そして美しい奥様にも！お二人が末永く幸せに過ごされますように！";
			link.l1 = "ありがとう、ジーノ。来てくれて嬉しいよ！この土地の……雰囲気が気にならなければいいんだが？";
			link.l1.go = "Jino_10";
		break;
		
		case "Jino_10":
			dialog.text = "この社会は俺には居心地がいいとは言えねえ。でも、お前はいつも人を見る目があったからな。お前を信じている以上、 俺も落ち着いていようと努めるぜ。";
			link.l1 = "もっと強い酒でも飲みたいのか？\nくつろいで、誰かと話してみたらどうだ？";
			link.l1.go = "Jino_11";
		break;
		
		case "Jino_11":
			dialog.text = "ありがとうございます、船長、もう水で薄めたワインは十分です。アルコールは肝臓、 そして場合によっては心臓にもあまり良くないと警告しておきます。\n会話についてですが、あの旦那とチリク・サナンゴの治癒効果について話そうとしました。 これはマナカとも呼ばれています。メインの先住民たちはこれを…";
			link.l1 = "当ててみようか――あの旦那は議論に耐えられなかったんだろう？ジーノ、頼むから今日だけでいい、 あそこのカウンターでヤンが注いでるラムを試してみてくれ。その材料を全部当てられたら、 あそこにいるネイサン・ホークもきっと感心するぜ。きっと君と一緒にいるのを喜ぶだろうし、 カウンターのスヴェンソンも同じさ。二人とも教養ある人間を尊敬してるからな。";
			link.l1.go = "Jino_3";
		break;
		
		// Лонгвэй
		case "Longway":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "「見知らぬ土地でひとりきり、異邦人のように感じながら、この晴れやかな祭の日にはなおさら家族が恋しくなる」";
			link.l1 = "ロングウェイ、お前が言葉の達人だったなんて思いもしなかったぜ！";
			link.l1.go = "Longway_1";
		break;
		
		case "Longway_1":
			dialog.text = "すみません、船長、最近いろいろ考えていました。これは王維という詩人の言葉です――私の故郷で昔、唐王朝が支配していた時代に生きた人です。";
			link.l1 = "この言葉は本当に美しいな。いつかまた故郷に帰れるといいな……";
			link.l1.go = "Longway_2";
		break;
		
		case "Longway_2":
			dialog.text = "「謎めいた石板のアーチの下をくぐろうとしても、その先にウーリンの谷がある道を見つけることは絶対にできない、 と保証し知ることはできるのだろうか？」\nいいえ、船長、あなたも知っているはずだ――ロングウェイはもう故郷には戻らない。今や、ここが私の家であり、今日はここで大きな祝い事がある！ あなたと美しい花嫁に心からの祝福を送るよ！あなた方の幸せが、星のダイヤモンドでちりばめられ、 蓮の真珠に挟まれた長江のように長く続きますように。";
			link.l1 = "ありがとう、古き友よ。お前の言葉は王維にも劣らず美しいな。";
			link.l1.go = "Longway_3";
		break;
		
		case "Longway_3":
			dialog.text = "飲もうぜ、船長！このラムは悲しみを吹き飛ばし、喜びを蘇らせるんだ。まるでマオタイみたいにな！";
			link.l1 = "ロングウェイ、君の健康を祝して！";
			link.l1.go = "Longway_4";
		break;
		
		case "Longway_4":
			DialogExit();
			npchar.dialog.currentnode = "Longway_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Longway_4_1":
			dialog.text = "素晴らしい結婚式だな、船長！";
			link.l1 = "飲んで楽しめ！";
			link.l1.go = "Longway_4";
		break;
		
		// Книппель
		case "Knippel":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				dialog.text = "鎖弾を撃て！みんながお前を祝福してるぜ！弾はどうだった？";
				link.l1 = "すべて順調だ、チャーリー！今や俺は正式に結婚して立派な身分になったし、俺の副官は今やモンペール夫人だ。";
			}
			else
			{
				dialog.text = "チェーンショットをくらったみてえなもんだ、なんて騒ぎだぜ、船長！ほとんど全てのバラナイト（兄弟団の男爵） がここに集まってやがる！スペインの敬虔な連中は、地獄ってのはこんな場所だと想像してるんじゃねえか！？ それにラム酒、こいつは格別だ、俺の樽にチェーンショットぶち込まれた気分だぜ！";
				link.l1 = "ああ、ここの連中はあまり法を守る方じゃねえが、俺たちだって聖人じゃねえだろ、チャーリー。それに、 この連中一人ひとりが俺にはそれぞれ大切なんだ。";
			}
			link.l1.go = "Knippel_1";
		break;
		
		case "Knippel_1":
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				dialog.text = "素晴らしいぜ、鎖弾がお尻に当たったみたいだ！船長、いや、この宴はあんたのためのものだ、ええと、俺は…おめでとう、いや…その…幸せと…ええ、俺はこういう挨拶は苦手なんだ。でもな、俺たちみんな、あんたたち二人を心から愛してるし、 地獄まででもついていくぜ、船長！";
				link.l1 = "「ありがとう、古い友よ。」";
			}
			else
			{
				dialog.text = "待てよ、いや…何言ってんだ俺、鎖弾がケツに当たったみてえなこと言っちまった！？船長、つまり今日はあんたのための日なんだよ、 えっと…おめでとう…それから…幸せを祈って…それと、悪いな船長、ちょっと酔いすぎてうまくしゃべれねえ、鎖弾が首に当たったみてえだ、 しばらくシラフじゃなかったからな、ははは！";
				link.l1 = "ははっ！大丈夫だ…ありがとう、古い友よ。";
			}
			link.l1.go = "Knippel_2";
		break;
		
		case "Knippel_2":
			Log_Info("You have got gems");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "jewelry4", 20);
			dialog.text = "あっ！それと、船長、これを受け取ってくれ。あんたと奥方のためにな。雨の日のために取っておいた石だ……金には困ってないってのは分かってるが、これも無駄にはならねえだろう？";
			link.l1 = "チャーリー、お前は本当に気前のいい奴だな。このエメラルドはモンペール夫人の家宝のイヤリングにぴったり映えるぜ！ ";
			link.l1.go = "Knippel_3";
		break;
		
		case "Knippel_3":
			dialog.text = "よし、それじゃあ乾杯だ、チェーンショットを俺の……ん？まあいい、幸せになれよ、お前もその美人もな、船長！";
			link.l1 = "やるぜ、チャーリー！";
			link.l1.go = "Knippel_4";
		break;
		
		case "Knippel_4":
			DialogExit();
			npchar.dialog.currentnode = "Knippel_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Knippel_4_1":
			dialog.text = "素晴らしい結婚式だな、船長！";
			link.l1 = "飲んで楽しめ！";
			link.l1.go = "Knippel_4";
		break;
		
		// Тонзаг
		case "Tonzag":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "俺は思いもしなかったぜ、船長、あんたが結婚するなんてよ。普通、俺たちが選んだ道は孤独な人生、 そして寂しい墓場に直行するもんだ。俺の記憶じゃ、その運命から逃れたのはあんたが初めてだぜ。 これは一杯余分に祝杯をあげる価値があるよな？";
			link.l1 = "これで終わりだ、相棒！本当に、この人生の一幕が終わってくれて嬉しいぜ。乾杯！";
			link.l1.go = "Tonzag_1";
		break;
		
		case "Tonzag_1":
			dialog.text = "お前たちの末永く幸せな人生に乾杯だ！くそ、あんたらを見てると、俺もかつては結婚してたことを思い出すぜ。";
			link.l1 = "お前が？結婚だと？そりゃ面白い話だな！でも、何があったんだ？";
			link.l1.go = "Tonzag_2";
		break;
		
		case "Tonzag_2":
			dialog.text = "何だ、俺がいつも火薬と血の臭いをさせた年寄りの片目野郎だったと思ってるのか、船長？だが違うぜ。 トンザグ夫人はな……ああ、きっと俺を愛してくれたんだろう。だがな、その後、嫌な出来事があったんだ。トンザグ夫妻が死んじまって、 傷だらけのガストン禿だけが生き残ったってわけさ。";
			link.l1 = "すまない、エルキュール、知らなかったんだ……";
			link.l1.go = "Tonzag_3";
		break;
		
		case "Tonzag_3":
			dialog.text = "忘れろよ、船長、その話はずっと昔のことだ。だが今、お前を見てると、 俺の物語もまだハッピーエンドになるかもしれねえって思えてくるぜ。だから、それに乾杯しようじゃねえか！";
			link.l1 = "そうしようぜ、相棒。お前な、俺はお前に初めて会った日から、ずっと自分の親父みたいに思ってきたんだ。だから、 いつか曾じいさんになるチャンスもあるかもな。まあ、とにかく乾杯だ！他のみんなも見てこなきゃいけねえから、 また後で話そうぜ。\n";
			link.l1.go = "Tonzag_4";
		break;
		
		case "Tonzag_4":
			DialogExit();
			npchar.dialog.currentnode = "Tonzag_4_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Baker") != -1)
				{
					sld = characterFromId("Baker");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					if (GetCharacterIndex("Tichingitu") != -1)
					{
						sld = characterFromId("Tichingitu");
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
					else
					{
						sld = characterFromId("Mary");
						sld.dialog.currentnode = "LongHappy_57";
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Tonzag_4_1":
			dialog.text = "盛大な祝宴だぜ、船長！";
			link.l1 = "飲んで楽しめ！";
			link.l1.go = "Tonzag_4";
		break;
		
		// Бейкер
		case "Baker":
			pchar.questTemp.LongHappy.Count = sti(pchar.questTemp.LongHappy.Count)+1;
			dialog.text = "おう、うちの船長が来たぜ！おめでとう、あんたと奥さんは本当にお似合いの夫婦だ！末永く幸せに暮らせよ！";
			link.l1 = "ありがとうございます、Raymond。";
			link.l1.go = "Baker_1";
		break;
		
		case "Baker_1":
			sTemp = "Sharptown";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP")) sTemp = "Sent Pierre";
			dialog.text = "どうやら自分の結婚式には酔いが足りねえみたいだな、船長。どうだ、ちょっと飲んでみるか？ 酒場で上等なシェリーを手に入れてきたぜ。地元のラムと混ぜりゃ最高だ！";
			link.l1 = "俺もそうしたいが、ここで誰かが見張ってないといけねえんだ。さもないと、\n "+sTemp+" 朝になれば、酒場だけじゃなくて他のものも恋しくなるだろうな。";
			link.l1.go = "Baker_2";
		break;
		
		case "Baker_2":
			DialogExit();
			npchar.dialog.currentnode = "Baker_2_1";
			if (CheckAttribute(pchar, "questTemp.LongHappy.MarrySP"))
			{
				if (GetCharacterIndex("Tichingitu") != -1)
				{
					sld = characterFromId("Tichingitu");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else
				{
					sld = characterFromId("Mary");
					sld.dialog.currentnode = "LongHappy_57";
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
			}
			else 
			{
				if (!CheckAttribute(pchar, "questTemp.LongHappy.Continue") && sti(pchar.questTemp.LongHappy.Count) >= sti(pchar.questTemp.LongHappy.CountNeed)) LongHappy_IslaTesoroToVine();
			}
		break;
		
		case "Baker_2_1":
			dialog.text = "うまい飯とうまいラムだな、船長！お前と若い奥さんに乾杯だぜ！";
			link.l1 = "ありがとう！";
			link.l1.go = "Baker_2";
		break;
		
		// Алексус
		case "Alexus":
			dialog.text = "若いの、何しに押し入ってきたんだ？船大工はもう閉まってるのが分からねえのか？明日また来な。";
			link.l1 = "旦那、申し訳ありませんが、ちょっと地下牢を通らせていただきます。結婚式のための物資がありまして、 酒場の酒もほとんど切れかけているんです。";
			link.l1.go = "Alexus_1";
		break;
		
		case "Alexus_1":
			dialog.text = "おお、シャルル・ド・モールとネイサン・ホークご本人たちじゃねえか！誰かの結婚式を祝いに来たんだろ？よし、 飲みに行ってこい。若いもんは楽しむべきだ――それがいつの時代も掟だぜ。だが帰り道で瓶をガチャガチャ鳴らすんじゃねえぞ――これから寝るんだからな！";
			link.l1 = "ありがとうございます、旦那、俺たちは一番穏やかな川のように静かにしますぜ。";
			link.l1.go = "Alexus_2";
		break;
		
		case "Alexus_2":
			DialogExit();
			npchar.dialog.currentnode = "Alexus_2_1";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
			pchar.GenQuestBox.Bermudes_Dungeon = true;
			pchar.GenQuestBox.Bermudes_Dungeon.box3.items.potionwine = 100;
			pchar.quest.longhappy_isla_box.win_condition.l1 = "locator";
			pchar.quest.longhappy_isla_box.win_condition.l1.location = "Bermudes_Dungeon";
			pchar.quest.longhappy_isla_box.win_condition.l1.locator_group = "box";
			pchar.quest.longhappy_isla_box.win_condition.l1.locator = "box3";
			pchar.quest.longhappy_isla_box.function = "LongHappy_IslaTesoroDungeon";
		break;
		
		case "Alexus_2_1":
			dialog.text = "さあ、ぼーっと突っ立ってないで、行けよ！さて、船長、全部に満足してるか？";
			link.l1 = "...";
			link.l1.go = "Alexus_2_2";
		break;
		
		case "Alexus_2_2":
			DialogExit();
			npchar.dialog.currentnode = "Alexus_2_1";
		break;
		
		// пиратус в подземелье
		case "DungeonPirate":
			dialog.text = "なんだと！？ジャックは「ここには誰も来ない」って言ってたじゃねえか！ユーゴ、戻って他の連中を呼んでこい、 道を開けるぞ。やっちまえ、野郎ども！\n";
			link.l1 = "「くそっ！」";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BandosInDungeonFight");
		break;
		
		// киллеры
		case "killer":
			dialog.text = "野郎ども、宝箱のことは忘れろ、客人が来たぞ！";
			link.l1 = "ジャックマンと一緒にてめえみたいなクズは全員くたばったと思ってたぜ。いいだろう、ケリをつけようじゃねえか！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_ResidenceFight");
		break;
		
		case "killer_1":
			dialog.text = "くそっ……見つかったぜ！警報だ！";
			link.l1 = "どけ、このクソ野郎！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_TavernKillerFight");
		break;
		
		// Ангерран
		case "Shivo":
			dialog.text = "モール旦那、こんばんは、いや、もう朝に近いかな？どうぞ、中へ、お掛けください。";
			link.l1 = "アンジェラン・ド・シェヴィウス！お前に会っても全然驚かねえぜ！女相手にしか戦えねえ、ちっぽけな野郎が！ まさかあいつらも縛り上げたのか！？今度こそ、マルティニークの決闘で始めたことを終わらせてやるぜ！";
			link.l1.go = "Shivo_1";
		break;
		
		case "Shivo_1":
			dialog.text = "落ち着け、若造、この銃が見えるか？二連銃だぜ。剣の腕は大したことねえが、射撃なら自信があるんだ――剣を下ろせよ。じゃねえと、綺麗な女たちに会えなくなるぜ、保証してやるよ。";
			link.l1 = "くそ野郎め……畜生が。";
			link.l1.go = "Shivo_2";
		break;
		
		case "Shivo_2":
			dialog.text = "そしてお前もだ、海賊の旦那、そこの武器を置け、そうだ、そのままだ。さて――座れ、ワインを注いでいいぞ――あそこ、テーブルの上にある。\nバルバゾンの旦那が、お前の仲間の海賊男爵どもの船をぶっ壊し終わるまで、少し待つことになるな。そしたら、 お前と俺でどうやって……ふむ、不一致を片付けるか決めようじゃねえか。";
			link.l1 = "争いを解決するって？どうやってだ？決闘でもしたいのか？";
			link.l1.go = "Shivo_3";
		break;
		
		case "Shivo_3":
			dialog.text = "ふざけるなよ、シャルル。お前とボト夫人のおかげで、俺はずいぶんと面倒をかけられたんだ。 その借りはきっちり返させてもらうぜ。もっとも、あいつの方がよっぽど厄介だったがな……だがな、お前と威圧的な海賊旦那が大人しくしていれば、名誉にかけて約束しよう――お前たちの妻は生かしておいてやる。大陸のスペイン領の植民地じゃ、そういう奴隷も価値があるらしい。非公式でもな。 だが、生きていられるだけマシだろう？";
			link.l1 = "アンジェラン、お前は臆病者で、ろくでなしで……くそっ、どの言語にもお前にふさわしい言葉がまだ見つからねえ！";
			link.l1.go = "Shivo_4";
		break;
		
		case "Shivo_4":
			dialog.text = "分かってるだろう、選択肢なんてねえんだ。せめてもの約束だが、すぐに終わらせてやるよ。だからな、 もしこの女たちのことを気にかけてるなら、大人しくして彼女たちの命を助けてやれ、自分の運命も少しは楽になるぜ。 ああ、それと——面倒じゃなきゃ扉に鍵をかけといてくれ。ありがとな。";
			link.l1 = "";
			link.l1.go = "Shivo_5";
		break;
		
		case "Shivo_5":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Shivo_6":
			dialog.text = "なんと勇ましいご婦人方だ。しかし、やはり慎重にしていただきたい。私は女性を殺すのは昔から好きじゃないんだ。";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomShot");
		break;
		
		case "Shivo_7":
			dialog.text = "くそっ……";
			link.l1 = "死ね、この野郎！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomFight");
		break;
		
		// Дюссак
		case "Dussak":
			dialog.text = "シャルル・ド・モール船長、ホーク男爵――これは嬉しい驚きだ！自己紹介させてくれ――私の名はモーリッツ・ドゥサックだ。";
			link.l1 = "どけ、この野郎！俺の女房はどこだ！？";
			link.l1.go = "Dussak_1";
		break;
		
		case "Dussak_1":
			dialog.text = "落ち着け、旦那たち！この銃が見えるか？二連銃だぜ。俺がそう呼ばれるのには理由がある――サーベルも好きだが、撃つ腕も確かなんだ、信じな。剣を下ろせ、さもねえと指を何本か失うことになるぜ！";
			link.l1 = "豚みてえにお前をぶっ殺してやるぜ、クズが……";
			link.l1.go = "Dussak_2";
		break;
		
		case "Dussak_2":
			dialog.text = "だが、お前はすでに未亡人になるんだぜ。それが望みじゃねえのか？だったら落ち着いて武器を下ろせ。\nホーク男爵、頼む、扉に鍵をかけてくれ。俺たちはここで静かにして、しばらく待つんだ。 外の港じゃジャック・バルバゾンがバッカニアの頭目どもを片付けてくれるさ。";
			link.l1 = "「それで、次はどうするんだ？抱き合って一緒に夕日に向かって駆け出すのか？」";
			link.l1.go = "Dussak_3";
		break;
		
		case "Dussak_3":
			dialog.text = "そうは思わねえな。お前を捕まえれば、ジャックが俺に金貨を山ほどくれるだろう。運が良けりゃ、 俺も男爵になれるかもな。女たちのことは、もしかしたら逃がしてやるかもしれねえが、お前は……残念だがな……。運が良けりゃ、俺自身でお前を殺す権利をもらうつもりだぜ、船長。お前は有名な剣士だ――腕試しにはうってつけだ。俺も自分を達人だと思ってるんだぜ。";
			link.l1 = "夜に家へ忍び込んで、寝ぼけている女を縛り上げる達人だと？お前は虫けらだ、それも哀れな虫けらだぜ！";
			link.l1.go = "Dussak_4";
		break;
		
		case "Dussak_4":
			DialogExit();
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "Danielle_5";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "Dussak_5":
			dialog.text = "聞けよ、奥さん、俺は女を殺したことなんかねえんだ、だから無理にやらせるなよ、いいか？ 船長も旦那もお前のせいでビビってるじゃねえか……くそっ！";
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomShot");
		break;
		
		case "Dussak_6":
			dialog.text = "「メルド…」";
			link.l1 = "死ね、この野郎！";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LongHappy_BedroomFight");
		break;
		
		// Барбазон
		case "Barbazon_boarding":
			dialog.text = "くそったれフランス野郎、剣も弾もなかったのか！？";
			link.l1 = "なあ、ジャック、俺はお前のために両方持ってきたぜ。正直言って、ジャックマンとの企みを知ったとき、 お前を生かしておいたのを少し後悔したくらいだ。だが今、それを正すつもりだ。";
			link.l1.go = "Barbazon_boarding_1";
		break;
		
		case "Barbazon_boarding_1":
			dialog.text = "自分の手下に囲まれてる時だけ威張ってるのか？それなら状況を変えてやるぜ！男爵どもは後回しだが、 お前はここから生きては帰れねえぞ、このクソネズミが！";
			link.l1 = "「予想通り…」";
			link.l1.go = "Barbazon_boarding_2";
		break;
		
		case "Barbazon_boarding_2":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			AddItems(npchar, "potion2", 1);
			QuestAboardCabinDialogFree();
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "LongHappy_BarbAfterFight");
			AddDialogExitQuest("MainHeroFightModeOn");
			// подкрепление
			sld = GetCharacter(NPC_GenerateCharacter("LH_BarbCabinHelper", "citiz_57", "man", "man", 35, PIRATE, 0, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 70, 70, "blade_21", "pistol4", "bullet", 300);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			AddItems(sld, "potion2", 2);
		break;
		
		// официантка
		case "waitress":
			dialog.text = "船長、助けて、この野蛮人が私をさらったんです！\nわ、私は家に帰らなきゃ――叔父がきっと町中をひっくり返して探しているはずです！";
			link.l1 = "落ち着けよ、美人さん、全部うまくいくぜ。ちょっとどいてくれ、お前の“野蛮人”と話があるんだ。";
			link.l1.go = "waitress_1a";
		break;
		
		case "waitress_1a":
			DialogExit();
			sld = characterFromId("Tichingitu");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "waitress_1":
			dialog.text = "ありがとうございます、船長！助けてくれて！今朝この浜辺で目覚めたとき、 まさかこの野蛮人と結婚することになるなんて…信じられません、彼は…";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 94)
			{
				link.l1 = "ああ、朝は夜の希望の結晶を打ち砕く厳しい槌だな。わかっている。しかし、彼はムスコギ族の出身で、 自分たちの厳しい掟に従って生きている。お前は自らの意思で彼に連れ去られ、二人で夜を過ごした。だから今や、 彼の神々の目にはお前たちは夫婦だ。さあ、荷物をまとめに行こう。身代金の件はお前の叔父さんと俺が話をつける。";
				link.l1.go = "waitress_2";
			}
			link.l2 = "申し訳ありません。ティチンギトゥは自分の部族の掟に従って生きておりますが、根は善良な人間です。どうか、 この誘拐の話は忘れてください。";
			link.l2.go = "waitress_5";
		break;
		
		case "waitress_2":
			dialog.text = "妻ですって？あの神々の前で！？違います、船長、お願いです、こんなのから私を救ってください！ただの…冒険だったんです、彼はとても勇敢で親切で、この田舎者たちとは違って…でも結婚なんて？私はまだ若すぎます、野蛮人と小屋で暮らすなんて無理です！";
			link.l1 = "彼は俺の部下であり、親友でもあるから心配はいらねえ。ちゃんと報酬も払ってるし、 あんたには望みうる最高の小屋を用意してやる。\nティチンギトゥは腕の立つ猟師だ、食料は彼が用意する。あんたは子を産み、子供たちの世話をするんだ。";
			link.l1.go = "waitress_3";
		break;
		
		case "waitress_3":
			dialog.text = "子供たち？食料を調達しろって？！やめてくれ、船長、お願いだから俺にそんなことさせないでくれ、頼むよ！";
			link.l1 = "そうだな、もしかしたら俺があいつを説得できるかもしれねえ。\nだが、簡単にはいかねえぞ。マスコギ族はこういうことにすごく厳しいんだ。もし誰かが、 あいつが女をさらって結婚しなかったって知ったら……";
			link.l1.go = "waitress_4";
		break;
		
		case "waitress_4":
			dialog.text = "お願いだから、やってみてよ！誰にも言わないし、誰にもバレないよ！おじさんには嘘をつくから、 これが初めてじゃないんだよ！";
			link.l1 = "いいだろう、行きな、美しいインディアン娘。俺の友達を近づけないようにしてみるぜ。";
			link.l1.go = "waitress_7";
		break;
		
		case "waitress_5":
			dialog.text = "奴は俺を…まるで納屋からヤギを盗むみたいに連れ去ったんだ！みんなに言ってやる！叔父さんがあいつを殺すぞ！ 怒った時の叔父さんは本当に恐ろしいんだ！昔はスペイン船を襲ってたんだぞ――冗談じゃ済まされねえんだ！";
			link.l1 = "よしよし、静かにしな、美しいお嬢さん、静かに。もしかして、俺の言葉よりも二万の「理由」を渡した方が、 あいつを許してもらえるんじゃねえか？それとも、まるで嫁の身代金みたいに、 その金をあんたの叔父さんに渡した方がいいか？どうせ皆この島にいるんだろ？明日また結婚式でも開けるさ…";
			link.l1.go = "waitress_6";
		break;
		
		case "waitress_6":
			if (sti(Pchar.money) >= 20000) AddMoneyToCharacter(pchar, -20000); 
			dialog.text = "いや、いや、船長、待ってくれ！お前の言うことに納得したよ。伯父さんが怒らないように何とか考えてみる。じゃあな！ そして、遠い平原から来た俺の愛馬よ、さようなら！また会いに来てくれよ……";
			link.l1 = "そうだ。その意見で一致して嬉しいぜ。家に帰りな、美人。";
			link.l1.go = "waitress_7";
		break;
		
		case "waitress_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_16";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		// тавернщик Сен Пьер
		case "tavernkeeper":
			dialog.text = "さて、船長、すべてに満足してくれたか？最高のラム酒、ラムのあばら肉、豚のハム、 さらにはあんたの科学者の友人のために俺の秘蔵の極上ワインまで用意したぜ！それから――あんたと美しい奥さんにおめでとうを言わせてくれ！";
			link.l1 = "ありがとう！正直に言うと、すべて完璧に仕切ってくれたな。\n貯蔵庫にはラム酒が十分あるといいが、朝まではまだまだ時間があるぜ。";
			link.l1.go = "tavernkeeper_1";
		break;
		
		case "tavernkeeper_1":
			dialog.text = "気にするな、樽が空になったら、助手を港の倉庫に行かせるさ。楽しんでくれ、旦那、何も心配はいらねえぞ。";
			link.l1 = "「いいだろう」 "+npchar.name+"。では客人たちのところへ行くとしよう。";
			link.l1.go = "tavernkeeper_2";
		break;
		
		case "tavernkeeper_2":
			DialogExit();
			npchar.dialog.currentnode = "tavernkeeper_3";
		break;
		
		case "tavernkeeper_3":
			dialog.text = "何になさいますか、船長？フライドリブ、スモークハム、それともブリスケット？奥方にはワインなどいかがでしょうか？ ";
			link.l1 = "";
			link.l1.go = "tavernkeeper_2";
		break;
		
		// моряки в таверне Сен Пьер
		case "sailor":
			dialog.text = RandPhraseSimple(LinkRandPhrase("「船長と奥方の健康を祝して！」","末永くお幸せに、船長！","お二人に長寿と幸せを！"),LinkRandPhrase("船長とその美人に万歳！","船長とその伴侶に幸運が生涯ついて回りますように！","順風満帆な家庭を祈ってるぜ、船長！"));
			link.l1 = LinkRandPhrase("ありがとう！","ありがとう！","乾杯！");
			link.l1.go = "sailor_1";
		break;
		
		case "sailor_1":
			DialogExit();
			npchar.dialog.currentnode = "sailor";
		break;
		
		// босс Ле Франсуа
		case "JanDavid":
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("気は確かか？人斬りになりたかったのか？海賊どもはみんなお前に怒ってるぜ、相棒、 だからここからさっさと出て行ったほうがいいぞ。","どうやらお前、頭がおかしくなっちまったみたいだな、相棒。ちょっと腕を伸ばしたかったのか？悪いが、 ここにお前の居場所はねえ。消えな！");
				link.l1 = RandPhraseSimple("聞いてくれ、俺は物事を正したいんだ…","「問題を解決するのを手伝ってくれ…」");
				link.l1.go = "pirate_town";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LongHappy.Baron"))
			{
				if (!CheckAttribute(npchar, "quest.Baron"))
				{
					dialog.text = "ああ、旦那、あんたの来訪を待ってたぜ。ヤン・スヴェンソンが、 あんたがル・フランソワの様子を見に必ず来るって教えてくれたんだ。今は全部俺が仕切ってる。雷に誓って言うが、 この村はあの忌々しいキンドマンの時代よりも繁栄させてみせるぜ。あいつなんざ、 地獄の一番暗ぇ地下室で悪魔どもに遊ばれてりゃいいんだ！";
					link.l1 = "お前がジャン・ダヴィッドだな？スヴェンソンが俺の取り分について何か言ってたんだが……";
					link.l1.go = "JanDavid_2";
				}
				else
				{
					dialog.text = TimeGreeting()+" 親分。ル・フランソワはいつも通り、何も問題ねえぜ。どうして来たんだ？何か手伝えることがあるか？";
					link.l1 = "ちょっと様子を見に立ち寄っただけだ。";
					link.l1.go = "JanDavid_1";
					if (sti(pchar.questTemp.LongHappy.BaronMoney) > 0)
					{
						link.l2 = "俺の取り分はどうなってるんだ？";
						link.l2.go = "JanDavid_5";
					}
				}
			}
			else
			{
				dialog.text = TimeGreeting()+" 相棒。何の用だ？何か手伝えることがあるか？";
				link.l1 = "ちょっと挨拶しに寄っただけだ。";
				link.l1.go = "JanDavid_1";
			}
		break;
		
		case "JanDavid_1":
			DialogExit();
			npchar.dialog.currentnode = "JanDavid";
		break;
		
		case "JanDavid_2":
			npchar.quest.Baron = "true";
			dialog.text = "お任せください、親分！あんたの取り分についてだが――毎月五日に、うちの連中が稼いだ金貨の一部をあんたのために取り分けておくぜ。 好きなときに受け取れるようにしておくからな。来月からは、いつでも受け取りに来てくれていいぜ。";
			link.l1 = "いいね！";
			link.l1.go = "JanDavid_3";
		break;
		
		case "JanDavid_3":
			dialog.text = "あとは俺に任せろ。森の悪魔が言ってたぜ、お前はル・フランソワみたいな些細なことに構ってる暇なんかねえってな…";
			link.l1 = "ちゃんと聞いていたんだな。よし、ジャン、頼りにしてるぜ、俺をがっかりさせるなよ。";
			link.l1.go = "JanDavid_4";
		break;
		
		case "JanDavid_4":
			dialog.text = "心配いらねえよ、親分。ここは全部俺がしっかり仕切ってるぜ、ははっ、もし何かやらかしたら、 二度と死ぬまでラムを飲まねえって誓うよ！";
			link.l1 = "よし、またな！";
			link.l1.go = "JanDavid_1";
			// запуск отчисления доли
			pchar.questTemp.LongHappy.BaronPart = "true";
			pchar.questTemp.LongHappy.BaronMoney = 0;
		break;
		
		case "JanDavid_5":
			dialog.text = "待ってましたぜ、旦那。そんで、その間にあんたのために集めておいたんだ "+FindRussianMoneyString(sti(pchar.questTemp.LongHappy.BaronMoney))+"。受け取れ。";
			link.l1 = "はっ、悪くねえな。よくやった、ジャン。";
			link.l1.go = "JanDavid_6";
		break;
		
		case "JanDavid_6":
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.LongHappy.BaronMoney));
			pchar.questTemp.LongHappy.BaronMoney = 0;
			dialog.text = "全力を尽くしますぜ、旦那。来月でも、いつでも好きな時に戻ってきてくれ――あんたの金は俺がしっかり預かっておくからな。";
			link.l1 = "ああ、じゃあな、Jean。";
			link.l1.go = "JanDavid_1";
		break;
		
		case "pirate_town":
             dialog.text = "問題を解決しろだと？自分が何をやらかしたかわかってるのか？まあいい、とにかく百万ペソ持ってこい。 そうすりゃ俺が野郎どもを説得して、お前のやったことを忘れさせてやる。気に入らねえなら地獄へ行きな。";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "よし、支払う準備はできている。";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "了解だ。行くぜ。";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "よし！これでまた清められたと思え。だが、もう二度とそんな汚らわしいことはするんじゃねえぞ。";
			link.l1 = "俺には無理だ。高すぎるぜ。じゃあな……";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
	}
} 
