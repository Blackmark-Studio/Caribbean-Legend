// 丹妮尔.霍克 - 纳撒尼尔.霍克的妻子
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	bool bOk1, bOk2;
	string 	sTemp, sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_" , 0) != -1)
 	{
        i = findsubstr(sAttr, "_" , 0);
	 	NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // 索引在末尾
 	    Dialog.CurrentNode = "SetGunBullets2";
 	}
	
	switch(Dialog.CurrentNode)
	{
		case "First time": // 第一次见面 - 结识
			PlaySound("Voice\English\saga\Denny Hawk-02.wav");
			dialog.text = "等等, 帅哥! 我觉得我们应该谈谈。 ";
			link.l1 = "我认识你吗? 不管怎样, 我总有些时间留给女士。 ";
			link.l1.go = "meeting";			
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			PlaySound("Voice\English\saga\Denny Hawk-01.wav");
			dialog.text = "别忙着做计划, 船长。 找些更年轻。 看起来更傻的女孩消磨时间吧。 我其实已经结婚了。 我丈夫叫纳撒尼尔.霍克。 ";
			link.l1 = "真是巧! 所以你就是那个... 嗯, 丹妮.霍克, 斯文森先生提到过你。 ";
			link.l1.go = "meeting_1";
		break;
		
		case "meeting_1":
			dialog.text = "如假包换。 是的, 我知道‘森林魔鬼’对我评价不高, 我对他也是一样, 但他肯定警告过你, 我佩戴军刀可不只是因为它好看。 所以, 直奔主题吧, 小子! \n我跟踪斯文森和他的访客有一段时间了, 因为是他把我丈夫送进丛林送死的。 我本以为他在和杰克曼合作, 但现在看来不是。 你谈话时我躲在窗下。 虽然没听清全部, 但听到了很多有用的信息。 \n你真的愿意去找我丈夫并收拾杰克曼吗? 还是只是说说而已? ";
			link.l1 = "偷听可不好, 霍克夫人。 但如果你用更尊重的方式和我说话, 我可以原谅你。 找不找霍克只是我的事。 有话就说, 没话就别烦我。 我不会再说第二遍。 ";
			link.l1.go = "meeting_2";
		break;
		
		case "meeting_2":
			dialog.text = "啊哈, 脾气还挺大! 来吧, 船长... 我的脾气肯定让你不舒服。 我看你不是懦夫, 也知道自己的价值。 那么... 我们认识一下吧。 我保证会谨慎措辞。 我需要你, 你也需要我。 我们目标一致。 带我加入你的船员, 不会后悔的。 我会真诚忠诚地为你服务, 直到找到纳森, 我向你保证。 ";
			link.l1 = "算你被录用了... 丹妮。 斯文森说你已经在找你丈夫了。 有没有什么发现? ";
			link.l1.go = "meeting_3";
		break;
		
		case "meeting_3":
			dialog.text = "不多, 但足够证明杰克曼在撒谎。 那混蛋说矿场的守卫 —我丈夫面对的那些 —从不抓俘虏。 虽然没人在海湾看到我丈夫的尸体, 但他们怎么会看到呢, 因为他实际上是被抓去矿场当俘虏了。 米斯基托人的萨满‘蛇眼’在那里找到了他。 \n他还安排了他的逃跑。 但我丈夫现在在哪里, 还不知道。 萨满嘟囔着什么库库尔坎吃掉了他, 但我没听懂。 此外, 那个红皮肤明确表示, 白人女人对他来说只是个笑话。 你应该和他谈谈, 也许他会更健谈。 ";
			link.l1 = "至少有点线索了! 这消息让我高兴。 我在哪里能找到这个印第安人? ";
			link.l1.go = "meeting_4";
		break;
		
		case "meeting_4":
			dialog.text = "丛林深处有个村庄。 我们需要在阿马蒂克峡登陆, 然后向西穿过丛林。 如果你找不到路, 我会给你指路。 村庄不远处有个石像, 野蛮人把它尊为神明。 我去过几次。 其实没什么特别的。 只是一块长满苔藓的普通石头。 ";
			link.l1 = "有意思。 好, 我们走。 我们会和萨满谈谈, 然后看看接下来怎么做。 准备好了吗? ";
			link.l1.go = "meeting_5";
		break;
		
		case "meeting_5":
			dialog.text = "当然! 我当然准备好了。 自从离开马龙镇后, 我一直在旅行。 而且我不想只是当你的乘客。 ";
			link.l1 = "好。 我们去我的船。 ";
			link.l1.go = "meeting_6";
		break;
		
		case "meeting_6":
			dialog.text = "是, 船长! ";
			link.l1 = "... ";
			link.l1.go = "meeting_7";
		break;
		
		case "meeting_7":
			DialogExit();
			chrDisableReloadToLocation = false;// 打开地点
			npchar.quest.OfficerPrice = sti(pchar.rank)*700;
			npchar.OfficerWantToGo.DontGo = true; // 不要试图离开
			npchar.CompanionDisable = true; // 不能加入伙伴 - 以免淹死
			LAi_SetImmortal(npchar, false);
			npchar.HalfImmortal = true; // 以免在陆战中被杀
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, true);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			NextDiag.CurrentNode = "Danielle_officer";
			npchar.HoldEquip = true; // 护林员 - 不交出 saber 和手枪																					 
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			AddQuestRecord("BaronReturn", "2");
			Saga_CreateSnakeEye();
			// 选择护身符
			pchar.questTemp.Saga.BaronReturn.Indian = "indian_"+(rand(10)+1);
			pchar.questTemp.Saga.BaronReturn.Amulet = "amulet_"+(rand(10)+1);
			pchar.questTemp.Saga.BaronReturn.Obereg = "obereg_"+(rand(10)+1);
			// 前往有石像的地点
			npchar.quest.talk = "dolly";
			pchar.quest.Saga_Dolly.win_condition.l1 = "location";
			pchar.quest.Saga_Dolly.win_condition.l1.location = "Pearl_jungle_03";
			pchar.quest.Saga_Dolly.function = "Saga_DannyTalk";
			AddCharacterExpToSkill(pchar, "Fortune", 50);// 运气
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.greeting = "danny_1";
		break;
		
		// 在丛林石像处
		case "Dolly":
			dialog.text = ""+ PChar.name+"! 来吧! 我带你去看那个印第安萨满说的石像。 就是根普通的石柱。 我们走! ";
			link.l1 = "... ";
			link.l1.go = "Dolly_1";
		break;
		
		case "Dolly_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "item", "torch1", "Saga_ShowDolly", -1);
		break;
		
		case "Dolly_2":
			dialog.text = "嘿! 看看, 只是个石像。 没什么特别的... ";
			link.l1 = "我知道... 不过顶部的图案有点邪恶, 你不觉得吗? ";
			link.l1.go = "Dolly_3";
		break;
		
		case "Dolly_3":
			dialog.text = "所有印第安雕像都看起来可怕又邪恶。 我以前见过类似的。 都一个样。 不管怎样, 我们走, 村庄就在附近! ";
			link.l1 = "走吧! ";
			link.l1.go = "Dolly_4";
		break;
		
		case "Dolly_4":
			chrDisableReloadToLocation = false;// 打开地点
			DialogExit();
			LAi_SetOfficerType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			npchar.dialog.currentnode = "Danielle_officer";
		break;
		
		// 在米斯基托人处
		case "SnakeEye":
			dialog.text = "那么, 你怎么说, "+pchar.name+"? 那个红皮肤腹语者告诉你什么了? 你从他的哲学话语中听懂了什么吗? ";
			link.l1 = "你又偷听了吗, 丹妮? ";
			link.l1.go = "SnakeEye_1";
		break;
		
		case "SnakeEye_1":
			dialog.text = "嗯... 有一点。 你知道, 我们女人就是这样。 但你必须理解 —我只是担心我丈夫。 我其实爱他。 我偷听又怎样? 不管怎样, 你得到什么有用的信息了吗? ";
			link.l1 = "我在努力想... 理解‘蛇眼’不容易。 不过, 我们进村时看到的那个石像好像是某种魔法传送门, 可以传送人。 ";
			link.l1.go = "SnakeEye_2";
		break;
		
		case "SnakeEye_2":
			dialog.text = "";
			link.l1 = "别那样看着我。 这不是我的想法, 而且目前我的脑子还没问题。 你问我萨满说了什么, 所以我在告诉你。 ";
			link.l1.go = "SnakeEye_3";
		break;
		
		case "SnakeEye_3":
			dialog.text = "请原谅。 我不会再那样看你了。 继续说。 ";
			link.l1 = "他说当纳森几乎被追捕者抓住时, 印第安人指给他看这个雕像作为逃生之路, 称它为库库尔坎, 说它把纳森活吞了, 又在某个地方把他吐了出来。 简单地说, 纳森好像是被雕像传送了。 ";
			link.l1.go = "SnakeEye_4";
		break;
		
		case "SnakeEye_4":
			dialog.text = "上帝啊, 这... 我和纳森以前也遇到过类似的麻烦, 现在又发生了。 我们在那个充满玛雅魔法的印第安神庙里已经受够了... ";
			link.l1 = "你刚才说什么? ";
			link.l1.go = "SnakeEye_5";
		break;
		
		case "SnakeEye_5":
			dialog.text = "啊, 没什么, "+pchar.name+", 不重要。 只是我年轻时的热血回忆。 但纳森怎么能做到呢? 我是说传送? 我们刚在那个偶像附近, 我绕着它走, 还摸了它... 它只是块石头! ";
			link.l1 = "‘蛇眼’告诉我, 雕像在午夜会活过来。 只有那时它才会发出金色的光芒, 当库库尔坎的灵魂进入它体内。 那是你不应该碰它的时候。 或者相反应该... ";
			link.l1.go = "SnakeEye_6";
		break;
		
		case "SnakeEye_6":
			dialog.text = "毛骨悚然... 现在怎么办? 我们等到午夜再去丛林? ";
			link.l1 = "不。 萨满说雕像不仅能传送人, 还会吞噬他们的生命。 据我理解, 他的意思是它会消耗他们的健康。 ‘蛇眼’穿过这些雕像三次, 每次传送后都用某种独特的药水治愈自己。 ";
			link.l1.go = "SnakeEye_7";
		break;
		
		case "SnakeEye_7":
			dialog.text = "你向他要这种药水了吗? ";
			link.l1 = "当然。 但首先, 只剩三瓶了, 其次, 他要求用三个护身符来交换。 ";
			link.l1.go = "SnakeEye_8";
		break;
		
		case "SnakeEye_8":
			dialog.text = "不用药水怎么样? 我们晚上去雕像那里摸它... ";
			link.l1 = "太冒险了。 我承认印第安人有点疯癫, 可能在骗我们, 但他看起来不像精神病患者, 所以我相信他说的是实话。 我记得你告诉过我一些印第安魔法... 你怀疑它的存在吗? ";
			link.l1.go = "SnakeEye_9";
		break;
		
		case "SnakeEye_9":
			dialog.text = "是的, 我说过。 我不怀疑, 因为我亲眼见过。 所以, 我想你是对的, 没必要冒险。 ";
			link.l1 = "正是。 所以我们要先找到护身符, 然后从萨满那里拿到那神奇的药水, 再去雕像那里。 我会去。 一个人去。 ";
			link.l1.go = "SnakeEye_10";
		break;
		
		case "SnakeEye_10":
			dialog.text = "为什么? 那我呢? ";
			link.l1 = "你留在我的船上, 在我离开时负责。 别争了, 丹妮。 只有三瓶药水。 如果萨满是对的, 而且这东西真的有效, 还不知道传送门会把人送到哪里。 也许我在那里都找不到纳森。 ";
			link.l1.go = "SnakeEye_11";
		break;
		
		case "SnakeEye_11":
			dialog.text = "你就像纳森。 所有男人都一样... 好吧, 我同意。 ";
			link.l1 = "很高兴我们达成共识。 现在走吧, 我们需要找到护身符。 ";
			link.l1.go = "Dolly_4";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets");
				if (CheckAttribute(pchar, "questTemp.Saga.HelenRelation") && sti(pchar.questTemp.Saga.HelenRelation) > 6) {
					AddDialogExitQuestFunction("HelenDrinking_GivePotionsDlg");
				}
			}
		break;
		
		// 前往石像前
		case "teleport":
			dialog.text = "那么? 你拿到药水了吗? ";
			link.l1 = "是的。 我拿到了药水和一些指示。 剩下的就是在午夜去雕像那里摸它。 ";
			link.l1.go = "teleport_1";
		break;
		
		case "teleport_1":
			dialog.text = "你害怕吗? ";
			link.l1 = "是的。 我担心萨满可能只是疯了, 根本不会发生传送。 ";
			link.l1.go = "teleport_2";
		break;
		
		case "teleport_2":
			dialog.text = "嗯嗯... 你真的不害怕吗? 一点都不? ";
			link.l1 = "丹妮, 别逼我... 如果你真的想知道, 那我确实不太有信心, 我必须承认。 ";
			link.l1.go = "teleport_3";
		break;
		
		case "teleport_3":
			dialog.text = "我和你一起去。 ";
			link.l1 = "你又要开始争论了吗? 我以为我们说好了... ";
			link.l1.go = "teleport_4";
		break;
		
		case "teleport_4":
			dialog.text = "你误会了。 我只会待在你附近。 我得确认雕像是否有效... 或者无效。 ";
			link.l1 = "我不反对。 但如果雕像‘吃’了我, 别想跟着我。 听到了吗? ";
			link.l1.go = "teleport_5";
		break;
		
		case "teleport_5":
			dialog.text = "听到了。 我保证不会跟着你... 船长。 ";
			link.l1 = "很好。 还有, 丹妮, 你好像不像他们说的那么难相处。 ";
			link.l1.go = "teleport_6";
		break;
		
		case "teleport_6":
			dialog.text = "你还不太了解我, "+pchar.name+"。 但现在我们别谈这个。 ";
			link.l1 = "别谈了... 好吧, 我们应该为夜间旅行做准备了! ";
			link.l1.go = "Dolly_4";
			npchar.quest.talk = "shadowstar";
			pchar.quest.Saga_Dolly1.win_condition.l1 = "location";
			pchar.quest.Saga_Dolly1.win_condition.l1.location = "Pearl_jungle_03";
			pchar.quest.Saga_Dolly1.win_condition.l2 = "Hour";
			pchar.quest.Saga_Dolly1.win_condition.l2.start.hour = 0.00;
			pchar.quest.Saga_Dolly1.win_condition.l2.finish.hour = 1.00;
			pchar.quest.Saga_Dolly1.function = "Saga_DannyTalk";
			
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets")) {
				DeleteAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets");
				if (CheckAttribute(pchar, "questTemp.Saga.HelenRelation") && sti(pchar.questTemp.Saga.HelenRelation) > 6) {
					AddDialogExitQuestFunction("HelenDrinking_GivePotionsDlg");
				}
			}
		break;
		
		// 传送前
		case "shadowstar":
			dialog.text = "看, "+pchar.name+"! 我以神圣的名义发誓, 雕像上方有奇怪的光! ";
			link.l1 = "看来萨满没撒谎。 如果黑暗没骗我, 雕像顶部看起来不再那么石头了。 ";
			link.l1.go = "shadowstar_1";
			QuestPointerDelLoc("Pearl_Jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("Pearl_Jungle_03", "camera", "dolly");
		break;
		
		case "shadowstar_1":
			dialog.text = "没错... 看起来像是纯金做的! 难以置信! ";
			link.l1 = "时间到了, 丹妮。 祝我好运, 为我祈祷。 别靠近雕像! 待在这里。 ";
			link.l1.go = "shadowstar_2";
		break;
		
		case "shadowstar_2":
			dialog.text = "祝你好运, "+pchar.name+"。 希望这能成功... 你准备好萨满的药水了吗? ";
			link.l1 = "是的, 我带了。 一切都会好的, 丹妮。 好了, 我走了! (按T激活雕像)";
			link.l1.go = "shadowstar_3";
		break;
		
		case "shadowstar_3":
			DialogExit();
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			DoQuestReloadToLocation(pchar.location, pchar.location.group, pchar.location.locator, "");
		break;
		
		// 传送后返回
		case "arrive":
			dialog.text = "啊 —啊 —啊? ! 该死! 你是什么怪物, 天杀的? ! 去你的! 我这辈子见过更可怕的东西, 包括范.德.戴肯本人! 现在我要给你点颜色看看! ";
			link.l1 = "(微弱地) 丹妮, 等等! 住手! 现在! ";
			link.l1.go = "arrive_1";
		// belamour legendary edition -->
			link.l2 = "(微弱地) 范.德.戴肯? 呃 —哈 —哈 —哈! 那条虫已经为我服务了! 现在轮到你了! 向我鞠躬, 忠诚的仆人! 你将领导我的亡灵大军! ";
			link.l2.go = "arrive_1a";
			SetMusic("music_jungle");
			if (CheckCharacterItem(pchar, "Ultimate_potion"))
			{
				pchar.systeminfo.NoNotifications = true;
				RemoveItems(pchar, "Ultimate_potion", 1);
				DeleteAttribute(pchar,"systeminfo.NoNotifications");
				notification("使用了科曼奇药水", "None");
				LAi_SetCurHPMax(PChar);
				AddCharacterHealth(pchar, 50);
				DeleteAttribute(pchar, "chr_ai.poison");
				notification("你感觉健康恢复了! ", "None");
				//Log_Info("A Comanche potion is used");
				//Log_Info("You are feeling that your health is restored!");
				//PlaySound("Ambient\Tavern\glotok_001.wav");
				PlaySound("Ambient\Horror\Fear_breath_01.wav");
			}
		break;
		
		case "arrive_1a":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			dialog.text = "啊 —啊 —啊 —啊 —啊 —啊 —啊 —啊 —啊 —啊 —啊! 走开! 现在不能发生这种事! ";
			link.l1 = "(微弱地) 丹妮, 等等! 住手! 现在! ";
			link.l1.go = "arrive_1";
		break;
		// < —legendary edition
		case "arrive_1":
			dialog.text = "啊? ! 你说什么? ! 丹妮? ";
			link.l1 = "(微弱地) 立刻住手! 拿着你的军刀! 让我把这东西摘下来! ";
			link.l1.go = "arrive_2";
		break;
		
		case "arrive_2":
			dialog.text = "该死, 你这怪物听起来像... "+pchar.name+"?!";
			link.l1 = "(微弱地) 哦 —哦... 你不说我也知道! ";
			link.l1.go = "arrive_3";
		break;
		
		case "arrive_3":
			DialogExit();
			RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			DoQuestCheckDelay("Pearl_TeleportArrive_1", 1.5);
		break;
		
		case "arrive_4":
			dialog.text = "该死, 你差点把我吓死! 我差点用军刀把你劈了! ";
			link.l1 = "我看到了... 你为什么这么激动, 嗯? ";
			link.l1.go = "arrive_5";
		break;
		
		case "arrive_5":
			dialog.text = "我就是这样的人... 哦, 我的心还在怦怦直跳... ";
			link.l1 = "丹妮, 我们现在在哪里? 离米斯基托村庄不远, 对吧? ";
			link.l1.go = "arrive_6";
		break;
		
		case "arrive_6":
			dialog.text = "我们还能在哪里! 这就是让你消失的雕像。 太壮观了! 我这辈子都不会忘记。 ";
			link.l1 = "我知道, 你从那以后一直在这里等我? ";
			link.l1.go = "arrive_7";
		break;
		
		case "arrive_7":
			dialog.text = "告诉我, 我还能做什么? 雕像‘吃’了你之后, 我只能希望有一天它会把你‘吐’出来。 此外, ‘蛇眼’说这是最可能发生的事。 \n我和米斯基托人住在一起, 每天观察雕像。 我们为什么要谈论这种废话? 告诉我! 那边发生了什么? 你去了哪里? ";
			link.l1 = "丹妮, 这故事太长了, 我看到了很多... 但为了让你安心, 我告诉你我找到纳撒尼尔了! ";
			link.l1.go = "arrive_8";
		break;
		
		case "arrive_8":
			dialog.text = "你找到纳森了? 他在哪里? 他怎么样? ! ";
			link.l1 = "我不骗你 —他还活着, 但状态很差。 他没有科曼奇的药水, 雕像耗尽了他所有的健康。 他躺在某个废弃船只岛上的一艘破旧船只的船舱里。 我也被传送到了那里, 所以‘蛇眼’是对的! ";
			link.l1.go = "arrive_9";
		break;
		
		case "arrive_9":
			dialog.text = "可怜的纳森... 那个该死的岛在哪里? 我们怎么去? 只能通过雕像吗? 我会试着从米斯基托人那里买下所有治疗药水, 今晚就去! 我会想办法的... ";
			link.l1 = "停下! 等等! 纳森病了, 但没有生命危险。 有个小伙子在照顾他, 给他喂食。 如果你通过雕像去, 会损害健康, 而且那个岛真的很危险。 太冒险了! ";
			link.l1.go = "arrive_10";
		break;
		
		case "arrive_10":
			dialog.text = "那你建议怎么办? 当纳森可能在受苦甚至 dying 时什么都不做? ";
			link.l1 = "别歇斯底里。 首先, 我告诉过你纳森病了但没死。 我和他谈过。 其次, 我要航行到那个岛, 你和我一起去。 ";
			link.l1.go = "arrive_11";
		break;
		
		case "arrive_11":
			dialog.text = "你知道那个岛在哪里吗? ";
			link.l1 = "当然知道! 我在那里不仅找到了纳森, 还找到了鲨鱼多德森。 我得到了那个岛的大致坐标和绕过周围礁石的航行方向。 现在我们回我的船, 驶向布鲁维尔德... ";
			link.l1.go = "arrive_12";
		break;
		
		case "arrive_12":
			dialog.text = "为了什么目的? 为什么我们不能现在就直航到那个岛? ";
			link.l1 = "丹妮, 我需要组织一次探险。 岛上严重缺乏物资, 所以我要尽可能多买食物。 然后我得选一艘能绕过岛上礁石的船。 我还想先和斯文森谈谈... ";
			link.l1.go = "arrive_13";
		break;
		
		case "arrive_13":
			dialog.text = "";
			link.l1 = "准备不会花很长时间。 那个岛离这里不远, 在哈瓦那西北, 墨西哥湾以东。 ";
			link.l1.go = "arrive_14";
		break;
		
		case "arrive_14":
			dialog.text = "好吧... 那就这么办。 你找到纳森了, 这是最重要的。 谢谢你! 他在那里感觉糟吗? ";
			link.l1 = "嗯... 他病了。 除此之外, 他还很沮丧和绝望。 他想你。 是的, 纳森让我告诉你他非常爱你。 ";
			link.l1.go = "arrive_15";
		break;
		
		case "arrive_15":
			dialog.text = "(擦去眼泪) 老傻瓜! 他从来不听我的... "+pchar.name+", 我们去你的船吧! 我想尽快航行到那里! ";
			link.l1 = "当然, 丹妮。 我会告诉你我的冒险经历。 我们走! ";
			link.l1.go = "Dolly_4";
			AddQuestRecord("BaronReturn", "9");
			LAi_LocationDisableOfficersGen("Pearl_jungle_03", false); // 允许军官进入传送地点
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);// 允许战斗
			setCharacterShipLocation(pchar, "Shore9"); // 卡莱乌切
			setWDMPointXZ("Shore9"); // 船在阿马蒂克峡
			bNoEatNoRats  = false; // 开启食物和老鼠
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog");
		break;
		
		// 在沉船岛码头
		case "nathaniel":
			dialog.text = "我以前从未见过这样的地方。 整个岛都是由船只组成的! ";
			link.l1 = "我告诉过你, 丹妮... ";
			link.l1.go = "nathaniel_1";
		break;
		
		case "nathaniel_1":
			dialog.text = "但现在我亲眼看到了。 不管怎样, 告诉我去哪里找纳撒尼尔? ";
			link.l1 = "他在其中一艘船里。 但你必须游泳过去。 ";
			link.l1.go = "nathaniel_2";
		break;
		
		case "nathaniel_2":
			dialog.text = "我不在乎。 告诉我怎么去那艘船。 ";
			link.l1 = "丹妮, 冷静点。 你和纳森已经等了很久, 再耐心一点! 我会带你去找他, 你自己永远找不到。 我不想让你遇到独角鲸帮或里瓦多斯, 你会和他们争吵, 结果不会好。 ";
			link.l1.go = "nathaniel_3";
		break;
		
		case "nathaniel_3":
			dialog.text = "好吧, 我们走。 我跟你走。 ";
			link.l1 = "别忘了我们得游很多泳。 ";
			link.l1.go = "nathaniel_4";
		break;
		
		case "nathaniel_4":
			dialog.text = "没关系, 我能应付。 ";
			link.l1 = "很高兴听到... 你很快就能见到你丈夫了! ";
			link.l1.go = "nathaniel_5";
		break;
		
		case "nathaniel_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.LSC_Danny_Natan.win_condition.l1 = "location";
			pchar.quest.LSC_Danny_Natan.win_condition.l1.location = "FernandaDiffIndoor";
			pchar.quest.LSC_Danny_Natan.function = "LSC_DannyAndNatan";
			AddQuestRecord("LSC", "15");
			// 下一个节点
			if (CheckCharacterItem(pchar, "keys_skel")) // 奥莱在
			{
				sld = characterFromId("Ole");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				if (GetCharacterIndex("Mary") != -1) // 否则玛丽
				{
					sld = characterFromId("Mary");
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
				else // 否则结束
				{
					chrDisableReloadToLocation = false;
					LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
				}
			}
		break;
		
		case "nathaniel_6":
			dialog.text = "纳撒尼尔... 纳森! 该死! 我的爱人... ";
			link.l1 = "... ";
			link.l1.go = "nathaniel_7";
		break;
		
		case "nathaniel_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			SetMusic("music_romantic");
			bDisableCharacterMenu = true;// 锁定界面
			locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
			Pchar.FuncCameraFly = "";
			DoQuestCheckDelay("LSC_DanielleRomantic", 15.0);
		break;
		
		case "nathaniel_8":
			dialog.text = "天啊, 看看你自己... 你为什么要这样对自己? ! ..(哭泣) 你从来不听我的, 从来没有! 我告诉过你不要进那片丛林! 但你还是去了! 为什么, 纳森? ! ";
			link.l1 = "丹妮... 对不起。 我别无选择, 你知道的... ";
			link.l1.go = "nathaniel_9";
		break;
		
		case "nathaniel_9":
			sld = characterFromId("Blaze");
			dialog.text = "我知道! 哦, 上帝, 亲爱的... 你怎么了! (含泪) 没关系, 亲爱的, 一切都会好起来的... 我在这里。 我们会带你去米斯基托人那里, 去找‘蛇眼’。 "+sld.name+" 告诉我萨满能治好你。 我们有船... 一切都会好的! ";
			link.l1 = "丹妮, 亲爱的... 我的爱人! 你的出现已经治好了我一半。 你说去哪里我们就去哪里。 如果是去找‘蛇眼’, 那就去找他。 ";
			link.l1.go = "nathaniel_10";
		break;
		
		case "nathaniel_10":
			dialog.text = "收拾你的东西。 哦, 我真蠢... 除了空瓶子没什么可收拾的。 纳森... ";
			link.l1 = "丹妮... ";
			link.l1.go = "nathaniel_11";
		break;
		
		case "nathaniel_11": // 转移pchar
			DialogExit();
			LAi_SetStayType(pchar);
			DeleteAttribute(pchar, "GenQuest.MusicContinue");
			SetMainCharacterIndex(GetCharacterIndex("Blaze"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "nathaniel_12";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;
		
		case "nathaniel_12":
			dialog.text = ""+pchar.name+" ... 原谅我和纳森刚才的场面。 ";
			link.l1 = "丹妮! 原谅什么? 没关系。 你为自己的感情感到羞耻吗? ";
			link.l1.go = "nathaniel_13";
		break;
		
		case "nathaniel_13":
			dialog.text = "不, 我没有... 只是... ";
			link.l1 = "没人会知道刚才的场面。 我保证。 也没人会知道纳森发生了什么。 马龙镇的海盗会看到一个强壮可怕的纳撒尼尔.霍克! ";
			link.l1.go = "nathaniel_14";
		break;
		
		case "nathaniel_14":
			dialog.text = "谢谢你, "+pchar.name+"! 我欠你... 我会把我丈夫带到船上。 别担心, 我记得路, 我会把他带到那里。 我会让他躺在床上, 陪着他。 等你在这里处理完一切, 我们就起航去‘蛇眼’那里。 我相信他有能力治好纳森。 ";
			link.l1 = "好的, 丹妮。 反正我们不会在这里待太久。 你确定不需要帮助吗? ";
			link.l1.go = "nathaniel_15";
		break;
		
		case "nathaniel_15":
			dialog.text = "确定。 我们会到达船上。 别担心, 我不会让我丈夫死的! ";
			link.l1 = "丹妮, 你真是... 太棒了! ";
			link.l1.go = "nathaniel_16";
		break;
		
		case "nathaniel_16":
			dialog.text = "(擦去眼泪) 走吧... 走吧, "+pchar.name+"... 请不要在这里浪费时间! ";
			link.l1 = "... ";
			link.l1.go = "nathaniel_17";
		break;
		
		case "nathaniel_17":
			chrDisableReloadToLocation = false;// 打开地点
			bDisableCharacterMenu = false;// 解锁界面
			EndQuestMovie();
			DialogExit();
			pchar.quest.LSC_NatanPassenger.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_NatanPassenger.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_NatanPassenger.function = "LSC_SetNatanPassenger";
			pchar.quest.Saga_NatanTreatment.win_condition.l1 = "location";
			pchar.quest.Saga_NatanTreatment.win_condition.l1.location = "Miskito_village";
			pchar.quest.Saga_NatanTreatment.function = "Saga_NatanPrepareTreatment";
			pchar.questTemp.Saga.BaronReturn = "shamane";
			AddQuestRecord("BaronReturn", "11");
			// 打开玛丽的入口
			if (GetCharacterIndex("Mary") != -1)
			{
				for (i=0; i<=3; i++)
				{
					LocatorReloadEnterDisable("LostShipsCity_town", "reload6"+i, false);
				}
			}
			else
			{
				bQuestDisableMapEnter = false; // 打开地图
				DeleteAttribute(pchar, "GenQuest.CannotWait");// 可以加速时间
			}
		break;
		
		case "treatment":
			dialog.text = "那么? 他会治好我丈夫吗? 告诉我他会治好他! ";
			link.l1 = "丹妮, 纳森必须留在这里。 一个人。 萨满要求不要打扰他的仪式。 这也包括你。 他承诺一个月内治好纳撒尼尔。 ";
			link.l1.go = "treatment_1";
		break;
		
		case "treatment_1":
			dialog.text = "你知道, "+pchar.name+", 现在我终于可以松口气了。 我坚信萨满会让我丈夫恢复正常。 我会毫不犹豫地把纳森留在这里, 因为如果‘蛇眼’治不好他 —没人能治好。 ";
			link.l1 = "一切都会好的, 丹妮。 ‘蛇眼’从没对我撒过谎。 我信任他。 ";
			link.l1.go = "treatment_2";
		break;
		
		case "treatment_2":
			dialog.text = "我也是。 我会在你身边待一段时间, "+pchar.name+", 你介意吗? 毕竟我们还得找到那个混蛋杰克曼, 他是我们所有麻烦的根源。 他组织了伏击! 他取代了纳森在马龙镇的位置! 他偷了我们的护卫舰‘百夫长’! ";
			link.l1 = "同意。 我们必须处理杰克曼。 在杰克曼死之前, 我们都不安全。 不过杀他可不容易。 ";
			link.l1.go = "treatment_3";
		break;
		
		case "treatment_3":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "鲨鱼多德森";
			else sTemp = "马库斯.泰瑞克斯";
			dialog.text = "有什么计划吗, "+pchar.name+"?";
			link.l1 = "还没有。 我需要去找扬.斯文森征求意见。 我们一件事一件事来, 首先得让"+sTemp+"当选海盗联盟的首领。 所以, 我们需要每个海盗男爵的投票。 ";
			link.l1.go = "treatment_4";
		break;
		
		case "treatment_4":
			dialog.text = "好, 我们去找斯文森。 听听那个老顽固怎么说... ";
			link.l1 = "你知道, 你不应该对扬这么消极。 实际上, 如果你能和他和解... 毕竟, 我们目标一致! ";
			link.l1.go = "treatment_5";
		break;
		
		case "treatment_5":
			dialog.text = "但只是因为我尊重你... 好吧, "+pchar.name+", 对不起。 我不是故意侮辱斯文森, 我只是紧张。 不会再发生了。 ";
			link.l1 = "很好。 丹妮, 一切都会好的。 我可以向你保证! ";
			link.l1.go = "treatment_6";
		break;
		
		case "treatment_6":
			dialog.text = "我完全信任你, "+pchar.name+"。 我们去找斯文森? ";
			link.l1 = "走吧, 丹妮! ";
			link.l1.go = "Dolly_4";
			AddQuestRecord("BaronReturn", "13");
		break;
		
		case "islatesoro":
			dialog.text = "怎么了? 我在听。 我能帮你什么? ";
			link.l1 = "你知道杰克曼可能藏在哪里吗? 你比我更了解这个混蛋。 也许他有什么地方, 一个基地... ";
			link.l1.go = "islatesoro_1";
		break;
		
		case "islatesoro_1":
			dialog.text = "我怎么知道! 雅各布总是很神秘。 我从没听说过他的巢穴。 也许最好试着逻辑思考... 再读一遍你从克尼夫那里得到的信。 我们可能会在里面找到线索。 ";
			link.l1 = "试试... ";
			link.l1.go = "islatesoro_2";
		break;
		
		case "islatesoro_2":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "嗯... 提到了特索罗岛和一些遗嘱... 你觉得熟悉吗? ";
			link.l1 = "我和扬认为Blaze Sharp在特索罗岛被杰克曼杀死, 鲨鱼被嫁祸。 还有遗嘱... 婊子... 一定是指海伦... 该死, 我之前怎么没想到! 这混蛋一定在特索罗岛附近航行! ";
			link.l1.go = "islatesoro_3";
		break;
		
		case "islatesoro_3":
			dialog.text = "那我们别浪费时间了, "+pchar.name+"? ";
			link.l1 = "对。 我们去特索罗岛。 老‘马林’号会帮我们突袭。 ";
			link.l1.go = "islatesoro_4";
		break;
		
		case "islatesoro_4":
			DialogExit();
			AddQuestRecord("BarbTemptation", "18");
			pchar.questTemp.Saga.BarbTemptation = "islatesoro";
			// 在特索罗岛设置中断
			pchar.quest.Saga_AttackJackman.win_condition.l1 = "location";
			pchar.quest.Saga_AttackJackman.win_condition.l1.location = "Bermudes";
			pchar.quest.Saga_AttackJackman.function = "Saga_CheckJackmanBermudes";
		break;
		
		case "after_boarding":
			dialog.text = "那个混蛋终于死了... 我不敢相信 —我又站在‘百夫长’号的甲板上了! 我熟悉这里的每一颗钉子, 好像船也认出了我。 ";
			link.l1 = "它又属于你了, 丹妮。 你和纳撒尼尔的。 ";
			link.l1.go = "after_boarding_1";
		break;
		
		case "after_boarding_1":
			PlaySound("Voice\English\saga\Denny Hawk-03.wav");
			dialog.text = "你无法想象我有多高兴。 纳森以前经常谈论我们的船, 他知道船回来了会很高兴。 ";
			link.l1 = "你现在打算做什么, 丹妮? ";
			link.l1.go = "after_boarding_2";
		break;
		
		case "after_boarding_2":
			dialog.text = "我? 我会把船开到夏普敦, 至少雇最小的船员, 然后驶向布鲁维尔德。 我会请扬.斯文森照看‘百夫长’号, 去米斯基托人那里, 在那里等到‘蛇眼’治好我丈夫。 ";
			link.l1 = "你真的要去拜访扬.斯文森? 我很惊讶... ";
			link.l1.go = "after_boarding_3";
		break;
		
		case "after_boarding_3":
			dialog.text = ""+pchar.name+", 这全是你的功劳。 我一直在想你说的话: ‘我们目标一致’。 记得吗? 我想和斯文森和解, 毕竟他帮我把纳森找回来了。 是时候停止争吵了。 ";
			link.l1 = "明智的话, 丹妮! 纳撒尼尔身体一好, 就能在马龙镇重新掌权。 ";
			link.l1.go = "after_boarding_4";
		break;
		
		case "after_boarding_4":
			dialog.text = "也许... 问题是, 海盗男爵是选举产生的。 如果其他人反对怎么办? ";
			link.l1 = "让斯文森处理。 他能说服任何人。 除掉杰克曼也会起作用。 ";
			link.l1.go = "after_boarding_5";
		break;
		
		case "after_boarding_5":
			dialog.text = "好吧。 反正我需要让斯文森成为我的朋友... "+pchar.name+"! 我想感谢你为我和纳森所做的一切。 你救了我丈夫, 把我们失去的一切都还给了我们。 我欠你。 ";
			link.l1 = "得了吧, 丹妮。 我们是朋友。 ";
			link.l1.go = "after_boarding_6";
		break;
		
		case "after_boarding_6":
			dialog.text = "我想让你知道, 我们在马龙镇永远欢迎你。 有空来找我们。 纳森和我会想办法报答你。 ";
			link.l1 = "天哪, 丹妮! 我很高兴接受你的邀请。 我们会坐下来, 喝一杯, 聊聊你和纳森怎么击沉了范.德.戴肯... ";
			link.l1.go = "after_boarding_7";
		break;
		
		case "after_boarding_7":
			dialog.text = "他说过? 哦, 别提醒我... ";
			link.l1 = "好吧, 丹妮。 你前面有很多工作要做, 我得去拜访我们的盟友 —马库斯和巴尔巴宗。 我希望你允许我翻遍这个船舱, 我肯定杰克曼的箱子里有很多有趣的东西。 ";
			link.l1.go = "after_boarding_8";
		break;
		
		case "after_boarding_8":
			dialog.text = "当然, 你真的认为我会反对吗? ";
			link.l1 = "很好。 其实和你分别很遗憾, 丹妮... 马龙镇见! ";
			link.l1.go = "after_boarding_9";
		break;
		
		case "after_boarding_9":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			LAi_SetHP(npchar, 280, 280); 
			LAi_SetImmortal(npchar, false); // 如果生效
			pchar.GenQuest.CannotTakeShip = true; // 不能夺取
			DoQuestFunctionDelay("Saga_CheckJackmanCabinItems", 5.0); // 5秒后首次检查
			AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;
		
		// 在马龙镇
		case "marun_town":
			dialog.text = ""+pchar.name+", 很高兴见到你! 我们回到马龙镇了, 纳森也回到了他应有的位置。 实际上, 村里每个人都为此高兴。 现在一切都会像以前一样好起来! 我非常感谢你无私的帮助! \n我想送你一份礼物。 拿着。 这个护身符能让你在战斗中更轻松。 这个配方能让你自己制作更多。 ";
			link.l1 = "谢谢, 丹妮! ";
			link.l1.go = "marun_town_1";
		break;
		
		case "marun_town_1":
			GiveItem2Character(pchar, "totem_12"); 
			GiveItem2Character(pchar, "recipe_totem_12"); 
			Log_Info("你收到了一个护身符");
			Log_Info("你收到了护身符的配方");
			PlaySound("interface\important_item.wav");
			dialog.text = "还没完。 我还在这里找到了两个装满金子的箱子。 无疑是杰克曼的财产。 把它们作为我感激的象征。 别拒绝! 我知道你为了帮助我和纳森花了多少钱。 ";
			link.l1 = "好吧, 好吧, 丹妮, 我收下了! ";
			link.l1.go = "marun_town_2";
		break;
		
		case "marun_town_2":
			TakeNItems(pchar, "chest", 2); 
			Log_Info("你收到了两箱达布隆");
			PlaySound("interface\important_item.wav");
			dialog.text = "太好了! "+pchar.name+", 我想让你知道, 从现在起你是我们最好的朋友。 纳森和我在马龙镇永远欢迎你! 多来看我们! ";
			link.l1 = "谢谢! 我会很高兴再见到你们, 所以等着我! ";
			link.l1.go = "exit";
			NextDiag.TempNode = "marun_town_3";
		break;
		
		case "marun_town_3":
			if (CheckAttribute(pchar, "GenQuest.MaruntownSex"))
			{
				dialog.text = "我们能为你做什么, "+pchar.name+"?";
				link.l1 = "唉, 我只是路过... 再见, 丹妮。 ";
				link.l1.go = "exit";
				if (CheckAttribute(pchar, "GenQuest.MaruntownSex2"))
				{
					dialog.text = "这不是"+GetFullName(pchar)+"嘛。 从你脸上就能看出你没浪费时间! ";
					link.l1 = "我必须承认, 你知道如何享乐! 谢谢你, 我玩得很开心。 ";
					link.l1.go = "marun_town_fuckgirl_3";
				}
				NextDiag.TempNode = "marun_town_3";
				break;
			}
			bOk1 = CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && IsOfficer(characterFromId("Mary"));
			bOk2 = CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && IsOfficer(characterFromId("Helena"));
			dialog.text = "很高兴见到你, "+pchar.name+"! 朗姆酒, 葡萄酒? 还是姑娘? ";
			link.l1 = "谢谢, 丹妮! 我只是想见见你... ";
			link.l1.go = "exit";
			if (bOk1 || bOk2)
			{
				link.l2 = "姑娘? 安静点, 丹妮! 你不想看到我被切成碎片, 整齐地叠在你家门口吧? 哈 - 哈。 我那位站在门外的忠实女士, 不会原谅我这种恶作剧的。 ";
				link.l2.go = "marun_town_fuckgirl_Otkaz_1";
			}
			else
			{
				link.l2 = "姑娘? 听起来很有趣, 丹妮。 我一直渴望... 女人的心跳... 我想我该看看 —你不会随便推荐人的, 对吧? ";
				link.l2.go = "marun_town_fuckgirl_1";
			}
			NextDiag.TempNode = "marun_town_3";
		break;
		
		// 丹妮推荐姑娘
		case "marun_town_fuckgirl_Otkaz_1":
			dialog.text = "真的吗? 你为什么这么苍白? 哈 - 哈, 我只是开玩笑。 照顾好她, 听到了吗? ";
			link.l1 = "当然。 她比这一带所有的宝藏都更珍贵! ";
			link.l1.go = "marun_town_fuckgirl_Otkaz_2";
		break;
		
		case "marun_town_fuckgirl_Otkaz_2":
			dialog.text = "这就对了, 哈 - 哈。 走吧, 你亲爱的可能已经紧张了。 ";
			link.l1 = "再见, 丹妮。 谢谢你的关心, 哈 - 哈。 ";
			link.l1.go = "exit";
		break;
		
		case "marun_town_fuckgirl_1":
			dialog.text = "我向你保证, 这位年轻美女绝对知道如何让你度过难忘的时光, "+pchar.name+"。 玩得开心! 她会在酒馆房间等你。 ";
			link.l1 = "谢谢你, 丹妮。 我这就去。 不想浪费一分钟! ";
			link.l1.go = "marun_town_fuckgirl_2";
		break;
		
		case "marun_town_fuckgirl_3":
			dialog.text = ""+pchar.name+", 马龙镇永远欢迎你。 最好的姑娘都是你的! ";
			link.l1 = "哦, 丹妮。 我发誓, 这里是我的第二故乡。 ";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.MaruntownSex2");
			
		break;
		
		case "marun_town_fuckgirl_2":
			DialogExit();
			pchar.GenQuest.MaruntownSex = "true";
			SetTimerCondition("MarunFuckGirl_4", 0, 0, 2, false);
			LocatorReloadEnterDisable("FortOrange_tavern", "reload2_back", false); // 打开房间
			sld = GetCharacter(NPC_GenerateCharacter("MarunFuckGirl", "women_2"+(rand(6)), "woman", "woman", 1, PIRATE, 1, false, "quest"));
			sld.Dialog.Filename = "Quest\Saga\Danielle.c";
			sld.dialog.currentnode = "MarunFuckGirl";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "FortOrange_tavern_upstairs", "goto", "goto1");
		break;
		
		// 与妓女的对话
		case "MarunFuckGirl":
			dialog.text = "我的船长来了。 今天你只属于我! 到我这里来, 我等你好久了... ";
			link.l1 = "哦, 是吗? 你等不及了? 好吧, 我们别浪费时间! ";
			link.l1.go = "MarunFuckGirl_2";
			LocatorReloadEnterDisable("FortOrange_tavern", "reload2_back", true); // 关闭房间
			chrDisableReloadToLocation = true;
		break;
		
		case "MarunFuckGirl_2":
			DialogExit();
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("MarunFuckGirl", "");
			pchar.GenQuest.MaruntownSex2 = "true";
		break;
		
		case "MarunFuckGirl_3":
			dialog.text = RandPhraseSimple("我的船长... 你真的知道如何征服女人! 我以前从未有过这样的经历! 也许你会多待几个小时? ", "亲爱的, 你已经要走了吗? ");
			link.l1 = RandPhraseSimple("我就知道你不会轻易放过我。 再见, 宝贝。 有大事等着我... ", "唉, 工作要紧。 但也许我们会再见面... ");
			link.l1.go = "MarunFuckGirl_4";
		break;
		
		case "MarunFuckGirl_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
		
	// ----------------------------------------- —传奇失败 ------------------------------------------------
		case "failcenturion":
			dialog.text = "我和纳森终于能松口气了! 这个该死的混蛋杰克曼死了! 我为‘百夫长’号感到难过, 但当那混蛋偷走它时, 我就已经接受了失去它的事实。 所以我不太担心。 ";
			link.l1 = "但我担心。 我是个白痴! 所有证据都和船一起沉入海底了。 这些证据本可以帮助我们在选举海盗联盟新首领时投票。 现在... 全没了。 ";
			link.l1.go = "failcenturion_1";
		break;
		
		case "failcenturion_1":
			dialog.text = "别太沮丧! 这种事难免。 下次你会更幸运... 不管怎样。 我想感谢你为我和纳森所做的一切。 你救了我丈夫的命。 我欠你很多。 \n我想让你知道, 马龙镇永远欢迎你。 有空来看看我和纳特。 我们会想办法报答你。 ";
			link.l1 = "好吧, 丹妮。 我肯定会去看你。 你已经要走了吗? ";
			link.l1.go = "failcenturion_2";
		break;
		
		case "failcenturion_2":
			dialog.text = "是的, 我会去米斯基托人那里, 希望‘蛇眼’已经治好了纳森。 然后我们会返回马龙镇。 ";
			link.l1 = "嘿, 我已经习惯有你在身边了, 真遗憾要和你分开... 祝你好运, 丹妮! ";
			link.l1.go = "failcenturion_3";
		break;
		
		case "failcenturion_3":
			DialogExit();
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Saga_FailCenturion", 10.0);
			npchar.greeting = "danny_2";
		break;
		
		case "before_kiss":
			dialog.text = "哦, 别装傻, 亲爱的。 查尔斯, 这个花痴日夜绕着那个雕像转, 还缠着可怜的‘蛇眼’问个不停。 然后她跑回家给他带了东西, 对吧? ";
			link.l1 = "";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenDrinking_JungleDialog2");
		break;
		
		case "after_kiss":
			dialog.text = "哦, 谢谢你的表演, 查尔斯。 整个马龙镇都会谈论这件事, 哈 - 哈! ";
			link.l1 = "我毫不怀疑这成了你新的首要任务 —确保它发生。 ";
			link.l1.go = "after_kiss_1";
		break;
		
		case "after_kiss_1":
			dialog.text = "实际上, 这在我的清单底部。 别生那女孩的气 —这是她第一次。 我和纳森冒险时, 整个群岛也在嘲笑我们。 ";
			link.l1 = "我们换个话题和心情吧。 我受够这个雕像了, 我们走。 ";
			link.l1.go = "after_kiss_2";
		break;
		
		case "after_kiss_2":
			dialog.text = "同意, 走吧, 英雄。 ";
			link.l1 = "";
			link.l1.go = "Dolly_4";
			
			AddDialogExitQuestFunction("HelenDrinking_AfterKiss3");
		break;
		
		//--> --------------------------------- —军官模块 ------------------------------------------
		case "Danielle_officer":
			dialog.text = "你想要什么, 船长? ";
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "danielle")
			{
				Link.l3 = "丹妮, 我想向你请教! ";
				Link.l3.go = "islatesoro";
			}
			Link.l1 = "听我的命令! ";
            Link.l1.go = "stay_follow";
			link.l2 = "没什么。 解散! ";
			link.l2.go = "exit";
			NextDiag.TempNode = "Danielle_officer";
			sld = characterFromId("Danielle");
		    sld.HoldEquip = true; // 护林员 - 不交出 saber 和手枪, 当前游戏使用。 所以这样, 没找到其他方法						 
		break;
		
		case "stay_follow":
            dialog.Text = "命令? ";
            Link.l1 = "待在这里! ";
            Link.l1.go = "Boal_Stay";
            Link.l2 = "跟着我, 跟上! ";
            Link.l2.go = "Boal_Follow";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			if(sGun != "")
			{
				rItm = ItemsFromID(sGun);
				if(CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
				{
					Link.l3 = "为你的火器更换弹药类型。 ";
					Link.l3.go = "SetGunBullets";
				}	
			}		
		break;
		
		case "SetGunBullets":
			Dialog.Text = "选择弹药类型: ";
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			makearef(rType, rItm.type);	
			for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
			{
				sAttr = GetAttributeName(GetAttributeN(rType, i));
				sBullet = rItm.type.(sAttr).bullet;
				rItem = ItemsFromID(sBullet);								
				attrL = "l" + i;
				Link.(attrL) = GetItemName(rItem);
				Link.(attrL).go = "SetGunBullets1_" + i;
			}
		break;	

		case "SetGunBullets2":
			i = sti(NPChar.SetGunBullets) + 1; 
			sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
			rItm = ItemsFromID(sGun);
			sAttr = "t" + i;
			sBullet = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
			LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
			NextDiag.CurrentNode = NextDiag.TempNode;
			rItem = ItemsFromID(sBullet);
			notification(GetFullName(NPChar)+" "+XI_ConvertString("AmmoSelectNotif")+GetItemName(rItem)+"", "AmmoSelect");
			DeleteAttribute(NPChar,"SetGunBullets");
			DialogExit();
		break;		
		
        case "Boal_Stay":
            Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
            AddDialogExitQuestFunction("LandEnc_OfficerStay");
            dialog.Text = "部署已变更! ";
            Link.l1 = "解散。 ";
            Link.l1.go = "Exit";
            Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
        break;
        
        case "Boal_Follow":
            SetCharacterTask_FollowCharacter(Npchar, PChar);
            dialog.Text = "部署已变更! ";
            Link.l1 = "解散。 ";
            Link.l1.go = "Exit";
        break;
		//< —--------------------------------- —军官模块 ----------------------------------------
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}