// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("さあ、何の用だ？","ちょうどその話をしていたところだ。忘れてしまったんじゃないか…","今日はその質問を持ち出すのはこれで三度目ですよ……","聞け、ここは店だ。人々はここで物を買うんだ。邪魔しないでくれ！","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("「知っているだろう、」 "+NPChar.name+"、また今度かもしれませんね。","そうだ、なぜか忘れてしまったんだ……","ああ、本当にこれで三度目だな……","ふむ、俺はやらない……",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			//Jason --> ----------------------------------мини-квест Бесчестный конкурент------------------------------------
			if (CheckAttribute(pchar, "questTemp.Shadowtrader"))
			{
				if(pchar.questTemp.Shadowtrader == "begin" && GetNpcQuestPastDayParam(npchar, "Shadowtrader_date") < 5 && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "ご依頼を果たしていただき、ありがとうございます、船長。さて、今や "+pchar.questTemp.Shadowtrader.Guardername+" ここにいると、少しは安心できる。";
					link.l1 = "ふむ……お節介に思われたくはありませんが、どうやら何かお困りのようですね。よろしければ事情をお聞かせいただけませんか――もしかするとお力になれるかもしれません。"; 
					link.l1.go = "Shadowtrader_fort";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.Trouble") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "それで？俺の手紙は届けてくれたか？";
					link.l1 = "あります。司令官は口頭で、あなたの書簡に記された証拠では市警備隊が行動を起こすには不十分だと返答しました。"; 
					link.l1.go = "Shadowtrader_trouble";
					pchar.quest.ShadowtraderTimeFort_Over.over = "yes";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Fort") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store" && CheckAttribute(pchar, "questTemp.Shadowtrader.EndFort"))
				{
					dialog.text = "もうすでに聞いております――今夜、衛兵たちが密輸業者の違法な取引所を発見し、全員を逮捕しました。 あれは滅多にいないほどの悪党が仕切っていましたが、もう大丈夫です。しばらくの間、誰にも害を及ぼせないでしょう。 \n司令官からあなたの活躍についても聞きました。本当に感謝いたします！約束を守ってくれましたね！さあ、 これを受け取ってください――1万5千ペソです。あなたは私を救ってくれました。もはや私の商売を脅かすものはありません！";
					link.l1 = "どういたしまして。簡単なことでした。"; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Escape") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "それで、何か良い知らせはあるか、 "+pchar.name+"?";
					link.l1 = "あなたのライバルを見つけた。もう二度とあなたの邪魔にはならない――俺がうまく説得して、この島を去らせたんだ。奴の「店」は街門近くの家にあった。 置き去りにされた積荷をどうするかは、あなた次第だ。役人に引き渡すもよし、自分で回収を試みるもよし。"; 
					link.l1.go = "Shadowtrader_Escape_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Free") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "すでにその知らせは聞きました――今夜、衛兵たちが家の一つの地下で密輸業者の隠れ家を発見したそうです。二人の悪党が死体で見つかったとか。 素晴らしい働きですね。 "+pchar.name+"、あなたには感服します！さあ、報酬の1万5千ペソを受け取ってください。あなたは私を救ってくれました！これで本格的に商売ができます！\nひとつ気になるのですが……あの二人の死者の中に、あいつらの頭もいましたか？";
					link.l1 = "いいえ。しかし、あいつは二度とあなたの町に顔を出さないでしょう。 今ごろはこの島から何十マイルも離れた場所にいるはずです。"; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
				if(CheckAttribute(pchar, "questTemp.Shadowtrader.End.Kill") && NPChar.location == pchar.questTemp.Shadowtrader.City + "_store")
				{
					dialog.text = "すでにその知らせは聞いております――昨夜、衛兵たちがある家で密輸業者の秘密の店を発見しました。三人の悪党が死体で見つかりました。 見事な働きぶりです。 "+pchar.name+"、感心したぞ！ほら、報酬の1万5千ペソだ。お前は俺を救ってくれた！これで本気で商売できるってもんだ！\nちょっと気になるんだが……奴らの頭目も、その死んだ二人の中にいたのか？";
					link.l1 = "ああ。これで永遠にライバルを排除したな。もう二度とお前を悩ませることはないだろう。"; 
					link.l1.go = "Shadowtrader_complete";
					break;
				}
			}
			//<-- мини-квест Бесчестный конкурент
		break;
		
		// --> мини-квест Бесчестный конкурент
		case "Shadowtrader_begin":
			pchar.questTemp.Shadowtrader = "true";
			pchar.questTemp.Shadowtrader_Block = true;
			pchar.questTemp.Shadowtrader.Guardername = GenerateRandomName_Generator(sti(npchar.nation), "man");
			dialog.text = "酒場に行って、という名の男を探してくれませんか "+pchar.questTemp.Shadowtrader.Guardername+" できるだけ早くここに来るように彼に伝えてくれないか？私は店を離れられないし、 あの間抜けは酒場でラムを飲みまくっている。きっと当番なのにここに来ることすら考えていないだろう。";
			link.l1 = "助けになれて嬉しいぜ、相棒――どうせ酒場に行くつもりだったからな。";
			link.l1.go = "Shadowtrader_begin_1";
			link.l2 = "俺をからかってるのか？俺が使いっ走りに見えるのか？酒場はここからほんの数歩だぜ――自分で行けよ。";
			link.l2.go = "exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
		break;
		
		case "Shadowtrader_begin_1":
			dialog.text = "ありがとうございます！すぐにここへ来るよう彼に伝えてください。ああ、まったく、 どうしてあの人はこんなに手間をかけさせるのかしら……";
			link.l1 = "心配するな。俺がそいつをお前のところに行かせる。";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.City = npchar.City;
			pchar.questTemp.Shadowtrader.nation = sti(npchar.nation);
			//создаем охранника
			sld = GetCharacter(NPC_GenerateCharacter("ShadowGuarder" , "officer_7", "man", "man", 10, sti(npchar.nation), 5, true, "quest"));
			FantomMakeCoolFighter(sld, 20, 50, 50, "topor_2", "pistol3", "bullet", 50);
			sld.name = pchar.questTemp.Shadowtrader.Guardername;
			sld.lastname = "";
			sld.dialog.FileName = "Quest\LineMiniQuests\ShadowTrader.c";
			sld.dialog.currentnode = "ShadowGuarder";
			sld.greeting = "pirat_common";
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator(pchar.questTemp.Shadowtrader.City + "_tavern", "sit_front1");
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "sit", "sit_front1");
			SaveCurrentNpcQuestDateParam(npchar, "Shadowtrader_date");
			AddLandQuestMark(sld, "questmarkmain");
		break;
		
		case "Shadowtrader_fort":
			dialog.text = "ああ、船長、あなたの助けを本当に感謝します。この手紙をできるだけ早く司令官に届けていただけませんか？ この些細な仕事に対して300枚のコインをお支払いします――すでに申し上げた通り、私は店を離れることができませんので。";
			link.l1 = "問題ない。その手紙を渡してくれ。";
			link.l1.go = "Shadowtrader_fort_1";
			link.l2 = "いや、旦那、もうそんな戯言に付き合ってる暇はないんだ。";
			link.l2.go = "Shadowtrader_fort_end";
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_fort_1":
			dialog.text = "どうぞ。今日中に彼に渡して、返事を持ってきてください。";
			link.l1 = "心配するな、俺がやる。";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "letter_1");
			ChangeItemDescribe("letter_1", "itmdescr_letter_1"); // 240912
			pchar.questTemp.Shadowtrader.Tradername = GetFullName(npchar);
			SetFunctionTimerCondition("ShadowtraderTimeFort_Over", 0, 0, 1, false);
			pchar.questTemp.Shadowtrader = "current"
			pchar.questTemp.Shadowtrader.Fort = "true";
			AddQuestRecord("Shadowtrader", "1");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
		break;
		
		case "Shadowtrader_fort_end":
			dialog.text = "どうやら他の人に聞くしかなさそうですね。お手数をおかけしてすみません、船長。";
			link.l1 = "問題ない。じゃあな！";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader = "true";
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
		break;
		
		case "Shadowtrader_trouble":
			dialog.text = "あいつがそう言ったのか？それで、俺にどんな証拠が必要だっていうんだ！？俺の死体か？このままじゃ、 すぐにそうなるぜ…";
			link.l1 = "「おいおい、」 "+npchar.name+"落ち着いてください、そうしないと卒中を起こしますよ。さあ、水でも飲んで……さて、どうしましたか――もしかしたらお力になれるかもしれませんよ？";
			link.l1.go = "Shadowtrader_trouble_1";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.Trouble");
			DelLandQuestMark(npchar);
		break;
		
		case "Shadowtrader_trouble_1":
			dialog.text = "ああ、船長！どうぞ、あなたの300ペソを受け取ってください――危うく忘れるところでした……もちろんお話ししますが、あなたにどう助けていただけるのか分かりません。私の商売はほとんど潰れかけています――すべてあの忌々しい密輸業者どもと、奴らを率いる正体不明のろくでなしのせいです。";
			link.l1 = "「密輸業者か？」";
			link.l1.go = "Shadowtrader_trouble_2";
			AddMoneyToCharacter(pchar, 300);
		break;
		
		case "Shadowtrader_trouble_2":
			dialog.text = "それだ！あの悪党どもは明らかに俺をこの町から追い出そうとしてやがる！それまではいつも通りだった――禁止品を転売し、巡回隊に見つかれば隠れるか賄賂を渡していた。だが最近、どこか裏通りに店を開いて、 人気商品を信じられない安値で売り始めやがったんだ！\n俺にはそんな贅沢はできねえ――税金だって払わなきゃならねえし――じわじわと身を削ってるってのに、水夫たちはもうほとんど俺の品なんて欲しがらねえ――全部あのごろつきどもから買ってやがるんだ。";
			link.l1 = "「しかし、当局に訴えるべきだったでしょう！結局のところ、こうした無法を止めるのは彼らの仕事ですから。」";
			link.l1.go = "Shadowtrader_trouble_3";
		break;
		
		case "Shadowtrader_trouble_3":
			dialog.text = "あなた自身が前回の嘆願の結果を見ただろう。総督は忙しすぎるし、 司令官は密輸業者が裏通りで店を開いているなんて信じなかった、あるいは信じていないふりをしている――まあ、そういうことだろうな\nもちろん、なぜそんなことをする必要がある？だが私は言うね： きっと俺を破滅させて町から追い出そうとする悪党が全部考え出したんだ、そして奴は静かに俺の商売を乗っ取って、 自分の汚い手をきれいにするつもりなんだよ。";
			link.l1 = "ふむ……あなたの意見も一理ありますな。商人というものは、誰かを利用するのが性分でして……あっ、失礼、もちろんあなたのことではありませんよ。 ";
			link.l1.go = "Shadowtrader_trouble_4";
		break;
		
		case "Shadowtrader_trouble_4":
			dialog.text = "ああ、何でもない……最近、どこぞのガキがやってきて、図々しく「これ以上騒ぎ立てるなら店に火をつけるぞ」と言いやがったんだ。\nだから用心棒を雇ったのさ。 "+pchar.questTemp.Shadowtrader.Guardername+" 安くはないが、あいつはプロだし、あいつの護衛下なら少しは安心できるんだ。";
			link.l1 = "なるほど……確かに不愉快な話ですね。どうやらあなたの言う通り、私にできることは何もなさそうです。しかし、 それでも物事はいずれ解決すると私は確信しています――そういった胡散臭い店はたいてい長続きしませんから。\nでは、ご武運を！";
			link.l1.go = "Shadowtrader_end";
			link.l2 = "なるほど。まあ、まだお力になれるかもしれませんね……";
			link.l2.go = "Shadowtrader_trouble_5";
		break;
		
		case "Shadowtrader_trouble_5":
			dialog.text = "それでも俺に助けを申し出てくれるのか？\nだが、お前はどうするつもりだ？";
			link.l1 = "あんたのその「同業者」を探して……あんたの邪魔をやめさせるよう説得してみるぜ。俺はな、人を説得する腕にはちょっと自信があるんだよ。";
			link.l1.go = "Shadowtrader_trouble_6";
		break;
		
		case "Shadowtrader_trouble_6":
			dialog.text = "本気ですか？主があなたの正義のために祝福を与えんことを！あの汚らわしい連中を追い払ってくれたら、 私はあなたに借りができるでしょう。";
			link.l1 = "よし、取引成立だな。じゃあ、さっそく探し始めるとしよう。";
			link.l1.go = "exit";
			pchar.questTemp.Shadowtrader.seeksmugglers = "true";
			AddLandQuestMark(characterFromId("BasTer_Smuggler"), "questmarkmain");
			AddQuestRecord("Shadowtrader", "2");
			AddQuestUserData("Shadowtrader", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Shadowtrader.City+"Gen"));
			AddQuestUserData("Shadowtrader", "sSex1", GetSexPhrase("ся","ась"));
		break;
		
		case "Shadowtrader_end":
			pchar.questTemp.Shadowtrader = "true";
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
			DialogExit();
		break;
		
		case "Shadowtrader_Escape_complete":
			dialog.text = "本当ですか？これで安心して商売ができますね？ああ、本当にありがとうございます！これがあなたへの報酬です――1万5千ペソ。あの家にある品物については、司令官に引き渡すのが一番でしょう。改めて感謝します！";
			link.l1 = "どういたしまして。そんなに難しくなかったよ。俺は説得が得意だって言っただろう。";
			link.l1.go = "Shadowtrader_complete";
		break;
		
		case "Shadowtrader_complete":
			dialog.text = "またお越しください、船長。いつでもお会いできて嬉しいですよ。";
			link.l1 = "もちろんです！それでは、これにて失礼いたします――やるべきことがありますので！ごきげんよう、商売繁盛をお祈りします。 "+npchar.name+"!";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Shadowtrader.End");
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.Shadowtrader = "complete";
			AddQuestRecord("Shadowtrader", "11");
			AddQuestUserData("Shadowtrader", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("Shadowtrader");
			DeleteAttribute(pchar, "questTemp.Shadowtrader_Block");
			DeleteAttribute(pchar, "questTemp.Shadowtrader.EndFort");
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("BasTer");
		break;
		//<-- мини-квест Бесчестный конкурент
	}
	UnloadSegment(NPChar.FileDialog2);
}
