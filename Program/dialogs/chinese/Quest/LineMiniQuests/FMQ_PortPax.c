// Addon-2016 Jason, 法国迷你任务 (ФМК) 太子港
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "明显的错误。 告诉开发者。 ";
			link.l1 = "哦, 我会的。 ";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "officer":
			PlaySound("Voice\English\z_arest_02.wav");
			dialog.text = "先生们, 这里到底发生了什么? 我听到了打斗声。 ";
			link.l1 = "你好, 军官, 我听到一个女人尖叫并且... ";
			link.l1.go = "officer_1";
		break;
		
		case "officer_1":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "officer_2":
			dialog.text = "";
			link.l1 = ""+GetFullName(pchar)+"。 "+GetFullName(pchar)+"船长。 ";
			link.l1.go = "officer_3";
		break;
		
		case "officer_3":
			dialog.text = "船长, 你现在可以走了。 我知道这里发生了什么, 如果有问题我们会传唤你。 ";
			link.l1 = "很好... ";
			link.l1.go = "officer_4";
		break;
		
		case "officer_4":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			sld.Dialog.currentnode = "noble_3";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "officer_5":
			PlaySound("Voice\English\z_arest_02.wav");
			dialog.text = "先生们, 这里到底发生了什么? 我听到了打斗声。 ";
			link.l1 = "谢谢你, 军官, 我听到一个女人呼救, 看到这位先生被两个恶棍袭击。 我试图救这个可怜的人, 但可惜我来晚了。 混蛋杀了他! ";
			link.l1.go = "officer_6";
		break;
		
		case "officer_6":
			dialog.text = "真该死... 他是西班牙人! 他为什么会在这里? 嗯。 那么你是谁, 先生? ";
			link.l1 = ""+GetFullName(pchar)+"。 "+GetFullName(pchar)+"船长。 ";
			link.l1.go = "officer_7";
		break;
		
		case "officer_7":
			dialog.text = "船长, 你现在可以走了。 你的话与证人的一致。 如果需要, 我们会叫你。 ";
			link.l1 = "很好... ";
			link.l1.go = "officer_8";
		break;
		
		case "officer_8":
			DialogExit();
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "");
		break;
		
		case "noble":
			dialog.text = "请允许我解释一切, 先生! 我叫唐.多明戈.奥尔蒂斯.阿尔瓦拉特, 来自圣多明戈。 我应一位年轻小姐的邀请来到太子港, 在这家酒馆停留等待约定的会面。 当我自顾自地坐着时, 被这两个该死的强盗袭击了。 如果不是这位恰好路过的好心人, 我现在已经在和天使共进晚餐了。 ";
			link.l1 = "唐.多明戈.奥尔蒂斯.阿尔瓦拉特? 你是西班牙人? ";
			link.l1.go = "noble_1";
		break;
		
		case "noble_1":
			dialog.text = "和费利佩国王一样纯正的西班牙人, 哈! 我还要指出我的文件都没问题。 我是西班牙贵族, 不是什么肮脏的海盗! ";
			link.l1 = "唐.多明戈, 对这不幸的事件我们深表歉意! 请跟我们来, 去驻军那里问些问题, 喝瓶酒。 我们会处理好一切。 至于你... ";
			link.l1.go = "noble_2";
		break;
		
		case "noble_2":
			DialogExit();
			sld = CharacterFromID("FMQP_off");
			sld.Dialog.currentnode = "officer_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		
		case "noble_3":
			PlaySound("Voice\English\LE\Domingo\Domingo_01.wav");
			dialog.text = "船长先生! 船长先生! 我以圣地亚哥和圣母玛利亚发誓, 你是个高尚的人, 卡斯蒂利亚的真正儿子总会报答这种高尚! 等我在这里处理完事务, 希望能给你奖赏。 请赏光访问我在圣多明戈的寒舍! 就在城门口附近。 我会为你准备盛宴, 我善良的骑士卡洛斯! 记住我的名字, 唐.多明戈.奥尔蒂斯.阿尔瓦拉特! ";
			link.l1 = "... ";
			link.l1.go = "noble_4";
		break;
		
		case "noble_4":
			DialogExit();
			AddMapQuestMarkCity("santodomingo", true);
			DoQuestReloadToLocation("Portpax_town", "reload", "reload4", "FMQP_AfterFightInTown");
		break;
		
		case "noble_5":
			dialog.text = GetFullName(pchar)+"船长? ! 哦, 我的上帝! 这是场灾难! 这里发生了什么, 好朋友? 这些人是谁? ";
			link.l1 = "很高兴见到你, 唐.多明戈。 这些是... 我来这里拜访你。 看到那边那个人了吗? 那是乌戈, 你的仆人, 他... ";
			link.l1.go = "noble_6";
		break;
		
		case "noble_6":
			dialog.text = "乌戈? ! 哦, 不, 你被骗了, 船长! ";
			link.l1 = "我明白了, 我好像经常遇到这种事。 三个恶棍闯入你家, 谋杀了你忠诚的仆人乌戈 --我发现他的尸体已经在楼上了 --然后设下埋伏等你。 我的到来不在他们的计划中。 他们没能在我们的会面中幸存下来。 ";
			link.l1.go = "noble_7";
		break;
		
		case "noble_7":
			dialog.text = "圣母玛利亚, 为我们祈祷吧! 你用剑的手法像托莱多的击剑大师一样! 你站在我这边真是太好了! 哦, 我可怜的乌戈! 他从小把我养大, 现在却... 被该死的无赖谋杀了! ";
			link.l1 = "唐.多明戈, 看来你还没脱离危险。 你的仆人乌戈知道些什么, 看看这张纸条。 我在桌子上找到的。 ";
			link.l1.go = "noble_8";
		break;
		
		case "noble_8":
			ChangeItemDescribe("letter_parol", "itmdescr_letter_parol");
			RemoveItems(pchar, "letter_parol", 1);
			dialog.text = "给我... (阅读) 这不可能... 哦, 不! 这太难以置信了! 路易斯叔叔... 但是... ";
			link.l1 = "知道是谁干的吗? ";
			link.l1.go = "noble_9";
		break;
		
		case "noble_9":
			dialog.text = "只有怀疑... 可怕的怀疑, 我的朋友! 我母亲的兄弟怎么能做出这种事? ";
			link.l1 = "你介意告诉我吗? 抱歉, 唐.多明戈, 但根据我的经验, 亲戚往往是一个人最可怕的敌人... ";
			link.l1.go = "noble_10";
		break;
		
		case "noble_10":
			dialog.text = "是的, 你说得对, 卡洛斯! 我会告诉你一切! 你已经救了我两次, 看来你是我现在唯一可以信任的人! 但我们离开这个可怕的地方吧, 它让我恶心。 我必须通知市长处理这个烂摊子, 他们会照顾可怜的乌戈。 我们去当地酒馆喝点酒平静一下 nerves 怎么样? ";
			link.l1 = "你的 nerves 确实比我更需要, 先生, 前面带路! ";
			link.l1.go = "noble_11";
		break;
		
		case "noble_11":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoQuestReloadToLocation("Santodomingo_tavern", "sit", "sit_base2", "FMQP_InSantoDomingoTavern");
		break;
		
		case "noble_12":
			LAi_SetSitType(pchar);
			dialog.text = "那么, 我的朋友, 请允许我告诉你... 我家族历史的简略版本。 我的母亲, 伊莎贝拉.奥尔蒂斯夫人, 嫁给了我的父亲, 侯爵里卡多.阿尔瓦拉特, 并按照习俗随了他的姓。 她的兄弟, 路易斯.奥尔蒂斯, 曾是殖民地的驻军指挥官, 但在我母亲结婚后, 他被我父亲任命为贝洛港附近一个甘蔗种植园的经理\n这是一个巨大而富裕的种植园, 确实非常盈利。 几年前我父母在海上不幸去世后, 我作为他们唯一的儿子继承了一切, 包括种植园。 我叔叔保留了他的职位, 我对他支付的租金也很满意。 他总是按时付款。 ";
			link.l1 = "所以你认为是你叔叔... ";
			link.l1.go = "noble_13";
		break;
		
		case "noble_13":
			dialog.text = "是的。 目前, 他只是个租户。 种植园是我的, 不是他的。 但是! 如果我有什么不测 --它就会成为他的财产。 ";
			link.l1 = "你知道, 多明戈, 我认识一些人, 他们会冷血谋杀所有亲戚, 只为了比那更小的利益。 ";
			link.l1.go = "noble_14";
		break;
		
		case "noble_14":
			dialog.text = "你显然需要交更好的朋友, 卡洛斯。 我亲爱的乌戈在最后一张纸条里提到了我叔叔的文件... 这是直接线索。 哦, 我不想相信! 但是... 我住在西班牙的表妹玛格丽塔.奥尔蒂斯不久前订婚了。 这会是原因吗, 我的好船长? ";
			link.l1 = "你溺爱的叔叔可能突然需要一些钱... ";
			link.l1.go = "noble_15";
		break;
		
		case "noble_15":
			dialog.text = "钱? ! 当然... 但别忘了侯爵的头衔! 那会让我表妹和她未来的丈夫很般配! 我的上帝! 我真蠢! ";
			link.l1 = "那个贵族头衔比甘蔗种植园更有价值。 ";
			link.l1.go = "noble_16";
		break;
		
		case "noble_16":
			dialog.text = "等等, 我的朋友! 我刚想起这不是第一次有人试图杀我! 几周前我在街上遇到一个乞丐! 那个喝醉的混蛋用我无法忽视的方式冒犯了我。 结果他是个该死的优秀剑客, 他拔出剑, 甚至在我杀了他之前用细剑刺伤了我。 ";
			link.l1 = "你到底怎么会在太子港的酒馆里? 你提到过某个年轻小姐? ";
			link.l1.go = "noble_17";
		break;
		
		case "noble_17":
			dialog.text = "(脸红) 先生... 是的, 船长, 现场有一位年轻漂亮的小姐... 现在我明白了, 她只是陷阱的诱饵。 混蛋, 到处都是混蛋, 谁都不能相信! 可怜的乌戈... 他现在死了。 ";
			link.l1 = "你应该做点什么, 多明戈。 逃到西班牙怎么样? ";
			link.l1.go = "noble_18";
		break;
		
		case "noble_18":
			dialog.text = "去西班牙? 把我的种植园留给那个恶棍? 船长, 我是侯爵多明戈.奥尔蒂斯.阿尔瓦拉特! ";
			link.l1 = "但是... ";
			link.l1.go = "noble_19";
		break;
		
		case "noble_19":
			dialog.text = "我的朋友卡洛斯, 我能请求你的帮助吗? 乌戈死了, 我身边没有可以信任的人。 你已经救了我两次! 两次! 我欠你很多, 我永远感激你, 但我还是敢请求你再帮个忙。 我以圣母发誓, 我会让你得到回报! ";
			link.l1 = "很好, 对于一个西班牙人来说你是个好人。 我能为你做什么, 多明戈? ";
			link.l1.go = "noble_20";
		break;
		
		case "noble_20":
			dialog.text = "我们去我在贝洛港的种植园吧! 我知道我叔叔现在在卡塔赫纳。 乌戈提到过一些文件, 所以我们检查一下唐.路易斯.奥尔蒂斯的账本和文件! 我们可能会找到一些东西, 帮助我们把他肮脏的阴谋公之于众。 去贝洛港有相当一段距离, 但我会全额支付航行费用! ";
			link.l1 = "现在拒绝你太荒谬了, 唐.多明戈。 我已经陷得太深, 无法退出了。 ";
			link.l1.go = "noble_21";
		break;
		
		case "noble_21":
			AddMoneyToCharacter(pchar, 20000);
			dialog.text = "感谢上帝, 我就知道你会帮我, 朋友! 给, 拿这两万比索作为去贝洛港的航行费用。 我们什么时候起航? 我们必须在我叔叔从卡塔赫纳回来之前赶紧出发! ";
			link.l1 = "那我们别浪费时间了。 ";
			if (CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 20) link.l1.go = "noble_22";
			else link.l1.go = "noble_22x";
		break;
		
		case "noble_22x":
			GiveNationLicence(HOLLAND, 20);
			dialog.text = "这是荷兰西印度公司的许可证。 有效期二十天, 我们把你的名字写进去。 好了。 这应该能帮助我们避免与海岸警卫队的任何麻烦。 ";
			link.l1 = "太好了! ";
			link.l1.go = "noble_22";
		break;
		
		case "noble_22":
			dialog.text = "现在允许我登上你的船了吗, 我的朋友? ";
			link.l1 = "你是尊贵的客人。 一旦我们遇到合适的风 --我们就起航。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_OnBoard");
			AddMapQuestMarkCity("portobello", true);
		break;
		
		case "noble_23":
			dialog.text = "那么, 卡洛斯船长, 我们到了。 现在我们应该找到我叔叔的房子, 检查里面有什么。 ";
			link.l1 = "唐.多明戈, 我们应该预料到警卫会有什么问题吗? ";
			link.l1.go = "noble_24";
		break;
		
		case "noble_24":
			dialog.text = "不。 虽然... 嗯。 路易斯有可能煽动他们反对我。 无论如何, 谨慎总是更好的选择。 我们找到需要的房子吧。 ";
			link.l1 = "你还不知道吗? 这是你的种植园。 ";
			link.l1.go = "noble_25";
		break;
		
		case "noble_25":
			dialog.text = "嗯... 说实话, 我上次来这里时只有八岁。 但我打算尽快解决这个问题! ";
			link.l1 = "我明白了。 那我们开始找吧。 你叔叔的房子一定是这里最大的。 ";
			link.l1.go = "noble_26";
		break;
		
		case "noble_26":
			DialogExit();
			chrDisableReloadToLocation = false;
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			AddQuestRecord("FMQ_Portpax", "7");
		break;
		
		case "noble_27":
			dialog.text = "你在这里找到了什么, 我的朋友? ";
			link.l1 = "看看, 唐.多明戈。 看起来是会计记录。 这可能很有趣。 ";
			link.l1.go = "noble_28";
		break;
		
		case "noble_28":
			ChangeItemDescribe("Almanac", "itmdescr_Almanac");
			RemoveItems(pchar, "Almanac", 1);
			dialog.text = "(阅读) 嗯... 是的。 看看这个... 我的天! 十万比索! 还有十五万! 还有这里... (翻页) 路易斯叔叔! ";
			link.l1 = "有什么有趣的吗? ";
			link.l1.go = "noble_29";
		break;
		
		case "noble_29":
			dialog.text = "有趣的东西! 我宝贵的叔叔收入比他告诉我的多五倍! 小偷! 贪污犯! ";
			link.l1 = "我并不惊讶。 不经常检查实际业务状况, 你不能完全信任任何人。 这只是常识。 ";
			link.l1.go = "noble_30";
		break;
		
		case "noble_30":
			dialog.text = "也许对普通人来说是常识。 我的教养让我对那些我认为可敬的绅士的欺骗视而不见! 你总是对的, 卡洛斯! 我自己的叔叔在偷我的东西! 该死! 这是我的错, 但我会解决的。 种植园是我的, 我叔叔从今天起被解雇了! 他什么都不是! 我会让他被 keelhauled! ";
			link.l1 = "唐.多明戈... 你不觉得你叔叔可能不同意这个决定吗? ";
			link.l1.go = "noble_31";
		break;
		
		case "noble_31":
			dialog.text = "我才不管他同不同意! 我是侯爵多明戈.奥尔蒂斯.阿尔瓦拉特, 路易斯.奥尔蒂斯只是个租户, 而且是前租户! 还有他... ";
			link.l1 = "冷静点, 先生。 你在这里是生面孔, 而我是法国人, 拿着荷兰许可证, 和西班牙反海盗巡逻队有过... 复杂的过往。 至于你叔叔, 他几乎拥有这个镇。 你认为警卫和地方长官会选你的边吗? ";
			link.l1.go = "noble_32";
		break;
		
		case "noble_32":
			dialog.text = "你一针见血... 也许... 不。 西班牙士兵绝不敢对贵族动手! 如果我叔叔敢, 他可以挑战我! ";
			link.l1 = "不过, 我建议走另一条路。 法院怎么样? ";
			link.l1.go = "noble_33";
		break;
		
		case "noble_33":
			dialog.text = "哈! 你说得对, 卡洛斯。 我们去和适当的当局谈谈。 我叔叔犯了一个错误, 在他的笔记中详细记录了与走私者的交易。 他从他们那里以非常便宜的价格购买奴隶。 这些账本对我们很有帮助, 我怀疑那个混蛋坐在地牢里时无法以任何方式伤害我。 我们走吧, 我的朋友! 去贝洛港! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PrepareUncle");
		break;
		
		case "noble_34":
			//PlaySound("Voice\English\LE\Domingo\Domingo_04.wav");
			dialog.text = "这完全是肮脏无礼的谎言! 他怎么敢用他不值钱的舌头玷污我父母的好名声! 该死的, 我会让他付出代价! 拔出你的剑, 你这个刺客! ";
			link.l1 = "";
			link.l1.go = "noble_35";
		break;
		
		case "noble_35":
			DialogExit();
			sld = CharacterFromID("FMQP_Uncle");
			sld.Dialog.currentnode = "uncle_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "noble_36":
			PlaySound("Voice\English\LE\Domingo\Domingo_05.wav");
			dialog.text = "路易斯叔叔在为他的灵魂准备的合适地方 --地狱... 卡洛斯, 你是我的守护天使派来的! 我很高兴你没有相信这个恶棍的话。 说实话, 我担心你会把我一个人留在这里和这个混蛋战斗\n是的, 先生, 我自己也不完美, 但是这个... 这个关于我雇佣海盗谋杀我自己父母的肮脏谎言! 指责我这个... 这个! 呸! 罪有应得。 ";
			link.l1 = "很高兴我们成功了, 唐.多明戈。 现在怎么办? 我希望我们没有违反西班牙法律。 ";
			link.l1.go = "noble_37";
		break;
		
		case "noble_37":
			dialog.text = "违反法律? 哈哈! 不, 卡洛斯, 我会出示这本精美的账本, 里面有我叔叔所有的走私活动。 别忘了他最近一次尝试后我们有很多证人。 别担心, 我的好朋友。 这是我的镇, 是时候让他们都看看了! ";
			link.l1 = "请谨慎行事, 先生。 让他们对你的看法比对你已故叔叔的看法更好。 ";
			link.l1.go = "noble_38";
		break;
		
		case "noble_38":
			dialog.text = "这就是计划, 船长。 但我不会对任何敢于反对我的人手下留情。 请允许我向你表达诚挚的感谢, 卡洛斯! 请去酒馆, 休息一下, 喝几杯。 我很乐意加入你, 但你是对的。 是时候变得更聪明, 自己掌控种植园了。 明天来这里见我, 船长! ";
			link.l1 = "很好, 唐.多明戈。 明天见。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_PlantatonPause");
		break;
		
		case "noble_39":
			DelLandQuestMark(npchar);
			PlaySound("VOICE\English\LE\Domingo\Domingo_05.wav");
			dialog.text = "啊, 我亲爱的朋友, 你来了! ";
			link.l1 = "你好吗, 唐.多明戈? 你的种植园怎么样? ";
			link.l1.go = "noble_40";
		break;
		
		case "noble_40":
			dialog.text = "种植园很好, 钱就不一样了 --原来我亲爱的叔叔一直把所有的钱都转到卡塔赫纳的银行。 要花很多律师的时间才能把我的金子拿回来。 但没关系, 我可以做到。 别难过, 船长, 我会遵守承诺, 奖励你的高尚。 诚实和友谊! ";
			link.l1 = "先生, 当我站在你这边战斗时, 从未想过奖励... ";
			link.l1.go = "noble_41";
		break;
		
		case "noble_41":
			dialog.text = "我知道, 船长, 这充分说明了你的性格! 任何善举都应该得到回报。 所以, 虽然我现在没有钱, 但我会下令把我种植园的货物装上你的船。 我是说咖啡, 一大批。 我相信你能以很高的利润卖掉。 ";
			link.l1 = "哦! 这太好了..";
			link.l1.go = "noble_42";
		break;
		
		case "noble_42":
			dialog.text = "此外, 我有一些对我来说价值不大, 但对你这样的水手来说价值很大的物品。 一个好的望远镜和三个护身符。 请接受这些, 现在都是你的了。 ";
			link.l1 = "感谢! ";
			link.l1.go = "noble_43";
		break;
		
		case "noble_43":
			Log_Info("你收到了一个好望远镜");
			Log_Info("你收到了三个护身符");
			PlaySound("interface\important_item.wav");
			dialog.text = "最后, 我把我的细剑赠送给你, 作为我对你无限感激的象征。 她为我服务得很好, 现在让她为你服务得更好。 看着她, 记住你的好西班牙朋友 --侯爵多明戈.阿尔瓦拉特! ";
			link.l1 = "非常感谢你, 先生! 我没想到... ";
			link.l1.go = "noble_44";
		break;
		
		case "noble_44":
			Log_Info("你收到了轻剑");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			dialog.text = "现在, 唉, 我必须说再见了。 我应该去贝洛港见总督, 然后去卡塔赫纳... 总之, 我无忧无虑的生活结束了, 是时候像个成年人一样生活了。 ";
			link.l1 = "嗯, 你现在聪明多了... ";
			link.l1.go = "noble_45";
		break;
		
		case "noble_45":
			dialog.text = "没错。 很高兴认识你, 我的朋友! 有空来看我。 海上一路顺风! ";
			link.l1 = "祝你在种植园生意上也一样, 唐.多明戈! ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_ReceiveReward");
		break;
		
		case "noble_46":
			PlaySound("Voice\English\YoungMan02.wav");
			dialog.text = "唉, 我们晚了, 先生! 真可惜, 我善良的老叔叔已经在他的文件中做了很好的清理工作... 看来他被告知了圣多明戈的事, 他采取了预防措施... 但我不会就这样算了! 我应该去见贝洛港的总督, 对我叔叔提起法律诉讼。 我受够了他管理我的财富。 ";
			link.l1 = "好决定。 ";
			link.l1.go = "noble_47";
		break;
		
		case "noble_47":
			dialog.text = "我想感谢你, 船长! 很高兴认识你! 我把我的细剑赠送给你, 作为我对你感激的象征。 她为我服务得很好, 现在让她为你服务得更好。 看着她, 记住你的好西班牙朋友 --侯爵多明戈.阿尔瓦拉特! ";
			link.l1 = "非常感谢你, 先生! 我没想到... ";
			link.l1.go = "noble_48";
		break;
		
		case "noble_48":
			Log_Info("你收到了轻剑");
			PlaySound("interface\important_item.wav");
			RemoveCharacterEquip(npchar, BLADE_ITEM_TYPE);
			GiveItem2Character(pchar, GetGeneratedItem("blade_16")); // belamour legendary edition 使用 GetGeneratedItem 否则从数组第一部分获取一堆相同的剑
			dialog.text = "现在, 唉, 我必须说再见了。 我应该去贝洛港。 我无忧无虑的生活结束了, 是时候像个成年人一样生活了。 海上一路顺风! ";
			link.l1 = "祝你和你叔叔好运, 唐.多明戈! 我相信你会赢的! ";
			link.l1.go = "noble_49";
		break;
		
		case "noble_49":
			DialogExit();
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("PortoBello_Plantation", "reload2_back", false);
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 40.0);
			pchar.questTemp.FMQP = "fail";
			AddQuestRecord("FMQ_Portpax", "13");
			CloseQuestHeader("FMQ_Portpax");
			sld = &Locations[FindLocation("PortoBello_Plantation")];
			sld.soldiers = true;
		break;
		
		case "uncle":
			PlaySound("Voice\English\OliverTrast02.wav");
			dialog.text = "看来我及时赶到了。 我无忧无虑的侄子和他的守护天使"+GetFullName(pchar)+"船长。 别这么惊讶, 法国人, 我知道你是谁。 ";
			link.l1 = "路易斯.奥尔蒂斯? ";
			link.l1.go = "uncle_1";
		break;
		
		case "uncle_1":
			dialog.text = "你说得对, 船长, 但你其他都错了。 你不应该干涉别人的家庭事务。 你甚至不知道你在保护谁。 我放荡的侄子多明戈是个一文不值的耙子, 每个酒馆和妓院的头号访客, 他欺骗或至少试图欺骗地平线线上的每个女孩。 我每月付他租金, 他几天就挥霍一空, 总是要求越来越多。 一次又一次。 他不断的无价值行为让他的母亲和我的妹妹发疯\n我听说谣言说这个淘气的男孩甚至雇佣并指挥一些英国私掠船攻击侯爵里卡多.阿尔瓦拉特的某艘船, 他们连同那位可敬的人和我亲爱的妹妹一起沉没了。 多明戈非常想要我们家族的钱, 他会为此杀人... 可悲的是, 我未能挖出足够的证据将这个恶棍送上绞刑架。 ";
			link.l1 = "";
			link.l1.go = "uncle_2";
		break;
		
		case "uncle_2":
			DialogExit();
			sld = CharacterFromID("FMQP_noble");
			sld.Dialog.currentnode = "noble_34";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "uncle_3":
			dialog.text = "典型。 大喊大叫, 刀剑和杯子的碰撞声, 充满了声音和愤怒, 却毫无意义。 他付了你多少钱, 船长, 让你保护他? ";
			link.l1 = "据我所知, 在你未能挖出任何反对你侄子的证据后, 你开始派刺客追杀他。 听起来简单的诉讼就足够了。 ";
			link.l1.go = "uncle_4";
		break;
		
		case "uncle_4":
			dialog.text = "你在说谎。 多明戈在这里树敌无数。 他留下了一串被抛弃的恋人和被戴绿帽的丈夫。 我奇怪他怎么能活这么久! 问问他, 他毁了多少婚礼? 他伤害或杀死了多少被侮辱的未婚夫? ";
			link.l1 = "他的仆人乌戈... ";
			link.l1.go = "uncle_5";
		break;
		
		case "uncle_5":
			dialog.text = "啊, 乌戈! 他们中最坏的流氓! 乌戈爱他那个耙子主人。 在他看来, 主人的所有罪行都只是孩子的恶作剧。 记住, 法国人, 家庭事务只属于家庭。 那些打探和窥探的人会发现自己陷入困境。 ";
			link.l1 = "现在你在威胁我。 ";
			link.l1.go = "uncle_6";
		break;
		
		case "uncle_6":
			int icpy = GetOfficersQuantity(pchar);
			iTotalTemp = 10000+10000*icpy;
			dialog.text = "不是威胁, 船长, 是承诺。 看这里, 孩子, 你走了很长的路, 但既然我把你当作被误导的受害者, 而不是敌人, 听听我简单而慷慨的提议: 走开。 我不想在这里流血。 我们不需要你的帮助来解决我们的家庭事务。 我甚至准备补偿你因为我白痴侄子而经历的麻烦 - "+FindRussianMoneyString(iTotalTemp)+" 八里亚尔。 拿着钱, 让我们相安无事。 拒绝我的提议, 我们会把你切成薄片送回你的船上。 ";
			link.l1 = "我总是说‘家庭第一’。 那与我无关, 把钱给我, ‘vaya con Dios.’";
			link.l1.go = "uncle_7";
			link.l2 = "你的故事比你种植园的肥料还臭。 唐.多明戈可能不是圣人, 但你先生是个魔鬼! ";
			link.l2.go = "uncle_8";
		break;
		
		case "uncle_7":
			AddMoneyToCharacter(pchar, iTotalTemp);
			dialog.text = "我就知道你是个通情达理的人。 拿着你的钱, 再见, 船长。 以后尽量不要翻别人的脏衣服 - 他们从不感激。 ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_UncleExit");
		break;
		
		case "uncle_8":
			dialog.text = "魔鬼? 好吧, 我会很高兴送你下地狱! ";
			link.l1 = "... ";
			link.l1.go = "exit";
			AddDialogExitQuest("FMQP_UncleFight");
		break;
		
		case "ugo":
			pchar.quest.FMQP_SantoDomingoOver.over = "yes";
			PlaySound("Voice\English\Serve_senior.wav");
			dialog.text = TimeGreeting()+" 先生。 我能为你做什么? ";
			link.l1 = "你好。 对不起, 这是唐.多明戈.阿尔瓦拉特的住所吗? ";
			link.l1.go = "ugo_1";
		break;
		
		case "ugo_1":
			dialog.text = "是的, 这是阿尔瓦拉特的家。 它很朴素但舒适。 我叫乌戈, 为年轻的主人服务。 你是来找他的吗? ";
			link.l1 = "是的, 先生。 唐.多明戈不久前邀请我来他这里。 他很有说服力。 我能见他吗? ";
			link.l1.go = "ugo_2";
		break;
		
		case "ugo_2":
			dialog.text = "唉, 我善良的骑士, 唐.多明戈现在不在家。 就我个人而言, 我也想知道在哪里能找到那个淘气的男孩... 呃, 请原谅, 年轻的先生。 我可以问一下你需要他做什么吗? ";
			link.l1 = "嗯... 我偶然帮助了唐.多明戈。 他在太子港的一家酒馆被两个恶棍袭击。 我帮助你的主人保护自己免受那些... 他怎么称呼他们... 该死的混蛋。 唐.多明戈邀请我在调查结束后到这里拜访他。 我认为现在一切都应该解决了, 所以我希望看到他在家。 ";
			link.l1.go = "ugo_3";
		break;
		
		case "ugo_3":
			dialog.text = "我的上帝! 你在这里讲的故事多么可怕! 我必须立即去见指挥官 - 警告他唐.多明戈现在面临的危险! 先生, 你必须走, 我应该快点! ";
			link.l1 = "放松点, 乌戈。 你年轻的主人很安全。 他提到他的文件没问题, 他们应该已经释放了他, 所以我来了。 我相信我们很快就会见到他。 ";
			link.l1.go = "ugo_4";
		break;
		
		case "ugo_4":
			dialog.text = "哦! 你怎么能这样? 我年轻的主人, 那个天真的男孩 - 在那些吃青蛙的法国人手里? 更不用说威胁他生命的 ladrones 了? 不, 我必须见指挥官! 先生, 请走吧! ";
			link.l1 = "好好好, 别这么固执。 我这就走。 ";
			link.l1.go = "ugo_exit";
			link.l2 = "先生, 为什么这么紧张? 我已经告诉你了, 你的主人没有危险。 让我留在这里等唐.多明戈先生到来, 我长途航行很累, 希望得到你的款待。 我想要一些清凉的淡水和热水澡来冲洗喉咙里的盐味。 然后你可以去当地驻军, 做你想做的事。 ";
			link.l2.go = "ugo_5";
		break;
		
		case "ugo_exit":
			DialogExit();
			LocatorReloadEnterDisable("Santodomingo_town", "houseSp4", true);
			DoQuestReloadToLocation("SantoDomingo_town", "reload", "houseSp4", "FMQP_SDMFail");
		break;
		
		case "ugo_5":
			dialog.text = "先生, 马上离开这所房子! ";
			link.l1 = "乌戈, 我真的怀疑一个仆人被允许以这种方式和一位绅士访客说话。 我也怀疑唐.多明戈会赞成这样对待一个救了他命的人! ";
			link.l1.go = "ugo_6";
		break;
		
		case "ugo_6":
			dialog.text = "哦, 真的吗? (朝楼上喊) 伙计们, 下来, 我们有麻烦了! ";
			link.l1 = "搞什么? ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQP_SantoDomingoFight");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}