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
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "何の用だ？";
			link.l1 = "「何でもない。」";
			link.l1.go = "exit";
		break;

		case "Naemnik":
			dialog.text = "お前、なかなかやるじゃねえか"+GetSexPhrase("","ess")+"……くそ、うまい"+GetSexPhrase("","エス")+"。だが、その仕事を終える前に、俺の話を聞いてくれ。きっと興味を引く話だと思うぜ。";
			link.l1 = "死ぬ前に最後の言葉ぐらいはしゃべらせてやるよ。\nだが、期待するな。この洞窟からは生きて出られねえぜ。";
			link.l1.go = "Naemnik_2";
		break;

		case "Naemnik_2":
			dialog.text = "港の親分か、ふん？俺の首を取りにお前を寄越したのか？";
			link.l1 = "相変わらず鋭いな。";
			link.l1.go = "Naemnik_3";
		break;

		case "Naemnik_3":
			dialog.text = "奴はお前に俺を殺せと命じたんだろう？見つけるためでも、捕まえるためでもなく――殺すために、だ。";
			link.l1 = "そうだぜ。それがどうした？";
			link.l1.go = "Naemnik_4";
		break;

		case "Naemnik_4":
			dialog.text = "はは……お前は本当に "+GetSexPhrase("うすのろ","小さなお馬鹿")+"。お前は考えたことがあるか？なぜあいつが俺を牢屋で朽ち果てさせるよりも、死なせることにこだわったのかを。 ないだろう？お前は自分が誰を救おうとしているのか、まるで分かっちゃいねえ。あの港の蜘蛛野郎が、 この場所全体に嘘の巣を張り巡らせてるんだ、そしてお前は、\n "+GetSexPhrase("少年","「あなた」")+"、どっぷりとハマっちまってるんだよ。\nあいつが正直な役人だと思ってるのか？はっ！正直者の夢を見るのは寝てるときだけさ。 海賊やオランダ野郎に情報を売りさばき、信じた奴らを裏切る。あんなクズは地面の下がお似合いだぜ！";
			link.l1 = "誰だって靴で泥を踏むもんさ。あんたも修道士には見えねえな。";
			link.l1.go = "Naemnik_5";
		break;

		case "Naemnik_5":
			dialog.text = "俺は坊主じゃねえし、そんなふりもしねえ。俺の剣は決して嘘をつかねえ。一目見りゃ、相手は死神が来たと悟るもんだ。 獲物に笑いかけたり、どうせ死ぬと知ってて握手したりなんてしねえ。違う。俺の覚悟ははっきりしてる。あの役人か？\nあいつは助けるふりして信じた奴ら全員を裏切るんだ。俺が墓に送ったどんなクズよりもタチが悪いぜ。";
			link.l1 = "お前が本当のことを言ってるとしよう。誰に雇われたんだ？";
			link.l1.go = "Naemnik_6";
		break;

		case "Naemnik_6":
			dialog.text = "名前なんて教えねえ――俺も知らねえからな。だが、あのクズにひどい目に遭わされた奴だ。正義を求める男……いや、復讐かもしれねえ。好きなように呼べ。あの腐れ役人の首一つで五百ドゥブロンだ！手を貸してくれりゃ、 報酬は山分けだぜ。";
			link.l1 = "くだらねえ話はもうたくさんだ！命乞いのためなら何だって言うんだろうが。しゃべらせてやったんだ、 今度は死ぬ番だぜ。";
			link.l1.go = "Naemnik_7";
			link.l2 = "面白い話だな。だが、そう簡単には信じねえぜ。お前の言葉以外に何かあるのか？証拠や証人は？それとも、 これも死を逃れるための新たな企みか？";
			link.l2.go = "Naemnik_8";
		break;
		
		case "Naemnik_7":
			DialogExit();
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("GS_Naemnik");
			LAi_SetImmortal(sld, false);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "GS_UbivaemNaemnika");
		break;
		
		case "Naemnik_8":
			dialog.text = "これらの羊皮紙は、私の後援者が戦いで打ち倒した私掠船乗りの部屋で発見されたものだ。その悪党は、 他ならぬ港の長官自身から情報を受け取っていた。ここには、船の航路、出港時刻、積荷の内容が細かく記録されている。 同じ船が後に襲われ、乗組員は殺されるか、果てしない青の彼方へと消えたのだ\nよく覚えておけ――この記録の筆跡は、公式の積荷目録と寸分違わぬものだ。この証拠が裏切り者の正体を暴くことになる。私の後援者は、 これらの書類が奴の死体の上に見つかることを望んでいる。判事の法廷などでは不十分だ\nこの悪党はあまりにも権力を握り、数えきれぬほどの腐敗した仲間を従えている。もし法廷に引き出したところで、 奴は正義の手から巧みに逃れるだろう。このような害虫に神の息吹を受ける資格などない。 永遠の悪名と共に死ぬことこそ、かかる裏切り者にふさわしい。";
			link.l1 = "裏切り者の犬め！男たちは自分の運命まで託しているってのに、あいつはその命を殺し屋や盗賊どもに売り渡しやがる！ この件、俺も味方だぜ。そんな奴、神の御許の下に生きる資格なんざねえよ。";
			link.l1.go = "Naemnik_9";
			GiveItem2Character(PChar, "GS_letters");
			AddQuestRecordInfo("GS_Letters", "1");
		break;

		case "Naemnik_9":
			dialog.text = "あの貴族の屋敷で家具を修理していた大工を通じて、奴の住居の鍵を手に入れたんだ。計画通りに進んでいたが、 奴が部屋を誰かと共有していることに気付いた。正義を下すために中へ入ったら、奥方がそこにいたんだ\n予想外の同席に、俺は一瞬ためらった。彼女の血に懸賞金はかかっていないし、 身分ある女を殺せば王冠の手先どもがもっと必死で追ってくるだろう。だから計画を変えて、 税関近くで奴を待ち伏せすることにしたのさ。";
			link.l1 = "ちくしょうめ！今や町中が警戒してやがる――以前みたいに堂々と手を出すことはできねえ。俺たちに残された道は何だ？";
			link.l1.go = "Naemnik_10";
		break;

		case "Naemnik_10":
			dialog.text = "俺は町を見張りながら、騒ぎが収まるのをじっと待っていたんだ。俺が動いた後、 あの臆病なネズミ野郎は慌てて女房を隠しやがった。俺の目で、あいつの女房が船に乗って港を出ていくのを見たぜ\n今やあいつは一人きり――始めたことを終わらせるには絶好の機会だ。闇に紛れてあいつの巣に忍び込み、この仕事にケリをつけろ。それから、 この証拠書類を誰の目にもつく場所に置いてやれ。そうすれば、 あいつの心に巣食っていた腐敗が誰の目にも明らかになる\nだが俺には町の門が閉ざされている。だが、お前なら……お前なら俺にできないことができる。衛兵どもはお前の顔を探していないし、見張りも簡単にすり抜けられるはずだ。 あいつの家は市の牢獄の近くだ。五百ドゥブロン！裏切り者が死んだら、その半分はお前のものだ。";
			link.l1 = "よかろう。この悪党は俺の手で成敗し、あの世へ送ってやる。証拠の書類は奴の屋敷に残しておく――奴の裏切りの真実を皆が知るためにな。\n俺の帰りを待っていろ。正義を果たしたら必ず戻る。";
			link.l1.go = "Naemnik_11";
		break;
		
		case "Naemnik_11":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Beliz_Cave")].DisableEncounters = false;
			AddQuestRecord("GS", "5");
			AddQuestUserData("GS", "sSex", GetSexPhrase("","а"));
			
			sld = CharacterFromID("GS_Naemnik");
			LAi_SetWarriorType(sld);
			LAi_SetCurHPMax(sld);
			LAi_GetCharacterMaxEnergy(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PEACE);
			NextDiag.CurrentNode = "Naemnik_12";
			
			sld = &Locations[FindLocation("Beliz_town")];
			sld.reload.l11.open_for_night = 1;
			sld = &Locations[FindLocation("Beliz_houseS5_room2")];
			sld.locators_radius.item.button01 = 1.0;
			
			pchar.quest.GS_SoldatyDoma.win_condition.l1 = "Hour";
			pchar.quest.GS_SoldatyDoma.win_condition.l1.start.hour = 0.00;
			pchar.quest.GS_SoldatyDoma.win_condition.l1.finish.hour = 5.00;
			PChar.quest.GS_SoldatyDoma.win_condition.l2 = "location";
			PChar.quest.GS_SoldatyDoma.win_condition.l2.location = "Beliz_houseS5";
			PChar.quest.GS_SoldatyDoma.function = "GS_SoldatyDoma";
		break;
		
		case "Naemnik_12":
			dialog.text = "「どうしてそこに突っ立ったまま固まってるんだ、まるで足が石灰にでも埋まったみてえに？」";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Naemnik_12";
		break;

		case "Portman_1":
			dialog.text = "お前か？なんだと？どうやってここに入ったんだ？";
			link.l1 = "俺がここに来た理由なんてどうでもいいさ。\nそれに、お前も心の奥では俺が来た理由を分かってるはずだ。";
			link.l1.go = "Portman_2";
			DelLandQuestMark(npchar);
		break;

		case "Portman_2":
			dialog.text = "いいや、わからない！報酬が目当てなら、明日役所に来い、全部渡してやる。";
			link.l1 = "とぼけるのはやめろ！俺は全部知ってるんだ。お前は客の船の情報を海賊に売ったんだろう。 そんな卑劣な奴がこの地位にいる資格はねえ。\nそれどころか、正直者たちと一緒に暮らす資格もねえんだ。旦那、お前の居場所は同類の連中と一緒――地獄だ。";
			link.l1.go = "Portman_3";
		break;

		case "Portman_3":
			dialog.text = "ああ、ち、違う！違うんだ！誤解だよ！や、奴らが無理やり……俺に脅しをかけてきて、協力しなきゃ家族に手を出すって……わ、分かってくれよ……";
			link.l1 = "お前のみっともない言い訳にはもううんざりだ！俺の手元には、 お前がチップの取り分を要求している証拠の書き付けがあるんだぜ！その偽善ぶりには反吐が出る、 もう我慢するつもりはねえ。武器を抜いて身を守れ、もしその度胸があるならな！";
			link.l1.go = "Portman_4";
		break;
		
		case "Portman_4":
			DialogExit();
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			
			sld = CharacterFromID("Beliz_portman_clone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "GS_PortmanDead");
		break;
		
		case "Naemnik_21":
			dialog.text = "それで、どうだ？何か知らせはあるか？俺たちの取引はこれで終わりか？";
			link.l1 = "俺のことを疑ってたのか？あの哀れな奴は、必死になって口からみじめな言い訳を絞り出そうとしたが、 全く無駄だったぜ。俺は約束通り、決定的な証拠の書類を絶対に見逃せない場所に置いておいた。";
			link.l1.go = "Naemnik_22";
		break;

		case "Naemnik_22":
			dialog.text = "あいつみたいな腰抜け野郎は、いつだって卑劣な嘘と金で正義の刃から赦しを買えると思い込んでやがるんだ。";
			link.l1 = "もうあいつは悩むことはねえさ。報酬を渡してくれ、そしたら俺は引き上げるぜ。";
			link.l1.go = "Naemnik_23";
		break;

		case "Naemnik_23":
			dialog.text = "これがあんたのドゥブロンだ、正当に稼いだ分だぜ。見事な働きだった、そこは認めてやる。だがよく覚えとけ――もし最初に刃を交えたとき、俺の手にもっと重い鋼があったなら、運命はまるで違ったものになってたかもしれねえ……あんたにとっちゃ、悔やんでも悔やみきれねえ結果になってただろうよ。あの狭っ苦しい部屋じゃ、 まともな武器は振り回せねえからな、仕方なくこの情けねえ爪楊枝一本で、手早く片付けてやろうと思ったんだ\nだが、もし事の成り行きを予見してたら、俺の器量にふさわしい剣を持ってきたさ。";
			link.l1 = "ははっ！あの世に行った仲間は、ロンセスバリェスの峡谷でローランのごとく武装していたとお前のことを言ってたぜ！ だが、実際はとんだパラディンだったな。";
			link.l1.go = "Naemnik_24";
			AddItems(pchar, "gold_dublon", 250);
		break;

		case "Naemnik_24":
			dialog.text = "へっ。恐怖ってのは大きな影を落とすもんだろ？お前自身の目で見ただろう、 俺がそのちっぽけな食器ナイフでお前の鼓動する心臓をもう少しで貫くところをよ。";
			link.l1 = "「もっと重い鋼を手にしていれば、俺の相手にふさわしい強敵になれたとでも言うのか？」";
			link.l1.go = "Naemnik_25";
		break;

		case "Naemnik_25":
			dialog.text = "中量級の刃物の扱いにおいて、俺の腕前に勝る者はいねえ――この命にかけて誓うぜ。疑うのか？いいだろう。今から俺が数々の危機を生き抜いてきた秘伝の技を教えてやる。 よく聞け――これは自慢話なんかじゃねえ、いつかお前を早死にから救うかもしれねえ知恵だ。こんな奥義は、 選ばれた価値ある弟子にしか伝えねえもんだぞ。";
			link.l1 = "...";
			link.l1.go = "Naemnik_26";
		break;
		
		case "Naemnik_26":
			DialogExit();
			SetLaunchFrameFormParam("An hour passes...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("GS_Spravedlivost_2", 0.0);
			LaunchFrameForm();
		break;

		case "Naemnik_27":
			dialog.text = "...";
			link.l1 = "なるほど、あなたは確かにその道の達人ですね。ご指導に感謝します。\nしかし、もしこれで用が済んだのなら、私はそろそろ失礼しなければなりません。";
			link.l1.go = "Naemnik_28";
			AddComplexSelfExpToScill(0, 500, 0, 0);
		break;

		case "Naemnik_28":
			dialog.text = "「ごきげんよう」 "+GetSexPhrase("船長","麗しきご婦人")+"。もう二度と刃を交えることがないよう願おう。お前をあの世に送るのは俺にとっても辛いからな。ははっ。";
			link.l1 = "俺が泥酔して片足で立っていたとしても、お前には勝ち目なんてこれっぽっちもねえぜ！じゃあな、傭兵。";
			link.l1.go = "Naemnik_29";
		break;
		
		case "Naemnik_29":
			DialogExit();
			AddDialogExitQuestFunction("Naemnik_29");
			
			AddSimpleRumourCity("Word has it the Port Chief was found dead in his own home. Documents were discovered on his body proving his involvement in the disappearance of ships. Just imagine—what a disgrace for our town...", "Beliz", 30, 1, "");
			AddSimpleRumourCity("Have you heard the news? Someone snuck into the Port Chief’s house, killed the guards, and took him out. They found notes on the body with routes of missing ships—written in his own hand! A servant of the Crown, yet a traitor in truth! Got what he deserved! And where was the Governor all these years?", "Beliz", 30, 1, "");
			AddSimpleRumourCity("The Port Master is dead! Killed right in his own home! The guards were slaughtered, and among his possessions were notes mapping routes of vanished ships. No doubt about it—he was behind the disappearances! Justice has finally caught up with the scoundrel.", "Beliz", 30, 1, "");
			break;
	}
}