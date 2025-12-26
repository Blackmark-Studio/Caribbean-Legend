// Леонард Маскетт - пьяница
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iPeso, iDubl;
	string sPeso, sDubl;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
			{
				dialog.text = "消え失せろ、相棒！俺は罪もない人間を襲うクズとはおしゃべりしねえんだ。";
				link.l1 = "ふむ……";
				link.l1.go = "exit";
				break;
			}
			// --> пей до дна
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_3") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.facio"))
			{
				dialog.text = "相棒、ちょうどいいところに来たな……ちょっと話したいことがあるんだ……大事な商売の話さ。";
				link.l1 = "本当か？レナード……お前が素面だなんて！珍しいものを見たもんだな！";
				link.l1.go = "facio";
				break;
			}
			// <-- пей до дна
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "あ、ああ……ひっく！よう、相棒……";
				link.l1 = TimeGreeting()+"……もう十分飲んだみたいだな、相棒。";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "「ああ、」 "+GetFullName(pchar)+"「……ひっく！何の用だ？」";
				link.l1 = LinkRandPhrase("「何か変わったことはあるか、レナード？」", "島で何か新しいことが起きたか？", "最近の噂話を教えてくれるか？");
				link.l1.go = "rumours_LSC";
				link.l2 = "この島についていくつか質問したいんだ。";
				link.l2.go = "int_quests"; //информационный блок
				link.l5 = "ちょっと様子を見に来ただけだ。じゃあな！";
				link.l5.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting": // первая встреча
			dialog.text = "ああ！もう十分か？いや、全然足りねえ、ひっく！そうだ、レオナード・マスケットは酔っぱらってるんだ、 それが当たり前だぜ！";
			link.l1 = "酒が好きなんだな？ああ、俺の名前は "+GetFullName(pchar)+"……ええと……お会いできて、嬉しいです。";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "そうかい。俺たちは…ひっく！…みんな集まったわけだが、さて…これからどうするんだ？";
			link.l1 = "そうかい、あんたが…えっと…忙しくて話せねえなら…また今度だな！";
			link.l1.go = "exit";
			link.l2 = LinkRandPhrase("ここらで何か変わったことはあったか？", "島で何か新しいことが起きたかい？", "最近の噂話を教えてくれないか？");
			link.l2.go = "rumours_LSC";
			link.l3 = "この島についていくつか質問したいんだ。";
			link.l3.go = "int_quests"; //информационный блок
			NextDiag.TempNode = "First time";
		break;
		
		// --> пей до дна
		case "facio":
			dialog.text = "あっはは、くたばれよ！ああ、相棒、俺は――ほとんど――しらふだぜ。そいつはな、俺たちにチャンスがあるからさ……";
			link.l1 = "どんな機会だ？話せ、俺の時間を無駄にするな！";
			link.l1.go = "facio_1";
			npchar.quest.facio = "true";
		break;
		
		case "facio_1":
			dialog.text = "相棒……金を稼ぎたいか？銀ペソに金のドゥブロンだぜ？やり方を教えてやるよ。ただし、俺と分け前を分かち合うんだ――一緒にやろうぜ。";
			link.l1 = "俺はいつだって金儲けには乗り気だぜ。\nだが、すべてはあんたの提案次第さ――どれだけ儲かるか、そして…どれだけ“合法”か、ってな。";
			link.l1.go = "facio_2";
		break;
		
		case "facio_2":
			dialog.text = "商売自体はまあ合法とは言えねえが、儲かるんだよ……それに、ケチな奴をその強欲の報いで懲らしめてやれるってわけさ。あいつが貧乏になることはねえ、 金は腐るほど持ってるからな。\nそれに、みんなあいつに分けてやってきたんだ、今度は恩返しの番ってもんだろう。なあ、お前は酒に強いのか？ ラムをどれだけ飲んだらテーブルの下に沈むんだ？";
			link.l1 = "場合によるな。俺はあんまり酒を浴びるように飲む習慣はねえんだ……で、そろそろ詳しい話をしてくれるのか？";
			link.l1.go = "facio_3";
		break;
		
		case "facio_3":
			dialog.text = "いいだろう。はっきり言ってやるよ。この島には太って醜い野郎がいる、ジュゼッペ・ファツィオだ。（ぺっと唾を吐く） あいつはナーワルもリヴァドスも島の連中も食い物にしてやがる。俺はしばらくあいつを見張ってて、 あることを知ったんだ…\nキャロライン号のあいつの船室には二つの箱がある。一つには書類、もう一つには金銀が入ってる。 どっちも違う鍵でしっかり閉めてあるんだ。あのデブ野郎は、いつも鍵を自分のポケットに入れてるぜ。";
			link.l1 = "それで、ファジオを襲うつもりか？悪いが、俺は手を貸さねえよ。しかも誰にも言わねえだけありがたく思え。 他の仲間を探しな。";
			link.l1.go = "facio_exit";
			link.l2 = "ははっ！面白いな！続けてくれ…";
			link.l2.go = "facio_4";
		break;
		
		case "facio_exit":
			dialog.text = "残念だな、残念だ……金なら二人分たっぷりあるってのによ……まあいいさ。それじゃ、またな。";
			link.l1 = "さらば。";
			link.l1.go = "exit";
		break;
		
		case "facio_4":
			dialog.text = "彼の船室には二つの扉がある。一つはいつも鍵がかかっているが、金の宝箱を開ける鍵がその扉も開けるんだ。 俺は実際に彼がそうしているのを見た。つまり、船室と宝箱、両方を開けるには一つの鍵だけでいい。でも、 その鍵をどうやって手に入れるかだな。\n俺には計画がある、しかも最高のやつだ。うまくいけば、ファツィオは何が起きたのかも、 誰を疑えばいいのかも分からねえ。奴は例の謎のラム酒と宝飾品泥棒の仕業だと思うだろう。ただ問題は、 この計画をやり遂げるには鉄の頭を持った相棒が必要ってことだ。分かるか？";
			link.l1 = "そうだ。続けてくれ。";
			link.l1.go = "facio_5";
		break;
		
		case "facio_5":
			dialog.text = "ファジオはサンチョの店で飲むのが大好きでな、しかもあいつは俺が今まで見た誰よりも酒に強いんだ！ 本人もそれを自覚してて、飲み比べのゲームまで考え出したんだぜ。つまり、誰がファジオを酔い潰せるかって勝負さ。\nもしそのゲームをやりたいって言えば、絶対に乗ってくる。そこからが面白いんだ。\nあいつと賭けをして、酒場に行ってラム酒のボトルを手に入れて、どっちかがテーブルにキスするまで飲み続ける。 もしお前が先に潰れたら、計画は全部パーだ。俺一人じゃどうにもならねえ。\nだからお前の酒の強さを聞いたんだ。ただ、あいつを先に潰せばいい。それだけだ。俺は近くで待ってる。 ファジオがダウンしたら、俺があいつの鍵を頂く。\nそれから、あのデブを上の階のベッドに運んで、寝てる間にキャビンに忍び込む。宝箱を漁ったらすぐに鍵は元に戻す――あいつは箱を開けるまで盗まれたことに気づきもしねえ、ははっ！\n鍵を手に入れたら、お前がキャビンに忍び込んで取れるだけ取れ。俺は外で見張ってる。宝箱の中身は半分こして、 それぞれの道を行く。どうだ、乗るか？";
			link.l1 = "狡猾な計画だな！もちろん、俺も乗るぜ。";
			link.l1.go = "facio_6";
			link.l2 = "いや、相棒。俺は遠慮しとくぜ。酒にはあまり強くなくてな。もっと俺より頑丈な奴を探してくれよ。";
			link.l2.go = "facio_exit";
		break;
		
		case "facio_6":
			dialog.text = "やっぱりお前は俺の見立て通りだったな。さて、ファジオのところへ行って、 夜九時過ぎに酒場で会う段取りをつけてこい。あの豚野郎を出し抜いてくれるといいがな！幸運を祈るぜ、 夜にまた会おう！";
			link.l1 = "全力を尽くすよ……じゃあな！";
			link.l1.go = "facio_7";
		break;
		
		case "facio_7":
			DialogExit();
			NextDiag.CurrentNode = "facio_wait";
			pchar.questTemp.LSC.Drink = "begin";
			pchar.questTemp.LSC.Drink.Chance = hrand(100); // итог бухалова
			if (CheckAttribute(pchar, "questTemp.CanDrink")) pchar.questTemp.LSC.Drink.Chance = sti(pchar.questTemp.LSC.Drink.Chance)+50;
			SetFunctionTimerCondition("LSC_DrinkOver", 0, 0, 3, false); // 3 дня
			AddQuestRecord("LSC_Drink", "1");
		break;
		
		case "facio_wait":
			dialog.text = "相棒、頼りにしてるぜ。あのケチなデブを飲み潰してくれよ……";
			link.l1 = "ああ、いいぜ。";
			link.l1.go = "exit";
			NextDiag.TempNode = "facio_wait";
		break;
		
		case "result_0":
			dialog.text = "終わったぜ、あの豚は上で寝ちまった。鍵は俺が持ってる。お前、調子いいじゃねえか。酔ってもいねえようだな！";
			link.l1 = "ほ、本当か？こんなに……ひっく……酔っぱらったのは久しぶりだぜ。ちょっとふらふらする……ひっく！行くか？\n";
			link.l1.go = "result_win";
		break;
		
		case "result_1":
			dialog.text = "終わったぜ、あのデブ豚は上の階で寝ちまってる。鍵は俺が持ってる。お前、やるじゃねえか……本当にあの豚野郎を飲み潰したんだな……";
			link.l1 = "あるさ、でも…ひっく！…こんなに酔ったのは久しぶりだ。頭がぐるぐるしてる……倒れる前に行こうぜ。";
			link.l1.go = "result_win";
		break;
		
		case "result_2":
			dialog.text = "おい、相棒、あのデブには飲み勝てなかったな……残念だぜ。まあ、少なくとも挑戦はしたよな……";
			link.l1 = "くっ、くそっ、あいつはまるで……底なしの樽みてえだ。ああ、ちょっと休ませてくれ……もう終わりだ、消えろ！ひっく……";
			link.l1.go = "result_fail";
		break;
		
		case "result_win":
			dialog.text = "ああ。行こうぜ！キャロライン号までついて来い！うろうろするなよ、時間がねえんだからな！\n";
			link.l1 = "あ、ああ、行こう！";
			link.l1.go = "result_win_1";
		break;
		
		case "result_win_1":
			DialogExit();
			NextDiag.CurrentNode = "result_win_2";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload6", "LostShipsCity_town", "reload", "reload39", "LSC_DrinkGotoCarolina", -1);
			AddQuestRecord("LSC_Drink", "3");
		break;
		
		case "result_win_2":
			pchar.quest.LSC_Drink1.over = "yes"; //снять таймер
			dialog.text = "ほら、鍵だ。持っていけ。必要な箱は入口の左側にある。できるだけ早く、できるだけ多く持っていけ。 終わったら必ずまた鍵をかけるんだぞ！何か見かけたら、俺がドアを三回ノックする。そしたら裏の回廊から逃げろ。\n";
			link.l1 = "よし。用心しろよ！";
			link.l1.go = "result_win_3";
		break;
		
		case "result_win_3":
			DialogExit();
			GiveItem2Character(pchar, "key_facioQ");
			NextDiag.CurrentNode = "result_grabbing";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload25", "LSC_DrinkGotoCarolina_3", -1);
		break;
		
		case "result_grabbing":
			// считаем деньги и дублоны взятые из сундука
			iPeso = sti(pchar.money)-sti(pchar.questTemp.LSC.Drink.Money);
			iDubl = GetCharacterItem(pchar, "gold_dublon")-sti(pchar.questTemp.LSC.Drink.Dublon);
			if (iPeso <= 0) sPeso = "not a single peso";
			else sPeso = ""+FindRussianMoneyString(iPeso)+"";
			if (iDubl <= 0) sDubl = "not a single doubloon";
			else sDubl = ""+iDubl+" doubloons";
			if (iPeso <= 10000 && iDubl <= 10) sTotalTemp = "What a miserable haul... Why'd we even bother? Eh... fine, let's split what we've got.";
			else
			{
				if (iPeso <= 50000 && iDubl <= 100) sTotalTemp = "I thought that there'd be much more... Hardly worth the risk. Eh... fine, let's split what we have got.";
				else
				{
					if (iPeso <= 100000 && iDubl <= 300) sTotalTemp = "Hm. Not bad. But I thought there'd be more. All right, let's split it.";
					else 
					{
						if (iPeso <= 150000 && iDubl <= 500) sTotalTemp = "Excellent! We've done well, partner! This is a lot of coin! Let's split it!";
						else
						{
							sTotalTemp = "Damn me! I never imagined the fat man's stash was so huge. Well done, partner! Let's split the loot!";
						}
					}
				}
			}
			dialog.text = "やっとか！あのケチから何を手に入れたんだ？見せてみろ！";
			if (iPeso <= 0 && iDubl <= 0)
			{
				link.l1 = "何もなかったよ。ちょっとしたガラクタ――お守りとか、そんなものだけさ。";
				link.l1.go = "grabbing_0";
			}
			else
			{
				link.l1 = "見つけた "+sPeso+" そして "+sDubl+"";
				link.l1.go = "grabbing_1";
			}
		break;
		
		case "grabbing_0":
			dialog.text = "いや！全部無駄だったみてえだな……もしかして、あの野郎は別の箱に隠したのかもな。ちっ！まあいい、鍵を渡せ、俺が返してくる。じゃあな、相棒……くそっ……";
			link.l1 = "...";
			link.l1.go = "grabbing_exit";
			AddQuestRecord("LSC_Drink", "6");
		break;
		
		case "grabbing_1":
			dialog.text = sTotalTemp;
			link.l1 = "分け合おう。";
			link.l1.go = "grabbing_part";
		break;
		
		case "grabbing_part":
			iPeso = makeint((sti(pchar.money)-sti(pchar.questTemp.LSC.Drink.Money))/2);
			iDubl = makeint((GetCharacterItem(pchar, "gold_dublon")-sti(pchar.questTemp.LSC.Drink.Dublon))/2);
			AddMoneyToCharacter(pchar, -iPeso);
			RemoveItems(pchar, "gold_dublon", iDubl);
			Log_Info("You have given "+iDubl+" doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "よし、鍵を渡せ。俺が返してやる。じゃあな、相棒。";
			link.l1 = "幸運を祈るぜ、相棒。";
			link.l1.go = "grabbing_exit";
			AddSimpleRumourCityTip("Fazio was complaining that someone cleaned out his chest. It seems the mysterious thief did it.", "LostShipsCity", 3, 1, "LSC", "");
			AddSimpleRumourCityTip("Haven't you heard? Fazio was robbed! He was robbed while lying dead drunk after having a game with you.", "LostShipsCity", 3, 1, "LSC", "");
			AddSimpleRumourCityTip("You have a strong head! To drink so much rum and stay on your feet! That's something.", "LostShipsCity", 3, 2, "LSC", "");
			AddQuestRecord("LSC_Drink", "5");
		break;
		
		case "grabbing_exit":
			DialogExit();
			RemoveItems(pchar, "key_facioQ", 1);
			int n = Findlocation("CarolineBank");
			locations[n].private2.QuestClosed = true; // запираем сундук
			LocatorReloadEnterDisable("CarolineBank", "reload1", false); // на галерею
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload38", "FleuronTavern", "goto", "goto2", "OpenTheDoors", 15.0);
			pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink4.win_condition.l1.date.hour  = sti(GetTime()+5);
			pchar.quest.LSC_Drink4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
		break;
		
		case "result_fail":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "LostShipsCity_town", "goto", "goto05_2", "", 10);
			chrDisableReloadToLocation = false;//открыть локацию
			n = Findlocation("CarolineBank");
			locations[n].private2.QuestClosed = true; // запираем сундук
			pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink4.win_condition.l1.date.hour  = sti(GetTime()+5);
			pchar.quest.LSC_Drink4.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
			AddQuestRecord("LSC_Drink", "4");
		break;
		// <-- пей до дна
		
