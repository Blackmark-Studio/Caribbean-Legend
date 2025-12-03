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
			dialog.text = "你想要什么?";
			link.l1 = "没什么。 ";
			link.l1.go = "exit";
		break;
		
		case "LEDR_Gonsalo_1":
			if (pchar.sex == "man")
			{
				dialog.text = "嘿, 小子! 你看起来像个勇敢的水手, 我敢打赌你打架也不差。 能不能帮俺去某地搞个小劫掠, 怎么样? ";
			}
			else
			{
				dialog.text = "嘿, 美人儿! 你既然敢来这儿, 肯定不是胆小的主。 要不要帮俺去哪里劫一票, 怎么样? ";
			}
			link.l1 = "我猜你就是那个在找人带路去古船的老头? ";
			link.l1.go = "LEDR_Gonsalo_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LEDR_Gonsalo_2":
			dialog.text = "呵呵……看来传闻比风还快。 没错, 就是我。 贡萨洛·佩拉尔塔—— '国王之剑' 号沉船中唯一幸存的人。 ";
			link.l1 = "而我是"+GetFullName(pchar)+"船长。 你想再看看你的船吗? ";
			link.l1.go = "LEDR_Gonsalo_3";
		break;

		case "LEDR_Gonsalo_3":
			dialog.text = "是的。 你知道吗, 最近我总是被同一个噩梦反复困扰。 但这还不是最糟的……信不信由你, 每天早上, 只要噩梦一结束, 我一醒来……就有一具该死的骷髅站在我面前……";
			link.l1 = "他们告诉我, 你把这个幻想讲给每个人听。 ";
			link.l1.go = "LEDR_Gonsalo_4";
		break;

		case "LEDR_Gonsalo_4":
			dialog.text = "幻想? 哼……要真是那样就好了。 几个月前, 我还像所有退休老水手一样, 过着安静的日子。 可现在, 那副骨架每天早上都会出现, 盯着我看, 发出令人毛骨悚然的尖叫……该死, 换了哪个大副都会吓得血都凉了……然后他就冲进战斗。 你知道吗? 每次他的攻击都比上次更凶狠。  这正是我想尽快回到船上的原因——我总觉得那里有我必须找到的东西。 ";
			link.l1 = "嗯……真是桩大买卖。 可这么久过去了, 你还指望在那里找到什么? ";
			link.l1.go = "LEDR_Gonsalo_5";
		break;
		
		case "LEDR_Gonsalo_5":
			dialog.text = "我不知道, 船长, 我真的不知道……可我就是被那艘船吸引, 就像一只老旧的船在风暴中漂泊。 我的梦、那具骷髅, 还有这种奇怪的感觉……大海在上, 它们之间肯定有某种联系。 我就是想不明白到底怎么回事。 ";
			link.l1 = "你的梦里到底发生了什么? 这和土著有什么关系吗? ";
			link.l1.go = "LEDR_Gonsalo_6";
			link.l2 = "所以, 你晚上会看到幻象, 早上还要和骷髅打架? 也许不是船的问题, 也许你该去看看医生。 我可不会纵容你这些天马行空的想象。 去找别的傻瓜相信你的鬼话吧。 ";
			link.l2.go = "LEDR_Gonsalo_6_end";
		break;
		
		case "LEDR_Gonsalo_6_end":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_End");
		break;
		
		case "LEDR_Gonsalo_6":
			dialog.text = "有联系? 你说对了, 见鬼……在那个梦里, 俺和死去的船员们一起待在 'La Espada del Rey' 号上。 咱们……正在伊斯帕尼奥拉岛上袭击加勒比土著村庄, 见人就杀——男人、女人、孩子都不放过。 不管是反抗的, 还是跪地求饶的, 全都杀掉。 咱们把他们的村子一个接一个烧成废墟。 印第安人的弓箭和棍棒对咱们来说, 就像破船对战舰一样不堪一击。 加勒比人绝望地求咱们谈判, 然后……";
			link.l1 = "天啊! 你竟然参与了那些无法无天的勾当? 你不是需要帮助, 你是该上绞刑架了! ";
			link.l1.go = "LEDR_Gonsalo_7";
		break;
		
		case "LEDR_Gonsalo_7":
			dialog.text = "不! 不, 该死, 那不是事实, 你明白吗? ! 我根本不知道为什么会梦到这些……但我以一切神圣之物发誓, 我和我的船员从未参与过这种暴行! ";
			link.l1 = "最好祈祷这是真的。 继续说。 ";
			link.l1.go = "LEDR_Gonsalo_8";
		break;

		case "LEDR_Gonsalo_8":
			dialog.text = "加勒比土著提出谈判请求, 船长同意了。 他邀请他们全部进入我们占领的一间小屋。 酋长们来了——至少有二十多个, 由他们的女王阿娜考娜带领。 但船长本人没有进去……我们谁也没进去。 等最后一个酋长进去后, 门被猛地关上, 用横梁顶住。 然后……该死……他们点火烧了屋子。 只有女王被留下, 但也没能活多久。 他们让她眼睁睁看着自己的族人被活活烧死……然后又把她吊死在树上。 ";
			link.l1 = "每晚都是这样吗? 同样的梦, 一遍又一遍地重复? 你知道吗, 说实话, 我一点也不会惊讶, 毕竟, 那个骷髅也许只是你发烧时幻想出来的……";
			link.l1.go = "LEDR_Gonsalo_9";
		break;

		case "LEDR_Gonsalo_9":
			dialog.text = "这还不是全部。 幸存的加勒比人逃到了古巴, 在当地部落中找到了支持, 很快就在某个酋长的带领下集结成了一支军队 阿图埃——我记得他好像叫这个名字。  他们把他当作最后的希望追随。 但我们几乎没费什么力气就把他们全都屠杀了。  阿图埃被俘, 准备处决。 当他们把他绑在十字架上, 准备点火烧死他时, 有个修士劝他皈依真信仰——说这样能减轻他的痛苦, 还能让他进入天堂。 阿图埃问修士, 天堂是不是也对西班牙人开放。 修士回答说, 当然, 只要是好西班牙人都能进天堂。 酋长毫不犹豫地说, 那他宁愿下地狱——只为不和这样残忍的人住在一起。 之后, 他又用自己的语言说了几句话, 柴堆就被点燃了。 火焰吞噬他的身体时, 他一声不吭。 海神在上, 我发誓, 现实中我可不想亲眼见到这种事。 我的梦总是这样结束: 船长坐着, 一动不动。 只有旁边的蜡烛冒着烟, 他不停翻着一本破旧的日记本。 慢慢地, 仿佛每个字都重如千金, 嘴里低声嘟囔着什么。 即使在梦里, "+GetSexPhrase("小子","姑娘")+", 我也明白——这是个信号。 是时候拔刀了, 因为他已经发动攻击。 \n帮我结束这个噩梦吧, 船长。 跟我一起去海湾。 我绝不会一个人去——我的火药快用完了。 但在你回答之前, 我得先提醒你: 我没钱付给你。 如果我能付钱, 早就有人排队帮忙了。 所以我只能指望同为水手的你能帮帮我。 ";
			link.l1 = "好吧, 行。 如果上船能帮你摆脱那些梦和幻象, 我就帮你。 上船吧。 我一办完自己的事, 我们就去海湾。 ";
			link.l1.go = "LEDR_Gonsalo_10";
		break;
		
		case "LEDR_Gonsalo_10":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_1");
			AddQuestRecord("LEDR", "2");
			AddQuestUserData("LEDR", "sSex", GetSexPhrase("ся","ась"));
		break;
		
		case "LEDR_Gonsalo_11":
			if (GetHour() >= 7 && GetHour() <= 19)
			{
				dialog.text = "就是它……曾经是西班牙商船队的骄傲, 如今却只剩下一堆勉强拼凑在一起的腐烂木板。 ";
				link.l1 = "很少见到这么庞然大物被放倒——就那样躺在岸上。 它怎么会到这儿来的? ";
				link.l1.go = "LEDR_Gonsalo_12";
				link.l2 = "那咱们就四处看看吧。 也许你真能在这儿找到点什么。 ";
				link.l2.go = "LEDR_Gonsalo_20_1";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "我不想显得忘恩负义或者胆小……但我现在在这里感觉不安全。 等天亮了我们再回来吧。 ";
				link.l1 = "好吧, 朋友, 既然你这么说。 ";
				link.l1.go = "exit";
				NextDiag.TempNode = "LEDR_Gonsalo_11";
			}
		break;
		
		case "LEDR_Gonsalo_12":
			dialog.text = "我们从圣地亚哥起航, 目的地是塞维利亚。 货物不多, 但有一位乘客——大人物, 还是位主教。 说实话, 船员们对这趟航行并不感冒……可谁又会来问我们的意见呢? \n我们根本没能驶入公海。 靠近特克斯群岛时, 一艘海盗双桅船袭击了我们——速度快, 机动灵活, 火力十足。 这可不是些破烂海盗, 而是真正的海狼。 起初, 船长想逃——他不想拿主教的命冒险。 但当时风向不利, 我们无法掉头, 南方又有风暴逼近。 别无选择——战斗就这样开始了。 ";
			link.l1 = "腹背受敌真是悲惨的命运。 然后发生了什么? ";
			link.l1.go = "LEDR_Gonsalo_13";
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;

		case "LEDR_Gonsalo_13":
			dialog.text = "战斗没持续多久。 我们成功打断了他们的前桅杆, 但那些海盗也不是吃素的——一发流弹把我们的舵绳打断了, 仿佛恶魔作祟, 船就这么僵在原地, 船头正对着迎面而来的风暴。 风暴逼近得极快, 那些海盗——愿链弹撕碎他们的主帆——选择了逃跑, 消失在土耳其人的某个海湾里。 我们只能等着风暴将我们吞没。 船长下令降帆、更换舵绳, 但一切都已经太迟了。 ";
			link.l1 = "所以, 风暴在特克斯群岛附近把你们卷住, 一路把你们拖到这里, 最后把你们扔上了岸? ";
			link.l1.go = "LEDR_Gonsalo_14";
		break;

		case "LEDR_Gonsalo_14":
			dialog.text = "事情就是这样发生的。 整艘船一片混乱。 狂风撕裂了索具, 桅杆一个接一个倒下, 砸碎甲板, 压死人。 来不及把自己绑牢的就被浪卷到海里; 绑住了的又被残骸压住。 甲板下也好不了多少——炮、箱子、炮弹像恶鬼一样来回乱飞, 碾碎一路上的所有东西。 最后我们被掀到岸上时, 我已经失去知觉。 我是在沙滩上醒过来的。 水手长塞尔吉奥找到我, 他身边还带着另外两个人。";
			link.l1 = "这么大的船, 收获却不多。";
			link.l1.go = "LEDR_Gonsalo_15";
		break;

		case "LEDR_Gonsalo_15":
			dialog.text = "唉, 船长……尸体太多了……我们立刻就明白: 不能再待在那里。 海浪随时可能把船和我们一起卷走。 附近我们发现了一个洞穴——在那里, 我们筋疲力尽, 一碰到地就睡着了。 等我醒来时, 洞里已经没有了塞尔吉奥和另外两个人的踪影。 \n我把整片海滩都找遍了, 可天打雷劈, 他们就是不见踪影。 我一个人也没法回到船上, 只好决定往内陆走。 就这样我才到了锐镇, 可惜我自己太蠢, 把事情搞砸了。 \n我想打听幸存者的消息, 于是逢人就讲我们遇到的事。 可那些家伙对我和船员根本不感兴趣——他们只惦记着能从船上抢到的财宝。 消息很快传遍了整个岛, 没多久, 那些贼人就成群结队地涌了过去。 ";
			link.l1 = "所以, 你还是不知道那些人发生了什么事? ";
			link.l1.go = "LEDR_Gonsalo_16";
		break;

		case "LEDR_Gonsalo_16":
			dialog.text = "回到船上实在太危险了。 任何胆敢潜进去捞宝的人, 都可能为了争夺战利品大打出手, 甚至一不小心就朝身边的人开枪……也可能根本不是意外。 老天, 我在酒馆里窝了一整周, 逢人就问有没有去过海湾的。 但没人听说过我的船员, 或者他们的下落。 最后, 我只能接受这个事实: 看来那该死的风暴里, 只有我一个人活了下来。 也许命运就是更偏爱我一点。 又或者……全都是托了那位年轻的Eugenio de la Torre船长曾送我的护身符。 我一直把它带在身边。 见鬼, 它还真给我带来了好运。 ";
			link.l1 = "那他现在在哪儿? 看来这东西也保护不了他不被骷髅袭击, 是吧……";
			link.l1.go = "LEDR_Gonsalo_17";
		break;

		case "LEDR_Gonsalo_17":
			dialog.text = "在我家院子修井口时, 它被从我脖子上扯了下来。 一根木头撞到我的脖子, 护身符掉进了水里。 井早就蓄满了水, 没人会为了区区一个小饰物去捞它。 ";
			link.l1 = "从那一刻起, 你就开始做噩梦了吗? ";
			link.l1.go = "LEDR_Gonsalo_18";
		break;

		case "LEDR_Gonsalo_18":
			dialog.text = "见鬼! 俺还真没想过, 但事实就是这样! 井一建好, 噩梦就开始了。 ";
			link.l1 = "真巧啊。 好了, 你现在如愿以偿地来了。 接下来打算怎么办? ";
			link.l1.go = "LEDR_Gonsalo_19";
		break;

		case "LEDR_Gonsalo_19":
			dialog.text = "我不知道, 船长……我真的不知道。 咱们先四处看看吧——我总觉得这里有东西等着我找, 这种感觉越来越强烈了。 ";
			link.l1 = "好吧。 希望我们这趟不是白来的。 ";
			link.l1.go = "LEDR_Gonsalo_20";
		break;
		
		case "LEDR_Gonsalo_20":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_3");
		break;
		
		case "LEDR_Gonsalo_20_1":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_3");
			pchar.questTemp.LEDR_NoStory = true;
		break;
		
		case "LEDR_Gonsalo_21":
			dialog.text = "听着……这种感觉越来越强烈了。 就像我离必须找到的东西只差一步。 我得上那艘船。 我以大海发誓, 船上一定有什么能解释那该死的骷髅为什么一直缠着我。 ";
			link.l1 = "所以, 也许你这么急着来这里不是没原因的? 你是不是在船上藏了什么贵重东西, 现在回来找你的宝藏了? ";
			link.l1.go = "LEDR_Gonsalo_22";
		break;

		case "LEDR_Gonsalo_22":
			dialog.text = "你在胡说什么? 你真以为老子在这四十年后会为了几枚达布隆金币, 千里迢迢穿越整个群岛? 要是你哪怕只见过那具骷髅一次, 这种念头绝不会出现在你脑海里。 ";
			link.l1 = "好啦, 好啦, 冷静点。 那么你到底打算怎么上船? ";
			link.l1.go = "LEDR_Gonsalo_23";
		break;

		case "LEDR_Gonsalo_23":
			dialog.text = "船尾有个暗门。 那是船长亲自凿出来的——以防被人登船时我们落了下风。 天打雷劈, 俺这把老骨头可没法自己钻过去, 但要是咱俩一起……";
			link.l1 = "好吧, 带路吧, 咱们赶紧把这事解决了。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_5");
		break;
		
		case "LEDR_Gonsalo_24":
			DelLandQuestMark(npchar);
			dialog.text = "老天爷, 真是场恶战! 运气好, 这些家伙没早上来找我的那个骷髅凶。怎么样, 现在你信我了吧? ";
			link.l1 = "看了这一幕, 不信都难。你怎么样? 还活着? ";
			link.l1.go = "LEDR_Gonsalo_24_1";
		break;
		
		case "LEDR_Gonsalo_24_1":
			dialog.text = "应该还行。 该死的不死怪……老子的腿像被砍断的桅杆一样软了。";
			link.l1 = "既然没事, 就别坐着了。来, 把手给我, 我拉你起来。";
			link.l1.go = "LEDR_Gonsalo_24_2";
		break;
		
		case "LEDR_Gonsalo_24_2":
			CharacterTurnByChr(npchar, CharacterFromID("blaze"));
			dialog.text = "...";
			link.l1 = "这样好多了。看来, 之前也有人知道怎么进来这里。";
			link.l1.go = "LEDR_Gonsalo_25";
			LAi_Fade("LEDR_GonsaloStay", "");
		break;

		case "LEDR_Gonsalo_25":
			dialog.text = "看起来这些是我的手下。 那些在风暴中活下来的……我认出了塞尔吉奥的背心——或者说剩下的那点布料。 不管怎样, 他们回来了——要么是来找幸存者, 要么是来埋葬死者。 但看来同样的邪恶也把他们给害了。 ";
			link.l1 = "奇怪, 怎么只剩下背心的碎片了。 其他什么都没有。 ";
			link.l1.go = "LEDR_Gonsalo_26";
		break;

		case "LEDR_Gonsalo_26":
			if(CheckAttribute(pchar, "questTemp.LEDR_NoStory"))
			{
			dialog.text = "就连我们那位乘客——主教的法衣都没留下半点痕迹。 看那边, 手里紧紧攥着钥匙的倒霉鬼, 八成就是他。 他从没把这钥匙放下过。 看来, 他的运气跟别人也没好到哪去。 老子敢拿大海发誓——这些不死怪绝不是无缘无故出现在这里的。 一定有什么东西把它们困在此地, 或者它们在守着什么。";
			DeleteAttribute(pchar, "LEDR_NoStory");
			}
			else
			{
			dialog.text = "就连主教的法衣也没留下半点痕迹。 看那边, 手里紧紧攥着钥匙的倒霉鬼, 八成就是他。 他从没把这钥匙放下过。 看来, 他的运气跟别人也没好到哪去。 老子敢拿大海发誓——这些不死怪绝不是无缘无故出现在这里的。 一定有什么东西把它们困在此地, 或者它们在守着什么。";
			}
			link.l1 = "现在我也觉得, 我们得在这里找到点什么。 快点解决掉吧——老子可不想在这鬼地方多待一会儿。";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_8");
		break;
		
		case "LEDR_Gonsalo_27":
			dialog.text = "那么, 船长, 你找到什么了吗? ";
			link.l1 = "看起来这是主教的箱子。 我发"+GetSexPhrase("现了","现了")+"里面有东西。 来看看吧。 ";
			link.l1.go = "LEDR_Gonsalo_28";
		break;

		case "LEDR_Gonsalo_28":
			dialog.text = "Velasquez……老天劈我吧……我在梦里见过这本日志! 这正是船长在他……之前翻看的那本! ";
			link.l1 = "...";
			link.l1.go = "LEDR_Gonsalo_29";
		break;

		case "LEDR_Gonsalo_29":
			dialog.text = "见鬼, 感觉他要把我的手都烫着了! ";
			link.l1 = "烫手吗? 哎呀, 别闹了, 这只是本旧日记本。 还是说你真觉得里面有什么黑暗力量? ";
			link.l1.go = "LEDR_Gonsalo_30";
		break;

		case "LEDR_Gonsalo_30":
			dialog.text = "我以所有圣徒发誓, 俺可没开玩笑! 那该死的日记本拿在手里就像在烧一样。 它必须被毁掉! 撕了、烧了、扔水里——怎么都行! 不, 等等……还是烧了好。 对, 烧了, 连灰都不剩! ";
			link.l1 = "如你所愿。 那我们就上岸, 点起篝火, 把这本罪恶编年史扔进火里烧掉。 ";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_10");
		break;
		
		case "LEDR_Gonsalo_31":
			dialog.text = "好了, 就这样吧……感觉心头的大石终于落地了。 ";
			link.l1 = "你觉得现在一切都结束了吗? ";
			link.l1.go = "LEDR_Gonsalo_32";
			TakeItemFromCharacter(pchar, "LEDR_book");
			CharacterTurnToLoc(npchar, "goto", "fire");
			CharacterTurnToLoc(pchar, "goto", "fire");
		break;

		case "LEDR_Gonsalo_32":
			dialog.text = "谁知道呢……但我以大海发誓, 我已经很久没有这么轻松过了。 就像一笔旧账终于被赦免了一样。 不过……我真希望自己从未见过那本该死的日记, 也没知道里面写了什么。 ";
			link.l1 = "难怪你会做那样的梦。 即使你没有参与这一切, 你也是唯一与那本日记有任何关联的在世之人。 ";
			link.l1.go = "LEDR_Gonsalo_33";
		break;
		
		case "LEDR_Gonsalo_33":
			dialog.text = "无论是黄金还是信仰, 都无法为人们在维拉斯凯兹指挥下所做的事情辩解。 我很庆幸所有能让我们想起那段往事的东西都已经被烧毁了。 这种东西绝不能落入那些可能会效仿他们的人手中。 ";
			link.l1 = "Velasquez只是众多中的一个。 谁知道在古老的欧洲还有多少这样日记在流传, 助长着新征服者的贪婪和无法无天? 有一点可以肯定——这本日记再也毒害不了其他人了。 对了, 主教的箱子里不仅有日记, 还有一大笔金币——总共三百枚。 其中一半理应归你所有。 ";
			link.l1.go = "LEDR_Gonsalo_34_share";
			link.l2 = "Velasquez已经为他的罪行付出了代价, 如果还有人想步他的后尘, 也会落得同样的下场。 迟早, 命运会让每个人得到应有的报应。 ";
			link.l2.go = "LEDR_Gonsalo_34_silence";
		break;
		
		case "LEDR_Gonsalo_34_share":
			dialog.text = "如果是这样——我当然不会拒绝。 人人都需要钱, 而我现在比任何时候都更需要。 没人会再雇我当水手了——我年纪太大了。 所以谢谢你, 船长, 没有像其他人那样把我赶走"+GetSexPhrase(", 小子",", 姑娘")+"。 ";
			link.l1 = "我得承认, 一开始你的故事听起来就像疯子的胡言乱语。 但你讲得太有说服力了, 不管你愿不愿意, 都会不由自主地开始相信。 不过, 那些不死土著的出现还是让我措手不及。 ";
			link.l1.go = "LEDR_Gonsalo_35_1";
			link.l2 = "我只是想看看你是不是疯了。 你知道, 这种故事可不是那么容易让人相信的。 ";
			link.l2.go = "LEDR_Gonsalo_35_2";
			RemoveDublonsFromPCharTotal(150);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.quest.LEDR_share = true;
		break;
		
		case "LEDR_Gonsalo_34_silence":
			dialog.text = "我也想相信……可在大海上, 俺见过太多被命运眷顾的家伙, 不管他们做了多黑的事。 也许他们的报应终会到来——只是不是在这儿, 而是在恶魔的地狱锅里。 还有, 谢谢你, 船长。 谢谢你没有袖手旁观, 谢谢你愿意倾听, 谢谢你送我一程。 你知道, 这对我意义重大。 ";
			link.l1 = "我得承认, 一开始你的故事听起来就像疯子的胡言乱语。 但你讲得太有说服力了, 不管你愿不愿意, 都会忍不住开始相信。 只是, 那些不死印第安人的出现还是让我措手不及。 ";
			link.l1.go = "LEDR_Gonsalo_35_1";
			link.l2 = "我只是想看看你是不是疯了。 你知道, 这种故事可不容易让人相信。 ";
			link.l2.go = "LEDR_Gonsalo_35_2";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;

		case "LEDR_Gonsalo_35_1":
			dialog.text = "现在你明白我第一次见到那些不死生物时的感受了吧。 我希望它们已经彻底消失了……否则, 我可不觉得自己还能再熬过那样的遭遇。 ";
			link.l1 = "好了, 既然这里的事都办完了, 是时候离开这个地方了。 上船吧, 我会把你送到Sharptown港口。 ";
			link.l1.go = "LEDR_Gonsalo_36";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "LEDR_Gonsalo_35_2":
			dialog.text = "现在你明白我第一次见到那些亡灵时的感受了吧。 我希望它们已经彻底消失了……否则, 我可不觉得自己还能再活着遇到那种事。 ";
			link.l1 = "好了, 既然这里的事办完了, 是时候离开这个地方了。 上船吧, 我会把你送到Sharptown港口。 ";
			link.l1.go = "LEDR_Gonsalo_36";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "LEDR_Gonsalo_36":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_12");
		break;
		
		case "LEDR_Gonsalo_37":
			dialog.text = "再次感谢您, "+GetFullName(pchar)+"船长。 海神在上, 那股怪异的感觉消失了, 希望它把那该死的一袋骨头也带走了。 要不要来喝一杯, 嗯? ";
			link.l1 = "谢谢你的邀请, Gonzalo, 不过我现在实在脱不开身。 也许下次吧。 替咱俩喝一杯。 ";
			link.l1.go = "LEDR_Gonsalo_38";
		break;
		
		case "LEDR_Gonsalo_38":
			if (CheckAttribute(npchar, "quest.LEDR_share"))
			{
				dialog.text = "我明白。 不过让我跟你说一句, 船长: 咱们一起经历了这么多, 我不能什么都不说就离开你, 这可不合适。 来, 拿着这个。 年轻时, 俺追宝可不止一次, 俺以大海发誓。 但如今身子骨不行了, 老腰也不听使唤。 可你——你还年轻, 是个老练的水手。 你一定能轻松找到它。 祝你好运, "+GetFullName(pchar)+", 一帆风顺, 龙骨下常有七尺水。 ";
				link.l1 = "谢谢你, Gonzalo。 也祝你好运, 告别了。 ";
				AddMapPart();
			}
			else
			{
				dialog.text = "那么, 是时候说再见了。 祝你一路顺风, "+GetFullName(pchar)+"船长! ";
				link.l1 = "再见, Gonzalo。 ";
			}
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_14");
		break;
		
		
		
	}
}