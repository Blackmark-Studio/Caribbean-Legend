// диалоги персонажей по квесту Мангароса
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
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
		
		// Амелия - знахарка-цыганка
		case "amelia":
			dialog.text = "俺の家で何の用だ？";
			if (CheckAttribute(pchar, "questTemp.Mangarosa") && pchar.questTemp.Mangarosa == "amelia")
			{
				link.l1 = "あんたの名前はアメリアだろ？ちょっと植物のことで聞きたいんだ。マンガローザってやつさ。";
				link.l1.go = "amelia_1";
			}
			else
			{
				link.l1 = "まだ話せることは何もない。だが、いつか必ず戻ってくるさ……";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "amelia";
		break;
		
		case "amelia_1":
			dialog.text = "面白いな！それで、誰が俺のことを教えたんだ、勇敢な若造？";
			link.l1 = "お前の仲間の一人だ。あの女が言ってたんだ、この植物の秘密を知っていて、特別な薬の作り方を教えてくれるって……";
			link.l1.go = "amelia_2";
		break;
		
		case "amelia_2":
			dialog.text = "まずは、お前が言っているその植物を見せてみろ。もしかしたら何も知らずに俺の時間を無駄にしてるだけかもしれねえ。 お前のマンガローザはどこだ？";
			if (CheckCharacterItem(pchar, "cannabis7"))
			{
				link.l1 = "ほら、見てみろ。";
				link.l1.go = "amelia_3";
			}
			else
			{
				link.l1 = "ふむ……";
				link.l1.go = "amelia_exit";
			}
		break;
		
		case "amelia_exit":
			dialog.text = "それで、俺に何を見せるつもりだったんだ？マンガ・ロサは持ってねえだろう。だから、とっとと出ていけ、相棒、 俺の機嫌が悪くなる前にな。この話はもう終わりだ。";
			link.l1 = "しかし……";
			link.l1.go = "exit";
			NextDiag.TempNode = "amelia_wait";
		break;
		
		case "amelia_wait":
			dialog.text = "またお前か？騒ぎを起こすんじゃねえぞ、坊主…";
			if (CheckCharacterItem(pchar, "cannabis7"))
			{
				link.l1 = "落ち着いてくれ、アメリア。前回どこかに落としたに違いない。ほら、マンガローザを持ってきたぞ。見てみな。";
				link.l1.go = "amelia_3";
			}
			else
			{
				link.l1 = "...";
				link.l1.go = "amelia_exit";
			}
			NextDiag.TempNode = "amelia_wait";
		break;
		
		case "amelia_3":
			dialog.text = "そうか……何か知っているようだな。で、俺の薬の秘密を教えてほしいってのか？";
			link.l1 = "その通りだ。しかも、タダじゃないんだろう……";
			link.l1.go = "amelia_4";
		break;
		
		case "amelia_4":
			dialog.text = "わかってるじゃねえか、若造！全くの馬鹿には見えねえな。まあ、知識を求めて、 この貴重な草をくだらねえ煙草なんかに無駄遣いしねえ奴なら、俺が教えてやってもいいぜ…";
			link.l1 = "アメリア、交渉を始める前に……マンガローザから作れる薬の基本的な知識を教えてもらえないか？";
			link.l1.go = "amelia_5";
		break;
		
		case "amelia_5":
			dialog.text = "値切りはなしだぜ、相棒。俺が値段を言う、それを払うかどうかはお前の決めることだ。値引きや割引なんて期待するな、 ここは市場じゃねえからな。\nそれで、お前の質問についてだが……マンガローザの特別な薬を作ることができる。それはお前の身体能力を強化するんだ。もっと力強くなったり、 持久力や速さが増したりするし、全身を変化させて全ての面で強くなる薬もある。ただし、 その場合は前の二つより効果が弱くなるぜ。";
			link.l1 = "興味深いな。値段を言え。";
			link.l1.go = "amelia_6";
		break;
		
		case "amelia_6":
			dialog.text = "俺が三つのレシピを教えてやるぜ。\n一つのレシピごとに、植物一つと金貨五百枚をもらうぞ。";
			link.l1 = "その薬についてもっと詳しく教えてくれ。\nそれぞれはどんな効果があるんだ？";
			link.l1.go = "amelia_7";
		break;
		
		case "amelia_7":
			dialog.text = "たった一つのポーションを調合するにも、錬金術の達人でなければならない。各ポーションの効果は、 飲むタイミングによって二日以内しか持続しない。もし真夜中に飲めば、ほぼ丸二日間は効くぞ\n最初のポーションは、力と耐久力を高めてくれる。戦いが有利になり、受けるダメージも減り、 より多くの荷物を運べるようになる\n二番目のポーションは、素早さと敏捷性、持久力を高め、さらに狙いも良くなる\n三番目のポーションは、前の二つより効果は半分だが、魅力や自信、幸運も与えてくれる\nすべてのマンガローザを使ったポーションは健康にも良い影響をもたらす。ただし、一度に飲めるのは一種類だけだ。 決して混ぜてはいけない――逆効果どころか、ひどい中毒に苦しむことになるぞ\nさて、いい男さん、今すぐ知識の代金を払うかい？それとも考える時間が欲しいかい？";
			if (CheckCharacterItem(pchar, "cannabis7") && PCharDublonsTotal() >= 500)
			{
				link.l1 = "ああ、準備はできてるぜ。";
				link.l1.go = "amelia_8";
			}
			link.l2 = "少し考えさせてくれ。これは大きな決断だからな。";
			link.l2.go = "exit";
			NextDiag.TempNode = "amelia_next";
		break;
		
		case "amelia_next":
			if (!CheckAttribute(npchar, "quest.ChickenGod") && CheckCharacterItem(pchar, "talisman11")) {
				if (CheckAttribute(npchar, "quest.recipe_power") || CheckAttribute(npchar, "quest.recipe_fast") || CheckAttribute(npchar, "quest.recipe_total")) {
					link.chickengod = "Amelia, you seem to have a knack for such things. Can you tell me if there is a demand for such stones among your people? I find them everywhere - it's like everyone is obsessed with them!";
					link.chickengod.go = "chickengod";
				}
			}
			
			if (CheckAttribute(npchar, "quest.ChickenGod") && !CheckAttribute(npchar, "quest.ChickenGod.Complete") && GetCharacterItem(pchar, "talisman11") >= 113) {
				link.chickengod = "Here you go, Amelia. Just as you ordered: one hundred and thirteen adder stones.";
				link.chickengod.go = "chickengod_collected";
			}
		
			if (CheckAttribute(npchar, "quest.recipe_all"))
			{
				dialog.text = "ああ、君か、若者！それで、俺の薬は役に立ったか？";
				link.l1 = "本当にそうだったよ、アメリア。ありがとう！";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "ああ、君か、若者！レシピを買いたいのかい？";
				if (CheckCharacterItem(pchar, "cannabis7") && PCharDublonsTotal() >= 500)
				{
					link.l1 = "その通りだ。だから俺はここに来たんだ。";
					link.l1.go = "amelia_8";
				}
				
				link.l2 = "まだだよ、アメリア。ただ様子を見に来ただけさ。";
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "amelia_next";
		break;
		
		case "amelia_8":
			dialog.text = "承知した。どんなレシピを買いたいんだ？";
			if (!CheckAttribute(npchar, "quest.recipe_power"))
			{
				link.l1 = "筋力と耐久力のポーションの調合法。";
				link.l1.go = "power";
			}
			if (!CheckAttribute(npchar, "quest.recipe_fast"))
			{
				link.l2 = "敏捷と不屈の薬のレシピ。";
				link.l2.go = "fast";
			}
			if (!CheckAttribute(npchar, "quest.recipe_total"))
			{
				link.l3 = "複雑な薬のレシピ。";
				link.l3.go = "total";
			}
		break;
		
		case "power":
			dialog.text = "よし。「タイダルウェーブ」と名付けたぞ。ほら、これが使い方の説明書だ。しっかり読んでおけ。 正しい使い方を忘れるなよ！";
			link.l1 = "ありがとう、Amelia…";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosapower");
			SetAlchemyRecipeKnown("mangarosapower");
			npchar.quest.recipe_power = true;
		break;
		
		case "fast":
			dialog.text = "よし。名前は「スコール」にしたぜ。ほら、これが使い方の説明書だ。しっかり読んでおけよ。 正しい使い方を忘れるんじゃねえぞ！";
			link.l1 = "ありがとう、Amelia…";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosafast");
			SetAlchemyRecipeKnown("mangarosafast");
			npchar.quest.recipe_fast = true;
		break;
		
		case "total":
			dialog.text = "よし。「シーハグ」と名付けたぜ。ほら、この説明書を持っていけ。しっかり読んでおけよ。 使い方を忘れるんじゃねえぞ！";
			link.l1 = "ありがとう、Amelia...";
			link.l1.go = "recipe_exit";
			AddQuestRecordInfo("Recipe", "mangarosatotal");
			SetAlchemyRecipeKnown("mangarosatotal");
			npchar.quest.recipe_total = true;
		break;
		
		case "recipe_exit":
			DialogExit();
			NextDiag.CurrentNode = "amelia_next";
			RemoveDublonsFromPCharTotal(500);
			RemoveItems(pchar, "cannabis7", 1);
			Log_Info("You have given 500 doubloons and one Manga Rosa");
			PlaySound("interface\important_item.wav");
			if (CheckAttribute(npchar, "quest.recipe_power") && CheckAttribute(npchar, "quest.recipe_fast") && CheckAttribute(npchar, "quest.recipe_total"))
			{
				npchar.quest.recipe_all = true;
				CloseQuestHeader("mangarosa");
			}
		break;
		
		case "chickengod":
			dialog.text = "バックス・デ・アダーか、確かに！価値はほとんどねえが、分かる奴には使い道があるんだ。百十三個持ってきな、 そしたら俺の宝箱の一つを開けてやるぜ。";
			link.l1 = "そりゃあ、ただの岩の山じゃねえか！まず、なんでそんなもんが必要なのか教えてくれよ。";
			link.l1.go = "chickengod_1";
		break;
		
		case "chickengod_1":
			dialog.text = "いいえ、あなた、もし尋ねなければならないなら、その知識はまだあなたには役に立たないわ。";
			link.l1 = "「それで、お前がそんなに気前よく開けてやると約束したその箱の中身は何なんだ？」";
			link.l1.go = "chickengod_2";
		break;
		
		case "chickengod_2":
			dialog.text = "船長が自ら手を動かすのを厭わないなら役立つものが山ほどあるぜ。\n時間を無駄にするなよ、お嬢ちゃん、どうせそんなに小石は集められやしないんだからな。";
			link.l1 = "それはどうかな！";
			link.l1.go = "exit";
			
			npchar.quest.ChickenGod = true;
		break;
		
		case "chickengod_collected":
			dialog.text = "ハハハ！冗談だよ、坊や！";
			link.l1 = "お前の小屋で火あぶりにされる時、笑うのはこっちじゃなくてお前だぞ、魔女め！";
			link.l1.go = "chickengod_collected_1";
		break;
		
		case "chickengod_collected_1":
			dialog.text = "それがあたしの運命じゃないよ、あんた……あんたのおかげでこのジプシーは誇りに思ってるんだ！さあ、この箱はあんたの好きにしていいよ。";
			link.l1 = "ありがとう、アメリア。でも、君の古い下着以外に何か役立つものが入っているといいんだが……";
			link.l1.go = "exit";
			
			TakeNItems(pchar, "talisman11", -113);
			npchar.quest.ChickenGod.Complete = true;
			AddDialogExitQuestFunction("ChickenGod_AmeliaOpenChest");
		break;
	}
} 