//--------------------------------------- блок вопросов и ответов ---------------------------------------------
		case "int_quests":
			dialog.text = "本当かい？…ひっく！聞いてるぜ…";
			if (!CheckAttribute(npchar, "quest.answer_1"))
			{
				link.l1 = "どうしてここに来ることになったんだ？";
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l2 = "いつも酒を飲んでるのか？それに、酒代はどこで手に入れてるんだ？";
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(npchar, "quest.answer_3"))
			{
				link.l3 = "この島の住人たちについて何か教えてくれないか？";
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(npchar, "quest.answer_4"))
			{
				link.l4 = "この場所を離れてスペイン領本土へ行きたいか？";
				link.l4.go = "ansewer_4";
			}
			link.l10 = "質問はない。失礼……";
			link.l10.go = "exit";
		break;
		
		case "ansewer_1":
			dialog.text = "えっ！そうだなあ、思い出せねえんだよ。本当だ、全然覚えてねえ！ずいぶん昔のことさ。どこかを航海してて…どうやってだったか…まあ、とにかく、最終的にここに流れ着いたってわけだ。ひっく！";
			link.l1 = "ふむ……わかった……";
			link.l1.go = "int_quests";
			npchar.quest.answer_1 = "true";
		break;
		
		case "ansewer_2":
			dialog.text = "ああ、飲むさ。俺は酒飲みだ……飲むんだよ、くそっ、他にやることなんて何もねえからな！わかるか、相棒、俺はもう終わっちまった。 このラム酒の瓶だけが、今の俺の唯一の望みさ。だから、飲み続けるぜ！それに金もな……へへ、ラムなんて大して金かからねえしな。\nそれに、別に払う必要もねえんだ。ラムでいっぱいの場所があるが、そこに行きたきゃ泳がなきゃならねえ。だから、 泳げねえくらい酔っ払った時だけラムを買うんだよ……ひっく……ジズジェゼゼジゼゼ……いや、どこに泳げばいいかなんて教えねえぜ、へへ、聞くなよ……";
			link.l1 = "「愉快だね。」";
			link.l1.go = "int_quests";
			npchar.quest.answer_2 = "true";
		break;
		
		case "ansewer_3":
			dialog.text = "何を言えばいいんだろうな、ひっく！あいつらについてか？話して飲むにはいい連中だぜ。 ジュゼッペ・ファツィオは偉い男さ、大物だ。奴の宝箱は金でパンパンだ…ぷふっ！ケチ野郎…でもレオナルド爺さんのことはちゃんと敬ってて、酒場で酒を奢ってくれるんだ。\nまあ、たまに見返りを求めたりもするが、大したことじゃねえ、ひっく！\nへへ、ファツィオがどれだけドゥブロン持ってるか知ってるか？あははは！ カリブ一番の酒場で一生遊んで暮らせるくらいさ、働かずに世界一のラムを飲みながらな。でも奴はここ、 島に居続けてる。どうやら、いくら金があっても足りねえみたいだな…";
			link.l1 = "了解だ…";
			link.l1.go = "int_quests";
			npchar.quest.answer_3 = "true";
			SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;
		
		case "ansewer_4":
			dialog.text = "出て行く？ひっく！なぜだよ？いや、俺は本土にもヨーロッパにも、世界のどんな貧乏くさい島にも行きたくねえ。 あっちにタダのラム酒があるか？ねえよ！タダのラムなんて……ひっく！つまり、俺にはあっちに用はねえってことさ……相棒、俺はここで十分だぜ。なあ、ひっく！みんなにこの場所を出たいか聞いてみろよ。誰も出たがらねえさ、 二人か三人を除いてな……ひっく！";
			link.l1 = "「面白いな……」";
			link.l1.go = "int_quests";
			npchar.quest.answer_4 = "true";
		break;
