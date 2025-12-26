// Лукас Роденбург - вице-директор ГВИК
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl"))
			{
				dialog.text = "はっきり話せ、坊や。ただし手短にな。俺は忙しいんだ。";
				link.l1 = "船長を雇っていると聞いた。";
				link.l1.go = "Holl_start";	
			break;
			}
			dialog.text = "私に頼みたい仕事でもあるのか？";
			link.l1 = "いいえ、すまない。俺は行くぜ。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Second_time":
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.questTemp.HWIC.Holl == "BaltazarEsc")
			{
				dialog.text = "今ごろはシント・マールテンの半分まで行ってるはずだったんだぜ、カピテン。";
				link.l1 = "出航の準備をしているところだ、旦那。";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "BaltazarCom")
			{
				dialog.text = "おお、カピテン、そこにいたのか！来たのに気づかなかったよ、ちょうどリッデブロックの手紙を読み終えたところだ。 君はかなりの印象を残したらしい。彼は君のことを「商人たちの守護者にして海賊どもの災厄、会社への神の贈り物」 とまで称えている！これについてどう思う？";
				link.l1 = "俺はただの普通の船長でいたいんだ。普通――だが裕福な船長にな。";
				link.l1.go = "SantiagoTrip";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripBegin")
			{
				dialog.text = "なぜまだここにいるんだ、キューバへ向かっていないのか！？";
				link.l1 = "はいはい、今行きますよ、旦那。";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripFinal")
			{
				sld = characterFromId("Santiago_usurer");
				dialog.text = "ああ、カピテン！正直、心配し始めていたんだ。どうだった？";
				link.l1 = "苦労はあったが、それについては後で話そう。まずは仕事だ。旦那\n "+GetFullName(sld)+" 「こう伝えろと言われた。『この男は死なねばならない』と。 そうすればジェラルディはこの件を終わったものと見なすそうだ。それに、 この決定は彼らの家族の意志でもあると言っていた。」";
				link.l1.go = "SantiagoTrip_8";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripComplete")
			{
				dialog.text = "会えて嬉しいぜ、カピテン！俺に会いに来てくれてよかったぜ。";
				link.l1 = "ごきげんよう、旦那。さて、また会社の仕事をお持ちですか？";
				link.l1.go = "JacobBerg";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "JacobTakeShip")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED)
				{
					dialog.text = "船を停泊させろと言っただろうが。命令も守れねえほど馬鹿か、それとも無知なのか？";
					link.l1 = "どちらでもありません、旦那。私はこれから向かうところです。";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "さて、船を停泊させたのだな。では、俺のシーベックを貸してやろう。\nすぐにこの任務を始める準備はできているか？\n俺の船は装備も万全で、すぐに出航できる。お前が心配することは何もないぜ。";
					link.l1 = "はい、もちろんです。私は準備ができております、ローデンブルク旦那。";
					link.l1.go = "JacobBerg_6";
					DelLandQuestMark(npchar);
				}
			break;
			}
			if (pchar.questTemp.HWIC.Holl == "JacobLongway")
			{
				dialog.text = "なぜまだここにいるんだ？すぐにロンウェイに会いに行け。";
				link.l1 = "すまない、今向かっているところだ。";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MirageTake")//а вот теперь начинается дурдом с перебором кораблей
			{
				int iMir = 0;
				int iMef = 0;
				for(i = 0; i < COMPANION_MAX; i++)
				{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE) iMir = 1;
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG) iMef = 1;
				}
				}//установили признак наличия кораблей в эскадре.
				RemoveItems(PChar, "JacobJournal", 1);//удалим журнал ван Берга
				pchar.quest.MirageConvoyOver.over = "yes"; //снять таймер
				if (iMir == 1 && iMef == 0)//потеряли Мейфенг
				{
					dialog.text = "カピテン…あなたの航海についてはすでに承知しております。";
					link.l1 = "「へえ、本当かい？じゃあ、知ってるはずだな……」";
					link.l1.go = "Jacob_lostMef";
					DelLandQuestMark(npchar);
					break;
				}
				if (iMir == 0 && iMef == 1)//потеряли Мираж
				{
					dialog.text = "カピテン……あなたの航海についてはすでに承知しております。";
					link.l1 = "そうか？じゃあ、知ってるはずだな……";
					link.l1.go = "Jacob_lostMir";
					DelLandQuestMark(npchar);
					break;
				}
				if (iMir == 0 && iMef == 0)//а это вообще плохо
				{
					dialog.text = "カピテン……あなたの航海についてはすでに承知しております。";
					link.l1 = "そうか？じゃあ、知ってるはずだな……";
					link.l1.go = "Jacob_failFull";
					DelLandQuestMark(npchar);
					break;
				}
					dialog.text = "お待ちしておりました、カピテン……あなたの旅についてはすでにすべて承知しております。";
					link.l1 = "そうか？じゃあ、知ってるはずだな…";
			link.l1.go = "Jacob_complete";
			DelLandQuestMark(npchar);
			break;
			}
			if (pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "アンティグアへ行け。今すぐだ。";
				link.l1 = "すまない、今向かっているところだ。";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "FleetwoodSink" || pchar.questTemp.HWIC.Holl == "FleetwoodCapture")
			{//опять начинаем проверять корабли
				iMir = 0;
				for(i = 0; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if(iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
						if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE) iMir = 1;
					}
				}//установили признак наличия Миража в эскадре.
				pchar.quest.ToAntiguaOver.over = "yes"; //снять таймер
				if (iMir == 0)//потеряли Мираж
				{
					dialog.text = "ご到着の報告は受けている、カピテン。それに、私のミラージュ号を戦闘で失ったことも知っているぞ。";
					link.l1 = "よくご存知ですね、ローデンブルク旦那。私がどれだけ努力しても、彼女を救うことはできませんでした。";
					link.l1.go = "Fleetwood_fail";
					DelLandQuestMark(npchar);
				}
				else
				{
					dialog.text = "ご到着の報せは受けております、カピテン。ミラージュ号が無事に入港しているのを確認しました。良いことです。";
					link.l1 = "全て旦那のご指示通りにやりましたぜ。フリートウッドを殺せと命じられ、奴はもう死んでます。 ミラージュ号をこの港に戻せと言われ、ちゃんとここに連れてきました。";
					link.l1.go = "Fleetwood_complete";
					DelLandQuestMark(npchar);
				}
				pchar.quest.Meifeng_fail.over = "yes";
				Group_DeleteGroup("Meifeng_Empty");
				sld = characterFromId("MeifengCap");
				sld.lifeday = 0;//зачистим Мейфенг без китайца
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "Abby_prepare")
			{
				dialog.text = "ああ、来たな。会えて嬉しいぞ。約束通り、もう一つ任務を頼みたい。";
				link.l1 = "お聞きします、旦那。";
				link.l1.go = "Abby";
				DelLandQuestMark(npchar);
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.HWIC.Holl.LucasMoney") && pchar.questTemp.HWIC.Holl == "AbbyAgreeMarried")
			{
				dialog.text = "ああ、会えて嬉しいぞ、坊や。来るのが遅かったから心配し始めていたんだ。アビゲイルから何か聞き出せたか？";
				link.l1 = "それだけじゃありません、他の問題も解決しました。島も見つけましたし、 シニョール・シュヌールの失われた財宝も手に入れました。ソロモンも満足していますし、 アビゲイルもあなたの求婚を受けるでしょう。おめでとうございます、マイネール！";
				link.l1.go = "Abby_2";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "NotFindAbbyIsland")
			{
				dialog.text = "ああ、会えて嬉しいよ、友よ。アビゲイルから何か聞き出せたか？";
				link.l1 = "はい。アビゲイルと彼女の父親と話をしました。問題があるのです、旦那：彼女の父親は財産を失っています。 アビゲイルは自分があなたにふさわしくないと感じており、持参金のない娘があなたのような紳士と結婚すれば、人々 の噂や陰口を恐れています。ご理解いただけると幸いです。";
				link.l1.go = "Abby_6";
				DelLandQuestMark(npchar);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LucasMoney") && pchar.questTemp.HWIC.Holl == "AbbyAgreeMarried")
			{
				dialog.text = "ああ、友よ！良い知らせを持ってきてくれたと信じているが？";
				link.l1 = "君の計画はうまくいった。アビゲイルは承諾するだろう。おめでとう、旦那。";
				link.l1.go = "Abby_8";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MerdokStart")
			{
				dialog.text = "お待ちしておりました。坊や、お前は大変な危険にさらされているのだ。";
				link.l1 = "どういう意味だ？";
				link.l1.go = "Merdok";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MerdokDie")
			{
				dialog.text = "港の私の手下が、あなたが到着したと知らせてきた。ヨハン・ファン・メルデンは死んだのか？";
				link.l1 = "ああ。奴とその仲間はもういない。激しい戦いだったが、俺がやり遂げたんだ。";
				link.l1.go = "Merdok_4";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "これ以上話すことはない、カピテン。";
			link.l1 = "承知した、出発する。";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "何だ？時間は金だぞ。";
		link.l1 = "悪いけど、俺は行くぜ。";
		link.l1.go = "exit";
		break;
		
//------------------------------------------------1 задание--------------------------------------------
		case "Holl_start":
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Bridgetown_tavernkeeper"));
			DelLandQuestMark(characterFromId("Knippel"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			dialog.text = "そうかもな。お前は誰だ？さっさと話せ、時間は金だぞ。";
			link.l1 = "俺が船長だ "+pchar.name+"、俺の船と俺自身があんたの役に立てるぜ。";
			link.l1.go = "Holl_start_0";			
		break;
		
		case "Holl_start_0":
			dialog.text = "ふむ、坩堝で試験すべき未知の合金だな。";
			link.l1 = "だからこそ、私はここに来たのです、旦那。";
			link.l1.go = "Holl_start_1";			
		break;
		
		case "Holl_start_1":
			pchar.questTemp.HWIC.Holl.PirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = "よろしい、それではお前の度胸を見せてもらおうか。さて、名前も知らんカピテンよ、 バルタザール・リッデブルックを知っているか？知らんのか？それは幸運だな。 あいつみたいな欲深くて不機嫌で短気な馬鹿は、そうそう見かけるもんじゃねえ。\nだが、どうやらそんな際立った性質だけじゃ満足できなかったらしく、あの男は「フィリバスター」 と呼ばれる奴を怒らせるほどの知恵もあったようだ "+GetName(NAMETYPE_ORIG,pchar.questTemp.HWIC.Holl.PirateName,NAME_NOM)+" 地元の酒場で、被害者が剣に手をかけた瞬間に衛兵を呼びやがったんだ…";
			link.l1 = "…そして、その海賊は最初に手に入った縄で首を吊られたのか？";
			link.l1.go = "Holl_start_2";			
		break;
		
		case "Holl_start_2":
			dialog.text = "そんなに単純な話じゃない。 "+GetName(NAMETYPE_ORIG,pchar.questTemp.HWIC.Holl.PirateName,NAME_NOM)+" 普通の海賊じゃなくて、オランダの私掠船乗りだ。イギリスとの直近二度の戦争を経験した古参だぜ。 地元の納税者たちにはかなり好かれてる。リッデルブロックについては、同じことは言えねえな。";
			link.l1 = "「じゃあ、俺たちの私掠船乗りはまだ生きてるのか？」";
			link.l1.go = "Holl_start_3";			
		break;
		
		case "Holl_start_3":
			dialog.text = "ああ、でもあいつは本当に怒ってるんだ。だからリッデブロックはビビりまくってるんだよ。";
			link.l1 = "私の幸運もそろそろ尽きるのでしょうか。ミニール・リッデルブロックにはいつ会えるのですか？";
			link.l1.go = "Holl_start_4";			
		break;
		
		case "Holl_start_4":
			dialog.text = "間もなくのことだ。フィリップスブルフの善良な人々が砂糖の積荷を待っている――我々共通の知人リッデブロックが届けると約束したやつだ。あの男の価値なんぞ靴の革にも及ばんと思っているが、 残念ながら我々のために働いている。だから港の事務所へ行け。そこでリッデブロックを見つけて、 私の命令で今すぐ出航するよう伝えろ。\nお前は彼の後をつけて……無事にフィリップスブルフまで護衛しろ。私は "+GetName(NAMETYPE_ORIG,pchar.questTemp.HWIC.Holl.PirateName,NAME_NOM)+" 「彼の積荷と一緒に会社の評判をカリブの底に沈めるために。」";
			link.l1 = "うっ、護衛任務か。こんな気の進まない仕事の報酬はどうなるんだ？";
			link.l1.go = "Holl_start_5";			
		break;
		
		case "Holl_start_5":
			dialog.text = "船長、まずは仕事を片付けろ。バルタザールは目的地に到着し次第、報酬を支払う。フィリップスバーグだぞ！ デイヴィ・ジョーンズの棺桶じゃねえ！\n仕事が終わったら俺のところに報告しろ。うまくやれば、俺と会社の後ろ盾を今後も期待できるぜ。以上だ。";
			link.l1 = "じゃあな、旦那。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Create_Baltazar");
			pchar.questTemp.HWIC.Holl = "BaltazarEsc";
			NextDiag.TempNode = "Second_time";
			pchar.quest.HWIC_ReturnOfficer.over = "yes";//чтобы офицер не доставал
			pchar.questTemp.HWIC.CanTake.Holl = "true";//признак, что голландка уже бралась
		break;
		
//----------------------------------------------задание 1а--------------------------------------------	
		case "SantiagoTrip":
			dialog.text = "ああ、リッデルブロックは同じオランダ人でもケチなろくでなしだ。まあ、もう俺には関係ねえ。さて、 今度はお前の話だ、名前なんてどうでもいいカピタン。お前のやり方、気に入ったぜ。 だからもう一つ仕事をやらせてやる。今度は俺が直接報酬を払うからな。";
			link.l1 = "お聞きしますぜ、旦那。";
			link.l1.go = "SantiagoTrip_1";			
			AddSimpleRumourCity("Ah, so you are the brave kapitein who escorted that scoundrel Ridderbrock? We heard all about about it... He paid you only five thousand pesos! He's been boasting about it nonstop at the tavern in Philipsburg drunk as a swine. If I were you captain, I drag him out into the street and thrash him.", "Villemstad", 20, 3, "");//слух по 1 заданию
		break;
		
		case "SantiagoTrip_1":
			dialog.text = "非常に重要な件で人手が必要だ。リッデブロックの件でよくやってくれたから、 会社としても君に任せられると考えている。";
			link.l1 = "光栄に思うべきなんだろうな。どうしたんだ？";
			link.l1.go = "SantiagoTrip_2";
		break;
		
		case "SantiagoTrip_2":
			sld = characterFromId("Santiago_usurer");
			dialog.text = "詳しいことは言えないが、これは私の仕事ではなく、会社の仕事だということは覚えておいてくれ。つまり、君には我々 のご機嫌を取るチャンスがあるというわけだ。これは非常に利益になると保証しよう。\nキューバのサンティアゴへ航海し、この包みをドンに届けてくれ "+GetFullName(sld)+"彼はジェラルディ銀行で高い地位にあり、私の…いや、我々のビジネスパートナーでもある。今から渡すこの金を彼に届けてもらいたい。君の誠実さを信じているよ、 カピテン。いや、誠実さでなくとも、生存本能は信じている。会社は我々から盗もうとする者を必ず見つけ出すからな。";
			link.l1 = "俺を疑ってるのか、旦那？";
			link.l1.go = "SantiagoTrip_3";
		break;
		
		case "SantiagoTrip_3":
			if (pchar.BaseNation == ENGLAND || pchar.BaseNation == FRANCE) sTemp = " I am also giving you this short-term Company trade license in order to spare you from any diplomatic entanglements with the Spanish. This will allow you to dock at Spanish colonies for some time.";
			else sTemp = "";
			dialog.text = "今のところ、君を疑ってはいない。信じてくれ、もし疑っていたらこんな話はしないさ。\nこの仕事を準備するのにかなり時間を費やしたんだ、だから君に与えられた猶予は十五日だけだ。"+sTemp+"\n私の伝言と荷物は必ず時間通りに届けなければならん。これは極めて重要だ、坊や。急げ、だが気をつけろ、 簡単な仕事じゃないぞ。";
			link.l1 = "他に何かあるのか？なぜ俺に警告するんだ、ローデンブルク旦那？";
			link.l1.go = "SantiagoTrip_4";
		break;
		
		case "SantiagoTrip_4":
			if (pchar.BaseNation == ENGLAND || pchar.BaseNation == FRANCE) GiveNationLicence(HOLLAND, 20);
			dialog.text = "まあ、ちょっとした疑念があると言っておこう。\n心配するな、前回の仕事のように素早くやってくれれば、 君にも会社の繊細な案件を任せられる有能なエージェントになるチャンスがあるぞ。";
			link.l1 = "この手紙と金をサンティアゴの銀行家に十五日以内に届ければいいだけか？表面上はそんなに難しくなさそうだな。";
			link.l1.go = "SantiagoTrip_5";
		break;
		
		case "SantiagoTrip_5":
			dialog.text = "慌てるな、坊主……この状況の重大さがまだ分かってねえようだな。この仕事をやり遂げてくれりゃ、俺はお前に大いに借りができる。だが、 失敗したら俺はとことんブチ切れるぜ。その時はお前にションベンぶっかけてやる。分かったか、カピテン\n "+GetFullName(pchar)+"?";
			link.l1 = "承知しました。約束します。ご機嫌を損ねないよう最善を尽くします。";
			link.l1.go = "SantiagoTrip_6";
		break;
		
		case "SantiagoTrip_6":
			dialog.text = "承知した。では、この手紙とこれらの箱を持って行き、条件と規約を忘れないように。\nそれからもう一つ、サンティアゴで問題を起こすなよ。";
			link.l1 = "承知しました。";
			link.l1.go = "SantiagoTrip_7";
		break;
		
		case "SantiagoTrip_7":
			DialogExit();
			GiveItem2Character(pchar, "NPC_Letter");
			ChangeItemDescribe("NPC_Letter", "itmdescr_NPC_Letter4");
			TakeNItems(pchar, "chest", 5); 
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("SantiagoTripOver", 0, 0, 32, false);
			}
			else SetFunctionTimerCondition("SantiagoTripOver", 0, 0, 16, false); //таймер
			AddQuestRecord("Holl_Gambit", "1-43");
			pchar.questTemp.HWIC.Holl = "SantiagoTripBegin";
			AddMapQuestMarkCity("Santiago", true);
			AddLandQuestMark(characterFromId("Santiago_usurer"), "questmarkmain");
		break;
		
		case "SantiagoTrip_8":
			dialog.text = "「“死ななきゃならん”…そんなあっさりと、か。まさかそう来るとは思わなかったぜ。ふむ。お前はよくやったな、カピテン。さあ、 報告を聞かせてくれ。」";
			link.l1 = "特に何も……楽な仕事だったよ。";
			link.l1.go = "SantiagoTrip_9";
			link.l2 = "サンティアゴで男に襲われて気絶させられ、さらわれたんだ。 そいつはお前とジェラルディの取引にやけに興味を持っていたよ。何とか逃げ出せたが、 まずそいつを殺さなきゃならなかった。唯一残された手がかりは「ガストン」という名の男だけだ。 何のことかさっぱり分からない。";
			link.l2.go = "SantiagoTrip_10";
			link.l3 = "サンティアゴで男に襲われて気絶させられ、さらわれたんだ。 そいつはあんたとジェラルディの取引にずいぶん興味があったらしい。なんとか逃げ出せたが、 まずはそいつを殺さなきゃならなかった。地獄に送る前に何も聞き出せなかったよ。";
			link.l3.go = "SantiagoTrip_11";
		break;
		
		case "SantiagoTrip_9":
			dialog.text = "会社の感謝は言葉だけにとどまらない。報酬を受け取れ、お前はそれに値する。";
			link.l1 = "会社のために働くのはかなり儲かるんだ。";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_10":
			dialog.text = "なんだと！誘拐だと……いや、待てよ……ガストン！なるほど……そういうことか。ああ、仕方ないな。哀れなことに、お前も汚い事件に巻き込まれてしまったんだな。 ここは未踏の海域だ、どう転ぶか見届けるしかない。生きて戻ってきてくれて本当に嬉しいよ。\nもっと楽しい話をしよう――この報酬を受け取ってくれ、十分に値するものだ。";
			link.l1 = "会社のために働くのはかなり儲かるんだ";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_11":
			dialog.text = "馬鹿なことを言うな！お前を誘拐だと…まあ、少しばかり疑念はあるがな。俺の下で働き続ければ、もっと色々分かるだろう。運が良かったな、 そして無事で何よりだ。\nさて、もっと楽しい話をしよう――この報酬を受け取れ、十分に値するものだ。";
			link.l1 = "会社で働くのはかなり儲かるんだ";
			link.l1.go = "SantiagoTrip_12";
		break;
		
		case "SantiagoTrip_12":
			AddMoneyToCharacter(pchar, 25000);
			dialog.text = "その通りだ、坊や！これからも一緒に働けば、君は会社の高給取りのエージェントになれるぞ。さあ、 今は航海の疲れを癒してきなさい。君は私の期待に応えてくれた。本当に感謝している、 一週間後にまた来てくれたら嬉しい。まだまだやるべきことが山ほどあるからな。";
			link.l1 = "私にお任せください、ローデンブルク旦那。";
			link.l1.go = "SantiagoTrip_13";
		break;
		
		case "SantiagoTrip_13":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "true";
			AddQuestRecord("Holl_Gambit", "1-46");
			AddCharacterExpToSkill(pchar, "Sailing", 100);//навигация
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 80);
			AddSimpleRumourCity("My brother at the Company says that Mynheer Rodenburg is quite pleased by your performance, kapitein. Don't lose your chance, Lucas rarely shows such favor.", "Villemstad", 10, 3, "");
			SetTimerFunction("GollandGambit_2_ZadanieStart", 0, 0, 7);
		break;
		
//-----------------------------------------------2 задание--------------------------------------------
		case "JacobBerg":
			dialog.text = "お前は頭が切れるな、船長。まさにその通りだ。さて、これからの任務の詳細について話そうか…";
			link.l1 = "お聞きしますよ。";
			link.l1.go = "JacobBerg_1";			
		break;
		
		case "JacobBerg_1":
			dialog.text = "君にとって非常に重大かつ重要な任務がある。私の指示通りにすべてを遂行してもらいたい。ご存知の通り、 連合州とイングランドの関係は……友好的とは言えない。イギリス人どもは自分たちだけが世界を支配すべきだと信じ込んでいる。しかし、 そんな主張に誰もが賛同するわけではない。彼らが商売のためにどこへ航海しようとも、安心してくれ、 オランダ西インド会社がすでに先に手を打っているのだ。\n我々オランダ人は世界最大の商船隊を持ち、共和国の利益をこの地でも本国でも守れる軍艦隊もある。イングランドは我々 の貿易力を妬み、会社の活動を妨害しようとあらゆる手を使ってくる。さて、 リチャード・フリートウッドというイギリス海軍の艦長がいる。彼はコモンウェルスの正式な士官でありながら、 今は海賊として活動している。カリブでオランダの旗の下に航海する船なら、どんな船でも襲い、略奪しているのだ。 彼はその行為を「イギリス商船を沈める“幽霊船”への対抗措置」だと説明している。そして、その“幽霊船”はオランダの私掠免状を持つ私掠船だと主張している。\n“幽霊船”の噂を聞いたことがあるか、カピタン？";
			link.l1 = "そんな与太話、どこの酒場でも聞けるさ。年寄りの甲板長にラムでも奢れば、好きな話をいくらでも聞かせてくれるぜ…";
			link.l1.go = "JacobBerg_2";
		break;
		
		case "JacobBerg_2":
			dialog.text = "この件は酔っ払いの妄想なんかじゃない。俺はこの“幽霊船”の行動を調査したんだ。\n調べてみると、あれは木と帆でできた普通の船で、乗っているのも普通の男たちだ。船の名は“ミラージュ”、ケッチ船だ。\n指揮しているのはヤーコブ・ファン・ベルクという男で、あの船を伝説の“フライング・ダッチマン”だと偽っているのさ。";
			link.l1 = "「ファン・ベルク？それはオランダの姓だな。本物の“フライング・ダッチマン”ってわけか？」";
			link.l1.go = "JacobBerg_3";
		break;
		
		case "JacobBerg_3":
			dialog.text = "その通りだ。ヤコブ・ファン・ベルクはオランダ人で、元はライデンの出身だ。 しかし共和国はずっと前に奴を絞首刑に処した。奴は逃亡中の犯罪者、自分の利益のためだけに動く海賊だ。 リチャード・フリートウッドがファン・ベルクを追っている。この事実をあの生意気なイギリス野郎に逆手に取ってやる。 \n私はできればフリートウッドをすぐに殺したくはない、奴はとっくにその価値があるがな。死だけでは奴には足りん。 私は奴を殺すだけでなく、その名誉も名声も徹底的に貶めてやりたい。それが私の望みだ。 他の傲慢なイギリス豚どもにも思い知らせてやれるだろう。\nさて、詳しい話をしよう。";
			link.l1 = "旦那、これはなんだか個人的な話になってきてるんじゃないか…";
			link.l1.go = "JacobBerg_4";
		break;
		
		case "JacobBerg_4":
			dialog.text = "それはお前の知ったことじゃない。命令に従えば報酬をやる。俺の手下のおかげで、ヤーコブ・ファン・ベルグが『 ミラージュ』と共にどこに潜んでいるか突き止めた。奴はスペイン領南部の都市を拠点にしている。そこへ行き、 奴の幽霊船がどこに停泊しているか探れ\nそれから奴を殺し、『ミラージュ』を見つけて戦利品として奪い、ここまで持ち帰れ。『ミラージュ』は必ず拿捕しろ、 沈めることなど考えるなよ。";
			link.l1 = "簡単そうだな。どこでヴァン・ベルグを探せばいいんだ？";
			link.l1.go = "JacobBerg_5";
		break;
		
		case "JacobBerg_5":
			dialog.text = "詳細は私の代理人がすべて説明する。名はロンウェイ、中国人だ。今回の任務には私の私有船、シーベック『メイフェン』 を提供する。ロンウェイがその船長だが、君の指示に従うことになっている。\nまずは現地の港役所へ行き、君の全ての船を係留してこい。終わったら私のところへ戻るのだ。";
			link.l1 = "よろしい、港長のところへ行ってくる。あまり待たせはしないさ。";
			link.l1.go = "exit";
			pchar.questTemp.HWIC.Holl = "JacobTakeShip";
			AddLandQuestMark(characterFromId("Villemstad_portman"), "questmarkmain");
		break;
		
		case "JacobBerg_6":
			dialog.text = "ロンウェイが外で待っている。彼が新しい船を案内し、ヴァン・ベルクの居場所についての情報も教えてくれるだろう。 幸運を祈るぜ、カピタン。俺をがっかりさせるなよ。\n『メイフェン』は必ず俺のもとに戻すんだ。『ミラージュ』を奪う時に沈めたりしないようにな。";
			link.l1 = "今行くぞ！";
			link.l1.go = "JacobBerg_7";	
		break;
		
		case "JacobBerg_7":
			DialogExit();
			pchar.quest.Create_Longway.win_condition.l1 = "location";
			pchar.quest.Create_Longway.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Create_Longway.function = "Create_Longway";
			pchar.questTemp.HWIC.Holl = "JacobLongway";
			AddQuestRecord("Holl_Gambit", "1-7");
			pchar.questTemp.HWIC.TakeQuestShip = "true";//все ПУ недоступны для стоянки до поры, также корабль нельзя продать
			pchar.questTemp.HWIC.HollEquip = "true";//форма солдат
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
		break;
		
		//дурдом продолжается
		case "Jacob_lostMir":
			dialog.text = "無能な愚か者め。お前は海賊船拿捕の任務に失敗した。私の計画はすべて台無しだ。『Meifeng』はお前から取り上げる。出て行け、もうお前は必要ない。";
			link.l1 = "申し訳ありません。さようなら、ローデンブルク旦那。";
			link.l1.go = "Jacob_RemoveShip";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MAYFANG;
		break;
		
		case "Jacob_lostMef":
			dialog.text = "お前はどうしようもない間抜けだな。「美鳳」を失ったとは許しがたい……「ミラージュ」は没収し、お前への報酬も損失の補填として差し引く。\n出て行け、もうお前は必要ない。";
			link.l1 = "申し訳ありません。さようなら、ローデンブルク旦那。";
			link.l1.go = "Jacob_RemoveShip";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MIRAGE;
		break;
		
		case "Jacob_failFull":
			dialog.text = "なんてこった、お前は本当に珍しい奴だな。無能なへっぽこで、しかも大馬鹿野郎だ。ミラージュの拿捕に失敗し、 メイフェンまで失ったとはな。さっさと俺の部屋から失せろ！";
			link.l1 = "俺は行くぜ。";
			link.l1.go = "exit";
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Longway");
			AddDialogExitQuestFunction("LandEnc_OfficerFired");//Лонгвэя из офицеров
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Detector = "holl_fail";
		break;
		
		case "Jacob_complete":
			dialog.text = "よくやった。お前の成功の噂はすでに俺の耳にも届いている。ファン・ベルクは死に、その船もお前が手に入れた。 報酬は五万ペソだ、受け取れ。\n「メイフェン」はここで引き取らせてもらう。これからは「ミラージュ」をお前に任せるぞ。 次の段階で重要な役割を果たすことになる。準備はいいか？";
			link.l1 = "はい、ローデンブルク旦那。";
			link.l1.go = "Fleetwood";
			pchar.questTemp.HWIC.Holl.ShipType = SHIP_MAYFANG;
			AddDialogExitQuestFunction("Jacob_RemoveShip");	
			AddSimpleRumourCity("They say that you are on special assignment for Mynheer Rodenburg himself. Something about sending those English to the bottom of the sea. It seems that you are a man on the rise, kapitein.", "Villemstad", 15, 3, "");
		break;
		
		case "Jacob_RemoveShip":
			DialogExit();
			AddDialogExitQuestFunction("Jacob_RemoveShip");	
			sld = characterFromId("Longway");
			sld.lifeday = 0;
			pchar.questTemp.HWIC.Holl = "end";
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//ПУ откроем
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Detector = "holl_fail";
			AddSimpleRumourCity("They say that you have failed Mynheer Rodenburg himself. Good luck, you'll need it.", "Villemstad", 20, 3, "");
		break;
		
//----------------------------------------------3 задание-------------------------------------------------
		
		case "Fleetwood":
			AddMoneyToCharacter(pchar, 50000);
			dialog.text = "これからフリートウッドを相手にする。奴が熱心に追い回している“幽霊船”ミラージュを使っておびき出すんだ。ドミニカ近海に罠を仕掛けろ。ミラージュが囮になる。\nまず、フリートウッドにミラージュがドミニカの近くで目撃されたと知らせるんだ。 あの勇敢なイギリス野郎は全てを投げ出して、獲物を求めてドミニカに突っ込んでくるさ。 直接フリートウッドに話しかけるな、命が惜しければな。セント・ジョンズの薬屋を探せ。 薬剤師のジョン・マードックは俺の古い友人だ。\n俺の命令で動いていると伝えれば、奴は地元の噂好きどもを紹介してくれる。“幽霊船”がドミニカ近海でイギリス商船を襲ったって、うまい嘘を流してもらえ。";
			link.l1 = "それはできます。目標はドミニカでフリートウッドを待ち伏せすること、合ってますね？";
			link.l1.go = "Fleetwood_1";
		break;
		
		case "Fleetwood_1":
			dialog.text = "その通りだ。ロンウェイと「メイフェン」はドミニカ近くでお前を待っている。 お前たち二人ならあのイギリス野郎を簡単に仕留められるはずだ。奴の船に乗り込んで船室を探せ。 航海日誌を持ってこい。それには追加報酬を払おう。\nだが最優先はあのフリートウッド野郎を殺すことだ。乗り込むのが無理なら、海の底に沈めてしまえ。何よりも 「ミラージュ」だけは絶対に守れ。次の計画段階で彼女が極めて重要な役割を果たすのだからな。";
			link.l1 = "承知しました。";
			link.l1.go = "Fleetwood_2";
		break;
		
		case "Fleetwood_2":
			dialog.text = "一つ忠告しておくぜ、カピタン。セント・ジョンズには錨を下ろすな。島のどこかの湾に上陸して、 ジャングルを抜けて町に行け、そうしないとジョンはお前と話してくれねえ。目立ちすぎると、 やつは知らんふりを決め込むからな。それから、海でも気をつけろ――『ミラージュ』号はイギリス植民地で悪名高い船だ。群れになった海狼どもに襲われたくなけりゃ、 イギリスの軍艦や入植地は避けるんだ。以上だ。神のご加護を。";
			link.l1 = "あいよ。";
			link.l1.go = "Fleetwood_3";
		break;
		
		case "Fleetwood_3":
			DialogExit();	
			pchar.questTemp.HWIC.Holl = "toAntigua";
			AddQuestRecord("Holl_Gambit", "1-15");
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			SetFunctionTimerCondition("ToAntiguaOver", 0, 0, 60, false); //таймер 2 месяца
			AddMapQuestMarkShore("Shore1", false);
			AddMapQuestMarkShore("Shore2", false);
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Fleetwood_complete":
			if (pchar.questTemp.HWIC.Holl == "FleetwoodSink")//Флитвуд утоп с журналом
			{
				dialog.text = "戻ってきたな、カピテン……リチャード・フリートウッドの航海日誌は持ってきたか？";
				link.l1 = "残念ながら、違う。奴が自分の船を沈める前に乗り込む機会はなかったんだ。";
				link.l1.go = "Fleetwood_complete_1";
				break;
			}
			if (!CheckCharacterItem(pchar, "FleetwoodJournal"))
			{
				dialog.text = "戻ったな、カピテン……リチャード・フリートウッドの航海日誌は持ってきたか？";
				link.l1 = "残念ながら、見つけられなかった。ヴァルキリー号に乗り込んで、あいつを白兵戦で倒すことはできたが、 日記帳は見つからなかったんだ。部下の一人が火薬庫に火をつけやがって、命からがら数秒で脱出するしかなかった。";
				link.l1.go = "Fleetwood_complete_1";
				break;
			}
			dialog.text = "戻ってきたな、カピテン……リチャード・フリートウッドの航海日誌は持ってきたか？";
			link.l1 = "やったぞ。これだ。ヴァルキリー号に乗り込むことに成功したが、危ういところだった。あの野郎、 自分の船に火薬庫ごと火をつけて吹き飛ばしやがったんだ。俺たちは命からがら逃げ延びたんだぜ。";
			link.l1.go = "Fleetwood_complete_2";
		break;
		
		case "Fleetwood_complete_1":
			AddMoneyToCharacter(pchar, 100000);
			dialog.text = "それはまったく残念だな、我々が抱えている多くの疑問に答えが得られたはずだったのに。\nだが、もうどうでもいい。あの生意気なイギリス野郎をお前が殺した、それが一番重要なことだ。\nこれが報酬だ――十万ペソだ。\nそれと『ミラージュ』号は預かるぞ、この船はイギリスに返還する。";
			link.l1 = "なんてこった！？あれは立派な船だ、俺は手元に置いておきたかったのに！";
			link.l1.go = "Fleetwood_complete_3";
		break;
		
		case "Fleetwood_complete_2":
			AddMoneyToCharacter(pchar, 150000);
			RemoveItems(PChar, "FleetwoodJournal", 1);
			dialog.text = "素晴らしい！あなたは非常に有能な男だ。もし我々の全ての船長が君のようであれば、 オランダ共和国は歴史上最も偉大な海洋国家の筆頭になっていただろう。これが報酬だ――十万ペソ、さらに航海日誌の分として五万ペソを追加しよう。『ミラージュ』号は引き取らせてもらう。 この船はイングランドに返還するつもりだ。";
			link.l1 = "なんてこった！？あれはいい船だ、俺は手元に置いておきたかったのに！";
			link.l1.go = "Fleetwood_complete_3";
		break;
		
		case "Fleetwood_complete_3":
			dialog.text = "坊や、お前は優秀な兵士だが、政治のことは俺と俺の経験を信じろ。 フリートウッドについて俺が言ったことを覚えているか？あいつの名前と評判を石臼にくくりつけて、 深い海に投げ込んでやるさ。ポートロイヤルのあの傲慢な貴族どもにも、嫌でも飲み込ませてやる、喉につかえさせてな。 \n俺たちはリチャード・フリートウッドを“幽霊船”ミラージュ号の船長に仕立て上げる。イングランドとオランダ、二つの国を手玉に取る人狼だ。 両国の善良な市民を略奪し、殺し、ただ自分の私腹を肥やすためだけに悪事を働く！なんて茶番だ！ 証拠も証人もすでに用意してあるが、“ミラージュ号”こそが俺の完璧な芝居の目玉になるのさ。";
			link.l1 = "なんてこった。俺の素晴らしい船をお前の計画のために犠牲にするつもりか！？";
			link.l1.go = "Fleetwood_complete_4";
			AddDialogExitQuestFunction("Lucas_ExangeShip");
		break;
		
		case "Fleetwood_complete_4":
			dialog.text = "言葉に気をつけろ、坊や。これは戦争だ。時には人だけでなく、 船や裕福な植民地も政治的目的のために犠牲にしなければならん。どんな戦争にも損失はつきものだ……損失といえば、悪い知らせがある。\nお前がいない間に、ウィレムスタッドがイギリスの私掠船に襲われた。要塞はなんとか奴らを追い払ったが、 火船で港に侵入されてしまった。\nお前の船は停泊中に巻き込まれ、水面まで焼け落ちた。完全な喪失だ。";
			link.l1 = "旦那、ふざけてんのかよ、今のは冗談だろうが！くそっ、全部台無しじゃねえか！俺はこれからどうすりゃいいんだよ！？ ";
			link.l1.go = "Fleetwood_complete_5";			
		break;
		
		case "Fleetwood_complete_5":
			dialog.text = "そんなに気を落とすな、カピタン。良い知らせもあるんだ。君の怒りを和らげるために、私の「美しき風」――シーベック『メイフェン』を譲ろう。常識の範囲で好きなように使ってくれて構わない。\nさらに、明日総督邸で私と会ってくれ。君はオランダ共和国と西インド会社の感謝を込めて、国家表彰に推薦されたのだ。 受け取るまでは町を離れないでくれよ、カピタン。";
			link.l1 = "それで少しは損失の痛みも和らぎますな。光栄です。ところで、旦那、ロンウェイはどこへ行ったのですか？";
			link.l1.go = "Fleetwood_complete_6";
		break;
		
		case "Fleetwood_complete_6":
			dialog.text = "俺がロングウェイにドミニカへ航海するよう命じた直後、やつは突然姿を消したんだ。 イギリスの諜報員どもが手を出したのかもしれねえ……いや、そうじゃないかもしれん。今、調査中だ。";
			link.l1 = "なるほど。ドミニカで彼の助けがあれば、どれほど心強かったことか。フリートウッドと彼の“ヴァルキリー”は恐ろしいコンビだった。ロンウェイがまだ生きていることを願う……\nでは、トット・ジーエンス、旦那！";
			link.l1.go = "Fleetwood_complete_7";
			pchar.questTemp.HWIC.Holl = "Award";
			AddQuestRecord("Holl_Gambit", "1-24");
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", true);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", true);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", true);
		break;
		
		case "Fleetwood_complete_7":
			DialogExit();
			AddDialogExitQuestFunction("GollandGambit_AwardFromLucas_1");
			AddSimpleRumour("Tell me captain, was that damned English dog Fleetwood was really responsible for plundering English 'and' Dutch merchants? Really? Such an artful dodger! It is good that you have eliminated this bastard. You are a real hero, captain!", HOLLAND, 10, 3);
		break;
		
		case "Fleetwood_fail":
			dialog.text = "お前はただの道化じゃねえ、まるごとサーカスそのものだ。あと一歩で最後の見せ場だったのに、 全部台無しにしやがって……フリートウッドの始末に三万ペソ払ってやる。もうお前に頼む仕事はねえし、これで俺たちの取引も終わりだ。 さっさと失せろ。";
			link.l1 = "かしこまりました。";
			link.l1.go = "Fleetwood_fail_1";			
		break;
		
		case "Fleetwood_fail_1":
			AddMoneyToCharacter(pchar, 30000);
			dialog.text = "悪い知らせがあります。\nあなたが不在の間に、ウィレムスタッドがイギリスの私掠船に襲撃されました。砦はなんとか彼らを追い払いましたが、 火船で港に侵入されてしまいました。\nあなたの船は停泊中に巻き込まれ、水面まで焼け落ちてしまいました。全損です。";
			link.l1 = "じゃあ、俺は自分で勝手にやるしかねえってことかよ！役立たずめ、ありがとよ！";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			CloseQuestHeader("Holl_Gambit");
			pchar.questTemp.HWIC.Holl = "end";
			pchar.questTemp.HWIC.Detector = "holl_fail";
			AddSimpleRumour("Tell me, captain, is it true that you have sunk this damned English dog Fleetwood? Really? It is good that you have eliminated this bastard. You did well, captain!", HOLLAND, 15, 3);
		break;
		
		case "LucasAward":
			dialog.text = "Kapitein "+GetFullName(pchar)+"「危険な国家犯罪者リチャード・フリートウッドを討ち取り、共和国に対する裏切りのイギリス陰謀を暴き、 勇敢さと勇気を示したことにより、オランダ共和国を代表して千枚の金ドゥブロンを授与する！\nさらに、全ての海軍士官の夢であるこの貴重な航海用具も授けよう。」";
			link.l1 = "私は共和国に仕えることができて嬉しいです！";
			link.l1.go = "LucasAward_1";			
		break;
		
		case "LucasAward_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_SetActorType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
			sld.dialog.currentnode = "Bek_7";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			GiveItem2Character(pchar, "bussol");
		break;
		
		case "LucasAward_2":
			dialog.text = "おめでとう、友よ。\nそれと、一週間後にぜひ私のところへ来てくれ。非常に繊細な件で君の力が必要なんだ。";
			link.l1 = "承知しました、ローデンブルク旦那。1週間後にお伺いします。";
			link.l1.go = "LucasAward_3";			
		break;
		
		case "LucasAward_3"://наведем порядок
			LAi_SetActorType(pchar);
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-25");
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			LAi_ActorGoToLocator(sld, "goto", "goto6", "BekSitDown", -1);
			for (i=1; i<=3; i++)
			{
				sld = characterFromId("LucasGuard_"+i);
				sld.lifeday = 0;//подчистим солдат
			}
			sld = characterFromId("Lucas");
			LAi_ActorGoToLocator(sld, "reload", "reload1", "LucasReturnInCabinet", -1);
			bDisableFastReload = true;
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			SetTimerFunction("GollandGambit_4_ZadanieStart", 0, 0, 7);
			AddSimpleRumourCity("They say that you were given a state award by Matias Beck himself! The Republic should be proud to have people like you, kapetein!", "Villemstad", 20, 4, "");
		break;
		
//--------------------------------------------------4 задание----------------------------------------------
		
		case "Abby":
			dialog.text = "一つ話をしよう。これを聞けば、次の任務がいかに繊細か分かるはずだ。数か月前、 イングランドの旗を掲げてウィレムスタッドへ向かっていたフリュート船が、故ヤーコプ・ファン・ベルクに襲われた。 彼はその船を奪い、我々の地図に載っていない島の近くで沈めた。フリュート船の乗客で生き残ったのは二人だけ。 ソロモン・シュヌールというユダヤ人と、その娘アビゲイルだ。他の乗客は皆、彼らの家族も含めて命を落とした。 我らが二人のユダヤ人は、残骸にしがみついて島にたどり着いた\nソロモンは家族の金貨が詰まった箱まで引きずってきた。実に倹約家だな。我々の物語のもう一人の人物、 リチャード・フリートウッドは近くを航行していて、戦闘の音を聞いた。 彼が到着した時にはファン・ベルクはすでに逃げており、「ミラージュ」は姿を消していた。 フリートウッドは島に生存者がいないか調べることにした\n彼はソロモンとアビゲイルを、あの無人島で確実な死から救い出した。不運なことに、 年老いたユダヤ人ソロモンには船乗りの目がなかった。彼はリチャードの「ヴァルケリー」をヤーコプの「ミラージュ」 と見間違え、海賊が戻ってきてとどめを刺しに来たと恐れ、金貨を島のどこかに隠した。その結果、 彼と娘は一文無しでここにたどり着き、フリートウッドにウィレムスタッド近くのブランカ・ラグーンで降ろされた、元々 の目的地だ\nこの話はソロモン本人から聞いた。オランダ共和国は信仰の自由を支持している。その方針の一環として、 会社もこの地のユダヤ人共同体を支援している。だから私は彼らに住む場所と食べ物、着る物を用意した。 私はよく彼らの家を訪ねた。アビゲイルは……素晴らしい娘だ。誠実で、人を信じやすい\n嘘は言わんよ、船長。私は彼女を手に入れたいし、妻にするつもりだ。彼女も私を愛してくれている。だが、我々 の間に何かが割り込んできた。";
			link.l1 = "彼女の父親は異教徒の婿にあまり乗り気じゃないのか？";
			link.l1.go = "Abby_0";			
		break;
		
		case "Abby_0":
			dialog.text = "ははっ！もし俺がアビゲイルと結婚したら、割礼してない婿でもソロモン爺さんは天にも昇る気分だろうよ。実際、 あの人はアビゲイルに俺の求婚を受けるよう勧めてるんだ。いやいや、 これはユダヤ人と異邦人の問題を超えた何かなんだ。頼むよ、坊や、この問題を解決してくれ。アビゲイルと話して、 何がいけないのか探ってくれ\n君はよそ者だから、彼女の慎み深さゆえに身内には絶対言わないことも話してくれるかもしれない。 シュネウルの家は会社の事務所に背を向けて右手にある。君が口がうまいのは知ってる\nだが一つだけ覚えておけ――リチャード・フリートウッドこそが「幽霊船」の本当の船長だった……アビゲイルと話す時はそのことを忘れるな。";
			link.l1 = "はっ！もちろん覚えていますよ、ローデンブルク旦那。結局、それは公式に認められた事実じゃありませんか？ それなら無駄な時間は使いません、すぐにあなたの愛しい人に会いに行きましょう。";
			link.l1.go = "Abby_1";			
		break;
		
		case "Abby_1":
			LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false);//откроем дом Аби
			DialogExit();
			pchar.questTemp.HWIC.Holl = "AbbyInHouse";
			AddQuestRecord("Holl_Gambit", "1-26");
			AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;
		
		case "Abby_2":
			dialog.text = "本当にソロモンが金を隠した島を見つけたのか？それは素晴らしい！ お前ならどんな仕事でもやり遂げるんじゃないかと思い始めてたところだ……他に隠し場所で何か見つけたか？";
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.ScullnotReturn"))
			{
				link.l1 = "いや、他には何もない。金だけだ。";
				link.l1.go = "Abby_3";
			}
			else
			{
				link.l1 = "面白い品があった――翡翠の髑髏だ。それをソロモンに渡したら、家宝だと言っていた。さらに、 あんたがそれを買い取るつもりだったとも話していたぞ…";
				link.l1.go = "Abby_4";
			}
		break;
		
		case "Abby_3":
			pchar.questTemp.HWIC.Holl.LucasItem = "obereg_11";
			dialog.text = "ふむ。まあ、いいだろう。しかし、どうにも妙な話だな。まあいい……俺はお前に借りができた、旦那。決して忘れねえ。報酬を用意してある――五万ペソとこのお守りだ。今やそれはお前のものだ。";
			link.l1 = "ありがとうございます、ローデンブルク旦那！";
			link.l1.go = "Abby_5";
		break;
		
		case "Abby_4":
			pchar.questTemp.HWIC.Holl.LucasItem = "totem_04";
			dialog.text = "素晴らしい！そうだ、私はこの遺物をソロモンから買い取るつもりだ。あいつには必要ないし、 私にはとても気前のいい買い手がいるんだ。君への報酬も用意してある――五万ペソとこのお守りだ。今やそれは君のものだ。";
			link.l1 = "ありがとうございます、ローデンブルク旦那！";
			link.l1.go = "Abby_5";
		break;
		
		case "Abby_5":
			dialog.text = "今のところ、お前のようなカピタンにふさわしい仕事はないんだ。だが、あまり長くキュラソーを離れるなよ、 すぐにまたお前の力が必要になるからな。";
			link.l1 = "分かったぜ、旦那。じゃあな！";
			link.l1.go = "exit";
			GiveItem2Character(pchar, pchar.questTemp.HWIC.Holl.LucasItem);
			AddMoneyToCharacter(pchar, 50000);
			pchar.questTemp.HWIC.Holl = "Merdok_wait";
			AddQuestRecord("Holl_Gambit", "1-34");
			DelMapQuestMarkCity("Villemstad");
			SetTimerFunction("GollandGambit_5_ZadanieStart", 0, 0, 10);
			AddSimpleRumourCity("Have you heard the latest news? Mynheer Rodenburg is going to marry Abigail Shneur, the beautiful daughter of the old crazy Jew Solomon. What can I say, she is a lucky girl. God willing, she'll be baptized a true Christian before the wedding!", "Villemstad", 20, 3, "");
		break;
		
		case "Abby_6":
			dialog.text = "はは、それだけか？まったく馬鹿げてる……いかにも女らしい発想だな。よく聞け、坊や。この問題は簡単に解決できる。ソロモンの隠し財産にいくら入っていたか、 私は知っている――20万ペソだ。私とアビゲイルの幸せのためなら、この金を惜しまない。君に金を渡すから、1週間か2週間キュラソーを離れてくれ。それからソロモンのもとへ戻り、金を渡すんだ。隠し財産を見つけたふりをしろ。 狼は満足し、羊は傷つかずに済む。さあ、必要な額を受け取れ\n";
			link.l1 = "いいぞ、単純で分かりやすい作戦だ。やってみよう。";
			link.l1.go = "Abby_7";
		break;
		
		case "Abby_7":
			dialog.text = "外海へ出て、十日後に俺のところへ戻ってこい。\n何か有意義なことをしてこい。マンガ・ローザを探すなり、材料を作るなり、何でもいいさ。";
			link.l1 = "お好きなように、ローデンブルク旦那。";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 200000);
			pchar.questTemp.HWIC.Holl = "GiveLucasMoney";
			SaveCurrentQuestDateParam("questTemp.HWIC.Holl.LucasMoney");
			pchar.questTemp.HWIC.Holl.LucasMoney = "true";
			AddQuestRecord("Holl_Gambit", "1-35");
		break;
		
		case "Abby_8":
			pchar.questTemp.HWIC.Holl.LucasItem = "obereg_11";
			dialog.text = "素晴らしい！今回も完璧にやってくれたな。俺はお前に借りができた、旦那。決して忘れないぜ。 報酬として五万ペソとこのお守りを用意した。今やそれはお前のものだ。";
			link.l1 = "ありがとうございます、ローデンブルク旦那！";
			link.l1.go = "Abby_5";
		break;
		
//-------------------------------------------5 задание-------------------------------------------------
		case "Merdok":
			dialog.text = "ああ、その通りだ。友よ、時には誰が味方で誰が敵か見分けるのは難しいものだ。 最も親しい仲間がいつの間にか仇となっていることもある。セントジョンズで共通の知り合いであるジョン・マードック――ヨハン・ファン・メルデンとも呼ばれているが――は、かつて会社のエージェントだったが、今やイギリス海軍に身を売った男だ。\n彼の最新の任務は、会社でもっとも輝く星の一人……つまり君を消すことだ。";
			link.l1 = "光栄です。教えてくれて嬉しいよ、そうじゃなきゃ全然予想できなかったからな。";
			link.l1.go = "Merdok_1";
		break;
		
		case "Merdok_1":
			dialog.text = "その通りだ、カピテン。あいつはずる賢い野郎だ。奴を見つけて、手を打たれる前に殺せ。アンティグアへ航海して、 奴の薬屋への秘密の入り口を探せ。教会の前にハッチがあって、それが秘密のトンネルにつながっている。それを使え。";
			link.l1 = "俺がやっておくぜ。";
			link.l1.go = "Merdok_2";
		break;
		
		case "Merdok_2":
			dialog.text = "もう一つ頼みがある、カピテン。ヨハンが死んだら、奴の死体と家、それに地下室を探せ。あいつは記録簿を持っている――会社の仕事中に書き残した、我々にとって致命的な内容が詰まった分厚い台帳だ。その情報が敵の手に渡れば、我々 全員が破滅する。\nその忌まわしい記録簿を見つけて私に届けろ。そうすれば追加で報酬を払おう。さあ行け。神のご加護を、カピテン。 "+pchar.name+"、そして無事に戻ってくるんだ。共和国がお前を必要としている！";
			link.l1 = "お約束しますよ、旦那、必ず無事に戻ります。それが私にとって一番得策ですから！";
			link.l1.go = "Merdok_3";
		break;
		
		case "Merdok_3":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "KillMerdok";
			AddQuestRecord("Holl_Gambit", "1-42");
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
			bDisableFastReload = false;
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);//откроем проход в подземелье из дома
			LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false);//откроем проход в дом из подземелья
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//аптеку закроем
			pchar.quest.Merdok_inCave.win_condition.l1 = "location";
			pchar.quest.Merdok_inCave.win_condition.l1.location = "SentJons_TownCave";
			pchar.quest.Merdok_inCave.function = "MerdokInUndergroundCave";
			LAi_LocationDisableOfficersGen("SentJons_TownCave", true);//офицеров в шахту не пускать
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("SentJons", false);
		break;
		
		case "Merdok_4":
			dialog.text = "素晴らしいです、船長！本当に嬉しいですよ。彼の書庫は見つかりましたか？";
			if (CheckCharacterItem(pchar, "MerdokArchive"))//архив
			{
				link.l1 = "はい、これです。薬剤師の死体や彼の箱の中には他の書類はありませんでした。";
				link.l1.go = "Merdok_book";
			}
			link.l2 = "いいや。あちこち探したが、何も見つからなかった。";
			link.l2.go = "Merdok_5";
			DeleteAttribute("SentJons_TownCave", "box2");//если не нашли шифр - уже и не найдем
		break;
		
		case "Merdok_5":
			dialog.text = "それは確かに残念だが、俺は別に構わねえよ。ヨハンがイギリス野郎に渡す時間がなかったのは間違いねえ、 そうじゃなきゃ今ごろ俺たちは首に縄をかけられてるはずだ……きっとどこかの隠し場所にしまい込んだんだろう……そのまま永遠に眠らせておけ！任務の成功を祝うぜ、カピテン！";
			link.l1 = "感謝する！";
			link.l1.go = "Merdok_6";
			
			SetTimerCondition("PZ_LigaInJungle", 0, 0, 7, false);	// проверку не прошёл, значит нападёт Лига через неделю, после чего начнётся таймер на 30 дней 1 этапа
		break;
		
		case "Merdok_book":
			dialog.text = "素晴らしい！これで無事にしかるべき場所に戻ったな。君がまたしても一番だと証明した…本を渡してくれ…記録保管所には報酬がある――この上等なマスケット銃だ。これは私に大いに役立ってくれたが、今度は君のものだ！";
			link.l1 = "";
			if (CheckAttribute(pchar, "questTemp.PZ_RodenburgUkradenaStranitsa"))
			{
				link.l1.go = "Merdok_book_2";
			}
			else
			{
				link.l1.go = "Merdok_book_6";
			}
			RemoveItems(PChar, "MerdokArchive", 1);
		break;
		
		case "Merdok_book_2":
			dialog.text = "お前の狙いは何だ、船長？何ページか抜けているじゃねえか――俺にとってとても大事なページだ。俺が気づかないとでも思って、俺に不利になるよう使うつもりだったのか？それとも、 もっと得しようとしたのか？どちらにしても、悪いが期待外れだぜ。";
			if (IsCharacterPerkOn(pchar, "Trustworthy"))
			{
				Notification_Perk(true, "Trustworthy");
				link.l1 = "（信頼できる）申し訳ありません。私の唯一の過ちは、事前に自分で記録を確認しなかったことです。";
				link.l1.go = "VD_Merdok_book_3";
				SetTimerCondition("PZ_Etap1_Start", 0, 0, 30, false);	// 1 этап стартует через 30 дней
			}
			else
			{
				Notification_Perk(false, "Trustworthy");
				link.l1 = "本当に俺がページを引き裂いて、何食わぬ顔で記録を渡すと思うか？";
				link.l1.go = "Merdok_book_3";
				SetTimerCondition("PZ_LigaInJungle", 0, 0, 7, false);	// проверку не прошёл, значит нападёт Лига через неделю, после чего начнётся таймер на 30 дней 1 этапа
			}
			LAi_Fade("", "");
		break;
		
		case "Merdok_book_3":
			dialog.text = "強欲、愚かさ、そして図々しさが時に人を最も狂気じみた行動へと駆り立てることがあるのですよ、船長。";
			link.l1 = "その三人の誰にも私は動機づけられておりません、保証しますよ。";
			link.l1.go = "Merdok_book_4";
		break;
		
		case "Merdok_book_4":
			dialog.text = "つまり、ヴァン・メルデンがそのページを抜き取って、どこか別の場所に隠したってことか？";
			link.l1 = "その通りです。必要とあらば、私が戻って彼らを探し、薬局中をひっくり返してでも、 あるいはセント・ジョンズ全体を捜索してでも構いません。";
			link.l1.go = "Merdok_book_5";
		break;
		
		case "Merdok_book_5":
			dialog.text = "必要ありません、旦那。大事なことはほとんどここにありますし、抜けているページがなければ、 残りは私にとって脅威ではありません。";
			link.l1 = "";
			link.l1.go = "Merdok_book_6";
		break;
		
		case "VD_Merdok_book_3":
			dialog.text = "つまり、不誠実や隠された意図ではなく、ただの無関心や好奇心の欠如ということか？\n君がこれを見つけた時から、すでにこうだったと思うか？";
			link.l1 = "おそらくローデンブルク旦那でしょう。もしかすると、 ファン・メルデンがあらかじめそのページを破り取ったのかもしれません。 ";
			link.l1.go = "VD_Merdok_book_4";
		break;
		
		case "VD_Merdok_book_4":
			dialog.text = "たぶん、それが最善だろう。あのページがなければ、残りの文書庫も私には脅威ではない――特に無知な者の手に渡ればなおさらだ。";
			link.l1 = "";
			if (IsCharacterPerkOn(pchar, "Trustworthy")) link.l1.go = "Merdok_book_6";
			else link.l1 = "Merdok_6";
		break;
		
		case "Merdok_book_6":
			dialog.text = "記録保管の報酬として、この上等なマスケット銃をやろう。\nこれは俺の誇り高き相棒だったが、今はお前のものだ！";
			link.l1 = "「ありがとう！」";
			link.l1.go = "Merdok_6";
			GiveItem2Character(PChar, "mushket2");
		break;
		
		case "Merdok_6":
			dialog.text = "俺たちはよくやったな、カピタン。お前がいなければ、ここまでのことは何一つ起きなかったと言っても過言じゃねえ。 共和国に仕え続ければ、お前の出世は間違いなしだ。もしかしたら貴族にだってなれるかもしれねえぞ。";
			link.l1 = "これでお別れですね、ローデンブルク旦那。";
			link.l1.go = "Merdok_7";
		break;
		
		case "Merdok_7":
			dialog.text = "「これでお別れだ」 "+pchar.name+"。ここでやりたかったことはすべて達成したので、私は一週間後にアムステルダムの我が家へ帰ります。 新しい妻アビゲイルと義父ソロモンも一緒です。 ピーター・スタイフェサントはすでに新しい会社の副長官を見つけているので、 何か必要なことがあれば彼に相談してください\nあなたの働きに感謝して、メイフェン号を贈ります。これからはあなたのものです、カピテン、 あなたにはその資格があります。";
			link.l1 = "ありがとうございます、ローデンブルク旦那。メイフェン号にはすっかり愛着が湧いて、 もう自分の船のように感じ始めています。";
			link.l1.go = "Merdok_8";
		break;
		
		case "Merdok_8":
			dialog.text = "さて、ここで君には席を外してもらわないといけない、坊や。出航前にやることが山ほどあるんだ……いつかアムステルダムに来てくれ！一緒に酒を酌み交わして、昔話に花を咲かせようじゃないか……";
			link.l1 = "ああ、旦那。新しい人生で皆が幸せに、そして繁栄していることを願っているぜ！じゃあな！";
			link.l1.go = "Merdok_9";
			// belamour legendary edition -->
			link.l2 = "ああ、旦那。新しい人生で皆が幸せに、そして繁栄していることを願ってるぜ！\n（歯を食いしばりながら）……もう二度と会わねえことを祈るぜ、この傲慢な野郎め。お前が“おしとやか”なユダヤ人の鬼嫁と結婚する喜びを味わう日が楽しみだな。";
			link.l2.go = "Merdok_9a";
		break;
		
		case "Merdok_9a":
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			DialogExit();
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			AddQuestRecord("Holl_Gambit", "1-41");
			CloseQuestHeader("Holl_Gambit");
			sld = characterFromId("Abigile");//уберем Аби
			sld.lifeday = 0;
			sld = characterFromId("Solomon");//уберем Соломона
			sld.lifeday = 0;
			pchar.quest.Lucas_quit.win_condition.l1 = "Timer";
			pchar.quest.Lucas_quit.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Lucas_quit.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Lucas_quit.function = "LucasQuit";//прерывание на Лукаса
			pchar.questTemp.HWIC.Detector = "holl_win";
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddSimpleRumourCity("Mynheer Rodenburg has sailed to Amsterdam with his young wife and father-in-law. Are you the new vice-director?", "Villemstad", 30, 3, "");
			AddSimpleRumour("They say, kapitein, that you are well regarded by the governor-general. Mynheer Rodenburg supposedly appointed you as his successor in the Company, is that so?", HOLLAND, 30, 3);
		break;
		
		case "Merdok_9":
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			DialogExit();
			DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip");//можно пользоваться ПУ
			DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
			pchar.questTemp.HWIC.Holl = "end";
			AddQuestRecord("Holl_Gambit", "1-41");
			CloseQuestHeader("Holl_Gambit");
			sld = characterFromId("Abigile");//уберем Аби
			sld.lifeday = 0;
			sld = characterFromId("Solomon");//уберем Соломона
			sld.lifeday = 0;
			pchar.quest.Lucas_quit.win_condition.l1 = "Timer";
			pchar.quest.Lucas_quit.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Lucas_quit.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
			pchar.quest.Lucas_quit.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 7);
			pchar.quest.Lucas_quit.function = "LucasQuit";//прерывание на Лукаса
			pchar.questTemp.HWIC.Detector = "holl_win";
			sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
			sld.Dialog.Filename = "Common_Mayor.c";//patch-8
			sld.dialog.currentnode = "First time";
			sld.quest.meeting = "1";
			DelMapQuestMarkCity("Villemstad");
			AddMapQuestMarkCity("FortFrance", false);
			AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
			AddSimpleRumourCity("Mynheer Rodenburg has sailed to Amsterdam with his young wife and father-in-law. Are you the new vice-director?", "Villemstad", 30, 3, "");
			AddSimpleRumour("They say, kapitein, that you are well regarded by the governor-general. Mynheer Rodenburg supposedly appointed you as his successor in the Company, is that so?", HOLLAND, 30, 3);
		break;
		
