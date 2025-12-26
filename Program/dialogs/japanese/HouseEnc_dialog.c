void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag, arRld, arDis;
	int i, Qty;
	ref rColony;
	
	int iTest;
	
	bool  ok; // лесник . спецпеременная.

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	iTest = FindColony(NPChar.City);
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_GoOut":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //закрываем вход в дом
					break;
    			}
    		}
			DoQuestFunctionDelay("HouseEnc_TimerGoUot", 10.0);
			pchar.questTemp.HouseEncTimer = pchar.location;
			pchar.questTemp.HouseEncTimer.Id = npchar.id;
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "exit_close":
			makearef(arRld, Locations[reload_cur_location_index].reload);
    		Qty = GetAttributesNum(arRld);
			for (i=0; i<Qty; i++)
    		{
    			arDis = GetAttributeN(arRld, i);
    			if (arDis.go == npchar.location)
    			{
					arDis.disable = true; //закрываем вход в дом
					break;
    			}
    		}
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//--------------------------------- мужик ---------------------------------
		case "HouseMan":
			NextDiag.TempNode = "HouseMan";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("町で警報が鳴ったようだ。どうやら俺も武器を取る時が来たらしいな……","もしかして、街の衛兵に追われてるんじゃねえか？ ","ここには逃げ場なんてねえが、肋骨の間に冷たい刃を何本も突き立てられることはあるぜ！"),LinkRandPhrase("何の用だ？"+GetSexPhrase("悪党","ろくでなし")+"！？街の衛兵たちはもうお前の匂いを嗅ぎつけてるぜ、そう遠くまでは逃げられねえぞ。 "+GetSexPhrase("汚い海賊","この海賊女め")+"!","汚い殺人者め！衛兵！！","俺はお前なんか怖くねえぞ。 "+GetSexPhrase("這い寄る","あばずれ")+"！すぐに我々の砦で絞首刑にされるぞ、お前はもう逃げられねえ……"));
				link.l1 = PCharRepPhrase(RandPhraseSimple("生きるのに飽きたようだな……","どうやら、ここの市民たちに安らかな暮らしはないようだ "+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("地獄へ落ちろ！","へっ、お前の人生もあと数秒で終わりだぜ……"));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "警告はしたぞ。あとは自分で面倒ごとに首を突っ込むかどうか決めな。";
					link.l1 = "へっ！";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "俺の家で何の用だ、このろくでなしめ！？十秒以内に出て行きやがれ！";
					link.l1 = LinkRandPhrase("へっ、ここでも俺のことを知ってるみたいだな！","俺の評判がちょうど先に広まっただけさ……","ふむ、なるほど。");
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("私の家へようこそお越しくださいました。ご用件でしょうか？","ご用件は何でしょうか？","ふむ……俺に何か用か？","申し訳ありませんが、用がないのであれば、どうか私を邪魔しないでください…","ブロック",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("いや、ただ見て回って、新しい人たちに会ってるだけだ…","いいえ、特に何も……","「何も……」","わかった、あなたの言う通りだ。",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseMan_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("申し訳ありませんが、夜は訪問にはふさわしくありませんので、すぐに私の家を出ていただかねばなりません！","もう言っただろう、遅いんだ。頼む、出ていってくれ。","失礼に思われたくはないが、今すぐ私の家から出て行ってもらいたい！","くそっ、何が起きてるんだ！？衛兵！泥棒だ！","ブロック",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("なるほど、わかった…","ああ、ちょっと待ってくれ……","わかった、そんなに興奮するなよ。","「盗賊だと！？黙れ！」",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "fight", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseMan_1":
			dialog.text = "「ああ、自己紹介させてくれ―」 "+GetFullName(npchar)+"。あなたをお迎えできてとても嬉しいです。この町では、もてなしの掟が守られております。";
			link.l1 = GetFullName(pchar)+"……よろしければ……";
			link.l1.go = "exit_setOwner";
		break;
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("お前は "+GetSexPhrase("盗人か、なるほど！衛兵ども、そいつを捕まえろ","泥棒か、なるほど！衛兵ども、あの女を捕まえろ")+"!!!","信じられない！ちょっと目を離した隙に、俺の持ち物を漁ってやがる！止まれ、泥棒！！！","衛兵！強盗だ！泥棒を止めろ！！！");
			link.l1 = "あああっ、悪魔め！！！";
			link.l1.go = "fight";
		break;
		// --------------------------------- баба ---------------------------------
		case "HouseWoman":
			NextDiag.TempNode = "HouseWoman";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("警告しておくわよ、うちの旦那はすぐに帰ってくるんだから！今すぐ私の家から出ていったほうがいいわよ！","逃げられるとは思っていないわよ！それに、私の夫がすぐに帰ってくることを覚えておきなさい！","「主人がもうすぐ帰ってきます！すぐに出て行ってください！」"),LinkRandPhrase("「旦那が家にいないのは残念だわ……出て行きなさい！今すぐ！！」","汚らわしい殺人者め、今すぐ私の家から出ていけ！衛兵！",""+GetSexPhrase("なんて悪党だ","なんて汚らわしい")+"「……もうすぐ私の旦那が戻ってくるわ、そうしたらあんたの血の色がどんなものか見せてやるんだから！」"));
				link.l1 = PCharRepPhrase(RandPhraseSimple("「ああ、旦那さんが……おおおお……俺、震えてきたぜ……」","へっ……なあ、お嬢ちゃん、あんたの旦那はたった一人の男だぜ……足元で死なせたくはねえだろ？"),RandPhraseSimple("黙れ、女、腹を裂かれたくなけりゃな…","俺は好きなだけここにいるぜ。お前も身のために黙ってたほうがいいぞ……"));
				link.l1.go = "exit_setOwner";
				break;
			}
			if (isBadReputation(pchar, 40))
			{
				if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
				{
					dialog.text = "警告したはずだ。出ていけ、さもないと後悔するぞ！";
					link.l1 = "なんて馬鹿な女だ……";
					link.l1.go = "exit";
				}
				else
				{					
					dialog.text = "「俺の家で何してやがる」 "+GetSexPhrase("ごろつき","悪党")+"？！十秒以内に立ち去らないと、衛兵を呼ぶぞ！";
					link.l1 = "なんて間抜けな女だ……";
					link.l1.go = "exit_GoOut";
				}
			}
			else
			{
				if (IsDay())
				{
					dialog.text = NPCStringReactionRepeat("我が家にお越しいただき嬉しいです。私の名前は "+GetFullName(npchar)+"。何かご用ですか？","まだここにいるのか？","ふむ、失礼だが、そろそろお引き取り願えないか？","どうか我々のもてなしに甘えすぎないようお願いしたい。","ブロック",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat(GetFullName(pchar)+" お役に立てます。特に理由もなく、ただあなたと知り合いたくてここに来ました。","まだここにいる。","うーん、どうだろうな……","「いいだろう。」",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("HouseWoman_1", "exit_setOwner", "exit_setOwner", "exit_setOwner", npchar, Dialog.CurrentNode);
				}
				else
				{
					dialog.text = NPCStringReactionRepeat("まあまあ、こんな時間にどうして私の家に押し入るのですか！本当に驚きましたわ……どうか、明日いらしてくださいませ！","どうか、私たちの家から出て行ってください！"+GetSexPhrase("","私は既婚の女よ！")+"","これが最後だ、俺たちの家から出ていってくれ！","「しかし、ここで何が起きているんだ！？」","ブロック",1,npchar,Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat("怖がるな、俺はお前に危害を加えたりしねえよ。","わかった、そんなに興奮するなよ。","俺は行くぜ。","どうした？",npchar,Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("exit_close", "exit_setOwner", "exit_setOwner", "HouseWoman_2", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "HouseWoman_1":
			dialog.text = "いつでもお客様を歓迎します。ただ、あまり長居はしないでくださいね。"+GetSexPhrase("……あたしは既婚の女だから……"," …やることがたくさんあるからな…")+"";
			link.l1 = "「ああ、はい、もちろん……」";
			link.l1.go = "exit_setOwner";
		break;
		case "Woman_FackYou":
			dialog.text = "そういうことか？私はお前を客として迎えたのに、うちの箱をあさっているのか！？\n衛兵！";
			link.l1 = "黙れ、このアマ！";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;
		case "HouseWoman_2":
			dialog.text = "丁寧に家を出てくれとお願いしたのに、あなたは全く聞こうとしなかった！もう我慢できません！助けて！衛兵！";
			link.l1 = "黙れ、この愚かな女め！気でも狂ったのか！？";
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break; 
		//--------------------------------- завсклад ---------------------------------		
		case "SkladMan":
			NextDiag.TempNode = "SkladMan1";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("町で警報が鳴ったようだ。どうやら俺も武器を取る時が来たらしいな……","もしかして、街の衛兵に追われてるんじゃねえか？ ","ここには隠れ場所なんてねえが、肋骨の間に冷たい刃を何本か突き立てられることはあるかもな！"),LinkRandPhrase("何の用だ？"+GetSexPhrase("悪党","悪党")+"？！街の衛兵たちはもうお前の匂いを嗅ぎつけてるぜ、そう遠くへは行けねえぞ。 "+GetSexPhrase("汚ねえ海賊","あばずれ")+"!","汚ねえ殺し屋め！衛兵！","「俺はお前なんか怖くねえ」 "+GetSexPhrase("這い寄る","あばずれ")+"！すぐに砦で絞首刑にされるぞ、お前はもう逃げられねえ……"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("生きるのに飽きちまったようだな……","どうやら、の市民には平穏な生活はないようだ "+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("地獄へ落ちろ！","へっ、これがお前の人生の最後の数秒になるぜ……"));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
				dialog.text = NPCStringReactionRepeat("いらっしゃいませ！私の名前は "+GetFullName(npchar)+"……ここでは俺が仕切ってるんだ、だから何も持ち出そうなんて考えるんじゃねえぞ……","おとなしくしてろよ、俺がちゃんと見張ってることを忘れるな。","宝箱を覗き見しなければ、ここにいてもいいぜ。どうせ一人じゃ退屈だからな……",RandPhraseSimple("あらまあ、退屈ですわ！","くそっ、どうすりゃいいんだ？ここにいるのは退屈でたまらねえ！"),"ブロック",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("わかった、心配するな。","もちろんだぜ！","なるほど……","ああ、それは困ったことだな。",npchar,Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);				
		break;
		
		case "SkladMan1":
			NextDiag.TempNode = "SkladMan1";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("町で警報が鳴ったようだ。どうやら俺も武器を取る時が来たらしいな……","もしかして、街の衛兵たちに追われてるんじゃねえか？ ","ここには隠れる場所なんてねえが、肋骨の間に冷たい刃を何寸か突き立てられることならあるかもな！"),LinkRandPhrase("何の用だ？"+GetSexPhrase("ろくでなし","悪党")+"？！街の衛兵たちはもうお前の匂いを嗅ぎつけてるぜ、そう遠くへは行けねえぞ。 "+GetSexPhrase("汚い海賊","あばずれ")+"!",""+GetSexPhrase("Filthy","Filthy")+" 殺人者だ！衛兵、来てくれ！！","俺はお前なんか怖くねえ、 "+GetSexPhrase("這い寄る","あばずれ")+"！すぐにお前は俺たちの砦で絞首刑だ、逃げ切れると思うなよ…"));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("生きるのに飽きたようだな……","そうらしいな、この町の市民に安らかな暮らしはないようだ "+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("地獄へ落ちろ！","へっ、これがお前の人生の最後の数秒だぜ……"));
				link.l1.go = NPCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			dialog.text = NPCStringReactionRepeat("ここでは俺が仕切ってるんだ、だから何も持ち出そうなんて考えるんじゃねえぞ……","おとなしくしてろよ、俺がちゃんと見張ってることを忘れるな。","宝箱を覗き見しなければ、ここにいてもいいぜ。どうせ一人じゃ退屈だからな……",RandPhraseSimple("あらまあ、退屈ですわ！","くそっ、どうすりゃいいんだ？ここにいるのは退屈でたまらねえ！"),"block",3,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("わかった、心配するな。","もちろんだ！","なるほど……","ああ、それは困ったことだな。",npchar,Dialog.CurrentNode);	
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "exit", npchar, Dialog.CurrentNode);				
			//открывание двери верфи по квесту промышленного шпионажа
			if (CheckAttribute(pchar, "questTemp.different.ShipyardsMap") && pchar.questTemp.different.ShipyardsMap == "toTarget" && npchar.city == pchar.questTemp.different.ShipyardsMap.city && locations[reload_cur_location_index].type == "shipyard")
			{
				link.l2 = "聞けよ、相棒、率直に話したいんだ。";
				link.l2.go = "ShipyardsMap_1";
				pchar.questTemp.different.ShipyardsMap = "toResult";					
			}
			// ugeen --> склад товаров для ГГ				
			if(CheckAttribute(NPChar,"Storage"))
			{
				if(!CheckAttribute(NPChar, "Storage.Speak"))
				{
					dialog.text = "お前さんにとっておきの話があるんだ。興味があるかもしれねえな。";
					link.l7 = "本当か？よし、聞いてやる。";
					link.l7.go = "storage_rent";
				}
				else
				{
					if(CheckAttribute(NPChar,"Storage.Activate"))
					{
						link.l7 = "倉庫まで連れて行け。中の様子を見たいんだ。";
						link.l7.go = "storage_0";
						link.l8 = "倉庫を空けることにした。もう必要ないからな。";
						link.l8.go = "storage_04";
					}
					else
					{
						if(!CheckAttribute(NPChar,"Storage.NoActivate"))
						{
							link.l7 = "倉庫のことを言っていたな。まだ空いているのか？";
							link.l7.go = "storage_01";
						}						
					}
				}		
			// <-- ugeen
			}		
		break;
		
		//--------------------------------- Аренда склада ---------------------------------
		case "storage_rent":
			NPChar.Storage.Speak = true;
			dialog.text = "倉庫に適した場所があります。手頃な価格で借りてみませんか？\n自分専用の倉庫で貴重な積み荷を保管できるんですよ……";
			link.l1 = "倉庫かい？ああ、確かに魅力的だな……十分に広いのか？それと、家賃はいくら取るつもりだ？";
			link.l1.go = "storage_rent1";
		break;
		
		case "storage_rent1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "港の倉庫にしてはかなり広いな。そうだな……5万センターの貨物が収容できるぜ。さて "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+"  月ごとにあなたの品物をお預かりできます。 "+"これには俺の部下と一緒に見張ったり、水浸しにならないように守ったり、ネズミと戦ったりすることも含まれるぜ。 どうだ？ああ、それと機密保持もな、言うまでもねえが。";
			link.l1 = "承知しました。見せていただいてもよろしいですか？";	
			link.l1.go = "storage_rent2";
			link.l2 = "高すぎるぜ。それに、どうせ水浸しでネズミだらけなんだろうな。";
			link.l2.go = "storage_rent3";		
		break;
		
		case "storage_rent2":
			dialog.text = "ああ、わかったよ。でもな…前金で一ヶ月分もらわねえと困るぜ。 ";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "あなたは……なかなかの商人ですね。はい、これが金だ……この小屋を借りるよ。";
				link.l1.go = "storage_11";
			}
			else
			{	
				link.l1 = "お前は……ずいぶん商売熱心だな。よし、金を取ってくるぜ。";
				link.l1.go = "exit";
			}	
		break;
		
		case "storage_rent3":
			dialog.text = "かしこまりました。気が変わったら、いつでも声をかけてください。それと、 こんな立派な倉庫が長く空いたままになることはまずありませんので……";
			link.l1 = "問題ないぜ。必要になったら知らせるよ。";
			link.l1.go = "exit";
		break;
		
		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 
			{
				dialog.text = "それから家賃についてだが、まだ俺に借りがあるぜ  "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = "わかった、今すぐ家賃を払うよ。";
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = "後で戻ってくるぜ。";
					link.l1.go = "exit";
				}
			}		
			else
			{ // лесник . если забыл с собой корабль то никак.
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		        if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{	
				dialog.text = "どうぞ。";
				link.l1 = "ありがとう。";
				link.l1.go = "storage_2";
				}
				else
				{
                dialog.text = RandPhraseSimple("船長、あなたの船はどこだ？どうやって貨物を運ぶつもりだ？","港にお前の船が停泊しているのが見えねえな。いったいどうやって積み込むつもりだ？");
                link.l1 = RandPhraseSimple("あっ…それをすっかり忘れてた！","くそっ、その通りだ！");
			    link.l1.go = "exit";
				break;
                }			
			}
			link.l2 = "いや、気が変わった。";
			link.l2.go = "exit"; 						
		break;
		
		case "storage_01":
			dialog.text = "「いや」 "+GetSexPhrase("旦那","奥様")+"、まだ空いていてあなたを待っているんだ。結局俺の提案を断らないって分かってたぜ。";
			link.l1 = "とてもいいな。借りるぜ。";
			link.l1.go = "storage_1";
			link.l2 = "いや、ただ思い出しただけだ……";
			link.l2.go = "exit";
		break;
		
		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar); 
			dialog.text = "覚えているだろうが、前払いで一ヶ月分の報酬が必要なんだ。";
			if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "もちろん、覚えているよ。はい、どうぞ。";
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = "ちくしょう。わかった、金を取ってくるぜ。";
				link.l1.go = "exit";
			}
		break;
		
		case "storage_11":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForStorage)); 
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			NPChar.Storage.Activate = true;
			Achievment_Set("ach_67"); // ugeen 2016
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
				
		case "storage_2":			
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;
		
		case "storage_3":			
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));			
		break;		

		case "storage_04":
			dialog.text = "もうお帰りですか？残念ですね、ここは本当に素晴らしい場所で、条件も最高なんですよ。カリブ中どこを探しても、 こんな取引は他にありませんよ、保証します。";
			link.l1 = "言っただろ、俺はここを引き払うんだ。\nそれとも空気の保管料でも払えってのか？\n他の借り手でも探すんだな。";
			link.l1.go = "storage_4";
			link.l2 = "カリブのどこにもないって言うのか？\nまあ、しばらく預かっておくとするか。\nだが、家賃がちょっと高すぎるぜ。";
			link.l2.go = "exit";
		break;
		
		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar,"Storage.Date") * sti(NPChar.Storage.MoneyForStorage); 
			if(sti(NPChar.MoneyForStorage) > 0) 			
			{
				dialog.text = "それから家賃についてだが、まだ俺に借りがあるぞ "+FindRussianMoneyString(sti(NPChar.MoneyForStorage))+".";
				if(sti(pchar.money) >= sti(NPChar.MoneyForStorage))			
				{
					link.l1 = "「いいだろう。」";
					link.l1.go = "storage_5";
				}
			}
			else
			{ // лесник . если нет корабля то и товар не забрать
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		        if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{	
				dialog.text = "荷物を集めてくれ、俺が倉庫を閉める。";
				link.l1 = "「いいだろう。」";
				link.l1.go = "storage_6";
				}
				else
				{
                dialog.text = RandPhraseSimple("船長、あなたの船はどこにあるんだ？荷物をどうやって運ぶつもりだ？","港にお前の船が停泊しているのが見えねえな。いったいどうやって積み込むつもりだ？");
                link.l1 = RandPhraseSimple("「あっ…それをすっかり忘れてた！」","くそっ、その通りだ！");
			    link.l1.go = "exit";
				break;
                }				
			}
		break;
		
		case "storage_5":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage)); 
			NPChar.Storage.NoActivate = true;
			DeleteAttribute(NPChar,"Storage.Activate");
			DialogExit();
		break;
		
		case "storage_6":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			DeleteAttribute(NPChar,"Storage.Activate");
			NPChar.Storage.NoActivate = true;
			DialogExit();
		break;		

		//--------------------------------- Аренда склада ---------------------------------
		
		case "ShipyardsMap_1":
			dialog.text = "へっ！よし、話そうぜ。";
			link.l1 = "誰もいない夜に造船所へ行く必要があるんだ。";
			link.l1.go = "ShipyardsMap_2";
		break;
		case "ShipyardsMap_2":
			if (sti(pchar.questTemp.different.ShipyardsMap.skladFight))
			{
				dialog.text = "見ろよ！おい、衛兵ども、ここに泥棒がいるぞ！！！";
				link.l1 = "「泥棒だって？俺はただ話がしたかっただけだ！」";
				link.l1.go = "fight";
				AddCharacterExpToSkill(pchar, "FencingL", 5);
				AddCharacterExpToSkill(pchar, "FencingS", 5);
				AddCharacterExpToSkill(pchar, "FencingH", 5);
				ChangeCharacterComplexReputation(pchar,"nobility", -1);
			}
			else
			{
				dialog.text = "おったまげたぜ！お前を見ろよ、 "+GetSexPhrase("相棒","娘")+"。そんな頼みごとを持って造船所の倉庫に来るなんて！";
				link.l1 = "俺は造船所に行く必要があるんだ。お前の倉庫なんざどうでもいいぜ。";
				link.l1.go = "ShipyardsMap_3";
				AddCharacterExpToSkill(pchar, "Fortune", 10);
			}
		break;
		case "ShipyardsMap_3":
			dialog.text = "「でも、なぜそれが必要なんだ？」";
			link.l1 = "必要があるんだ。そして、そのためなら金を払うつもりだ……";
			link.l1.go = "ShipyardsMap_4";
		break;
		case "ShipyardsMap_4":
			dialog.text = "ふむ、これでよし……よし！さあ、渡してくれ "+FindRussianMoneyString(sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000)+"、それで翌日には造船所の扉を開けておくよ。";
			link.l1 = "それは高すぎるな。じゃあ、諦めるしかねえか……";
			link.l1.go = "exit";
			if (sti(pchar.money) >= (sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000))
			{
				link.l2 = "よし、わかった。約束通りに金を受け取ってやる。";
				link.l2.go = "ShipyardsMap_5";
			}
		break;
		case "ShipyardsMap_5":
			dialog.text = "心配するな、必ずやってみせる。";
			link.l1 = "そうだといいんだが……";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.ShipyardsMap.sklad)*1000);
			AddQuestRecord("ShipyardsMap", "5");
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			//снимаем close_for_night
			string  sName;
			int location_index = FindLocation(npchar.city + "_town");
    		makearef(arRld, Locations[location_index].reload);
    		Qty = GetAttributesNum(arRld);
    		for (int a=0; a<Qty; a++)
    		{
    			arDis = GetAttributeN(arRld, a);
				sName = arDis.go;
    			if (findsubstr(sName, "_shipyard" , 0) != -1)
    			{
					DeleteAttribute(arDis, "close_for_night");
					break;
    			}
    		}
			LocatorReloadEnterDisable(npchar.city + "_shipyard", "reload2", true);
			//ставим таймер на возврат close_for_night
			SetTimerFunction("ShipyardsMap_returnCFN", 0, 0, 2);
		break;

	}
}
