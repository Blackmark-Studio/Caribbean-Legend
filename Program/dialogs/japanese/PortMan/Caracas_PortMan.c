// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("どんな質問だ？","何の用だ、 "+GetAddress_Form(NPChar)+"?"),"もうすでに俺に質問しようとしただろ "+GetAddress_Form(NPChar)+"...","今日はこれで三度目の質問だな……","港の用件について何も話すことがないなら、俺に質問してくるんじゃねえぞ。","ブロック",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("考えを変えた。","話すことは何もねえ。"),"気にするな。","確かに、これでもう三度目だな……","悪いが、今は港の用事には興味がないんだ。",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			
			// belamour legengary edition на пару с Акулой -->
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet"))
			{
				if(pchar.questTemp.SharkGoldFleet == "toCarPortOffice" || pchar.questTemp.SharkGoldFleet == "start" || pchar.questTemp.SharkGoldFleet == "afterGvik" || pchar.questTemp.SharkGoldFleet == "buyincar")
				{
					link.l1 = "実はな、俺は今にもポルトベロへ出航するところなんだ。植民地であんたから仕入れた品を積んでな。道中、 もし運ぶ荷や引き受けられる仕事があればと思って声をかけたんだ……もちろん、報酬はいただくぜ。";
					link.l1.go = "SharkGoldFleet";
				}
				if(pchar.questTemp.SharkGoldFleet == "LightVar")
				{
					if(!bImCasual) pchar.quest.SharkGoldFleetToCPO10.over = "yes";
					link.l1 = "またお会いしましたね。あなたの手紙はポルトベロに届けました。そこで、あなたへの返事を託されました。";
					link.l1.go = "SharkGoldFleet_09";
				}
				if(pchar.questTemp.SharkGoldFleet == "DifficultVar")
				{
					if(!bImCasual) pchar.quest.SharkGoldFleetToCPO10.over = "yes";
					link.l1 = "こんにちは。私はポルトベロから来ました。地元の港湾当局の同僚がこの手紙をあなたに渡すよう頼みました。";
					link.l1.go = "SharkGoldFleet_13";
				}
			}
			//<-- на пару с Акулой
		break;
		
		// belamour на пару с Акулой -->
		case "SharkGoldFleet":
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet.Fail21"))
			{
				pchar.questTemp.SharkGoldFleet = "toCurierDie";
				AddQuestRecord("SharkGoldFleet", "5");
				SGF_CreateCurierInWorld("");
				dialog.text = "ご心配いただきありがとうございますが、そのような案件はありません。実は一件だけ依頼がありましたが、 あなたは本当にあと数日遅かったのです。そのために私は急ぎの伝令用ラガー船を送り出しました。";
				link.l1 = "分かった……まあ、ありがとな。";
				link.l1.go = "exit";
			}
			else
			{
				if(!bImCasual) pchar.quest.SharkGoldFleet21.over = "yes"; 
				if(!bImCasual) pchar.quest.SharkGoldFleet30.over = "yes"; 
				if(GetCompanionQuantity(pchar) > 1)
				{
					pchar.questTemp.SharkGoldFleet = "toCurierWait";
					AddQuestRecord("SharkGoldFleet", "10");
					SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
					dialog.text = "船一隻も持っていないようだな。裕福な商人か？ふむ……だが、このあたりの艦隊持ちの商人は顔で全部覚えているが、お前のことは知らねえ。だから悪く思うなよ、 だが大事な仕事は任せられねえんだ。";
					link.l1 = "了解だ…まあ、ありがとな。";
					link.l1.go = "exit";
				}
				else
				{
					if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
					{
						pchar.questTemp.SharkGoldFleet = "toCurierWait";
						AddQuestRecord("SharkGoldFleet", "11");
						SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
						dialog.text = "ふむ……仕事があるんだが、今のお前の船じゃ条件に合わねえ。速さと力強さ、両方を兼ね備えた船が必要なんだが、 お前のはどちらも同時には満たしてねえんだ。少なくとも今はな。だから、勘弁してくれよ。";
						link.l1 = "了解だ……まあ、ありがとな。";
						link.l1.go = "exit";
					}
					else
					{
						if(!CheckAttribute(pchar,"questTemp.SharkGoldFleet.LicenceOk"))
						{
							pchar.questTemp.SharkGoldFleet = "toCurierWait";
							AddQuestRecord("SharkGoldFleet", "12");
							SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
							dialog.text = "俺にはやることがある……それにお前の船はいい船だ。ただ、どう見ても商船には見えねえな。しかも、 オランダ西インド会社の長期許可証も持ってないようだ。悪く思うなよ、だがどう見ても商人には見えねえ。 俺はそのリスクは取れねえんだ。";
							link.l1 = "わかった……まあ、ありがとな。";
							link.l1.go = "exit";
						}
						else
						{
							if(pchar.questTemp.SharkGoldFleet != "toCarPortOffice" || GetSquadronGoods(pchar, GOOD_COFFEE) < 300 || GetSquadronGoods(pchar, GOOD_CHOCOLATE) < 300)
							{
								pchar.questTemp.SharkGoldFleet = "toCurierWait";
								AddQuestRecord("SharkGoldFleet", "13");
								SetFunctionTimerCondition("SGF_CreateCurierInWorld", 0, 0, 1+rand(2), false);
								dialog.text = "俺にはやることがある……それに、お前の船はいい船だ。ただ、何を取引するつもりなのかが分からねえ……お前はポルトベロに商品を売りに行くと言ったが、俺の知る限り、植民地でうちから商品を買ったわけじゃねえだろう。 悪く思うなよ、だがどう見ても商人には見えねえんだ。俺はそのリスクは取れねえ。";
								link.l1 = "分かった……まあ、ありがとな。";
								link.l1.go = "exit";
							}
							else
							{
								dialog.text = "私にはやることがあるんだ。当然だが、あんたのことは知らねえ……だが正直に言うと、俺が覚えてるのは艦隊を率いる商人だけさ。その他の連中は覚えちゃいねえ。それに、 あんたは長期の許可証を持ってるから、経験豊富な商人だってことは明らかだ。だが、あんたの船は興味深いな。 なぜフリゲートで交易してるんだ？";
								link.l1 = "ははっ、こいつはただのフリゲートじゃねえぜ。積荷が満載でもとんでもない速力を出せるんだ。 海賊から逃げる方が戦うよりずっと楽だろう？\n俺の船は普通の商船より積載量は少ねえが、その分リスクはずっと低いのさ。";
								link.l1.go = "SharkGoldFleet_01";
							}
						}
						
					}
					
				}
			}
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "ふむ、だが確かにその通りだな！スペイン人は船の造り方をよく知っているじゃねえか？そうだ、そうだ、 この立派な船がうちの造船所から出たものだとすぐに分かったぜ。それに、今日ちょうど聞いたんだが、 あんたがうちの商人からコーヒーとカカオをまとめて買って、ポルトベロで転売するつもりだってな。いい取引だぜ。 商売を知らねえ連中は、こっちじゃプランテーションのおかげでこういう品が安いってことも、 ポルトベロじゃ大人気だってことも分かっちゃいねえ。あそこから本国に運ばれるからな。\n";
			link.l1 = "まあ、そういうことさ、旦那。たった数ペソじゃ、俺の船をそんな遠くまで出す気にはなれねえよ。";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "そうだな、実を言うとお前に頼みたい仕事があるんだぜ。しかも、お前の船は速い上に、 いざという時には自分で身を守れるってのは本当にありがたいことだ。";
			link.l1 = "待てよ、旦那……あんたの話だと、俺が戦わなきゃならねえってことか……？";
			link.l1.go = "SharkGoldFleet_03";
		break;
		
		case "SharkGoldFleet_03":
			dialog.text = "いや、いや！実は、俺の頼みはできるだけ簡単なんだ。ポルトベロの港湾局に手紙を届けてほしい。\n手紙は封印されていて、絶対に開けてはいけない。誰にも話す必要はない、このやり取りは……個人的なものだ。\n必ず直接手渡してくれ。期限は十日間だ。それを過ぎたら、もう意味がなくなる。";
			link.l1 = "そんなに簡単なのか？それで俺はいくらもらえるんだ？";
			link.l1.go = "SharkGoldFleet_04";
		break;
		
		case "SharkGoldFleet_04":
			dialog.text = "五千ペソだ。ポルトベロまで伝令船を出さずに済んだ分の支払いと思ってくれ。";
			link.l1 = "「それで、俺と俺の船について何を聞きたかったんだ？」";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			dialog.text = "気にしないでくれ。ただ、この書簡は重要だから、確実に宛先に届くようにしなければならんのだ。だから、 特に変わったことはない。官僚仕事さ……普通の人には、こういう書類なんて興味もないだろう。";
			link.l1 = "そうだな、同意するぜ。書類をここに用意しよう。俺がポルトベロに着き次第、お前の同僚に届ける。 十日以内に何とかするから、心配すんな。";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			dialog.text = "少々お待ちください。申し訳ありません、あなたのお名前をすっかり忘れてしまいました。\n教えていただけますか？書類に記載する必要があるのです。";
			link.l1 = "俺の名はアンドレアス・ガルシアだ。";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "ありがとうございます。さて……よろしい。覚えておけ、この書類を届けるのはお前自身だ、しかも必ず宛先本人の手に直接渡すんだ。はい、これだ。 報酬はポルトベロの港湾局長が渡してくれる。良い旅を！";
			link.l1 = "ありがとうございます！では、失礼します。";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			DialogExit();
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleetToPB10", 0, 0, 10, false);
			else NewGameTip("Exploration mode: timer is disabled.");
			AddCharacterSkillDontClearExp(pchar, SKILL_LEADERSHIP, 1);
			AddCharacterSkillDontClearExp(pchar, SKILL_SNEAK, 1);
			TakeNItems(pchar, "letter_1", 1);
			ChangeItemDescribe("letter_1", "itmdescr_letter_SharkGoldFleet_1");
			AddQuestRecord("SharkGoldFleet", "14");
			pchar.questTemp.SharkGoldFleet = "toPBPortOffice";
		break;
		
		case "SharkGoldFleet_09":
			RemoveItems(PChar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_2");
			dialog.text = "素晴らしい！とても助かったよ。何か困ったことはあったか？";
			link.l1 = "いいえ、特に問題はありませんでした。ただし、あなたの同僚はあなたを罵っていましたよ。 ここは全員ケチだと言っていました――というのも、急使船を送らずに商船に託すうえ、受取人にまで料金を請求するからだそうです。 ハバナに苦情を書いてやるとまで脅していました……\n";
			link.l1.go = "SharkGoldFleet_10";
		break;
		
		case "SharkGoldFleet_10":
			dialog.text = "「なんだと！？俺が偏屈者だと！？あいつは自分を何様だと思ってやがるんだ？まずはその五千…いや、六千ペソでも取っておけ！俺は本当に泣いてるんだぜ！」";
			link.l1 = "ありがとうございます。あなたの同僚があなたについて誤解していたことが分かってよかったです。";
			link.l1.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_11":
			AddMoneyToCharacter(pchar, 6000);
			dialog.text = "そしてもう一つ、このろくでなしは二ヶ月前、カラカスからポルトベロへ、 さらにそこからハバナへ航海した商船の維持費を全部俺に押し付けたことを忘れてやがる！ 後半の旅費はあいつが払うって約束だったんだぜ！借金は一度も返さず、先月には全部清算すると言ってたくせによ！ それでいてケチ呼ばわりされるのは俺の方か……。よし、自分でハバナに訴状を書いてやる！";
			link.l1 = "まあ、そりゃあマドリード宮廷の情熱を持ってるんだろうな……";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			AddQuestRecord("SharkGoldFleet", "20");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date)
			pchar.questTemp.SharkGoldFleet = "LightVarToShark";
			SetFunctionLocationCondition("SharkGoldFleetToShark", "Curacao", false);
			dialog.text = "いや、今思い返せば……なんて図々しい奴だ！まあいい、またあいつの相手をしてやるさ……さて、これで失礼する。これから急ぎの用があるんだ。君と取引できて楽しかったぜ！";
			link.l1 = "「幸運を祈るぜ！」";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_13":
			RemoveItems(PChar, "letter_2", 1);
			ChangeItemDescribe("letter_2", "itmdescr_letter_2");
			dialog.text = "素晴らしい！君は本当に助かったよ。まあ、俺はあいつらに伝令用のラガー船を送ったんだが、 向こうは通りすがりの船で返事をよこしてきたんだ。うん……それでいて、まだこっちにケチが座ってるって文句を言ってくるんだぜ。";
			link.l1 = "まあ、伝令のための金を節約したのかもな……";
			link.l1.go = "SharkGoldFleet_14";
		break;
		
		case "SharkGoldFleet_14":
			AddMoneyToCharacter(pchar, 5000);
			AddQuestRecord("SharkGoldFleet", "20");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date)
			pchar.questTemp.SharkGoldFleet = "DifficultVarToShark";
			SetFunctionLocationCondition("SharkGoldFleetToShark", "Curacao", false);
			dialog.text = "「たぶん」じゃなくて、間違いなくそうだって言ってるんだ！まあ、どうでもいいさ。ほら、仕事を受け取れ。さて、 俺も忙しいんでな、失礼するぜ。";
			link.l1 = "まあ、伝令に使う金は節約したのかもな……";
			link.l1.go = "exit";
		break;
		// <-- на пару с Акулой
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
