void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sGroup;
	bool bOk, bOk1;
	
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	int iTemp = sti(npchar.EncQty);
	string sTemp = "Gang" + locations[FindLocation(npchar.location)].index + "_";

	switch(Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();			
		break;

		case "exit_Robbed":
			int iMoney = makeint(makeint(Pchar.money)/20)*10;
			AddMoneyToCharacter(pchar, -iMoney);
			AddSimpleRumour(LinkRandPhrase("Have you heard? The local robber " + GetFullName(npchar) + " found a new victim. One captain got scared and bought off. They say, he gave him " + FindRussianMoneyString(iMoney) + ", he-he... ", 
				"Yeah, captain " + GetFullName(pchar) + ", I already heard that you had to pay " + FindRussianMoneyString(iMoney) + ", to buy off a local bandit, " + GetFullName(npchar) + ". Now that's what I call bad luck! Ha-ha-ha!", 
				"Have you heard that the local bandits attacked one captain? He was totally robbed, he lost " + FindRussianMoneyString(iMoney) + "!"), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "OnceAgain";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}
			DialogExit();			
		break;

		case "exit_fight":
			sGroup = "RaidersGroup_" + locations[FindLocation(npchar.location)].index;
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, sGroup);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "LandEnc_RaidersAfrer");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_RunFight":
			AddSimpleRumour(LinkRandPhrase(RandPhraseSimple("Have you heard? That bandit " + GetFullName(npchar) + " has finally found justice. He and his boys tried to rob "+ GetSexPhrase("some captain, but he turned out to be","some lady captain, but she turned out to be") +" a tough nut. So our dear robber shited his pants, ha-ha! That will be a lesson for him! Robbing the local farmers is one thing, but a brave captain is a different story!", 
				"Thank you, captain " + GetFullName(pchar) + ", for finally dealing with the gang of that bandit " + GetFullName(npchar) + ". Those rascals were really a pain in everyone's ass. We were scared to even send couriers to the farm for milk, they could have intercepted them and rob of all the money."), 
				"Have you heard, "+ GetSexPhrase("finally, some captain","finally, some lady captain") +" stopped that rascal " + GetFullName(npchar) + ", who was in 'charge' of the jungle, terrorizing all the local farmers. I do hope, it will stop them from their dirty deeds for long enough...", 
				"Have you heard that local bandit " + GetFullName(npchar) + " and his boys attempted to rob "+ GetSexPhrase("some captain","some lady captain") +"? Bah! Nothing of the sort! That captain turned out to be a tough nut. They say, he chased on these robbers over all the jungle like a shark chases flock of sardines. Thank God that there are still people who can stand up for us at time when the authorities do nothing, too busy with their dark deeds..."), sti(npchar.nation), 5, 1);
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_ActorAfraid(sld, Pchar, true);
				sld.Dialog.CurrentNode = "GetTheHellOut";
			}
			DialogExit();
		break;

		case "exit_noFight":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				sld.LifeDay = 0;
				LAi_SetWarriorTypeNoGroup(sld);
				sld.Dialog.CurrentNode = "GetLost";
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld)-1, true, "LandEnc_RaidersBeforeDialog");
			}		
			DialogExit();			
		break;

		case "First Time":
			for(i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetImmortal(sld, false);
			}
			dialog.text = LinkRandPhrase(LinkRandPhrase("そこに立て、武器を捨てろ！金を出すか、命を落とすかだ！","その場を動くな "+GetSexPhrase("旅人","娘")+"！）武器に手を出すな、そして急な動きはするな！","「そこを動くな」 "+GetSexPhrase("旅人","娘")+"！ここは通行料が必要な道だ。通りたきゃ、通行料を払え。"),LinkRandPhrase("「おい、」 "+GetSexPhrase("相棒","娘")+"！待て、そんなに急ぐな！お前の財布がどれだけ重いか見せてもらおうじゃねえか。","もっと近くに来てくれないか、友よ？お前の財布の中で金貨が鳴る音を聞きたいんだ。","「待て、」 "+GetSexPhrase("相棒","娘")+"。俺たち仲間と賭けをしたんだ、お前の財布にどれだけ金貨が入るかってな。さあ、 暴れになる前に中身を確認しねえとな。"),"「急ぐな」 "+GetSexPhrase("旅人","「あなた」")+"！腹を割って話そうじゃねえか？");				
			Link.l1 = LinkRandPhrase(LinkRandPhrase("「なんでそんな馬鹿なことを言うんだ？」","どうした？","何の話だ？"),"どういう意味だ？","「一体何を言いたいんだ？」");
			Link.l1.go = "Node_2";
			Link.l2 = LinkRandPhrase(LinkRandPhrase("山賊どもか！？いいぞ、戦いを待ち望んでたんだぜ！","おお、お前らは盗賊か！正義から逃げているんだろう？だが、どうやらその正義が今ここに来たようだな……","見ず知らずの人にくだらない話をふっかけるのは無作法だって教わらなかったのか？ どうやら俺がその礼儀を叩き込んでやる必要がありそうだな……"),LinkRandPhrase("おい、お前はずいぶん生意気じゃねえか！？その舌と同じくらい剣も切れるといいがな。","舌の使い方は達者なようだな、剣の腕前も同じくらいだといいがな。","おお、盗賊どもめ！お前らの仲間は何人も絞首台送りにされてきたのに、まだ自分から死に急ぐつもりか。"),LinkRandPhrase(RandPhraseSimple("おい、野郎ども！俺はな、普段お前らみたいな連中に言葉なんざかけねえんだよ！","なんて無礼な野郎だ！蒸れたクソの山みてえな臭いしやがって、それでもまともな\n "+GetSexPhrase("野郎","少女")+"."),"お前と無駄話はしねえが、俺のピストルは雄弁だぜ！","また山賊か！まあ、絞首台は約束できねえが、腹に二つ三つ穴を開けてやることはできるぜ！"));
			Link.l2.go = "CheckSkills";	
			Link.l3 = LinkRandPhrase("お前、俺の後ろを巡回隊がぴったり追ってるのを知ってるか？俺がちょっと口笛でも吹けば、お前は終わりだぜ。",RandPhraseSimple("知ってるか、俺は巡回隊を呼べるんだぜ。怖くねえのか？あいつらはすぐ近くにいるんだ。 お前を探してるんじゃねえかと思うぜ。","最近、あなたを捜索するために巡回隊が派遣されたばかりで、いつ現れてもおかしくない状況です。 大きな危険を冒していますよ。"),RandPhraseSimple("できるだけ早く逃げたほうがいいぜ。巡回隊がこっちに向かってるんだ。さっきそこの隊長と話したばかりだ。","喜んで会話を続けたいところだが、さっき出会った巡回隊が俺たちの仲を深めさせてはくれそうにないな。"));
			Link.l3.go = "Node_3";
		break;
		
		case "Node_2":
			dialog.text = LinkRandPhrase(LinkRandPhrase("ふざけるんじゃねえ！金を即座に払え、そうすりゃお前を放してやるかもな！","旅の通行料を聞いたことがねえのか？金を出さなきゃ、首を出すことになるぜ！","へっ、このちょっとした冒険は財布が飛ぶぜ……俺が怒らなきゃな。"),RandPhraseSimple("とても簡単なことだ。お前が持ってる金を全部渡せば、自由に立ち去っていい。だが、ここにとどまるなら、 どうせ俺たちが全部奪うだけだぜ。もっとも、後者はお前の望むところじゃねえだろうが、へっへっへ。","とぼけてんじゃねえぞ！死にたくなけりゃ財布をよこせ、さもなきゃ死体から奪うことになるぜ！"),"説明してやるよ、そんなに頭が悪いならな。命が惜しけりゃ、持ってる金を全部よこせ。");
			Link.l1 = "ちくしょう、このろくでなしめ！俺にはまだ "+makeint(makeint(Pchar.money)/20)*10+" ペソ。";
			Link.l1.go = "CheckMoney";
			Link.l2 = LinkRandPhrase(LinkRandPhrase("俺の金が欲しいのか？取りに来いよ、てめえの価値を見せてもらおうじゃねえか！","なんて無礼な奴だ！礼儀ってものを叩き込んでやるぞ！","なんて自信満々なんだ！さて、本物を相手にどうなるか見せてもらおう "+GetSexPhrase("海狼","「ルーヴ・デ・メール」")+"!"),LinkRandPhrase("こんな無礼を働いたら鞭打ちの刑にされるべきだぞ！","貴様ら悪党どもめ！地獄で温かい場所を悪魔に祈っておけ！","お前らみたいな絞首台の鳥はとっくに吊るされてるべきだったんだ！\nまあいい、俺のサーベルをお前らの血で染めてやるしかねえな！"),RandPhraseSimple("「俺がなんでお前に金を渡さなきゃならねえんだ？」","それに、俺がしっかり武装してて、ただの散歩でここに来たわけじゃねえって気づかなかったのか？"));
			Link.l2.go = "CheckSkills";	
		break;

		case "Node_3":
			bOk = makeint(pchar.reputation.nobility) < 11 || makeint(pchar.reputation.nobility) > 90;  
			if(bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) == 100 || CheckCharacterPerk(pchar, "Trustworthy") || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				dialog.text = RandPhraseSimple("ちくしょう！よし、行っていいぜ。だが、ここにいる間は絶対に騒ぐんじゃねえぞ！","今回は運が良かったな、だが次は倍の額を払ってもらうぜ！忘れずに俺たちに知らせるんだな、へっへっ。");
				Link.l1 = RandPhraseSimple("「もちろんだ。」","今のうちに逃げろ、まだ間に合ううちにな。");
				Link.l1.go = "Exit_NoFight";
			}
			else
			{
				bOk = makeint(pchar.reputation.nobility) < 51 && makeint(pchar.reputation.nobility) > 41; // Captain Beltrop, 23.01.21 - жесть!!! Надо было всего лишь убрать единичку!
				if(!bOk || GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 35)
				{
					dialog.text = RandPhraseSimple("静かにお前を始末してやるぜ、一声も上げさせねえからな。","くそっ！お前が警報を鳴らす前にさっさと始末しねえとな。");
					Link.l1 = "ふん、これはお前の葬式だぜ。警告はしたからな。";
					Link.l1.go = "Exit_Fight";
				}
				else
				{
					dialog.text = RandPhraseSimple("「で、なんで俺があんたの巡回なんか気にしなきゃならねえんだ？俺が奴らに金を払ってるんだぜ。さあ、 財布をよこして、くだらねえ口を閉じな。」","俺を脅せると思ってるのか？このジャングルでお前みたいな奴を見張ってるのは俺自身だぜ。今まで誰一人、 料金を払わずにここを出た奴はいねえ！");
					Link.l1 = "くそっ、このろくでなしめ！俺にはまだ "+makeint(makeint(Pchar.money)/20)*10+" ペソ。";
					Link.l1.go = "CheckMoney";	
					Link.l2 = RandPhraseSimple(LinkRandPhrase("へっ、俺はお前みたいな腰抜けの命令なんか聞かねえぞ。","そんな生意気な口をききやがって、頭に新しい穴を二つ開けてやるぜ！ちょっと脳みそに風通ししてやるんだ。","そのような無礼、許しておかねえぞ！"),"そんなこと、するべきじゃなかったんだ……");
					Link.l2.go = "CheckSkills";
				}
			}
		break;
		
		case "CheckSkills":
		    bool isStrong = (GetCharacterSkillToOld(Pchar, "FencingL") >= 7) || (GetCharacterSkillToOld(Pchar, "FencingS") >= 7) || (GetCharacterSkillToOld(Pchar, "FencingH") >= 7);
			bool z_ok = (isStrong) && (makeint(Pchar.Rank) >= 8) && (Makeint(PChar.reputation.nobility) <= 30); // Captain Beltrop & mitrokosta, 23.01.21 проверяем на оружие (новый вариант)
			if (z_ok || CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				Diag.TempNode = "GetLost";
				dialog.text = LinkRandPhrase(RandPhraseSimple("「おい、そんなに興奮するなよ、」 "+GetSexPhrase("相棒","娘")+"！冗談だって！もう行っていいぜ！","よし、考えを変えた。そんなに手強いなら、行ってもいいぜ。"),"なんだ、 "+GetSexPhrase("『勇敢な船長』","『戦う娘』")+"「またか？まあいい、安らかに行け……」","「落ち着け」 "+GetSexPhrase("相棒","娘")+"。実は、俺たちが間違っていたんだ、 "+GetSexPhrase(" 俺たちはあんたを商人だと思ってたぜ"," 俺たちはあんたを商人だと思ってたぜ")+"。行ってよい。");
				Link.l1 = LinkRandPhrase(LinkRandPhrase("よし、また会う日までな！","まだできるうちに、人を襲うのはやめておいたほうがいいぜ。","わかった、だが次にお前に会ったら……"),RandPhraseSimple("次は、誰に脅しをかけているのかよく考えろ、この野郎。","今日は機嫌がいいから、神に感謝だ。"),RandPhraseSimple("この悪どい商売はいずれお前を破滅させるだろう。さらばだ。","それは賢明な判断だ。では、幸運を祈る！"));
				Link.l1.go = "Exit_NoFight";
				Link.l99 = LinkRandPhrase("いや、友よ。今から礼儀ってものを教えてやるぜ！","おう、びびったか？まあ、自分のやったことには責任を取らなきゃな、そうだろ？","「いやだ！お前の皮を生きたまま剥ぐまでは、俺は絶対に落ち着かねえ！」");
				Link.l99.go = "GetTheHellOut";
			}
			else 
			{
				dialog.text = LinkRandPhrase("お前は穏便に済ませることもできたんだぜ！今となっちゃ、自業自得だな！","始めたのはお前が悪いんだ、このろくでなしめ！今から犬みたいに死ぬがいい！","ああ、そうかよ！てめえをバラバラにしてやるぜ！肝を引きずり出して犬どもに食わせてやる！");
				Link.l1 = RandPhraseSimple("てめえの言葉をそのまま喉に突っ込んでやるぜ！","誰に脅しをかけてるんだ、このクズ野郎！？");
				Link.l1.go = "Exit_Fight";
			}
		break;

		case "CheckMoney":
			if(makeint(makeint(Pchar.money)/20)*10 >= makeint(Pchar.rank)*100)
			{
				Diag.TempNode = "OnceAgain";
				dialog.text = LinkRandPhrase(RandPhraseSimple("よし！渡せ、そしてとっとと失せろ！","大した額じゃねえが、何もないよりはマシだな。頭の切れる奴と取引できてよかったぜ！もう行っていいぞ。"),"それはまた別の話だぜ！俺の友達がよく言ってたんだ、「賢い奴の話を聞くのも悪くねえが、 馬鹿と話す方がずっと面白い」ってな！へへ！","お前の金と引き換えに、ひとつ忠告してやるぜ：もしお前が\n "+GetSexPhrase("そんな腰抜けだな。酒場でラムでも飲んでろ、そうすりゃお前も財布も無事でいられるぜ！","娘さん。盗まれただけで済んだのは、まだましな方だぜ。")+".");
				Link.l1 = "くたばりやがれ！";
				Link.l1.go = "Exit_Robbed";				
			}
			else
			{
				dialog.text = "お前、俺を騙そうとしてるんだな！心配すんな、ナイフでくすぐってやるぜ、そしたら何か落とすかもな。";
				Link.l1 = "くそっ！";
				Link.l1.go = "Exit_Fight";				
			}				
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = LinkRandPhrase("またお前か？俺が怒る前に母ちゃんのところへ帰りな！","何だと？まだ全部の金貨を渡してねえのか？ははっ！","「見ろ、」 "+GetSexPhrase("相棒","娘")+"「もううんざりだ！生きてるうちに俺の目の前から消え失せろ！」");
			Link.l1 = "ああ、もう行くぜ。";
			Link.l1.go = "Exit";
			Link.l2 = "不公平だと思ったんだ。だから、俺は正すことにした……";
			Link.l2.go = "Exit_Fight";
		break;
				
		case "GetLost":
			Diag.TempNode = "GetLost";
			dialog.text = LinkRandPhrase("他に何が必要なんだ？もう出ていくって話はついてるだろう！","「俺にかまうな」 "+GetSexPhrase("野郎","娘")+"。俺は俺のことだけ考えてるし、お前にもお前の事情がある。だから、無理に仲良くしようとする必要なんてねえんだよ！ ","「今すぐ出て行け」 "+GetSexPhrase("相棒","娘")+"！くそっ、本当に全部の金を差し出すつもりか？");
			Link.l1 = "ああ、もう行くぜ。";
			Link.l1.go = "Exit";
			Link.l2 = "お前が別れの挨拶をしなかったことを思い出したぜ！だから、きちんとお別れを言おうじゃねえか…";
			Link.l2.go = "Exit_Fight";
		break;

		case "GetTheHellOut":
			Diag.TempNode = "GetTheHellOut";
			dialog.text = LinkRandPhrase("ほっといてくれ！助けてくれ！生きたいんだ！","助けてくれ！ "+GetSexPhrase("奴は狂人だ","あいつは狂人だ")+"！殺さないでくれ！","助けてくれ！俺はただのしがない野盗だ！死ぬにはまだ若すぎるんだ！");
			Link.l1 = LinkRandPhrase(LinkRandPhrase("家にいれば、生き延びられたのに！","そんなこと、前に考えておくべきだったんだぜ！","結果は必ず伴うってこと、知っておくべきだったんだぜ！"),"遅かれ早かれ、こうなる運命だったんだ。","今さら悔やんでも遅いぜ、かかってこい、このクズ野郎！");
			Link.l1.go = "exit_Fight";			
		break; 				
	}
}
