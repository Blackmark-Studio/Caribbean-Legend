// старпом Акулы - Лейтон Декстер
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
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "邪魔するな、坊主。話があるならシャークにしろ、ここはあいつの仕切りだ。";
				link.l1 = "せめて挨拶くらいはしてもいいか？それとも、それもルール違反かい？";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				if (CheckAttribute(npchar, "quest.map"))
				{
					link.l2 = "レイトン、シャークが君が正義の島の地図を持ってるって教えてくれたんだ。譲ってもらえないか？";
					link.l2.go = "map";
				}
				dialog.text = "「ああ、」 "+GetFullName(pchar)+"！俺に用か、それともただ話したいだけか？どっちでもいいが、次はラム酒を一本持ってこいよ、はは！";
				link.l1 = "いや、ただ挨拶したかっただけだ。次はお前のためにラム酒を持ってくるぜ。";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "はっ！冗談好きか！よし……俺の名はレイトン・デクスターだ。ここに流れ着く前はシャークの相棒だったが、今じゃこの“正義の島”で奴の副官をやってる。（ぺっ）\n毎日、市民に食料を売ったり、怠け者のファジオから金を搾り取ろうとしたりして過ごしてるぜ。";
			link.l1 = "俺は "+GetFullName(pchar)+"…お会いできて嬉しい…と思うよ。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// Акула погиб по варианту N
		case "admiral":
			dialog.text = "スティーブが死んだって、もう聞いてるだろう。やったのはナーワルどもさ。";
			link.l1 = "聞いたぜ……お前が新しい提督か？";
			link.l1.go = "admiral_1";
			AddQuestRecord("SharkHunt", "28");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition	
		break;
		
		case "admiral_1":
			dialog.text = "そうだ。チャドはナーヴァルに寝返ったし、スティーブは死んじまった。だから……俺が提督だ。文句あるか？";
			link.l1 = "いや……異論はない。";
			link.l1.go = "admiral_2";
		break;
		
		case "admiral_2":
			dialog.text = "「よし。」";
			link.l1 = "「シャークの死の復讐をナーワル族に果たすつもりか？」";
			link.l1.go = "admiral_3";
		break;
		
		case "admiral_3":
			dialog.text = "つまり、俺があいつらに宣戦布告するかってことか？いや、しねえよ。奴らにツケを払わせるには、 もっといい方法があるんだ。\nまずは、食料の値段を三倍にしてやる。それが気に入らなくてサン・アウグスティン号に手を出すようなら、 血で償わせてやるさ。\n次に、リヴァドスと休戦交渉をするつもりだ。もちろん、あの汚い黒人どもなんざ信用できやしねえ、 特に魔術師チミセットが死んだ後じゃな。でも、食い物とラムがあれば、どんな罪もなかったことにできるもんさ。";
			link.l1 = "そうか…。じゃあ…さよなら、レイトン…。";
			link.l1.go = "admiral_4";
		break;
		
		// нода пересечения
		case "admiral_4":
			dialog.text = "待て。スティーブが、お前はこの島を出て船で戻るつもりだと言っていたが、それは今も変わらないのか？";
			link.l1 = "そうだ。";
			link.l1.go = "admiral_5";
		break;
		
		case "admiral_5":
			dialog.text = "この航海用ルターを持っていけ。これにはここへ無事に戻るための航路が記されている――つまり、暗礁に乗り上げることも、潮流に流されることも、外縁の難破船にぶつかることもないってわけだ。\nこれがなけりゃ、島を見逃すか……あるいは新たな難破船になるだけだ。\n暗礁を抜けるには、喫水の浅い小型船を使うことを忘れるな。タルターヌ、ラガー、スクーナー、スループ……それ以上の大きさは駄目だ。わかったか？";
			link.l1 = "ああ、知ってるぜ。ありがとう。";
			link.l1.go = "admiral_6";
		break;
		
		case "admiral_6":
			GiveItem2Character(pchar, "LSC_navigation_map");
			dialog.text = "積荷室に必ず食糧を積んでおくんだ――俺がいい値で買い取ってやるからな。\nそれと、この書類は絶対に誰にも見せるなよ。俺たちの基地は秘密のままでいなきゃならねえ。\nお前にこれを渡すのは、スティーブ本人が渡すつもりだったってことと、お前がヤン・スヴェンソンの友人だからだ。";
			link.l1 = "これを誰にも見せないと約束します。改めてありがとう、レイトン。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dexter_wait";
			AddQuestRecord("LSC", "5");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			// убираем квестовые предметы
			sld = ItemsFromID("key_capper");
			sld.price = 10;
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
		break;
		
		case "Dexter_wait":
			dialog.text = "脱出計画は進んでいるのか、 "+pchar.name+"?";
			link.l1 = "まだだ、レイトン。今取り組んでいるところだ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dexter_wait";
		break;
		
		// Акула погиб по варианту M
		case "admiral_7":
			dialog.text = "いたな。話があるんだ。";
			link.l1 = "それで、今はお前が提督ってわけか？";
			link.l1.go = "admiral_8";
		break;
		
		case "admiral_8":
			dialog.text = "ああ、俺が提督だ。スティーブの相棒として何でも一緒にやってきたから、あいつが死んだ今は俺が仕切る。文句あるか？ ";
			link.l1 = "いや……異議はない。お前にはその権利がある。";
			link.l1.go = "admiral_9";
		break;
		
		case "admiral_9":
			dialog.text = "分かり合えて嬉しいぜ。何か必要なら遠慮なく言ってくれよ。";
			link.l1 = "シャークの死の復讐をナーワル族に果たすつもりか？";
			link.l1.go = "admiral_10";
		break;
		
		case "admiral_10":
			dialog.text = "つまり、俺があいつらに宣戦布告するかってことか？いや、しねえよ。奴らに報いを受けさせるには、 もっといい方法があるんだ。\nまずは、補給品の値段を三倍にしてやる。それが気に入らなくてサン・アウグスティンを攻撃しようとするなら、 今度は血で払わせてやるさ。\nそれに、今はリバドスといい関係を築いてるから、ナーワルどももまた俺たちに手を出すのはためらうだろうよ。";
			link.l1 = "なるほど。他に何かあるか、それとももう行っていいか？";
			link.l1.go = "admiral_4";
		break;
		
		case "plan":
			PlaySound("Voice\English\LSC\Layton Dexter-07");
			dialog.text = "ああ。ナーヴァルたちに近づく方法は一つしか思いつかねえ。完璧じゃねえが、他に手はねえだろう。\n二手に分かれて攻める。ロングボートに乗った殺し屋どもがセレス号に乗り込み、 もう一方はリヴァドスと合流してエスメラルダ号を襲撃する。\nこれで奴らを完全に殲滅できるか、サン・ガブリエル号へ逃げ込ませるかのどちらかだ。\n後者の方が可能性は高いな。サン・ガブリエル号は守りが堅いし、包囲するには時間がかかる。どちらに転んでも、 俺たちの勝ちだ。";
			link.l1 = "";
			link.l1.go = "plan_1";
		break;
		
		case "plan_1": // ноду Акуле
			DialogExit();
			npchar.greeting = "dexter_1";
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "whyskey_final_3";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			NextDiag.CurrentNode = "plan_2";
		break;
		
		case "plan_2":
			dialog.text = "ドナルド・グリーンスパンとの会話の報告を待っている。\nこれは極めて重要だ、時間を無駄にするな。";
			link.l1 = "今向かっている。";
			link.l1.go = "exit";
			NextDiag.TempNode = "plan_2";
		break;
		
		case "map":
			dialog.text = "ああ、地図なら持ってるぜ。欲しいなら、たった二百ドゥブロンでお前のものにしてやるよ。";
			link.l1 = "ペソはどうだ？";
			link.l1.go = "map_1";
		break;
		
		case "map_1":
			dialog.text = "いや、俺は金貨しか受け取らねえ――値切っても無駄だぜ。この地図の価値はちゃんとわかってる、二百ドゥブロンだ。";
			if (PCharDublonsTotal() >= 200)
			{
				link.l1 = "わかった、承知した。これがあんたの金だ。";
				link.l1.go = "map_2";
			}
			link.l2 = "そんなに金貨は持ってねえ。もしかしたら後で……";
			link.l2.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "map_2":
			RemoveDublonsFromPCharTotal(200);
			PlaySound("interface\important_item.wav");
			Log_Info("You have received a map of the City of Abandoned Ships");
			GiveItem2Character(pchar, "map_LSC");
			dialog.text = "地図を持っていけ。値段に見合う価値はあるぜ――この地図を描くために一週間も街中を這い回ったんだ。\nまあ、正直言って安く売りすぎたと思ってるくらいさ。";
			link.l1 = "安く！？はっ！まあ……ありがとう。";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			DeleteAttribute(npchar, "quest.map");
		break;
		
		// геймовер диким геймерам за издевательство над игрой
		case "LSC_GameOverPrison":
			dialog.text = "そこまでだ、相棒！ああ、シャークの言った通りだ、この野郎は正気じゃねえ。こいつのせいで何人も死んだんだ……縛り上げて船倉にぶち込め！";
			link.l1 = "...";
			link.l1.go = "LSC_GameOverPrison_1";
		break;
		
		case "LSC_GameOverPrison_1":
			DialogExit();
			DoQuestReloadToLocation("TartarusPrison", "quest", "prison4", "LSC_GameOverInPrison");
		break;
		
		case "return":
			dialog.text = "スティーブが自分の代わりに俺を提督に任命した――つまり、あんたと彼は一緒にカリブへ戻るんだな。\n俺はここに残って商売を続けるさ。俺もスティーブも、こんな素晴らしい拠点を失いたくねえからな。それに、 もちろんあんたはいつでも歓迎するぜ、ここでな。";
			link.l1 = "ありがとう、レイトン。水平線に気をつけて見張っててくれ、俺はいつか戻ってくるからな。";
			link.l1.go = "return_1";
		break;
		
		case "return_A":
			dialog.text = "「ああ、」 "+GetFullName(pchar)+"！やったな！スティーブの航海指示で正義の島を見つけたんだろ？とんでもねえ奴だな……おかえり！";
			link.l1 = "ありがとう、レイトン。いつか戻るって言っただろ、ははっ！";
			link.l1.go = "return_1";
		break;
		
		int iTrade = GetSquadronGoods(pchar, GOOD_FOOD)-GetCrewQuantity(pchar);
		int iMoney = 0;
		case "return_1":
			dialog.text = "わかった。何か食べ物を売ってくれないか？市場価格の倍額で買うつもりだ。";
			if (iTrade > 0)
			{
				link.l1 = "ああ、食料を売ってるぜ。";
				link.l1.go = "trade";
			}
			link.l2 = "あいにく、今はあなたに売れるものが何もないんだ。";
			link.l2.go = "return_2";
			npchar.quest.foodqty = 0; // предел затарки складов = 15 000
		break;
		
		case "return_2":
			dialog.text = "残念だな。次は忘れずに持ってきてくれよ――たっぷり払うぜ。";
			link.l1 = "忘れないようにするよ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "head";
		break;
		
		case "trade":
			dialog.text = "いくらだ？";
			link.l1.edit = 4;
			link.l1 = "";	
			link.l1.go = "trade_1";
		break;
		
		case "trade_1":
			iTemp = dialogEditStrings[4];
			int iMax = GetSquadronGoods(pchar, GOOD_FOOD)-GetCrewQuantity(pchar);
			if (iTemp <= 0 || iTemp > GetSquadronGoods(pchar, GOOD_FOOD))
			{
				dialog.text = "なんだ、お前酔ってるのか？ちゃんと真面目に話す気になったらまた来いよ。";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
			break;
			}
			if (iTemp <= 50)
			{
				dialog.text = "そんなはした金じゃ話にならねえ！俺の時間の無駄だ、もっと持ってこい！";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
			break;
			}
			if (iTemp > iMax)
			{
				dialog.text = "自分の食料もなしでどうやって航海するつもりだ、相棒？仲間たちを飢えさせたいのか？せめて "+FindRussianQtyString(GetCrewQuantity(pchar))+".";
				link.l1 = "「うん、その通りだ。」";
				link.l1.go = "exit";
			break;
			}
			if (iTemp >= 15000) // лесник
			{
			 iTemp = (15000 - sti(npchar.quest.foodqty))	
             dialog.text = "イエス・キリスト、それは俺たちには多すぎるぜ！腐る前に食いきれやしねえ。今はそれ以上は受け取れねえんだ "+iTemp+".";
			 link.l1 = "あんたの言う通りだ。";
			 link.l1.go = "trade_3";
			 break;
            }							  
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			dialog.text = ""+FindRussianQtyString(iTemp)+"？わかった、払うよ "+FindRussianMoneyString(iMoney)+"……取引成立か？";
			link.l1 = "取引成立だ！いい商売ができて嬉しいぜ！";
			link.l1.go = "trade_2";
			link.l2 = "うーん…いや、やっぱり気が変わった。";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		case "trade_3": // лесник 
		    iTemp = (15000 - sti(npchar.quest.foodqty))	
		    iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			dialog.text = "取引成立だ。支払おう "+FindRussianMoneyString(iMoney)+" 品物のためだ。いいか？";
			link.l1 = "「公正だな！取引できてよかったぜ！」";
			link.l1.go = "trade_4";
			link.l2 = "うーん……やっぱり気が変わった。";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		case "trade_4": // лесник 
		    iTemp = (15000 - sti(npchar.quest.foodqty))	
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			AddMoneyToCharacter(pchar, iMoney);
			RemoveCharacterGoods(pchar, GOOD_FOOD, iTemp);
			npchar.quest.foodqty = sti(npchar.quest.foodqty)+iTemp;
			if(!CheckAttribute(pchar,"Achievment.LSCfood")) pchar.Achievment.LSCfood = iTemp;
			else pchar.Achievment.LSCfood = sti(pchar.Achievment.LSCfood) + iTemp;
			if(sti(pchar.Achievment.LSCfood) >= 20000) Achievment_Set("ach_CL_112");
			if (sti(npchar.quest.foodqty) >= 15000) // склады затарены на полгода
			{
				SetFunctionTimerCondition("LSC_ClearFoodStorage", 0, 0, 180, false);
				dialog.text = "ちくしょう、俺の目が信じられねえ！倉庫が満杯だ！これで半年は食料を買う必要がねえな。";
				link.l1 = "よし。では、半年後に次の食糧を持ってきてやる。";
				link.l1.go = "exit";
				AddQuestRecord("LSC", "25");
			}
			else
			{
				dialog.text = "いいぞ！次ももっと持ってきてくれ。";
				link.l1 = "もちろんだ！";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "head";
		break;
		case "trade_2":
			iTemp = dialogEditStrings[4];
			iMoney = (50+hrand(5, "&Slayer"))*iTemp;
			AddMoneyToCharacter(pchar, iMoney);
			RemoveCharacterGoods(pchar, GOOD_FOOD, iTemp);
			npchar.quest.foodqty = sti(npchar.quest.foodqty)+iTemp;
			if(!CheckAttribute(pchar,"Achievment.LSCfood")) pchar.Achievment.LSCfood = iTemp;
			else pchar.Achievment.LSCfood = sti(pchar.Achievment.LSCfood) + iTemp;
			if(sti(pchar.Achievment.LSCfood) >= 20000) Achievment_Set("ach_CL_112");
			if (sti(npchar.quest.foodqty) >= 15000) // склады затарены на полгода
			{
				SetFunctionTimerCondition("LSC_ClearFoodStorage", 0, 0, 180, false);
				dialog.text = "素晴らしい！これで俺の倉庫は満杯だ。これから半年は食料を買う必要がねえな。";
				link.l1 = "よし。それじゃあ、次の食糧を半年後に持ってくるぜ。";
				link.l1.go = "exit";
				AddQuestRecord("LSC", "25");
			}
			else
			{
				dialog.text = "素晴らしい！次はもっと持ってきてくれ。";
				link.l1 = "もちろんだぜ！";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "head";
		break;
		
		case "head": // стандартный диалог Декстера-адмирала
			dialog.text = "「あ、あ、」 "+GetFullName(pchar)+"！会えて嬉しいぜ！何の用だ？";
			if (iTrade > 0 && sti(npchar.quest.foodqty) < 15000)
			{
				link.l1 = "俺から食料を買わねえか？";
				link.l1.go = "trade";
			}
			link.l2 = "たいしたことじゃねえ、ただ様子を見に来ただけさ。";
			link.l2.go = "exit";
			NextDiag.TempNode = "head";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
