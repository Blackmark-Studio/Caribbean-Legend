// Арчибальд Колхаун
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "您需要什么吗? ";
			link.l1 = "没有, 什么都没有。";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "portroyal":
			dialog.text = "哈哈, de Maure先生! 欢迎来到皇家港! 还记得我吗? ";
			link.l1 = "嗯……你是Calhoun先生吧? Henry Calhoun? ";
			link.l1.go = "portroyal_1";
		break;
		
		case "portroyal_1":
			dialog.text = "差点就……Archibald Calhoun。";
			link.l1 = "哦, 请原谅, 先生。是的, 我记得您。我们在Catoche角的海湾见过面。您的船长也在场, William Patterson。我认出了他的舰队。";
			link.l1.go = "portroyal_2";
		break;
		
		case "portroyal_2":
			dialog.text = "完全正确! 请原谅我们船长, 他对陌生人总是这么粗鲁。你干得漂亮, 把Diego de Montoya的要塞打得落花流水, 咱们正好也在那儿磨爪子……";
			link.l1 = "顺便一提, 这一切都是为了正义。要不是你们船长事先做了准备, 老实说, 老子在西班牙大炮的轰击下, 根本不可能冲上去捞到好处。你们指挥官找到他想要的东西了吗? ";
			link.l1.go = "portroyal_3";
		break;
		
		case "portroyal_3":
			dialog.text = "是的。他在堡垒下的炮室里钻得可深了, 还发现了什么档案库。高兴得不得了。对了, 恕我冒昧问一句, 你怎么突然跑去攻打丛林里的那个堡垒? ";
			link.l1 = "在圣皮埃尔被我打败后, Don Diego就开始耍花招, 最后竟然公然袭击了古巴。可他打到一半就溜了, 逃进了通往大陆的山里。哼, 我下定决心要一劳永逸地解决掉这个胆小鬼, 让他再也别来给法国人丢脸。";
			link.l1.go = "portroyal_4";
		break;
		
		case "portroyal_4":
			dialog.text = "是啊, 俺早就听说过Charles de Maure船长的传奇事迹, 今天算是亲眼见识了……";
			link.l1 = "是啊, 我也听说过William Paterson的英勇。你能有他这样的船长, 真是走运。";
			link.l1.go = "portroyal_5";
		break;
		
		case "portroyal_5":
			dialog.text = "俺运气不错, 确实如此。虽然他现在成了个大人物, 什么上流社会、会见、舞会、游行还有私人宴会……每次咱们到皇家港, 他都死赖在总督府里不肯出来。其实他现在又在那儿呢。\nCharles de Maure船长, 能不能帮俺这个苏格兰醉汉一个忙? 来陪俺聊聊天吧! 老是见到同样的脸, 俺都快腻歪了, 你看起来倒是个能说上话的人。去俺那儿坐坐, 放松一下, 咱们来一桶上好的威士忌。俺请客! ";
			link.l1 = "嗯……很诱人, 不过……";
			link.l1.go = "portroyal_6";
		break;
		
		case "portroyal_6":
			dialog.text = "哎呀, 别忙了, 船长, 您也得找时间休息啊。对了, 我还从本地商人的店里弄了点精致的小吃。我就在店铺楼上租了个房间。您要是想吃点东西或者喝一杯, 随时下楼就行, 哈哈! 多方便啊! 走吧, 咱们一起去! ";
			link.l1 = "你把我说服了! ";
			link.l1.go = "portroyal_7";
		break;
		
		case "portroyal_7":
			dialog.text = "太好了, 跟我来! ";
			link.l1 = "……";
			link.l1.go = "portroyal_8";
		break;
		
		case "portroyal_8":
			DialogExit();
			NextDiag.CurrentNode = "portroyal_9";
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload6_back", "PortRoyal_store", "goto", "goto2", "GuardOT_ArchyIntoStore", -1);
			LAi_ActorFollow(pchar, npchar, "", -1);
		break;
		
		case "portroyal_9":
			LAi_SetSitType(Pchar);
			dialog.text = "你看这地方多舒服? 又凉快……这儿还有几桶威士忌! 来, 船长, 干了! ";
			link.l1 = "那就为咱们这次幸运的相遇和愉快的结识干一杯吧! ";
			link.l1.go = "portroyal_10";
		break;
		
		case "portroyal_10":
			dialog.text = "太高兴了! ……啊! 您最近才到加勒比海, 对吧, de Maure先生? ";
			link.l1 = "比较近……也可能没那么近。我也说不清楚怎么表达。感觉自己半辈子都在这儿过了。";
			link.l1.go = "portroyal_11";
		break;
		
		case "portroyal_11":
			dialog.text = "唉, 这种感觉我懂得……其实我自己也在这儿待了很久。还记得当初我被William救下的那个倒霉岛上……哎哟, 老子那会儿真觉得半条命都丢在那儿了。";
			link.l1 = "有意思! 是哪座岛? ";
			link.l1.go = "portroyal_12";
		break;
		
		case "portroyal_12":
			dialog.text = "Willy是俺的老朋友, 咱俩早在俺还在苏格兰呼吸清新空气的时候就认识了……那会儿日子可真美好。俺当时傻乎乎地和那些该死的天主教徒还有宗教裁判官闹了矛盾, 结果他就派人来取俺性命。那时候俺还是个商人, 自己有艘长笛船。\n唉, 那倒霉的一天, 俺的船被西班牙人袭击了, 他们还打扮成了海盗。咱们拼死反抗, 可还是被他们像老鼠一样逼进了死角! 不过老Colhaun那会儿可没慌, 抱着一桶水和几块木板就跳海了。\n俺趁着夜色从船上游走, 士兵们根本没发现俺。活下来的几率其实很渺茫, 可留在船上连一点希望都没有。两天后, 俺被海浪冲到了某个荒岛的岸上。\n那时候俺在加勒比混了好一阵子, 可从来没听说过那地方! 那岛又小又没人住……俺在那里熬了两年, 简直像过了一个世纪。到现在俺都不明白自己怎么还能保持清醒。";
			link.l1 = "你在无人岛上住了两年? ";
			link.l1.go = "portroyal_13";
		break;
		
		case "portroyal_13":
			dialog.text = "当然去了, 那鬼地方! 幸好有淡水。老子靠螃蟹、藤壶、鱼和鸟活了下来。所以我给那地方取名叫螃蟹岛。老子手里啥武器都没有, 只能像野人一样学会了用鱼叉、长矛和箭! 嗬嗬! 喝啊喝, 船长! 老子也不介意润润嗓子……";
			link.l1 = "唉……我可不羡慕你。";
			link.l1.go = "portroyal_14";
		break;
		
		case "portroyal_14":
			dialog.text = "就是这样! 这正是俺第一次踏上那片大沙滩时说的话: “老Archy啊, 你这处境确实不怎么样, 但也还没到绝路! ”你知道是什么让俺活下来的, 船长? ";
			link.l1 = "有船从岛边经过? ";
			link.l1.go = "portroyal_15";
		break;
		
		case "portroyal_15":
			dialog.text = "不! 是劳动救了我! 劳动、信仰, 还有对活下去的渴望! 我把整座岛都翻了个遍, 连每个角落都没放过, 最后得到了一个箱子, 里面装满了木匠工具、写字用具, 还有些杂七杂八的小玩意儿。你知道那一刻我对自己说了什么吗? 再来点, 船长, 继续干下去! \n\n我对自己说: Archie, 你得干活, 才能让脑子清醒, 老天已经把一切都赐给你了。你看! 我就在海湾边上开始盖房子, 你知道吗? 这事救了我, 让我不再胡思乱想, 也给了我活下去的理由! ";
			link.l1 = "您真是个活生生的榜样, Calhoun先生。换作别人, 恐怕在那种情况下什么都做不了, 甚至连一点作为都难……";
			link.l1.go = "portroyal_16";
		break;
		
		case "portroyal_16":
			dialog.text = "没错, 老Calhaun生在苏格兰可不是没道理的! 对! 咱们可是山里的汉子——强壮、勇敢、硬气, 比那些沼泽地的软蛋强多了。再倒点……对了, 我刚才说到哪儿了? 对! 俺拼死拼活给自己盖了间像样的房子, 还开了本日记, 专门记俺倒霉的事。那会儿Willy救了俺, 俺就把日记带上了。\n现在每次咱们在皇家港落脚, 俺都把它放在这桌子上, 每晚躺在暖和柔软的床上重读一遍。\n俺把一切都写进去了, 俺到那儿前后的遭遇全都记得清清楚楚。这也是俺脑子还没糊涂的原因之一。";
			link.l1 = "所以原来是Paterson先生把你从岛上带走的? 可他怎么会找到那地方? 你刚才不是说……";
			link.l1.go = "portroyal_17";
		break;
		
		case "portroyal_17":
			dialog.text = "是啊是啊, 那岛在任何地图上都找不到。但Willy, 他可是老Willy! 他什么都能干! 他找到了那该死的岛, 还救了我一命, 这份恩情老子一辈子都记着。嗯……";
			link.l1 = "你喜欢为Paterson先生效力吗? 你想靠自己再闯一回吗? ";
			link.l1.go = "portroyal_18";
		break;
		
		case "portroyal_18":
			dialog.text = "老子不想再独来独往了。Willy年轻又有本事, 俺跟他也算是老朋友了, 还能缺啥? 不行, 俺这辈子都跟着Willy混, 除非哪天又喝多了被他踢出去, 哈哈! 说到喝酒, 赶紧倒上! ";
			link.l1 = "唉……喝酒Calhoun先生, 跟我说说吧。我听说你以前是个寻宝猎人, 这是真的吗, 还是胡扯? ";
			link.l1.go = "portroyal_19";
		break;
		
		case "portroyal_19":
			dialog.text = "谁告诉你的? 唉, 瞒也瞒不住。俺以前确实是那样的人。不过结果可不怎么样, 正是那该死的寻宝把俺引到了耶稣会和那个岛上。那些神父因为俺的缘故活活折磨死了一个人, 而俺自己……算了, 往事就让它过去吧。\n俺已经为自己的罪孽付出了足够的代价, 希望以后再也不会重蹈覆辙。不, Willy绝不会让那种事再发生, 俺敢肯定! ";
			link.l1 = "听着, Archibald。你听说过一个叫Miguel Dichoso的人吗? ";
			link.l1.go = "portroyal_20";
		break;
		
		case "portroyal_20":
			dialog.text = "我以前从没听过这个名字。他是谁? ";
			link.l1 = "哦, 没什么有趣的人……只是个喜欢冒险和寻宝的家伙而已。既然你没听说过他, 那咱们就不提他了。";
			link.l1.go = "portroyal_21";
		break;
		
		case "portroyal_21":
			dialog.text = "对, 对, 咱们别聊这个! 还是说说老欧洲吧! 我记得二十年前在苏格兰……";
			link.l1 = "……";
			link.l1.go = "portroyal_22";
		break;
		
		case "portroyal_22":
			DialogExit();
			AddDialogExitQuest("GuardOT_MCOutFromArchyRoom");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