//----------------------------------------------за Англию------------------------------------------------------
		case "Lucas_abordage":
			dialog.text = "天にまします神よ！フリートウッドの犬め！今日の勝負はお前のものかもしれんが、 ルーカス・ローデンブルクは命を安売りはしないぞ。";
			link.l1 = "そうは思わねえな。お前の命はタダで俺がもらうぜ、このケチなオランダ野郎。";
			link.l1.go = "Lucas_abordage_1";
		break;
		
		case "Lucas_abordage_1":
			PlaySound("Voice\English\hambit\Lucas Rodenburg-04.wav");
			dialog.text = "地獄の底からお前の口にクソをぶち込んでやる！\n今、俺は貨物倉に火をつけたばかりだ、この炎はすぐに火薬庫まで広がるぜ！\n俺たちの船は密着して絡み合ってるから、逃げ道なんてねえ！\nお前は焼け死ぬか、サメの餌になるしかねえんだ！";
			link.l1 = "くそっ！退け、野郎ども、撤退するぞ！";
			link.l1.go = "Lucas_abordage_2";
			// belamour legendary edition -->
			link.l2 = "お前の魂が体を離れるまで、俺はここを動かねえ。じっとしてろ、痛いぜ。";
			link.l2.go = "Lucas_abordage_2a";
		break;
		
		case "Lucas_abordage_2a":
			AddCharacterExpToSkill(pchar, "FencingL", 60);
			AddCharacterExpToSkill(pchar, "FencingS", 60);
			AddCharacterExpToSkill(pchar, "FencingH", 60);
			AddCharacterExpToSkill(pchar, "Pistol", 60);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom1"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
		case "Lucas_abordage_2":
			AddCharacterExpToSkill(pchar, "Leadership", 120);
			// <-- legendary edition
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom1"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
		