// <-- блок вопросов и ответов
		
//----------------------------------------- специальные реакции -----------------------------------------------
		//обнаружение ГГ в сундуках
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("おい、豚野郎、俺の――ひっく！――隠し酒に手を出すんじゃねえ！", "レナードが酒飲みだからって、盗めると思ってんのか？ああ？見せてやるよ！", "俺の宝箱から離れろ！誰に送り込まれたんだ、あのデブのファジオか！？");
			link.l1 = "この酔っ払い野郎め！";
			link.l1.go = "fight";
		break;
		
		case "Woman_FackYou":
			dialog.text = "俺の宝箱に触るんじゃねえ、この悪党め！";
			link.l1 = "「愚かな娘め！」";
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
			dialog.text = LinkRandPhrase("なあ、旦那、剣をしまいなよ、ひっく……誰かケガさせちまうぜ。", "酔ってないな……剣を持つほど酔っちゃいないだろう。しまって、こっちで一杯やろうぜ。", "そんなふうに剣を振り回してると、本当に嫌な奴に見えるぜ。しまえよ、ひっく……しまっとけ。");
			link.l1 = LinkRandPhrase("いいだろう。", "わかった。", "クソ野郎……わかったよ。");
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;	
		
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = NPCharSexPhrase(NPChar, "聞けよ、おい、ひっく……そんなふうに剣を振り回しちゃダメだぜ。やめとけって。", "酔ってないな……剣を持つほど酔っ払ってねえ。しまって、こっちで一杯やろうぜ。");
				link.l1 = LinkRandPhrase("「いいだろう。」", "ああ、いいぜ。", "おっしゃる通りだな……");
			}
			else
			{
				dialog.text = NPCharSexPhrase(NPChar, "なあ、旦那、剣をしまえよ、ひっく……誰かケガさせちまうぜ。", "そんなふうに剣を振り回してると、本当に嫌な奴に見えるぜ。しまえよ、ひっく……しまっとけって。");
				link.l1 = RandPhraseSimple("すまない。", "俺はそれを片付けてるところだ。");
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