//----------------------------------------------против всех--------------------------------------------------
		case "LucasPrisoner":
			dialog.text = "なんでここに来たんだ、この野郎？俺を嘲りに来たのか？それとも、 やっとこの芝居でのお前の役割を教えてくれるってわけか。ブリガンティンを拿捕したのはお前だろ？ 最初からこれがお前の計画だったのか？";
			link.l1 = "俺は伝言を届けに来た、ルーカス・ローデンブルク。裏切った相手、ジョン・マードックからのご挨拶だ。 お前は俺の標的だったが、任務は完了した。じゃあな、また会おう。";
			link.l1.go = "LucasPrisoner_1";
		break;
		
		case "LucasPrisoner_1":
			PlaySound("Voice\English\hambit\Lucas Rodenburg-04.wav");
			dialog.text = "ヨハンか？ははは！つまり、すべての黒幕はあの男だったのか！あの老いぼれの悪党め！だが、 まだ勝負は終わっちゃいねえぞ。ヤーコプ・ファン・ベルフが貴様を追ってくる、逃げられると思うな！ 貴様も貴様の船も、もう終わりだ、この哀れな海の乞食め！";
			link.l1 = "「絞首台の法廷で弁明でもしたらどうだ、ローデンブルク。」";
			link.l1.go = "LucasPrisoner_2";
		break;
		
		case "LucasPrisoner_2":
			DialogExit();
			pchar.questTemp.jailCanMove = true; //разрешить пройти мимо стражи
			LAi_SetPlayerType(pchar);
			pchar.quest.Login_Joakim.win_condition.l1 = "location";
			pchar.quest.Login_Joakim.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Login_Joakim.function = "Create_Joakim";
			pchar.questTemp.HWIC.Self = "JoakimMeeting";
			SetFunctionTimerCondition("LucasQuit", 0, 0, 7, false);
		break;
	}
}
